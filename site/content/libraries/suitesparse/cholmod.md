+++
title = "cholmod"
description = "Comprehensive sparse Cholesky factorization library"
template = "page.html"

[extra]
layer = 0
library = "SuiteSparse"
header_file = "CHOLMOD/Include/cholmod.h"
+++

Comprehensive sparse Cholesky factorization library

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

## Algorithm

<div class="algorithm-card">

Update/Downdate (rank-k modification):
  Given L·L' = A, compute L̃ such that L̃·L̃' = A ± C·C':
  - Uses Givens rotations for numerical stability
  - O(k × nnz(L)) complexity for rank-k modification

<div class="math">

For A = L·L': L(j,j) = √(A(j,j) - Σ L(j,k)²)
$$L(i,j) = (A(i,j) - Σ L(i,k)·L(j,k)) / L(j,j) \text{ for }i > j$$

</div>

**Complexity:** Factorization: $O(nnz(L)$²/m) with supernodal method
  Solve: $O(nnz(L)$) per right-hand side
  Fill-in (nnz(L)) depends on ordering quality

<div class="refs">

**References:**
- Davis (2006). "Direct Methods for Sparse Linear Systems".      SIAM. ISBN: 978-0-898716-13-9. Chapter 4-8.
- Chen, Davis, Hager, Rajamanickam (2008). "Algorithm 887: CHOLMOD,      Supernodal Sparse Cholesky Factorization and Update/Downdate".      ACM Trans. Math. Software 35(3).

</div>

</div>

## See Also

- ldl.h for simple LDL' factorization
- amd.h, colamd.h for fill-reducing orderings
- cholmod_finish() to free all workspace at end
- cholmod_start()
- cholmod_finish()
- cholmod_allocate_sparse() to create
- cholmod_triplet for triplet (COO) format
- cholmod_analyze() to create symbolic factor
- cholmod_factorize() to compute numeric factor
- cholmod_solve() to solve using the factor
- cholmod_allocate_dense() to create
- cholmod_solve() to solve with dense right-hand sides
- cholmod_factorize() to compute numerical factorization
- cholmod_analyze_p() to provide a user permutation
- cholmod_analyze()
- cholmod_analyze() for symbolic analysis
- cholmod_solve() to solve using the factorization
- cholmod_factorize()
- cholmod_factorize() to compute the factorization
- cholmod_solve2() for reusable workspace version
- cholmod_solve()

## Source

Header file: {{ link(path="/browser/?library=SuiteSparse&file=CHOLMOD/Include/cholmod.h", text="`CHOLMOD/Include/cholmod.h`") }}

