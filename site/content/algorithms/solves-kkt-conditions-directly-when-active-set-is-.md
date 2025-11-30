+++
title = "Solves KKT conditions directly when active set is known."
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Uses Cholesky factorization of reduced Hessian.

## Mathematical Formulation

<div class="math-block">

s.t. lb <= x <= ub

This is more efficient than QProblem when there are no general
linear constraints. The active set consists only of bounds.

Key methods:
- init(): First QP solve (cold start)
- hotstart(): Subsequent solves with modified g, lb, ub

</div>

## Implementations

### qpOASES

- **[QProblemB.hpp](/coin-or-kb/browser/?library=qpOASES)** - Box-constrained QP solver (bounds only, no linear constraints)

Solves QPs with only variable bounds (no constraint matrix A):
