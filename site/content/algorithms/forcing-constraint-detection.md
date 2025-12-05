+++
title = "Forcing Constraint Detection"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

Compute implied bounds on row activity: LB_i ≤ Σ a_ij x_j ≤ UB_i
  using variable bounds l_j ≤ x_j ≤ u_j

  Useless constraint: LB_i ≥ row_lb and UB_i ≤ row_ub
  - Constraint can never be violated → remove it

  Forcing constraint: LB_i = row_ub or UB_i = row_lb
  - All variables forced to bounds that achieve the activity limit
  - Fix variables, remove constraint

## Mathematical Formulation

<div class="math-block">

Activity bounds: LB_i = Σ_{a_ij>0} a_ij l_j + Σ_{a_ij<0} a_ij u_j
  UB_i = Σ_{a_ij>0} a_ij u_j + Σ_{a_ij<0} a_ij l_j
  Forcing: if UB_i = row_lb, then each term must achieve its min

</div>

## Complexity

Time: O(nnz) to compute activity bounds for all rows
  Very effective for tightly bounded problems
  Can fix many variables simultaneously

## Implementations

### CoinUtils

- **[CoinPresolveForcing.hpp](/browser/?library=CoinUtils)** - Forcing and useless constraint detection
