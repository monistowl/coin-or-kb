+++
title = "drop_empty_cols_action"
description = "Physically removes empty columns in presolve, and reinserts empty columns in postsolve."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveEmpty.hpp"
api_url = "/api/coinutils/drop_empty_cols_action.json"
+++

Physically removes empty columns in presolve, and reinserts empty columns in postsolve.


## Inheritance

Inherits from: `CoinPresolveAction`

## Description

Physical removal of rows and columns should be the last activities performed during presolve. Do them exactly once. The row-major matrix is not maintained by this transform.
To physically drop the columns, CoinPrePostsolveMatrix::mcstrt_ and CoinPrePostsolveMatrix::hincol_ are compressed, along with column bounds, objective, and (if present) the column portions of the solution. This renumbers the columns. drop_empty_cols_action::presolve will reconstruct CoinPresolveMatrix::clink_.
TodoConfirm correct behaviour with solution in presolve.

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

### `~drop_empty_cols_action`

```cpp
 ~drop_empty_cols_action()
```

### `presolve`

```cpp
const CoinPresolveAction * presolve(CoinPresolveMatrix * , const int * ecols, int necols, const CoinPresolveAction * )
```

**Parameters:**

- `` (CoinPresolveMatrix *)
- `ecols` (const int *)
- `necols` (int)
- `` (const CoinPresolveAction *)

### `presolve`

```cpp
const CoinPresolveAction * presolve(CoinPresolveMatrix * prob, const CoinPresolveAction * next)
```

**Parameters:**

- `prob` (CoinPresolveMatrix *)
- `next` (const CoinPresolveAction *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveEmpty.hpp`
