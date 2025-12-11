+++
title = "Parallelization Deep Dive"
description = "How optimization solvers exploit multiple cores and distributed systems"
template = "learning-path.html"
weight = 6

[extra]
tagline = "From pivot-level parallelism to distributed branch-and-bound"
duration = "~4 hours"
prereqs = "LP Fundamentals, Branch and Bound basics"
steps = [
    { id = "why-parallel", title = "Why Parallelization is Hard", duration = "20 min" },
    { id = "simplex-parallel", title = "Parallel Simplex Strategies", duration = "35 min" },
    { id = "tree-parallel", title = "Parallel Branch-and-Bound", duration = "40 min" },
    { id = "decomposition", title = "Decomposition Methods", duration = "45 min" },
    { id = "bcp-architecture", title = "BCP: A Parallel Framework", duration = "35 min" },
    { id = "patterns", title = "Parallel-Safe Patterns", duration = "25 min" },
    { id = "practice", title = "Choosing Your Strategy", duration = "20 min" },
]
+++

<div class="key-insight">

Optimization is hard to parallelize. Unlike embarrassingly parallel workloads (rendering, data processing), optimization algorithms have deep dependencies between iterations. This path explores the clever techniques COIN-OR uses to extract parallelism despite these challenges — from batching simplex pivots to distributed tree search.

</div>

## Why This Path?

Modern hardware has many cores, but optimization algorithms often struggle to use them all:

- **Simplex pivots are inherently sequential** — each pivot depends on the previous
- **Branch-and-bound has pruning dependencies** — bounds from one node affect others
- **Memory bandwidth often bottlenecks** before CPU does

Understanding these challenges helps you:

- **Choose the right solver configuration** — sometimes serial is faster!
- **Design parallelizable formulations** — decomposition changes everything
- **Recognize when parallel helps** — large problems benefit most
- **Debug performance issues** — contention vs. coordination overhead

---

<h2 id="why-parallel">1. Why Parallelization is Hard</h2>

### The Sequential Core of Simplex

Each simplex iteration depends on the previous:

```
Iteration k:
  1. Compute reduced costs using current basis B_k
  2. Select entering variable based on reduced costs
  3. Compute pivot column: B_k^{-1} * a_j
  4. Ratio test to find leaving variable
  5. Update basis: B_{k+1} = B_k with one column swapped

→ B_{k+1} depends on B_k — fundamentally sequential!
```

### The Pruning Problem in B&B

Branch-and-bound's power comes from **bounding**:

```
Node A (LP bound = 15):
  ├── Node B (LP bound = 12) ← Can prune if incumbent > 12
  └── Node C (LP bound = 18)
        ├── Node D
        └── Node E (finds integer solution, value = 14)
              → Updates incumbent to 14
              → Now Node B can be pruned!
```

In parallel: If Node B and Node E process simultaneously, we might waste work on B before learning about the incumbent from E.

### Amdahl's Law Reality

If 10% of your algorithm is inherently sequential:
- 2 cores → 1.82x speedup (not 2x)
- 8 cores → 4.7x speedup (not 8x)
- 64 cores → 9.5x speedup (not 64x)

<div class="key-insight">

**The COIN-OR approach:** Rather than forcing parallelism where it doesn't fit, COIN-OR provides multiple strategies: from batched pivots (PAMI) to distributed tree search (BCP). Choose based on your problem structure.

</div>

---

<h2 id="simplex-parallel">2. Parallel Simplex Strategies</h2>

HiGHS implements three strategies for dual simplex, each with different parallelization approaches.

### Plain: Serial Dual Simplex

The baseline — one pivot at a time:

```cpp
// kSimplexStrategyDualPlain
while (!optimal) {
    chooseRow();      // Select leaving variable (CHUZR)
    btran();          // Compute pivot row (BTRAN)
    price();          // Find entering variable (PRICE)
    chooseColumn();   // Ratio test (CHUZC)
    updateBasis();    // Pivot
}
```

Best for: Small problems, sparse updates, warm-started resolves.

### SIP: Suboptimization with Independent Parallelism

Task-based parallelism with independent subproblems:

```
Main thread:
  - Manages overall optimization
  - Coordinates task scheduling

Worker threads:
  - Handle independent pricing operations
  - Process FTRAN/BTRAN on separate columns
```

Best for: Problems where pricing dominates (many variables).

### PAMI: Parallel Minor Iterations

The most sophisticated approach — **batch multiple pivots**:

<div class="step-by-step">

<div class="step">
<h5>PAMI Algorithm (iterateMulti)</h5>

**Major iteration (parallel):**
1. `majorChooseRow`: Select k candidate leaving rows in parallel
2. `majorChooseRowBtran`: Parallel BTRAN for all k row vectors

