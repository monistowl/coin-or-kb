+++
title = "Duff's device - Tom Duff's loop unrolling technique that uses switch"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

statement fall-through to handle remainder elements, reducing loop
           overhead from O(n) branches to O(n/8) branches.

## Complexity

Summary of major functions:
            - CoinCopyN, CoinDisjointCopyN, CoinFillN, CoinZeroN: O(n)
            - CoinIsSorted: O(n)
            - CoinIotaN: O(n)
            - CoinDeleteEntriesFromArray: O(n + k log k) where k = deletions
            - CoinDrand48: O(1) per call

## Implementations

### CoinUtils

- **[CoinHelperFunctions.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Low-level utility functions for array manipulation, copying, and comparison

Provides optimized template functions for common array operations used throughout
COIN-OR: copying (with Duff's device optimization), filling, zeroing, sorting checks,
iota generation, and element deletion. Also includes random number generation and
file I/O utilities.

Many functions offer ~2x speedup over naive loops via loop unrolling and
Duff's device techniques.

## References

- Duff, T. (1983). "Duff's Device" - Usenet comp.lang.c posting.
     Originally for copying to memory-mapped display registers.
