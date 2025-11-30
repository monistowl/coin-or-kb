+++
title = "Function Pointer Dispatch (scatterStruct)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Precomputed table of specialized ScatterUpdate{1..8,4N} functions
  avoids branch misprediction in small-column cases.

## Complexity

O(nnz) per scatter/gather operation
  With SIMD: ~4x speedup on vectorizable sections
  With Cilk: ~Kx speedup on K cores for large columns

## Implementations

### Clp

- **[CoinAbcHelperFunctions.hpp](/coin-or-kb/browser/?library=Clp)** - SIMD-optimized scatter/gather operations for ABC factorization

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
