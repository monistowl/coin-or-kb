+++
title = "CoinUtils"
description = "Layer 0 - Foundation utilities for COIN-OR solvers"
template = "library.html"
sort_by = "title"

[extra]
layer = 0
+++

CoinUtils provides the fundamental building blocks used by all COIN-OR optimization libraries:

- **Sparse Matrix Classes**: Efficient storage and operations for large, sparse matrices
- **Factorization**: LU decomposition with Markowitz pivoting for basis matrices
- **I/O Utilities**: MPS and LP file format reading/writing
- **Memory Management**: Custom allocators and array handling
- **Presolve**: Problem simplification and reduction techniques

## Key Classes

The most important classes include:

- `CoinFactorization` - Sparse LU factorization with Forrest-Tomlin updates
- `CoinPackedMatrix` - Column-major sparse matrix storage
- `CoinIndexedVector` - Sparse vector with fast access patterns
- `CoinMpsIO` - MPS file parser and writer
