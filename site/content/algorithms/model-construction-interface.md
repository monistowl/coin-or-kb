+++
title = "Model Construction Interface"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Three building modes:
  1. Row-by-row: addRow(indices, values, lb, ub)
  2. Column-by-column: addCol(indices, values, lb, ub, obj)
  3. Element-by-element: setElement(row, col, value)

  Name handling: hash tables for row/column name lookup
  Expression parsing: "2 x1 + 3 x2 <= 5" string syntax

## Complexity

Insertion: O(1) amortized with dynamic arrays
  Name lookup: O(1) expected with hash tables
  Conversion to CoinPackedMatrix: O(nnz)

## Implementations

### CoinUtils

- **[CoinModel.hpp](/coin-or-kb/browser/?library=CoinUtils)** - High-level model building with string names and expressions

CoinModel provides a flexible interface for constructing LP/MIP models.
Supports row/column names, string-based expressions, and incremental
building. Convert to CoinPackedMatrix for solver use.
