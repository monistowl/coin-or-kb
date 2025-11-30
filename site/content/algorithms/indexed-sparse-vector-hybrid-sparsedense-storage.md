+++
title = "Indexed sparse vector - hybrid sparse/dense storage"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Data Structures"
implementation_count = 1
+++

## Mathematical Formulation

<div class="math-block">

Storage for n-dimensional vector with k nonzeros:
      - elements[n]: dense array storing values (zeros at unused positions)
      - indices[k]: list of positions with nonzero values
      Random access: elements[i] gives value directly
      Sparse iteration: for j in indices, access elements[indices[j]]

</div>

## Complexity

Element access: O(1) via dense array
            Sparse iteration: O(k) where k = number of nonzeros
            Insert: O(1) amortized
            Clear: O(k) - must zero out nonzero positions in dense array

@note Does NOT support negative indices or duplicate checking

## Implementations

### CoinUtils

- **[CoinIndexedVector.hpp](/browser/?library=CoinUtils)** - Sparse vector with dense backing array for O(1) element access

CoinIndexedVector combines sparse index storage with a dense values array,
enabling O(1) random access while tracking which positions are non-zero.
Designed for simplex operations where sparse updates need fast access.
Has optional "packed" mode that behaves more like CoinPackedVector.
