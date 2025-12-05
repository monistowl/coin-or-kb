+++
title = "Tripleton Elimination"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

Given equality constraint ax + by + cz = d with three variables:
  1. Solve for y: y = (d - ax - cz) / b
  2. Substitute y into objective and all constraints containing y
  3. Eliminate the constraint row and variable y
  Only applied if substitution doesn't increase total nonzeros

## Mathematical Formulation

<div class="math-block">

Original: ax + by + cz = d
  Substitution: y = (d - ax - cz) / b
  Objective: c_y·y = c_y·d/b - (c_y·a/b)x - (c_y·c/b)z
  Postsolve recovers y from optimal (x*, z*)

</div>

## Complexity

Time: O(nnz(col_y) × avg_row_length) per tripleton
  Fill-in check prevents growth: only apply if beneficial
  Less common than doubleton but can still reduce problem size

## Implementations

### CoinUtils

- **{{ link(path="/browser/?library=CoinUtils", text="CoinPresolveTripleton.hpp") }}** - Tripleton row presolve: three-variable equation substitution
