+++
title = "Sparse LU with Markowitz Pivoting"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Matrix Factorization"
implementation_count = 1
+++

Computes PA = LU minimizing fill-in during elimination.
  1. Find pivot (r,s) minimizing Markowitz count: (nnz_row - 1)(nnz_col - 1)
  2. Swap row r to current position, column s to current position
  3. Perform Gaussian elimination on remaining submatrix
  4. Store L factors by row and column, U factors by row and column
  Updates via eta vectors (product form of inverse):
  B_{k+1}^{-1} = E_k * B_k^{-1} where E_k is eta matrix

## Mathematical Formulation

<div class="math-block">

LU factorization: PA = LU, L unit lower triangular, U upper triangular
  FTRAN: solve Bx = b via Ly = Pb, Ux = y
  BTRAN: solve B'x = b via U'y = b, L'z = y, x = P'z
  Update: B_new = B_old + (a_q - B*e_p)*e_p' handled by eta vectors

</div>

## Complexity

Factorization: O(n³) worst, typically O(n·nnz) with good pivoting
  FTRAN/BTRAN: O(nnz(L) + nnz(U)) per solve
  Update: O(n) per eta vector, refactorize after ~100 pivots

## Implementations

### CoinUtils

- **[CoinSimpFactorization.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Simple LU factorization for LP basis matrices

Straightforward LU factorization implementation. Less optimized than
CoinFactorization but simpler and useful as reference implementation.
