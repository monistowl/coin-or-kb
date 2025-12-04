+++
title = "QProblemB"
description = "Box-constrained QP solver (bounds only, no linear constraints)"
template = "page.html"

[extra]
layer = 1
library = "qpOASES"
header_file = "include/qpOASES/QProblemB.hpp"
+++

Box-constrained QP solver (bounds only, no linear constraints)

Solves QPs with only variable bounds (no constraint matrix A):

## Algorithm

<div class="algorithm-card">

Solves KKT conditions directly when active set is known.
           Uses Cholesky factorization of reduced Hessian.

<div class="math">

$$\text{ s.t. }lb <= x <= ub$$

This is more efficient than QProblem when there are no general
linear constraints. The active set consists only of bounds.

Key methods:
- init(): First QP solve (cold start)
- hotstart(): Subsequent solves with modified g, lb, ub

</div>

</div>

## See Also

- QProblem for QPs with general linear constraints

## Source

Header file: `include/qpOASES/QProblemB.hpp`

