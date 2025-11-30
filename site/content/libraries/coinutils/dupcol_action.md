+++
title = "dupcol_action"
description = "Detect and remove duplicate columns."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveDupcol.hpp"
api_url = "/api/coinutils/dupcol_action.json"
+++

Detect and remove duplicate columns.

<div class="api-link"><a href="/api/coinutils/dupcol_action.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinPresolveAction`

## Description

The general technique is to sum the coefficients a_(*,j) of each column. Columns with identical sums are duplicates. The obvious problem is that, e.g., [1 0 1 0] and [0 1 0 1] both add to 2. To minimize the chances of false positives, the coefficients of each row are multipled by a random number r_i, so that we sum r_i*a_ij.
Candidate columns are checked to confirm they are identical. Where the columns have the same objective coefficient, the two are combined. If the columns have different objective coefficients, complications ensue. In order to remove the duplicate, it must be possible to fix the variable at a bound.

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

### `~dupcol_action`

```cpp
 ~dupcol_action()
```

### `presolve`

```cpp
const CoinPresolveAction * presolve(CoinPresolveMatrix * prob, const CoinPresolveAction * next)
```

**Parameters:**

- `prob` (CoinPresolveMatrix *)
- `next` (const CoinPresolveAction *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveDupcol.hpp`
