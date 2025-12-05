+++
title = "Branch-and-Bound Tree Search"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

## Why This Matters

Branch-and-bound is the fundamental algorithm for solving mixed-integer programs — problems where some variables must be integers. This includes:

- **Scheduling**: Assigning discrete tasks to time slots or machines
- **Network design**: Whether to build a facility (yes/no = 0/1)
- **Vehicle routing**: Which routes to use, how many trucks to deploy

**The key insight**: Instead of trying all $2^n$ combinations, we systematically partition the search space and use LP relaxations to prune provably suboptimal regions. A good implementation explores only a tiny fraction of the theoretical tree.

**Node selection matters enormously**:
- **Best-first**: Prioritizes nodes with best bounds, proves optimality quickly but uses lots of memory
- **Depth-first**: Finds feasible solutions fast with minimal memory, but may not prove optimality efficiently
- **Hybrid strategies**: Cbc uses sophisticated combinations that adapt during the solve

---

Maintains a priority queue of open nodes, each representing a subproblem.
  Node selection strategies:
  - Best-first: select node with best LP bound (minimize gap)
  - Depth-first: select deepest node (find solutions quickly)
  - Breadth-first: select shallowest node (explore broadly)
  - Best-estimate: use estimated integer solution quality

## Mathematical Formulation

<div class="math-block">

Node attributes:
  - depth: distance from root (root = 0)
  - quality: LP relaxation value (lower bound for minimization)
  - fractionality: number of integer-infeasible variables
  - true_lower_bound: valid dual bound (may differ with column generation)

</div>

## Complexity

Node operations: O(log n) insertion, O(log n) extraction
  where n = number of open nodes. Uses heap-based priority queue.
  Sibling nodes stored together for efficient processing.

## Implementations

### CoinUtils

- **[CoinSearchTree.hpp](/browser/?library=CoinUtils)** - Search tree data structures for branch-and-bound

Provides tree node management with various comparison strategies
(best-first, depth-first, breadth-first).
