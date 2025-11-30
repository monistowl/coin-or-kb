+++
title = "Variable Substitution (Non-Singleton)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

For implied free variable x_j in equality constraint i:
  1. Solve constraint i for x_j: x_j = (b_i - Σ_{k≠j} a_ik x_k) / a_ij
  2. Substitute x_j expression into all other rows containing x_j
  3. After substitution, x_j becomes column singleton
  4. Apply implied_free_action to remove x_j and row i

  Fill-in control: only substitute if total nnz doesn't increase too much

## Mathematical Formulation

<div class="math-block">

Substitution creates fill-in: originally empty positions become nonzero
  Fill estimate: (nnz(col_j) - 1) × (nnz(row_i) - 1) new elements
  Controlled by fill_level parameter to prevent explosion

</div>

## Complexity

Time: O(nnz(col_j) × nnz(row_i)) per substitution
  Can significantly reduce problem when fill-in is controlled
  Postsolve must undo all substitutions in reverse order

## Implementations

### CoinUtils

- **[CoinPresolveSubst.hpp](/browser/?library=CoinUtils)** - Variable substitution from equality constraints
