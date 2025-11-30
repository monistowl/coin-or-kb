+++
title = "Empty Row/Column Removal"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

drop_empty_cols_action:
  - Compress column arrays, renumber remaining columns
  - Store original bounds, cost, solution for postsolve
  - Adjust objective constant for fixed-at-bound variables

  drop_empty_rows_action:
  - Renumber rows, compress row bounds
  - Track which row filled each position for postsolve

## Mathematical Formulation

<div class="math-block">

Empty column j: a_*j = 0 (all zeros in column)
  For minimization: set x_j = l_j if c_j > 0, x_j = u_j if c_j < 0
  Empty row i: a_i* = 0 → constraint always satisfied, remove

</div>

## Complexity

Time: O(m + n) for scanning and renumbering
  Must be done last: other transforms may create empty rows/cols
  Postsolve reinserts in reverse order, first step after solve

## Implementations

### CoinUtils

- **[CoinPresolveEmpty.hpp](/browser/?library=CoinUtils)** - Drop and reinsert empty rows/columns

Should be last presolve step. Physical removal of empty entities.
