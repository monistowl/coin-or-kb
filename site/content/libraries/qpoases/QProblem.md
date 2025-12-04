+++
title = "QProblem"
description = "QP solver with general linear constraints"
template = "page.html"

[extra]
layer = 1
library = "qpOASES"
header_file = "include/qpOASES/QProblem.hpp"
+++

QP solver with general linear constraints

Solves convex QPs with bounds and linear constraints:

## Algorithm

<div class="algorithm-card">

Online Active Set Strategy:
  1. Start from a primal-dual feasible point
  2. Track active set (constraints at bounds)
  3. Update active set incrementally when parameters change
  Efficient for parametric QPs where data varies smoothly.

<div class="math">

lb  <= x <= ub       (bounds)

Key methods:
- init(): First QP solve (cold start)
- hotstart(): Subsequent solves with modified data

</div>

**Complexity:** O(n^3) worst case per iteration, but typically much
            faster due to hot-starting and sparse updates.

</div>

## See Also

- QProblemB for box-constrained QPs (no A matrix)
- SQProblem for varying Hessian

## Source

Header file: `include/qpOASES/QProblem.hpp`

