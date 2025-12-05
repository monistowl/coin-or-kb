+++
title = "Dual Bound Propagation"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

Use dual feasibility to fix primal variables:
  1. For slacks s_i: d_{n+i} = -y_i, bound y_i from slack bounds
  2. For singletons x_j: d_j = c_j - y_i·a_ij, bound y_i from d_j sign
  3. Propagate bounds through reduced cost equation d_j = c_j - y'a_j
  4. If d_j > 0 at optimality: x_j at lower bound (minimization)
  5. If d_j < 0 at optimality: x_j at upper bound

## Mathematical Formulation

<div class="math-block">

Reduced cost: d_j = c_j - Σ_i y_i a_ij
  Dual feasibility (min): d_j ≥ 0 if x_j at lower, d_j ≤ 0 if at upper
  Bound propagation: y_i^L ≤ y_i ≤ y_i^U → d_j^L ≤ d_j ≤ d_j^U

</div>

## Complexity

Time: O(iterations × nnz) for bound propagation
  Very powerful for detecting fixed variables without solving LP
  Can prove unboundedness when required bound is missing

## Implementations

### CoinUtils

- **{{ link(path="/browser/?library=CoinUtils", text="CoinPresolveDual.hpp") }}** - Fix variables using dual bounds and reduced cost analysis
