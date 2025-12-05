+++
title = "Online Active Set Strategy"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

1. Start from a primal-dual feasible point
  2. Track active set (constraints at bounds)
  3. Update active set incrementally when parameters change
  Efficient for parametric QPs where data varies smoothly.

## Mathematical Formulation

<div class="math-block">

lb  <= x <= ub       (bounds)

Key methods:
- init(): First QP solve (cold start)
- hotstart(): Subsequent solves with modified data

</div>

## Complexity

O(n^3) worst case per iteration, but typically much
            faster due to hot-starting and sparse updates.

## Implementations

### qpOASES

- **{{ link(path="/browser/?library=qpOASES", text="QProblem.hpp") }}** - QP solver with general linear constraints

Solves convex QPs with bounds and linear constraints:
