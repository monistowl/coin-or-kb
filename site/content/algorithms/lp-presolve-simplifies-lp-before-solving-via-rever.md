+++
title = "LP Presolve - simplifies LP before solving via reversible transforms"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

## Mathematical Formulation

<div class="math-block">

Presolve applies a sequence of transformations T_k to original LP:
      min c'x s.t. Ax = b, l <= x <= u  -->  min c'x' s.t. A'x' = b', l' <= x' <= u'
      Each T_k is recorded to enable postsolve recovery of original solution.

@note Presolve typically reduces problem size 30-90%, dramatically speeding solve

</div>

## Implementations

### CoinUtils

- **{{ link(path="/browser/?library=CoinUtils", text="CoinPresolveMatrix.hpp") }}** - Core presolve data structures and action base class

Defines CoinPrePostsolveMatrix (common base), CoinPresolveMatrix (for
presolve), CoinPostsolveMatrix (for postsolve), and CoinPresolveAction
(base class for all presolve transformations).

## References

- Andersen, E., Andersen, K. (1995). "Presolving in Linear Programming".
     Mathematical Programming 71:221-245.
