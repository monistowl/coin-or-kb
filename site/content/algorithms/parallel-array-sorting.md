+++
title = "Parallel Array Sorting"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Problem: sort array A while permuting arrays B, C, ... identically
  Approach 1 (standard): Create array of tuples, sort, scatter back
  Approach 2 (EKK sort): In-place quicksort carrying parallel arrays

  EKK Quicksort variant (COIN_USE_EKK_SORT):
  1. Check if already sorted (linear scan)
  2. Median-of-three pivot selection
  3. Non-recursive stack-based partitioning
  4. Insertion sort for small subarrays (n ≤ 10)
  Falls back to std::sort for n > 10000

## Complexity

CoinSort_2/3: O(n log n) average, O(n²) worst
  CoinShortSort_2: O(n log n) but optimized for small n
  Space: O(n) for tuple approach, O(log n) stack for EKK

## Implementations

### CoinUtils

- **[CoinSort.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Sorting utilities for pairs, triples, and parallel arrays

Provides CoinPair, CoinTriple, and sort functions for sorting
multiple related arrays together (e.g., indices and values).
