+++
title = "ABC (Alternative Basis Code) LU Factorization"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Matrix Factorization"
implementation_count = 1
+++

Enhanced sparse LU with modern CPU optimizations:
  1. Markowitz pivot selection with singleton detection
  2. SIMD-vectorized scatter/gather for column updates
  3. Cache-blocking (BLOCKING8) for L2/L3 efficiency
  4. Parallel elimination using Cilk (when ABC_PARALLEL=2)
  5. Hyper-sparse mode for very sparse intermediate results

## Mathematical Formulation

<div class="math-block">

B = L·U with row/column permutations P, Q:
  P·B·Q = L·U, where L unit lower triangular, U upper triangular
  Markowitz criterion: select pivot minimizing (r_i - 1)(c_j - 1)

Note: 32 bits assumed sufficient for row/column counts,
but CoinBigIndex can be 64-bit for element indices.

</div>

## Complexity

Factorization: O(nnz × fill-in), highly structure-dependent
  FTRAN/BTRAN: O(nnz(L) + nnz(U)) with SIMD acceleration
  SIMD speedup: 2-4x for dense column operations

## Implementations

### Clp

- **[CoinAbcBaseFactorization.hpp](/browser/?library=Clp)** - Core ABC SIMD-optimized LU factorization implementation
