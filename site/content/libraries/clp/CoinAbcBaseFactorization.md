+++
title = "CoinAbcBaseFactorization"
description = "Core ABC SIMD-optimized LU factorization implementation"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/CoinAbcBaseFactorization.hpp"
+++

## Algorithm

<div class="algorithm-card">

ABC (Alternative Basis Code) LU Factorization:
  Enhanced sparse LU with modern CPU optimizations:
  1. Markowitz pivot selection with singleton detection
  2. SIMD-vectorized scatter/gather for column updates
  3. Cache-blocking (BLOCKING8) for L2/L3 efficiency
  4. Parallel elimination using Cilk (when ABC_PARALLEL=2)
  5. Hyper-sparse mode for very sparse intermediate results

<div class="math">

B = L·U with row/column permutations P, Q:
  P·B·Q = L·U, where L unit lower triangular, U upper triangular
  Markowitz criterion: select pivot minimizing ($r_{i}$ - 1)($c_{j}$ - 1)

Note: 32 bits assumed sufficient for row/column counts,
but CoinBigIndex can be 64-bit for element indices.

</div>

**Complexity:** Factorization: $O(nnz × fill-in)$, highly structure-dependent
  FTRAN/BTRAN: $O(nnz(L)$ + nnz(U)) with SIMD acceleration
  SIMD speedup: 2-4x for dense column operations

</div>

## See Also

- CoinAbcFactorization.hpp for instantiation
- CoinAbcHelperFunctions.hpp for SIMD kernels

## Source

Header file: `src/CoinAbcBaseFactorization.hpp`

