+++
title = "colamd"
description = "Column Approximate Minimum Degree ordering for sparse LU factorization"
template = "page.html"

[extra]
layer = 0
library = "SuiteSparse"
header_file = "COLAMD/Include/colamd.h"
+++

Column Approximate Minimum Degree ordering for sparse LU factorization

COLAMD computes a column permutation Q that reduces fill-in during LU
factorization of an unsymmetric matrix A. The ordering minimizes the
fill-in of A*Q when factored as LU.

SYMAMD computes a symmetric ordering for a symmetric matrix, using COLAMD
on the matrix's structure. Both are related to the minimum degree family
of algorithms.

## Algorithm

<div class="algorithm-card">

SYMAMD (Symmetric AMD using COLAMD):
  For symmetric A, apply COLAMD to A+A' structure to find fill-reducing order.

<div class="math">

Approximate column degree for LU:
deg(j) ≈ # rows in current column's nonzero pattern after elimination
Aggressive absorption reduces degree overestimates from element merging.

</div>

**Complexity:** Time: $O(nnz(A)$·α(n)) average with aggressive absorption
  Space: $O(nnz(A)$ + n) for quotient graph representation
  Slightly slower than AMD but better for unsymmetric patterns.

<div class="refs">

**References:**
- Davis, Gilbert, Larimore, Ng (2004). "A Column Approximate Minimum      Degree Ordering Algorithm". ACM Trans. Math. Software 30(3):353-376.

</div>

</div>

## See Also

- amd.h for symmetric matrix ordering
- umfpack.h for sparse LU factorization using COLAMD
- colamd()
- colamd_recommended()
- colamd_set_defaults()
- colamd_recommended(), colamd_set_defaults()
- colamd()
- amd_order() for alternative symmetric ordering
- symamd()
- colamd_report()
- symamd_report()

## Source

Header file: [`COLAMD/Include/colamd.h`](/browser/?library=SuiteSparse&file=COLAMD/Include/colamd.h)

