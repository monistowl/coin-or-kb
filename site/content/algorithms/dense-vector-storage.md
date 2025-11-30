+++
title = "Dense Vector Storage"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Data Structures"
implementation_count = 1
+++

Contiguous array of size n: elements_[0..n-1]
  All positions allocated, O(1) random access
  Element-wise operations: v3 = v1 + v2 applies to all indices

  Supported operations: +, -, *, / (element-wise)
  Norms: oneNorm (L1), twoNorm (L2/Euclidean), infNorm (L∞/max)

## Mathematical Formulation

<div class="math-block">

Dense storage: x[i] stored for all i ∈ {0,...,n-1}
  oneNorm = Σ|x_i|, twoNorm = √(Σx_i²), infNorm = max|x_i|

</div>

## Complexity

Element access: O(1)
  Vector operations: O(n)
  Space: O(n) always, regardless of sparsity

## Implementations

### CoinUtils

- **[CoinDenseVector.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Dense vector template with element-wise arithmetic operations

CoinDenseVector<T> stores all elements in a contiguous array.
Unlike sparse vectors, every position has storage. Supports
arithmetic operators (+, -, *, /) with other dense vectors.
