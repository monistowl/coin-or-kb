+++
title = "Dense LU Factorization (LAPACK-style)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Matrix Factorization"
implementation_count = 1
+++

Computes PA = LU using partial pivoting (row interchanges).
  1. For k = 1 to n: find pivot = max|A(i,k)| for i >= k
  2. Swap rows k and pivot row
  3. Compute L(i,k) = A(i,k) / A(k,k) for i > k
  4. Update A(i,j) -= L(i,k) * A(k,j) for i,j > k

## Mathematical Formulation

<div class="math-block">

Dense LU: PA = LU where P is permutation, L unit lower triangular,
  U upper triangular. FTRAN solves Lx = b then Ux = y.
  BTRAN solves U'y = b then L'x = y.

</div>

## Complexity

Time: O(n³/3) for factorization, O(n²) per solve
  Space: O(n²) for dense storage
  Use only for small basis matrices (n < 100-200)

## Implementations

### CoinUtils

- **[CoinDenseFactorization.hpp](/browser/?library=CoinUtils)** - Dense matrix factorization and CoinOtherFactorization base class

Provides CoinOtherFactorization abstract base class for alternative
factorization methods, plus CoinDenseFactorization for small dense
problems using LAPACK-style LU.
