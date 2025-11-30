+++
title = "Multifrontal LU with threshold partial pivoting"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Matrix Factorization"
implementation_count = 1
+++

1. Symbolic analysis: compute column elimination tree and frontal matrices
     - COLAMD ordering for unsymmetric, AMD for symmetric patterns
     - Identify supernodes: columns with identical nonzero patterns
  2. Numerical factorization (multifrontal):
     - Process columns in elimination tree postorder
     - For each frontal matrix: dense partial LU with threshold pivoting
     - Assemble child contributions (extend-add operation)
     - Extract L and U columns, pass remainder to parent front
  3. Solve phase: forward/back substitution through frontal matrices

## Mathematical Formulation

<div class="math-block">

Factorization: P·R·A·Q = L·U where:
  - P, Q are permutation matrices (row/column reordering)
  - R is diagonal scaling matrix (row equilibration)
  - L is unit lower triangular, U is upper triangular
  Threshold pivoting: select pivot if |a_kk| ≥ τ·max_i|a_ik| (τ ≈ 0.1)

</div>

## Complexity

Time: O(nnz(L+U)·f̄) where f̄ is average front size
  Typically O(n^1.5) to O(n^2) for 2D problems, O(n^2) for 3D
  Space: O(nnz(L+U) + front_stack) where front_stack depends on ordering

## Implementations

### SuiteSparse

- **[umfpack.h](/browser/?library=SuiteSparse)** - Multifrontal sparse LU factorization for unsymmetric matrices

UMFPACK computes a sparse LU factorization of a general (unsymmetric)
square matrix A:
  P*R*A*Q = L*U
where P and Q are permutation matrices, R is diagonal scaling, L is
unit lower triangular, and U is upper triangular.

Key features:
- Multifrontal algorithm with BLAS-3 dense kernels
- Automatic strategy selection (symmetric vs unsymmetric)
- Fill-reducing orderings: AMD (symmetric), COLAMD (unsymmetric)
- Real and complex matrices (double precision)
- Row scaling for numerical stability

Typical workflow:
1. umfpack_di_symbolic: Symbolic analysis (ordering, memory estimates)
2. umfpack_di_numeric: Numerical LU factorization
3. umfpack_di_solve: Solve Ax = b, A'x = b, etc.
4. umfpack_di_free_symbolic, umfpack_di_free_numeric: Free memory

## References

- Davis (2004). "Algorithm 832: UMFPACK V4.3 - An unsymmetric-pattern
     multifrontal method". ACM Trans. Math. Software 30(2):196-199.
- Davis (2004). "A column pre-ordering strategy for the unsymmetric-pattern
     multifrontal method". ACM Trans. Math. Software 30(2):165-195.
- Duff, Reid (1983). "The Multifrontal Solution of Indefinite Sparse
     Symmetric Linear Equations". ACM Trans. Math. Software 9(3):302-325.
