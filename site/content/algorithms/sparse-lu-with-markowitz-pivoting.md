+++
title = "Sparse LU with Markowitz Pivoting"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Matrix Factorization"
implementation_count = 1
+++

## Why This Matters

LU factorization is the computational engine inside simplex. Every iteration requires solving two systems of equations (FTRAN and BTRAN), and LU makes this fast. Without good factorization:

- A 10,000-row LP would require ~$10^{12}$ operations per iteration with dense methods
- With sparse LU and good pivoting, the same problem might need only ~$10^6$ operations

**Markowitz pivoting** prevents "fill-in" — the phenomenon where a sparse matrix becomes dense during elimination. The pivot score $(r_i - 1)(c_j - 1)$ measures potential fill-in: a pivot in a row with 3 nonzeros and a column with 4 nonzeros creates at most $(3-1)(4-1) = 6$ new elements.

**Why this matters for MIP**: During branch-and-bound, the solver might re-solve hundreds of thousands of LPs. If each factorization is slow or creates too much fill-in, the solver bogs down. This is why CoinUtils provides multiple factorization implementations for different problem structures.

---

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

- **{{ link(path="/browser/?library=CoinUtils", text="CoinSimpFactorization.hpp") }}** - Simple LU factorization for LP basis matrices

Straightforward LU factorization implementation. Less optimized than
CoinFactorization but simpler and useful as reference implementation.
