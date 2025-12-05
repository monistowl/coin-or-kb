+++
title = "MIP Journey"
description = "From LP relaxation to branch-and-cut"
template = "learning-path.html"
weight = 2

[extra]
tagline = "Understand how integer programming solvers work"
duration = "~6 hours"
prereqs = "LP Fundamentals path"
steps = [
    { id = "what-is-mip", title = "What is Mixed-Integer Programming?", duration = "20 min" },
    { id = "lp-relaxation", title = "LP Relaxation and Bounds", duration = "30 min" },
    { id = "branch-and-bound", title = "Branch-and-Bound Trees", duration = "45 min" },
    { id = "cutting-planes", title = "Cutting Planes", duration = "45 min" },
    { id = "branching-strategies", title = "Branching Strategies", duration = "30 min" },
    { id = "heuristics", title = "Primal Heuristics", duration = "30 min" },
    { id = "putting-together", title = "Putting It Together: Branch-and-Cut", duration = "40 min" },
]
+++

<div class="key-insight">

This path builds on LP Fundamentals to show how MIP solvers handle integer variables. You'll understand why MIP is hard, how branch-and-bound explores solutions, and why cutting planes and heuristics make modern solvers practical.

</div>

## Prerequisites

You should have completed [LP Fundamentals](/learning-paths/lp-fundamentals/) or be comfortable with:
- The simplex method (primal and dual)
- LP duality and reduced costs
- Why LP can be solved efficiently

---

<h2 id="what-is-mip">1. What is Mixed-Integer Programming?</h2>

MIP extends LP by requiring some variables to be integers:

$$\min_{x,y} \quad c^T x + d^T y$$
$$\text{s.t.} \quad Ax + By = b$$
$$\quad x \geq 0, \quad y \in \mathbb{Z}^p_{\geq 0}$$

Where $x$ are continuous and $y$ are integer variables.

### Why Integers Matter

Many real decisions are discrete:
- Build a factory or not (binary: 0 or 1)
- Number of trucks to deploy (integer)
- Which routes to use (binary selection)

### Why MIP is Hard

LP is solvable in polynomial time. MIP is **NP-hard**.

<div class="concept-box">
<h4>The Combinatorial Explosion</h4>

With $n$ binary variables, there are $2^n$ possible combinations:
- 20 variables → ~1 million combinations
- 40 variables → ~1 trillion combinations
- 100 variables → more than atoms in the universe

We can't enumerate. We need to be clever.
</div>

### Types of Integer Programs

| Type | Variables | Example |
|------|-----------|---------|
| Pure IP | All integer | Scheduling |
| Mixed IP (MIP) | Some integer, some continuous | Facility location |
| Binary IP | All 0-1 | Set covering |
| MIQCP | Integer + quadratic constraints | Portfolio with lots |

<div class="code-connection">

In COIN-OR, MIP is solved by [Cbc](/libraries/cbc/) (COIN-OR Branch and Cut). It uses [Clp](/libraries/clp/) for LP relaxations and [Cgl](/libraries/cgl/) for cut generation.

</div>

---

<h2 id="lp-relaxation">2. LP Relaxation and Bounds</h2>

The key idea: **relax** integer constraints to get an LP, then use its solution to guide the search.

### LP Relaxation

Drop the integrality requirements:
$$y \in \mathbb{Z}^p \quad \rightarrow \quad y \in \mathbb{R}^p$$

The resulting LP is called the **LP relaxation**.

### Why Relaxation Helps

<div class="key-insight">

**Bounding property:** For minimization:
$$\text{LP optimal} \leq \text{MIP optimal}$$

The LP relaxation provides a **lower bound** on the best possible integer solution. This lets us prune parts of the search space.

</div>

### Example

**MIP:** min $-x$ s.t. $x \leq 2.5$, $x \in \mathbb{Z}_{\geq 0}$
- LP relaxation optimal: $x = 2.5$, objective = $-2.5$
- MIP optimal: $x = 2$, objective = $-2$

The LP bound ($-2.5$) is valid but optimistic.

### The Integrality Gap

$$\text{Gap} = \frac{\text{MIP optimal} - \text{LP optimal}}{\text{MIP optimal}}$$

Smaller gaps mean:
- LP relaxation is a good approximation
- Branch-and-bound will be faster
- Cutting planes are more effective

<div class="code-connection">

Cbc tracks bounds in `CbcModel`. The method `getBestPossibleObjValue()` returns the current lower bound from the LP relaxation.

</div>

---

<h2 id="branch-and-bound">3. Branch-and-Bound Trees</h2>

Branch-and-bound systematically explores the solution space by dividing it into smaller subproblems.

<div class="diagram-container">
<img src="../diagrams/branch-and-bound-tree.svg" alt="Branch-and-bound tree example" class="algorithm-diagram">
</div>

### The Algorithm

<div class="step-by-step">

