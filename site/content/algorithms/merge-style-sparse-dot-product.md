+++
title = "Merge-style sparse dot product"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Data Structures"
implementation_count = 1
+++

## Mathematical Formulation

<div class="math-block">

Computes x·y = Σ x_i * y_i where x and y share index i
      Uses sorted merge to find common indices in linear time.

</div>

## Complexity

O(k1 + k2) where k1, k2 are the number of nonzeros
@pre Both vectors must be sorted by increasing index

## Implementations

### CoinUtils

- **[CoinPackedVector.hpp](/coin-or-kb/browser/?library=CoinUtils)** - Sparse vector that owns its index/value storage

CoinPackedVector stores a sparse vector as parallel arrays of indices
and values. Unlike CoinShallowPackedVector, this class owns its storage
and supports modification operations.
