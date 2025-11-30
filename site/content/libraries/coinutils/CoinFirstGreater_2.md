+++
title = "CoinFirstGreater_2"
description = "Function operator."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSort.hpp"
api_url = "/api/coinutils/CoinFirstGreater_2.json"
+++

Function operator.

<div class="api-link"><a href="/api/coinutils/CoinFirstGreater_2.json">JSON API</a></div>

## Description

Returns true if t1.first > t2.first (i.e, decreasing).

## Public Methods

### `operator()`

Compare function.

```cpp
bool operator()(const CoinPair< S, T > & t1, const CoinPair< S, T > & t2)
```

**Parameters:**

- `t1` (const CoinPair< S, T > &)
- `t2` (const CoinPair< S, T > &)

## Source

Header: `layer-0/CoinUtils/src/CoinSort.hpp`
