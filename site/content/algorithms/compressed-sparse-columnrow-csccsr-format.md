+++
title = "Compressed Sparse Column/Row (CSC/CSR) format"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Data Structures"
implementation_count = 1
+++

## Mathematical Formulation

<div class="math-block">

Storage arrays for m×n matrix with nnz nonzeros:
      - elements[nnz]: coefficient values
      - indices[nnz]: minor indices (row indices for CSC, column for CSR)
      - starts[major+1]: start position of each major vector
      Memory: O(nnz + major) vs O(m·n) for dense

</div>

## Complexity

Major vector access: O(1) to get start, O(nnz_j) to iterate
            Minor vector access: O(nnz) full scan required
            Matrix-vector multiply: O(nnz)

@note Column-major (CSC) is standard for LP constraint matrices since
      simplex primarily accesses columns (entering variables).

## Implementations

### CoinUtils

- **[CoinPackedMatrix.hpp](/browser/?library=CoinUtils)** - Sparse matrix stored in compressed row or column format

CoinPackedMatrix represents a sparse matrix using compressed storage.
Can be stored row-major or column-major. Efficient for major-dimension
operations (accessing rows in row-major, columns in column-major).