**Minor iterations (sequential within batch):**
3. For i = 1 to k:
   - `minorChooseRow`: Pick best from remaining candidates
   - `chooseColumnSlice`: Parallel PRICE across matrix slices
   - `minorUpdate`: Update data structures locally

**Major update (parallel):**
4. `majorUpdate`: Apply all k updates to LU factors at once

</div>

</div>

The key insight: **defer factor updates** until a batch completes.

$$\text{Complexity: } O\left(\frac{k \times nnz}{p} + k^2 \times m\right) \text{ for } k \text{ pivots on } p \text{ processors}$$

<div class="code-connection">

**In the codebase:**
- [HEkkDual](@/libraries/highs/HEkkDual.md) implements all three strategies
- `chooseSimplexStrategyThreads()` selects based on problem characteristics
- `slice_*` data structures partition the matrix for parallel PRICE
- See [PAMI algorithm](@/algorithms/pami-parallel-minor-iterations-iteratemulti.md) for details

</div>

### When Does Parallel Simplex Help?

| Scenario | Best Strategy | Why |
|----------|---------------|-----|
| Small LP (< 1000 rows) | Plain | Overhead exceeds benefit |
| Dense LP | PAMI | Batch updates amortize matrix ops |
| Sparse LP | Plain/SIP | Hyper-sparse FTRAN is hard to parallelize |
| Re-optimization | Plain | Warm start minimizes iterations |
| Cold start, large | PAMI | Many iterations benefit from batching |

---

<h2 id="tree-parallel">3. Parallel Branch-and-Bound</h2>

Tree search offers more natural parallelism than simplex — different nodes can process simultaneously.

### The Challenge: Bound Synchronization

```
Serial B&B:                    Parallel B&B:

Node 1 → bound 20              Node 1 ──┐
Node 2 → bound 18              Node 2 ──┼──► Process simultaneously
Node 3 → INTEGER, obj=15       Node 3 ──┘
  → Update incumbent                ↓
Node 4 → bound 17 > 15         Incumbent update delayed!
  → PRUNE                      Node 4 might process before
                               learning about incumbent 15
```

**Parallel B&B may explore more nodes** than serial, but wall-clock time still decreases if parallelism is high enough.

### Work Distribution Strategies

**1. Master-Worker (BCP style)**

```
┌─────────────────────────────────────────┐
│           Tree Manager (TM)             │
│  - Global bound tracking                │
│  - Node distribution                    │
│  - Solution collection                  │
└───────────┬─────────────────────────────┘
            │ assigns nodes
    ┌───────┴───────┬───────────────┐
    ▼               ▼               ▼
┌───────┐       ┌───────┐       ┌───────┐
│ LP 0  │       │ LP 1  │       │ LP n  │
│Worker │       │Worker │       │Worker │
└───────┘       └───────┘       └───────┘
```

- TM makes global decisions, workers solve relaxations
- Good for heterogeneous nodes (some harder than others)
- Communication overhead: node descriptions, solutions, bounds

**2. Work Stealing**

Each worker maintains local queue, steals from others when idle:

```
Worker 0: [N1, N2, N3]  →  Process N1
Worker 1: [N4]          →  Process N4
Worker 2: []            →  Steal from Worker 0
                            Gets N3
```

- Better load balancing
- Less central coordination
- Complex implementation for B&B (bound updates need care)

**3. Domain Decomposition**

Partition variable space, each worker owns a subtree:

```
x_1 ≤ 5:  Worker 0 handles all descendants
x_1 ≥ 6:  Worker 1 handles all descendants
```

- Minimal communication
- Risk of imbalanced work
- Good when partitions have similar difficulty

<div class="code-connection">

**In COIN-OR:**
- [BCP](@/libraries/bcp/_index.md) uses master-worker architecture
- [SYMPHONY](@/libraries/symphony/_index.md) supports shared-memory and distributed modes
- [Alps](@/libraries/chipps-alps/_index.md) (CHiPPS) provides abstract parallel search framework
- Cbc has shared-memory parallelism via `CbcModel::setNumberThreads()`

</div>

---

<h2 id="decomposition">4. Decomposition Methods</h2>

The most powerful parallelization often comes from **problem structure**, not algorithm tricks.

### Dantzig-Wolfe Decomposition

Transform problems with special structure into master + subproblems:

**Original:**
$$\min c'x$$
$$Ax = b \quad \text{(coupling constraints)}$$
$$D^k x^k = d^k \quad \text{(block } k \text{)}$$

**Decomposed:**

```
Master Problem:                 Pricing Subproblems (parallel):

min Σ_k Σ_j c_j^k λ_j^k        For each k:
                                 Solve: min (c^k - π' A^k) x^k
Σ_k Σ_j A^k p_j^k λ_j^k = b           s.t. D^k x^k = d^k

Σ_j λ_j^k = 1  ∀k              If reduced cost < 0:
                                 Add column to master
λ_j^k ≥ 0
```

