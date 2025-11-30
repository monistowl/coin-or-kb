+++
title = "Hyper-sparse Computation"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Data Structures"
implementation_count = 1
+++

Exploits sparsity in FTRAN/BTRAN when < 10% of elements nonzero.
  Uses specialized scatter/gather for cache efficiency.

## Complexity

Per-iteration: O(nnz(B^{-1}·v)) for FTRAN/BTRAN
  Hyper-sparse: O(nnz(result)) when exploiting sparsity
  Parallelization: independent FTRAN/BTRAN across columns

## Implementations

### HiGHS

- **[HEkk.h](/coin-or-kb/browser/?library=HiGHS)** - Edinburgh simplex kernel - high-performance LP solver core

HEkk (Edinburgh Kernel) is the main simplex implementation in HiGHS,
supporting both dual and primal simplex methods.

**HEkk Class:**
Central simplex solver managing LP data, basis, and solve state:
- solve(): Run simplex algorithm (auto-selects dual/primal)
- setBasis(): Initialize from HighsBasis
- getSolution(): Extract primal/dual solution

**Key Components:**
- lp_: The LP being solved (may be scaled/dualized copy)
- basis_: SimplexBasis with basic variable indices and status
- simplex_nla_: Numeric linear algebra (factorization)
- dual_edge_weight_: Steepest edge or Devex weights

**Simplex Operations:**
- btran/ftran: Backward/forward transformation with basis
- pivotColumnFtran: Compute pivot column for ratio test
- unitBtran: Compute row of B^{-1}

**Transformations:**
- dualize/undualize: Convert LP to/from dual form
- permute/unpermute: Reorder LP for efficiency

**Parallelism:**
- chooseSimplexStrategyThreads(): Configure parallel strategy

## References

- Huangfu, Q. and Hall, J.A.J. (2018). "Parallelizing the dual revised
  simplex method". Math. Prog. Computation 10:119-142.
- Hall, J.A.J. and McKinnon, K.I.M. (2005). "Hyper-sparsity in the
  revised simplex method and how to exploit it". Comp. Opt. Appl. 32:259-283.
