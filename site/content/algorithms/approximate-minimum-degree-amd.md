+++
title = "Approximate Minimum Degree (AMD)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Repeatedly eliminates the node with minimum approximate external degree:
  1. Select pivot i with minimum approximate degree d̃(i)
  2. Form element e from eliminated node and merge with adjacent elements
  3. Update approximate degrees for remaining nodes
  4. Apply aggressive absorption: absorb element e into element f if
     adj(e) ⊆ adj(f), even when f is not adjacent to current pivot

## Mathematical Formulation

<div class="math-block">

Approximate external degree:
  d̃(i) ≈ |adj(i) ∪ (∪ adj(e) : e ∈ elements adjacent to i)| - |absorbed|
  The true minimum degree would require d(i) = |L_{*i}| - 1 (column count
  in Cholesky factor), but this is expensive to compute exactly.

</div>

## Complexity

Time: O(nnz(A)·α(n)) average case with aggressive absorption,
  where α is the inverse Ackermann function. Worst case O(n·nnz).
  Space: O(nnz(A) + n) for the quotient graph representation.

## Implementations

### SuiteSparse

- **[amd.h](/coin-or-kb/browser/?library=SuiteSparse)** - Approximate Minimum Degree ordering for sparse matrix factorization

AMD computes a fill-reducing permutation P for sparse Cholesky or LU
factorization. Given a symmetric matrix A (or A+A' if A is unsymmetric),
AMD finds P such that P*A*P' has fewer nonzeros in its Cholesky factor
than A would.

## References

- Amestoy, Davis, Duff (1996). "An Approximate Minimum Degree Ordering
     Algorithm". SIAM J. Matrix Analysis and Applications 17(4):886-905.
- George, Liu (1989). "The Evolution of the Minimum Degree Ordering
     Algorithm". SIAM Review 31(1):1-19.

Key features:
- Aggressive absorption for better approximate degrees
- Dense row/column detection and deferral
- Post-ordering of the elimination tree
- Both int32_t and int64_t versions available
