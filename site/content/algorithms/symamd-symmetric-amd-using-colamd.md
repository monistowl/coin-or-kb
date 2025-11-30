+++
title = "SYMAMD (Symmetric AMD using COLAMD)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

For symmetric A, apply COLAMD to A+A' structure to find fill-reducing order.

## Mathematical Formulation

<div class="math-block">

Approximate column degree for LU:
  deg(j) ≈ # rows in current column's nonzero pattern after elimination
  Aggressive absorption reduces degree overestimates from element merging.

</div>

## Complexity

Time: O(nnz(A)·α(n)) average with aggressive absorption
  Space: O(nnz(A) + n) for quotient graph representation
  Slightly slower than AMD but better for unsymmetric patterns.

## Implementations

### SuiteSparse

- **[colamd.h](/browser/?library=SuiteSparse)** - Column Approximate Minimum Degree ordering for sparse LU factorization

COLAMD computes a column permutation Q that reduces fill-in during LU
factorization of an unsymmetric matrix A. The ordering minimizes the
fill-in of A*Q when factored as LU.

SYMAMD computes a symmetric ordering for a symmetric matrix, using COLAMD
on the matrix's structure. Both are related to the minimum degree family
of algorithms.

## References

- Davis, Gilbert, Larimore, Ng (2004). "A Column Approximate Minimum
     Degree Ordering Algorithm". ACM Trans. Math. Software 30(3):353-376.