<div class="key-insight">

**Why decomposition enables parallelism:**
- Subproblems are **independent** given master duals
- Each can run on a different processor
- Master coordinates, subproblems do heavy lifting
- Communication: dual values down, columns up

</div>

### Column Generation Loop

```python
while not converged:
    # 1. Solve restricted master (sequential)
    master_solution = solve_master_lp()
    duals = master_solution.dual_values

    # 2. Pricing subproblems (PARALLEL)
    new_columns = []
    parallel_for k in subproblems:
        reduced_cost, column = solve_subproblem(k, duals)
        if reduced_cost < -tolerance:
            new_columns.append(column)

    # 3. Update master with new columns
    if new_columns.empty():
        converged = True
    else:
        add_columns_to_master(new_columns)
```

### Examples in COIN-OR

**Cutting Stock ([CSP](@/libraries/bcp/CSP.md)):**
- Master: Select patterns to cover demand
- Subproblem: Knapsack to find profitable patterns
- One subproblem → serial pricing (but fast)

**Multi-Commodity Flow ([MCF](@/libraries/bcp/MCF.md)):**
- Master: Bundle constraints (arc capacities)
- Subproblems: Shortest path per commodity
- K subproblems → parallel pricing

**Vehicle Routing:**
- Master: Cover all customers
- Subproblems: Shortest path with resource constraints
- Often hundreds of subproblems → high parallelism

<div class="code-connection">

**In the codebase:**
- [DecompAlgo](@/libraries/dip/DecompAlgo.md) in Dip orchestrates decomposition
- `DecompAlgoPC`: Price-and-Cut (Dantzig-Wolfe + cuts)
- `DecompAlgoRC`: Relax-and-Cut (Lagrangian)
- See [Price-and-Cut Hybrid](@/algorithms/price-and-cut-hybrid-generatevars-generatecuts.md) for the algorithm loop

</div>

---

<h2 id="bcp-architecture">5. BCP: A Parallel Framework</h2>

BCP (Branch-Cut-Price) is COIN-OR's comprehensive parallel framework for decomposition-based optimization.

### Architecture

```
┌──────────────────────────────────────────────────────────────┐
│                     Tree Manager (TM)                        │
│  • Manages search tree and node selection                    │
│  • Tracks global upper/lower bounds                          │
│  • Schedules work to LP processes                            │
│  • Stores variables/cuts locally and distributed             │
└──────────────────────┬───────────────────────────────────────┘
                       │ assigns nodes
         ┌─────────────┼─────────────┐
         ▼             ▼             ▼
┌─────────────┐ ┌─────────────┐ ┌─────────────┐
│   LP (0)    │ │   LP (1)    │ │   LP (n)    │
│             │ │             │ │             │
│ Solves LP   │ │ Solves LP   │ │ Solves LP   │
│ relaxation  │ │ relaxation  │ │ relaxation  │
└──────┬──────┘ └──────┬──────┘ └──────┬──────┘
       │               │               │
       ▼               ▼               ▼
┌─────────────┐ ┌─────────────┐ ┌─────────────┐
│     CG      │ │     CG      │ │     VG      │
│  Cut Gen    │ │  Cut Gen    │ │  Var Gen    │
└─────────────┘ └─────────────┘ └─────────────┘
```

### Process Roles

| Process | Responsibility | Parallelism |
|---------|----------------|-------------|
| **TM** | Coordinate tree, track bounds | Single coordinator |
| **LP** | Solve node relaxations | Multiple workers |
| **CG** | Generate cutting planes | Can be co-located with LP |
| **VG** | Generate variables (columns) | Can be co-located with LP |

### Communication Optimization: Delta Encoding

Instead of sending full node descriptions:

```cpp
// Naive: Send everything
struct NodeDescription {
    vector<double> all_var_bounds;    // Huge!
    vector<Cut> all_cuts;             // Huge!
    WarmStartBasis full_basis;
};

// BCP: Send only changes
struct BCP_node_change {
    vector<bound_change> var_changes; // Small
    vector<int> new_cut_indices;      // Small
    BCP_warmstart_basis basis_delta;
};
```

<div class="code-connection">

**Key BCP classes:**
- `BCP_tm_prob`: Tree Manager state
- `BCP_lp_prob`: LP worker state
- `BCP_obj_change`: Variable/cut deltas
- `BCP_user_data`: Parallel-safe user state
- See [BCP overview](@/libraries/bcp/_index.md)

</div>

---

<h2 id="patterns">6. Parallel-Safe Patterns</h2>

The MCF (Multi-Commodity Flow) examples demonstrate three patterns for handling state in parallel B&B.

### Pattern 1: Global State (MCF-1)

