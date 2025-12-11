+++
title = "Interactive Branch and Bound Example"
description = "Step through a complete branch-and-bound solve for integer programming"
template = "branch-bound-interactive.html"
weight = 20
+++

This interactive example walks you through **Branch and Bound** for solving an Integer Linear Program (ILP). Click through each step to see node selection, branching decisions, bounding, and pruning in action.

## The Problem

A small investment problem with integer constraints:

$$\max \quad 5x_1 + 4x_2$$

Subject to:
$$x_1 + x_2 \leq 5 \quad \text{(budget)}$$
$$10x_1 + 6x_2 \leq 45 \quad \text{(resource)}$$
$$x_1, x_2 \geq 0 \text{ and integer}$$

### Why LP Relaxation Isn't Enough

The LP relaxation (ignoring integrality) gives $x_1 = 2.5$, $x_2 = 2.5$ with objective 22.5. But we need integers!

Simply rounding doesn't work reliably:
- Round to (3, 2): violates $10(3) + 6(2) = 42 \leq 45$ ✓ but objective = 23... wait, is this feasible? Let's check: $3 + 2 = 5 \leq 5$ ✓. Actually feasible but we can't know this without systematic search.
- Round to (2, 3): $10(2) + 6(3) = 38 \leq 45$ ✓, objective = 22
- Which is optimal? We need Branch and Bound to prove it.

## How Branch and Bound Works

The algorithm maintains:

1. **A tree of subproblems** — each node represents an LP with additional variable bounds
2. **A global upper bound** — the best LP relaxation value seen (for maximization)
3. **An incumbent** — the best integer solution found so far

At each step:
1. **Select** an open node (best-first or depth-first)
2. **Solve** its LP relaxation
3. **Prune** if infeasible, integer, or bound ≤ incumbent
4. **Branch** by adding constraints that partition the fractional variable

## What to Watch For

As you step through the tree:

1. **Node selection strategy**: This example uses best-first (highest LP bound). Cbc also supports depth-first diving for finding solutions quickly via `CbcCompareActual`.

2. **Branching variable choice**: We branch on fractional variables. Strong branching evaluates both children to pick the best split via `CbcBranchActual`.

3. **Pruning by bound**: When a node's LP bound can't beat the incumbent, we prune — no need to explore children. This is the key to efficiency.

4. **Pruning by infeasibility**: When adding bounds makes the LP infeasible, that branch is dead.

5. **Pruning by integrality**: When the LP solution is already integer, we have a candidate solution!

## Connection to COIN-OR Code

In Cbc (COIN-OR Branch and Cut), the tree search is implemented in [CbcModel](@/libraries/cbc/CbcModel.md):

| Concept | This Example | Cbc Implementation |
|---------|--------------|-------------------|
| **Node storage** | Visual tree | Priority queue (`CbcTree`) |
| **Node selection** | Best-first | Configurable strategy (`CbcCompareBase`) |
| **Branching** | Simple binary | Strong/pseudo-cost (`CbcBranchDecision`) |
| **Cutting planes** | None | Before branching ([Cgl](@/libraries/cgl/_index.md)) |

<div class="code-connection">

**Code Spotlight**: The main B&B loop is in `CbcModel::branchAndBound()`:

```
while (tree has unexplored nodes) {
    node = tree.bestNode()           // Node selection
    lpStatus = node.solveLP()        // Solve relaxation

    if (lpStatus == infeasible)
        prune(node)
    else if (node.isIntegerFeasible())
        updateIncumbent(node)        // New best solution!
    else if (node.bound <= incumbent)
        prune(node)                  // Can't improve
    else {
        var = selectBranchingVar()   // Choose fractional variable
        createChildren(node, var)    // Add x ≤ floor, x ≥ ceil
    }
}
```

The actual implementation handles many more details: cut generation, heuristics, parallelism, and preprocessing.

</div>

## Key Insight: Bounding Makes It Tractable

Without bounds, we'd enumerate all $2^n$ combinations for binary problems. But bounding lets us prove entire subtrees can't contain the optimum — cutting the search space exponentially.

The tighter the LP relaxation (better cuts), the more we prune, and the faster we solve.

## Try It Below

Use **Next Step** to explore the tree. Watch how:
- The **global bound** decreases as we explore
- The **incumbent** updates when we find integer solutions
- **Pruned** nodes (red) stop exploration early
- **Integer solutions** (green) update our best known answer
