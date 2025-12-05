+++
title = "LU factorization with Markowitz pivot selection"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Matrix Factorization"
implementation_count = 1
+++

## Mathematical Formulation

<div class="math-block">

Decomposes basis matrix B = L·U where:
      - L is lower triangular (stored by columns, implicit unit diagonal)
      - U is upper triangular (stored by columns)
      FTRAN solves Bx = b via: Ly = b, then Ux = y
      BTRAN solves B'y = c via: U'z = c, then L'y = z

</div>

## Complexity

Factorization: O(nnz * fill) where fill depends on pivot order
            FTRAN/BTRAN: O(nnz(L) + nnz(U)) per solve
            Rank-one update: O(nnz(column)) via Forrest-Tomlin

## Implementations

### CoinUtils

- **{{ link(path="/browser/?library=CoinUtils", text="CoinFactorization.hpp") }}** - LU factorization of sparse basis matrix for simplex

Implements LU factorization with hyper-sparse handling for efficient
FTRAN/BTRAN operations. Supports rank-one updates during pivoting.

## References

- Forrest, Tomlin (1972). "Updated Triangular Factors of the Basis
     to Maintain Sparsity in the Product Form Simplex Method".
     Mathematical Programming 2:263-278.
- Suhl, Suhl (1990). "Computing Sparse LU Factorizations for
     Large-Scale Linear Programming Bases". ORSA J. Computing 2:325-335.
- Forrest, Tomlin (1972). Mathematical Programming 2:263-278.
