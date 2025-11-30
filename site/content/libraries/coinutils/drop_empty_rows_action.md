+++
title = "drop_empty_rows_action"
description = "Physically removes empty rows in presolve, and reinserts empty rows in postsolve."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveEmpty.hpp"
api_url = "/api/coinutils/drop_empty_rows_action.json"
+++

Physically removes empty rows in presolve, and reinserts empty rows in postsolve.

<div class="api-link"><a href="/api/coinutils/drop_empty_rows_action.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinPresolveAction`

## Description

Physical removal of rows and columns should be the last activities performed during presolve. Do them exactly once. The row-major matrix is not maintained by this transform.
To physically drop the rows, the rows are renumbered, excluding empty rows. This involves rewriting CoinPrePostsolveMatrix::hrow_ and compressing the row bounds and (if present) the row portions of the solution.
TodoConfirm behaviour when a solution is present in presolve.

## Public Methods

### `name`

A name for debug printing.

```cpp
const char * name()
```

### `postsolve`

Apply the postsolve transformation for this particular presolve action.

```cpp
void postsolve(CoinPostsolveMatrix * prob)
```

**Parameters:**

- `prob` (CoinPostsolveMatrix *)

### `~drop_empty_rows_action`

```cpp
 ~drop_empty_rows_action()
```

### `presolve`

```cpp
const CoinPresolveAction * presolve(CoinPresolveMatrix * prob, const CoinPresolveAction * next)
```

**Parameters:**

- `prob` (CoinPresolveMatrix *)
- `next` (const CoinPresolveAction *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveEmpty.hpp`
