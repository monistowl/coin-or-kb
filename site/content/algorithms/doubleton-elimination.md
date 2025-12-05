+++
title = "Doubleton Elimination"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

Given equality constraint ax + by = c with two variables:
  1. Solve for y: y = (c - ax) / b
  2. Substitute y in objective: c_x x + c_y y → c_x x + c_y(c-ax)/b
  3. Substitute y in all constraints containing y
  4. Transfer bounds: l_y ≤ y ≤ u_y becomes bounds on x
  5. Remove row and column y from problem

## Mathematical Formulation

<div class="math-block">

Original: min c_x·x + c_y·y s.t. ax + by = c, bounds
  After: min (c_x - c_y·a/b)x + c_y·c/b, modified bounds on x
  Postsolve recovers y = (c - ax)/b from optimal x*

</div>

## Complexity

Time: O(nnz(col_y)) per doubleton - updating all rows with y
  Typically reduces problem size significantly when equality rows exist
  Cascading effect: may create new singletons or doubletons

## Implementations

### CoinUtils

- **[CoinPresolveDoubleton.hpp](/browser/?library=CoinUtils)** - Doubleton row presolve: substitute y from ax+by=c
