+++
title = "CoinFirstLess_3"
description = "Function operator."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSort.hpp"
api_url = "/api/coinutils/CoinFirstLess_3.json"
+++

Function operator.

<div class="api-link"><a href="/api/coinutils/CoinFirstLess_3.json">JSON API</a></div>

## Description

Returns true if t1.first < t2.first (i.e., increasing).

## Public Methods

### `operator()`

Compare function.

```cpp
bool operator()(const CoinTriple< S, T, U > & t1, const CoinTriple< S, T, U > & t2)
```

**Parameters:**

- `t1` (const CoinTriple< S, T, U > &)
- `t2` (const CoinTriple< S, T, U > &)

## Source

Header: `layer-0/CoinUtils/src/CoinSort.hpp`