```cpp
class MCF1_lp : public BCP_lp_user {
    // DANGER: Shared mutable state
    std::vector<branch_decision> branch_history;  // Global!

    void initialize_new_search_tree_node(...) {
        // Reconstruct from global history
        for (auto& d : branch_history) {
            apply_bound_change(d);
        }
    }
};
```

**Problem:** In parallel, multiple LPs modify `branch_history` simultaneously → race conditions.

**Use only for:** Sequential execution, prototyping.

### Pattern 2: Delta Encoding (MCF-2)

```cpp
// Parent transmits changes via BCP_obj_change
void create_children(...) {
    // Child receives: parent_state + delta
    // BCP handles encoding/decoding
}
```

**Better:** Reduces data size, cleaner API.

**Still needs care:** LP must reconstruct full state from deltas.

### Pattern 3: User Data (MCF-3) — Recommended

```cpp
class MCF3_user : public BCP_user_data {
    std::vector<branch_decision> branch_history;  // Per-node!

    void pack(BCP_buffer& buf) const {
        buf.pack(branch_history.size());
        for (auto& d : branch_history) {
            buf.pack(d.arc).pack(d.lb).pack(d.ub);
        }
    }

    void unpack(BCP_buffer& buf) {
        // Reconstruct from buffer
    }
};

class MCF3_lp : public BCP_lp_user {
    void set_user_data_for_children(BCP_presolved_lp_brobj* best, int sel) {
        for (int i = 0; i < best->child_num; ++i) {
            auto* child = new MCF3_user(*current_user_data);
            child->add_decision(new_decisions[i]);
            best->user_data[i] = child;
        }
    }
};
```

<div class="key-insight">

**Why MCF-3 is parallel-safe:**
- Each node carries its own complete state
- No shared mutable data between LP workers
- `BCP_user_data` serializes for distribution
- Slightly more memory, but no race conditions

</div>

<div class="code-connection">

**In the codebase:**
- [MCF examples](@/libraries/bcp/MCF.md) show all three patterns
- `BCP_user_data::pack()`/`unpack()` for serialization
- `set_user_data_for_children()` for state propagation

</div>

---

<h2 id="practice">7. Choosing Your Strategy</h2>

### Decision Tree

```
Is your problem structure decomposable?
│
├─ YES → Use decomposition (BCP, Dip)
│        │
│        ├─ Many independent subproblems → High parallelism
│        └─ Few subproblems → Moderate parallelism
│
└─ NO → Standard MIP approach
        │
        ├─ Large tree expected?
        │  ├─ YES → Parallel B&B (Cbc threads, SYMPHONY)
        │  └─ NO  → Serial often faster
        │
        └─ LP dominant?
           ├─ YES → Consider PAMI (large, dense)
           └─ NO  → Plain simplex
```

### Rules of Thumb

| Scenario | Recommendation |
|----------|----------------|
| LP < 10K rows, sparse | Serial simplex (Plain) |
| LP > 100K rows, dense | PAMI with 4-8 threads |
| MIP with easy LP relaxations | Parallel B&B (tree parallelism) |
| MIP with hard LP relaxations | Serial (LP dominates) |
| Block-diagonal structure | Dantzig-Wolfe (subproblem parallelism) |
| Cutting stock, VRP, scheduling | BCP with column generation |
| Need reproducibility | Serial (parallel is non-deterministic) |

### Communication vs. Computation

```
Speedup = Work / (Work/P + Communication + Synchronization)

Where:
- P = number of processors
- Communication = data transfer overhead
- Synchronization = waiting for bounds, etc.
```

As P increases, communication/synchronization eventually dominate.

**Typical sweet spots:**
- Shared memory B&B: 4-16 threads
- Distributed B&B: 10-100 nodes for large problems
- Decomposition: depends on subproblem count

---

## What's Next?

You now understand COIN-OR's parallel optimization strategies! Next steps:

- **[Interactive Parallel Example](@/learning-paths/parallelization-example.md)** — Visualize parallel B&B tree exploration
- **[BCP Documentation](@/libraries/bcp/_index.md)** — Build your own parallel solver
- **[HiGHS Parallelization](@/libraries/highs/HEkkDual.md)** — Configure simplex parallelism
- **[Decomposition with Dip](@/libraries/dip/_index.md)** — Dantzig-Wolfe and Lagrangian methods

<div class="key-insight">

**You've learned:**
- Why optimization is fundamentally hard to parallelize (sequential dependencies)
- Three simplex strategies: Plain, SIP, PAMI
- Parallel B&B challenges: bound synchronization, work distribution
- Decomposition as the key to high parallelism
- BCP's master-worker architecture and delta encoding
- Parallel-safe patterns: global → delta → user_data
- How to choose the right strategy for your problem

The best parallelization often comes from **reformulating your problem** to expose structure, not from throwing more cores at a monolithic formulation.

</div>

