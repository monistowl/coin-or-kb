+++
title = "Branch and Bound Correctness"
description = "Why relaxation bounds guarantee global optimality"
weight = 5

[extra]
prerequisites = ["mixed_integer_programming", "LP_relaxation"]
related_algorithms = ["branch_and_bound", "cutting_planes"]
+++

# Branch and Bound Correctness

Branch and bound is the fundamental algorithm for mixed-integer programming (MIP). It searches a tree of subproblems, using bounds to prune provably suboptimal branches. This derivation proves why the algorithm always finds a global optimum (if one exists).

## Setup

Consider the mixed-integer linear program:

$$\min_{x} \quad c^T x \quad \text{subject to} \quad Ax \leq b, \quad x_i \in \mathbb{Z} \; \forall i \in I$$

where $I \subseteq \{1, \ldots, n\}$ is the set of integer variables.

**Key insight**: MIP is NP-hard, so we can't expect a polynomial-time algorithm. But branch and bound is *correct* — it provably finds the global optimum by systematically eliminating all suboptimal solutions.

---

## The LP Relaxation

The **LP relaxation** drops integrality constraints:

$$\min_{x} \quad c^T x \quad \text{subject to} \quad Ax \leq b$$

**Theorem**: The LP relaxation provides a lower bound on the MIP optimum.

**Proof**: Every MIP-feasible solution is LP-feasible (it satisfies all LP constraints). Therefore:

$$\{x : Ax \leq b, x_I \in \mathbb{Z}\} \subseteq \{x : Ax \leq b\}$$

The minimum over a subset is at least as large as the minimum over the superset:

$$z^*_{\text{MIP}} = \min_{\text{MIP feasible}} c^T x \geq \min_{\text{LP feasible}} c^T x = z^*_{\text{LP}}$$

∎

**Key property**: If the LP relaxation solution is integer-feasible, it solves the MIP.

---

## Branching

When the LP solution $\bar{x}$ has a fractional value $\bar{x}_j \notin \mathbb{Z}$ for some $j \in I$, we **branch** by creating two subproblems:

- **Left child**: Add constraint $x_j \leq \lfloor \bar{x}_j \rfloor$
- **Right child**: Add constraint $x_j \geq \lceil \bar{x}_j \rceil$

**Lemma (Disjunction)**: Every integer solution satisfies at least one branch.