<div class="step">
<h5>Step 1: Solve LP Relaxation</h5>

At each node, solve the LP. If solution is integer-feasible, we have a candidate.

</div>

<div class="step">
<h5>Step 2: Check Pruning Conditions</h5>

**Prune** (don't explore further) if:
- LP is infeasible (no integer solution possible)
- LP bound ≥ best known integer solution (can't improve)
- Solution is integer-feasible (record if best)

</div>

<div class="step">
<h5>Step 3: Branch</h5>

Choose a fractional variable $y_j = f$ (e.g., $f = 2.7$).

Create two children:
- **Left branch:** Add $y_j \leq \lfloor f \rfloor$ (i.e., $y_j \leq 2$)
- **Right branch:** Add $y_j \geq \lceil f \rceil$ (i.e., $y_j \geq 3$)

</div>

<div class="step">
<h5>Step 4: Select Next Node</h5>

Choose which unexplored node to process next (see node selection strategies below).

</div>

</div>

### Visualizing the Tree

```
                    Root (LP: -2.5)
                   /              \
        y₁ ≤ 2                    y₁ ≥ 3
           |                        |
      Node 1 (LP: -2.3)        Node 2 (LP: -2.8)
      Integer! Best = -2.3     Better bound, explore...
                               /              \
                    y₂ ≤ 1                    y₂ ≥ 2
                       |                        |
                   Infeasible              Pruned (bound ≥ -2.3)
```

### Node Selection Strategies

| Strategy | Description | When to use |
|----------|-------------|-------------|
| Best-first | Explore node with best bound | Prove optimality |
| Depth-first | Explore deepest node | Find solutions fast, low memory |
| Best-estimate | Use heuristic prediction | Balance exploration |
| Diving | Go deep, then backtrack | Find good solutions early |

<div class="key-insight">

**The power of pruning:** If we find a good solution early (incumbent), we can prune huge parts of the tree. This is why **primal heuristics** matter so much.

</div>

<div class="code-connection">

`CbcModel` manages the tree. `CbcNode` represents nodes. Tree traversal strategies are in `CbcTree` and `CbcCompare*` classes. See [branch-and-bound tree search](/algorithms/branch-and-bound-tree-search/).

</div>

---

<h2 id="cutting-planes">4. Cutting Planes</h2>

Cutting planes tighten the LP relaxation by adding constraints that cut off fractional solutions without removing integer solutions.

### What is a Cutting Plane?

A **valid inequality** $\alpha^T x \leq \beta$ that:
1. Is satisfied by all integer-feasible points
2. Cuts off the current fractional LP solution

### Example: Gomory Cut

If the LP solution has $y_1 = 2.7$ with tableau row:
$$y_1 + 0.3y_2 - 0.5y_3 = 2.7$$

The Gomory cut captures that the fractional parts must sum to an integer:
$$0.3y_2 + 0.5y_3 \geq 0.7$$

(Because $y_1$ must be integer, the fractional contributions from $y_2, y_3$ must compensate.)

### Types of Cuts

| Cut Type | What it exploits | Generated by |
|----------|-----------------|--------------|
| Gomory | Simplex tableau structure | `CglGomory` |
| Knapsack cover | Knapsack constraints | `CglKnapsackCover` |
| Clique | Conflicts between binaries | `CglClique` |
| MIR (Mixed Integer Rounding) | Mixing integer and continuous | `CglMixedIntegerRounding` |
| Flow cover | Network structure | `CglFlowCover` |
| Lift-and-project | Disjunctions | `CglLandP` |

<div class="key-insight">

**Why cuts help:** Each cut tightens the LP relaxation, bringing the LP optimum closer to the MIP optimum. This reduces the integrality gap, which means:
- Better bounds at each node
- More nodes can be pruned
- Faster convergence to optimality

</div>

### Cut Management

Adding too many cuts can slow down the LP. Solvers manage cuts by:
- Limiting cuts per round
- Removing inactive cuts
- Aging out old cuts

<div class="code-connection">

The [Cgl library](/libraries/cgl/) provides cut generators. `CbcModel` calls them via `CglCutGenerator`. See the [lift-and-project algorithm](/algorithms/lift-and-project-cutting-planes/).

</div>

---

<h2 id="branching-strategies">5. Branching Strategies</h2>

How you choose which variable to branch on dramatically affects performance.

### Most Fractional

Branch on the variable closest to 0.5 (most "undecided").

**Pros:** Simple, no overhead
**Cons:** Often inefficient

### Pseudo-cost Branching

Track history: for each variable, record how much the LP bound changed when branching on it before.

$$\text{score}_j = f_j \cdot \text{down\_pseudo} + (1-f_j) \cdot \text{up\_pseudo}$$

**Pros:** Learns from experience
**Cons:** No history at start

### Strong Branching

Actually solve the LP for both branches (partially) to estimate bound improvement.

**Pros:** Best predictions
**Cons:** Expensive (many LPs per node)

### Reliability Branching

Hybrid: use strong branching until pseudo-costs are "reliable" (enough observations), then switch.

<div class="key-insight">

**The trade-off:** Better branching decisions mean fewer nodes, but each decision takes time. Modern solvers use adaptive strategies that invest more in branching decisions near the root (where impact is highest).

</div>

<div class="code-connection">

Cbc's branching strategies are in `CbcBranch*` classes. `CbcBranchDynamic` implements reliability branching. See [branching variable selection](/algorithms/branching-variable-selection-strategies/).

</div>

---

<h2 id="heuristics">6. Primal Heuristics</h2>

Heuristics find good (not necessarily optimal) integer solutions fast. A good incumbent enables massive pruning.

### Why Heuristics Matter

Without an incumbent, we can't prune anything. The sooner we find a good solution:
- The more we can prune
- The better our gap estimate
- The faster we converge

### Common Heuristics

<div class="concept-box">
<h4>Rounding</h4>

Round the LP solution to integers. Simple but often infeasible.

Variants: round toward integer, round to improve feasibility.
</div>

<div class="concept-box">
<h4>Feasibility Pump</h4>

Iterate between:
1. Round LP solution to nearest integers
2. Solve LP to get closest point to rounded solution

Converges to an integer-feasible point.
</div>

<div class="concept-box">
<h4>RINS (Relaxation Induced Neighborhood Search)</h4>

Fix variables that agree between LP and current incumbent. Solve the reduced MIP.

Uses the incumbent to guide the search.
</div>

<div class="concept-box">
<h4>Diving</h4>

Greedily round variables one at a time, re-solving LP after each. If infeasible, backtrack.
</div>

<div class="key-insight">

**Heuristic scheduling:** Solvers run different heuristics at different times:
- Root node: extensive search (feasibility pump, RINS)
- During tree: lightweight heuristics (rounding)
- Periodically: local search to improve incumbent

</div>

<div class="code-connection">

Cbc heuristics inherit from `CbcHeuristic`. See `CbcHeuristicFPump` for feasibility pump and `CbcHeuristicRINS` for RINS. The [primal heuristics framework](/algorithms/mip-primal-heuristics-framework/) documents the design.

</div>

---

<h2 id="putting-together">7. Putting It Together: Branch-and-Cut</h2>

Modern MIP solvers combine everything into **branch-and-cut**:

### The Full Algorithm

<div class="step-by-step">

<div class="step">
<h5>Presolve</h5>

Simplify the problem: fix variables, tighten bounds, detect infeasibility.

</div>

<div class="step">
<h5>Root Node Processing</h5>

1. Solve LP relaxation
2. Generate cutting planes (multiple rounds)
3. Run primal heuristics extensively
4. Establish initial incumbent and bound

</div>

<div class="step">
<h5>Branch-and-Bound Tree Search</h5>

While unexplored nodes remain and gap > tolerance:
1. Select a node
2. Solve LP (warm-starting from parent)
3. Try to prune
4. If fractional: generate cuts, run heuristics, branch

</div>

<div class="step">
<h5>Postsolve</h5>

Map solution back to original problem space.

</div>

</div>

### Performance in Practice

| Technique | Typical impact |
|-----------|----------------|
| Presolve | 2-10x speedup |
| Root cuts | 10-100x speedup |
| Good incumbent | 10-1000x speedup |
| Strong branching | 2-5x speedup |

<div class="key-insight">

**Why modern solvers are fast:** It's not any single technique—it's the combination. Good cuts reduce the tree size. Good heuristics enable pruning. Good branching minimizes nodes visited. All together, they can solve problems that would be impossible with basic branch-and-bound.

</div>

### Monitoring Progress

Solvers report:
- **Gap:** `(incumbent - bound) / incumbent` — how far from optimal
- **Nodes:** Number explored and remaining
- **Time:** Wall clock and per-node

When gap reaches tolerance (often 0.01%), solver declares optimal.

<div class="code-connection">

The main loop is in `CbcModel::branchAndBound()`. See [branch-and-cut algorithm](/algorithms/branch-and-cut-bc-for-mixed-integer-programming/).

</div>

---

## What's Next?

You now understand the core MIP algorithms! Next steps:

- **[Browse Cbc source](/browser/?library=Cbc)** - See the implementation
- **[Cutting plane algorithms](/algorithms/?category=cutting-planes)** - Deep dive on specific cuts
- **Try it:** Solve a MIP with Cbc and watch the log output. Match what you see to the concepts here.

<div class="key-insight">

**You've learned:**
- Why MIP is computationally hard (combinatorial explosion)
- How LP relaxation provides bounds
- Branch-and-bound tree search
- Cutting planes and why they help
- Branching strategies and their trade-offs
- Primal heuristics for finding incumbents
- How branch-and-cut puts it all together

You can now read Cbc code and understand what it's doing!

</div>
