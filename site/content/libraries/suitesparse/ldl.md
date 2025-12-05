+++
title = "ldl"
description = "Simple sparse LDL' factorization for symmetric matrices"
template = "page.html"

[extra]
layer = 0
library = "SuiteSparse"
header_file = "LDL/Include/ldl.h"
+++

Simple sparse LDL' factorization for symmetric matrices

LDL computes a sparse LDL' factorization of a symmetric matrix A:
  A = L * D * L'
where L is unit lower triangular and D is diagonal. This factorization
works for symmetric indefinite matrices (D may have negative entries).

The factorization is performed in two phases:
1. ldl_symbolic: Compute elimination tree and allocate storage
2. ldl_numeric: Compute numerical values of L and D

Triangular solves (ldl_lsolve, ldl_dsolve, ldl_ltsolve) complete the
solution of Ax = b.

## Algorithm

<div class="algorithm-card">

Sparse LDL' factorization (up-looking):
  1. Symbolic: compute elimination tree and nonzero pattern of L
     - Parent[j] = min{i > j : L(i,j) ≠ 0} defines elimination tree
     - Lnz[j] = # nonzeros in column j of L (excluding diagonal)
  2. Numeric: compute L and D column by column
     - For each column j: gather contributions from columns k < j
     - where k has nonzero in row j (i.e., L(j,k) ≠ 0)
     - D(j,j) = A(j,j) - Σ L(j,k)² D(k,k)
     - L(i,j) = (A(i,j) - Σ L(i,k) L(j,k) D(k,k)) / D(j,j)

<div class="math">

A = L * D * L' where L is unit lower triangular, D is diagonal.
Unlike Cholesky (A = L*L'), LDL' handles indefinite matrices.
If A is positive definite, D has all positive entries.
D may have negative entries for indefinite matrices.

</div>

**Complexity:** Time: $O(nnz(L)$²/n) average, $O(nnz(L)$·nnz(A)) worst case
  Space: $O(nnz(L)$ + n) for factors
  Simple implementation - for production use CHOLMOD instead.

<div class="refs">

**References:**
- Davis (2005). "Algorithm 849: A Concise Sparse Cholesky Factorization      Package". ACM Trans. Math. Software 31(4):587-591.

</div>

</div>

## See Also

- cholmod.h for more sophisticated Cholesky implementation
- amd.h for fill-reducing orderings to use with LDL

## Source

Header file: [`LDL/Include/ldl.h`](/browser/?library=SuiteSparse&file=LDL/Include/ldl.h)

