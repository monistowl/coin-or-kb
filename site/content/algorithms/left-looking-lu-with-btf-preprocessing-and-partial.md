+++
title = "Left-looking LU with BTF preprocessing and partial pivoting"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Matrix Factorization"
implementation_count = 1
+++

1. BTF pre-ordering (Tarjan's algorithm):
     - Find strongly connected components of digraph(A)
     - Permute to block upper triangular form (BTF)
     - Each diagonal block factored independently
  2. Fill-reducing ordering within blocks:
     - AMD for symmetric pattern blocks, COLAMD for unsymmetric
  3. Left-looking column-by-column LU:
     - For column k: solve L_{1:k-1, 1:k-1} · x = A_{1:k-1, k}
     - Apply partial pivoting within column
     - Extract L_{k+1:n, k} and U_{1:k, k}

## Mathematical Formulation

<div class="math-block">

Block Triangular Form: P·A·Q has structure
  | B_11  B_12  ...  B_1m |
  |   0   B_22  ...  B_2m |
  |   ⋮     ⋱    ⋱    ⋮  |
  |   0    0   ...  B_mm |
  Each B_ii is factored as P_i·B_ii = L_i·U_i independently.
  Off-diagonal blocks solved via triangular solves.

</div>

## Complexity

Time: O(Σ nnz(L_i)·nnz(U_i)/n_i + off-diagonal work)
  For circuit matrices: typically O(n) to O(n log n) due to BTF structure
  Much faster than UMFPACK for matrices with many small diagonal blocks.
  Space: O(nnz(L+U)) for factors, O(maxblock) workspace per block.

## Implementations

### SuiteSparse

- **{{ link(path="/browser/?library=SuiteSparse", text="klu.h") }}** - Sparse LU factorization optimized for circuit simulation matrices

KLU computes a sparse LU factorization of a square matrix A:
  P*A*Q = L*U
where P and Q are permutation matrices, L is unit lower triangular,
and U is upper triangular.

KLU is specifically designed for matrices arising from circuit simulation,
which tend to be sparse and nearly block-triangular. The factorization
proceeds in three phases:
1. klu_analyze: BTF pre-ordering + fill-reducing ordering (AMD/COLAMD)
2. klu_factor: Numerical LU factorization (left-looking, column-by-column)
3. klu_solve: Forward/back substitution to solve Ax = b

## References

- Davis, Palamadai (2010). "KLU: A Direct Sparse Solver for Circuit
     Simulation Problems". ACM Trans. Math. Software.
- Duff, Reid (1978). "An Implementation of Tarjan's Algorithm for the
     Block Triangularization of a Matrix". ACM Trans. Math. Software 4(2).
