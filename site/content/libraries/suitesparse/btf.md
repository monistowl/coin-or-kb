+++
title = "btf"
description = "Block Triangular Form permutation for sparse matrices"
template = "page.html"

[extra]
layer = 0
library = "SuiteSparse"
header_file = "BTF/Include/btf.h"
+++

Block Triangular Form permutation for sparse matrices

BTF computes permutations to transform a sparse matrix into block upper
triangular form (BTF). This decomposes the matrix into independent blocks
that can be processed separately, improving efficiency for factorization.

Three main routines:
- btf_maxtrans: Maximum transversal (zero-free diagonal matching)
- btf_strongcomp: Strongly connected components (block decomposition)
- btf_order: Combined BTF ordering (calls both above)

## Algorithm

<div class="algorithm-card">

Tarjan's Strongly Connected Components:
  Find permutation P such that P*A*P' is block upper triangular.
  1. Build directed graph: edge i→j if A(i,j) ≠ 0 and i ≠ j
  2. Find SCCs using depth-first search with low-link values
  3. Order SCCs in reverse topological order

<div class="math">

Structural rank: max # nonzeros achievable on diagonal = sprank(A)
If sprank(A) < n, matrix is structurally singular.
$$BTF form: P*A*Q = | B_11  B_12 ... | with square diagonal blocks B_ii$$
|  0   B_22 ... |

</div>

**Complexity:** Maximum transversal: $O(nnz + n)$ time and $O(n)$ space
  SCC decomposition: $O(nnz + n)$ time (single DFS pass)
  Total BTF ordering: $O(nnz + n)$ time and space

<div class="refs">

**References:**
- Duff (1981). "On Algorithms for Obtaining a Maximum Transversal".      ACM Trans. Math. Software 7(3):315-330.
- Tarjan (1972). "Depth-first search and linear graph algorithms".      SIAM J. Computing 1(2):146-160.

</div>

</div>

## See Also

- klu.h for sparse LU factorization using BTF
- btf_order() for combined BTF ordering
- btf_maxtrans()
- btf_order() for combined BTF ordering
- btf_strongcomp()
- btf_maxtrans(), btf_strongcomp()
- btf_order()

## Source

Header file: `BTF/Include/btf.h`

