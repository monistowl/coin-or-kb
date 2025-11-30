+++
title = "Singleton Column/Row Elimination"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

Singleton column (one nonzero): variable x_j appears in one constraint
  - Compute x_j bounds from constraint bounds and coefficient sign
  - If bounds tighter than variable bounds, update variable bounds
  - If bounds prove infeasibility, detect and report

  Slack doubleton: row ax ≤ b with single variable, explicit bound
  - Convert to column bound: x ≤ b/a (adjust for sign)
  - Remove the constraint, tighten column bound

## Mathematical Formulation

<div class="math-block">

For singleton row ax_j = b: x_j = b/a (fixed value)
  For singleton column in ax_j ≤ b with a > 0: x_j ≤ b/a
  For singleton column in ax_j ≥ b with a > 0: x_j ≥ b/a

</div>

## Complexity

Time: O(1) per singleton processed
  Very effective: singletons common in practical LP/MIP models
  Cascading: removing singletons may create new singletons

## Implementations

### CoinUtils

- **[CoinPresolveSingleton.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Singleton row/column presolve transforms
