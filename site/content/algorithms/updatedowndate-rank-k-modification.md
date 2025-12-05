+++
title = "Update/Downdate (rank-k modification)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Given L·L' = A, compute L̃ such that L̃·L̃' = A ± C·C':
  - Uses Givens rotations for numerical stability
  - O(k × nnz(L)) complexity for rank-k modification

## Mathematical Formulation

<div class="math-block">

For A = L·L': L(j,j) = √(A(j,j) - Σ L(j,k)²)
  L(i,j) = (A(i,j) - Σ L(i,k)·L(j,k)) / L(j,j) for i > j

</div>

## Complexity

Factorization: O(nnz(L)²/m) with supernodal method
  Solve: O(nnz(L)) per right-hand side
  Fill-in (nnz(L)) depends on ordering quality

## Implementations

### SuiteSparse

- **{{ link(path="/browser/?library=SuiteSparse", text="cholmod.h") }}** - Comprehensive sparse Cholesky factorization library

CHOLMOD provides high-performance sparse Cholesky factorization for
symmetric positive definite (SPD) and symmetric positive semi-definite
matrices. It supports:

Key features:
- Supernodal and simplicial Cholesky (LL' and LDL')
- Fill-reducing orderings: AMD, COLAMD, METIS, CAMD
- Real, complex, and pattern-only matrices
- Single and double precision (float/double)
- Row/column updates and downdates
- GPU acceleration (NVIDIA CUDA)

Typical workflow:
1. cholmod_start: Initialize Common workspace
2. cholmod_analyze: Symbolic analysis (fill-reducing ordering)
3. cholmod_factorize: Numerical Cholesky factorization
4. cholmod_solve: Solve Ax = b using the factors
5. cholmod_finish: Free workspace

## References

- Davis (2006). "Direct Methods for Sparse Linear Systems".
     SIAM. ISBN: 978-0-898716-13-9. Chapter 4-8.
- Chen, Davis, Hager, Rajamanickam (2008). "Algorithm 887: CHOLMOD,
     Supernodal Sparse Cholesky Factorization and Update/Downdate".
     ACM Trans. Math. Software 35(3).
