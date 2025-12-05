+++
title = "Bound Tightening"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

For each constraint Σ a_ij x_j ≤ b_i:
  1. Compute max activity without x_k: M_k = Σ_{j≠k} max(a_ij l_j, a_ij u_j)
  2. New upper bound: x_k ≤ (b_i - M_k) / a_ik (if a_ik > 0)
  3. New lower bound: x_k ≥ (b_i - M_k) / a_ik (if a_ik < 0)
  4. Iterate until no bound changes or fixed point reached

  tighten_zero_cost: fix variables with zero objective at bounds

## Mathematical Formulation

<div class="math-block">

Implied bound: given Σa_j x_j ≤ b and x_j ∈ [l_j, u_j]
  x_k ≤ (b - Σ_{j≠k} a_j l_j) / a_k when a_k > 0
  Dual bound tightening uses similar logic from reduced costs

</div>

## Complexity

Time: O(iterations × nnz) for propagation
  Very effective for tightly constrained problems
  May prove infeasibility or fix variables

## Implementations

### CoinUtils

- **[CoinPresolveTighten.hpp](/browser/?library=CoinUtils)** - Tighten variable bounds using constraint propagation
