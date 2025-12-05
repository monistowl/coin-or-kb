+++
title = "drop_zero_coefficients_action"
description = "Removal of explicit zeros."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveZeros.hpp"
api_url = "/api/coinutils/drop_zero_coefficients_action.json"
+++

Removal of explicit zeros.


## Inheritance

Inherits from: `CoinPresolveAction`

## Description

The presolve action for this class removes explicit zeros from the constraint matrix. The postsolve action puts them back.

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

### `~drop_zero_coefficients_action`

```cpp
 ~drop_zero_coefficients_action()
```

### `presolve`

```cpp
const CoinPresolveAction * presolve(CoinPresolveMatrix * prob, int * checkcols, int ncheckcols, const CoinPresolveAction * next)
```

**Parameters:**

- `prob` (CoinPresolveMatrix *)
- `checkcols` (int *)
- `ncheckcols` (int)
- `next` (const CoinPresolveAction *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveZeros.hpp`
