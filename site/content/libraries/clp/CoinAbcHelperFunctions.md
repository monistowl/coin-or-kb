+++
title = "CoinAbcHelperFunctions"
description = "SIMD-optimized scatter/gather operations for ABC factorization"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/CoinAbcHelperFunctions.hpp"
+++

SIMD-optimized scatter/gather operations for ABC factorization

High-performance kernels for sparse matrix operations using:
- Manual loop unrolling (UNROLL_SCATTER, UNROLL_GATHER)
- AVX/AVX2 intrinsics when available
- Cilk parallel loops with configurable grainsize
- Prefetching hints (coin_prefetch macros)

Key operations:
- CoinAbcScatterUpdate: region[index[j]] -= value[j] * pivot
- CoinAbcGatherUpdate: dot product over sparse indices
- Memory utilities: CoinAbcMemcpyLong, CoinAbcMemset0Long

Includes specialized ScatterUpdateN functions for N=1..8 and 4N variants
using function pointer dispatch (scatterStruct) for optimal performance.

## Algorithm

<div class="algorithm-card">

Function Pointer Dispatch (scatterStruct):
  Precomputed table of specialized ScatterUpdate{1..8,4N} functions
  avoids branch misprediction in small-column cases.

**Complexity:** $O(nnz)$ per scatter/gather operation
  With SIMD: ~4x speedup on vectorizable sections
  With Cilk: ~Kx speedup on K cores for large columns

</div>

## See Also

- CoinAbcFactorization which uses these kernels
- [AbcSimplex](@/libraries/clp/AbcSimplex.md) which uses these for FTRAN/BTRAN

## Source

Header file: {{ link(path="/browser/?library=Clp&file=src/CoinAbcHelperFunctions.hpp", text="`src/CoinAbcHelperFunctions.hpp`") }}

