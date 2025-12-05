+++
title = "Fixed Variable Removal"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

For variable x_j with l_j = u_j = v (fixed):
  1. Substitute x_j = v into all constraints: b_i := b_i - a_ij·v
  2. Remove column j from constraint matrix
  3. Adjust objective constant: z += c_j·v
  4. Store column for postsolve restoration

  make_fixed_action: Force bounds equal to fix variable
  remove_fixed_action: Remove already-fixed variable from matrix

## Mathematical Formulation

<div class="math-block">

Substitution: Ax = b with x_j = v becomes A'x' = b - a_j·v
  where A' is A without column j, x' is x without x_j
  Postsolve: restore x_j = v in solution

</div>

## Complexity

Time: O(nnz(column_j)) per fixed variable
  Reduces problem dimension, may create new singletons or empty rows
  Very common in practical models (constants, derived bounds)

## Implementations

### CoinUtils

- **{{ link(path="/browser/?library=CoinUtils", text="CoinPresolveFixed.hpp") }}** - Remove fixed variables and make variables fixed