**Proof**: For any $x_j \in \mathbb{Z}$, either $x_j \leq \lfloor \bar{x}_j \rfloor$ or $x_j \geq \lceil \bar{x}_j \rceil$ (or both, if $\bar{x}_j \in \mathbb{Z}$, but then we wouldn't branch). ∎

**Corollary**: Branching partitions the feasible region without losing any integer solutions.

---

## The Branch and Bound Algorithm

```
Initialize:
  - Active nodes = {root node (original problem)}
  - Best integer solution = none (incumbent z̄ = +∞)

While active nodes is not empty:
  1. SELECT a node from active nodes
  2. SOLVE its LP relaxation
  3. If LP infeasible:
       PRUNE (no integer solutions in this subtree)
  4. Else if LP optimal value ≥ z̄:
       PRUNE (can't improve incumbent)
  5. Else if LP solution is integer-feasible:
       UPDATE incumbent: z̄ = LP value
       PRUNE (found best solution in this subtree)
  6. Else:
       BRANCH: create children and add to active nodes

Return incumbent (or "infeasible" if none found)
```

---

## Main Theorem: Correctness

**Theorem (Branch and Bound Correctness)**: The algorithm terminates with the global optimum (or correctly reports infeasibility/unboundedness).

**Proof**:

We prove three properties:

### Property 1: Termination

**Claim**: The algorithm terminates in finite time.

*Proof*: Each branch adds a bound constraint, reducing the feasible region. The tree has depth at most $n \cdot \max_j (\lceil u_j \rceil - \lfloor l_j \rfloor)$, where $l_j, u_j$ are variable bounds.

With finite branching at each node (one branch per fractional variable) and finite depth, the tree is finite. Since we process one node per iteration and prune or branch at each, termination is guaranteed. ∎

### Property 2: Lower Bound Validity

**Claim**: At any point, $\min_{\text{active nodes}} z^*_{\text{LP}}$ is a valid lower bound on $z^*_{\text{MIP}}$.

*Proof by induction*:

**Base case**: The root LP relaxation lower-bounds the MIP (proved above).

**Inductive step**: Suppose node $P$ has LP bound $z^*_P$. When we branch, creating children $P_L$ and $P_R$:
- $z^*_{P_L} \geq z^*_P$ (more constraints, higher minimum)
- $z^*_{P_R} \geq z^*_P$ (same reasoning)

The disjunction lemma ensures all integer solutions in $P$ are in $P_L \cup P_R$.

So $\min(z^*_{P_L}, z^*_{P_R}) \geq z^*_P$, and the global lower bound is preserved. ∎

### Property 3: Optimality of Incumbent

**Claim**: When the algorithm terminates, the incumbent is optimal.

*Proof*: At termination, all active nodes have been pruned. Consider any MIP-feasible solution $x^*$:

1. $x^*$ lies in some path from root to a leaf in the full branch-and-bound tree.

2. At some node along this path, $x^*$ was pruned by one of:
   - **LP infeasibility**: Impossible (we assumed $x^*$ is MIP-feasible)
   - **Bound pruning**: The LP bound $z^*_{\text{LP}} \geq \bar{z}$. Since $c^T x^* \geq z^*_{\text{LP}} \geq \bar{z}$, the incumbent is at least as good.
   - **Integer solution found**: If $x^*$ was found, it became the incumbent.

3. In all cases, $c^T x^* \geq \bar{z}$.

Since this holds for all MIP-feasible $x^*$, the incumbent $\bar{z}$ is optimal. ∎

---

## Pruning Rules

The algorithm uses three pruning criteria:

| Rule | Condition | Why It's Safe |
|------|-----------|---------------|
| Infeasibility | LP has no solution | Tighter constraints won't help |
| Bound | $z^*_{\text{LP}} \geq \bar{z}$ | Can't improve incumbent |
| Integrality | LP solution is integer | Best in this subtree |

**Key insight**: Bound pruning is the workhorse. The better our bounds (tighter LP relaxation, better incumbent), the more we prune.

---

## Dual Bound and Optimality Gap

During the search:

- **Primal bound** ($\bar{z}$): Best integer solution found so far
- **Dual bound**: $\min_{\text{active}} z^*_{\text{LP}}$ (best possible improvement)
- **Gap**: $(\bar{z} - z^*_{\text{dual}}) / |z^*_{\text{dual}}|$

The algorithm terminates when gap = 0 (or below tolerance).

**Practical note**: For large MIPs, proving optimality (closing the gap) is often harder than finding a good solution. Many solvers run with a gap tolerance (e.g., 1%).

---

## Strengthening the Relaxation

The LP relaxation bound determines pruning effectiveness. Stronger bounds mean:
- More aggressive pruning
- Smaller trees
- Faster solve times

**Techniques to strengthen bounds**:

1. **Cutting planes**: Add valid inequalities that cut off fractional solutions
2. **Presolve**: Tighten variable bounds, remove redundant constraints
3. **Branching strategy**: Better branching creates more imbalanced children (more pruning)
4. **Primal heuristics**: Better incumbents enable more bound pruning

---

## Connection to Code

### Cbc (Branch and Cut)

```cpp
// CbcModel.cpp implements the main B&B loop
// Key data structures:
//   - CbcNode: represents a node in the tree
//   - CbcTree: manages active nodes (priority queue)
//   - bestObjective_: incumbent value (z̄)

void CbcModel::branchAndBound() {
    while (!tree_->empty()) {
        CbcNode* node = tree_->bestNode();  // Node selection

        int status = node->solve();  // LP relaxation

        if (status == LP_INFEASIBLE) {
            // Prune by infeasibility
            delete node;
        } else if (node->objectiveValue() >= bestObjective_) {
            // Prune by bound
            delete node;
        } else if (node->isIntegerFeasible()) {
            // Update incumbent
            updateBestSolution(node);
            delete node;
        } else {
            // Branch
            CbcBranch* branch = chooseBranch(node);
            tree_->push(node->createChild(branch, UP));
            tree_->push(node->createChild(branch, DOWN));
        }
    }
}
```

### Node Selection Strategies

```cpp
// CbcCompareDepth: depth-first (finds solutions fast)
// CbcCompareBest: best-first (proves optimality fast)
// CbcCompareHybrid: switches between strategies

// Depth-first pros: small memory, finds incumbents early
// Best-first pros: proves optimality efficiently, better bounds
```

### Branching Variable Selection

```cpp
// CbcBranchDynamicDecision: pseudocost branching
// CbcBranchAllDifferent: strong branching
//
// Strong branching: solve LP for each candidate variable
//   Expensive but gives best bounds
// Pseudocost: estimate improvement from history
//   Cheap approximation to strong branching
```

---

## Summary

| Component | Role |
|-----------|------|
| LP relaxation | Provides lower bound |
| Branching | Partitions without losing solutions |
| Pruning | Eliminates provably suboptimal regions |
| Incumbent | Upper bound from best solution found |
| Termination | Finite tree + exhaustive search |

Branch and bound is an *exact* algorithm: it guarantees the global optimum. The challenge is computational — the tree can be exponentially large. Modern MIP solvers combine B&B with cutting planes, heuristics, and presolve to make large problems tractable.
