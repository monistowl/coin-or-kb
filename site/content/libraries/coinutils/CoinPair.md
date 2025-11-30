+++
title = "CoinPair"
description = "An ordered pair."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSort.hpp"
api_url = "/api/coinutils/CoinPair.json"
+++

An ordered pair.

<div class="api-link"><a href="/api/coinutils/CoinPair.json">JSON API</a></div>

## Description

It's the same as std::pair, just this way it'll have the same look as the triple sorting.

## Public Methods

### `CoinPair`

Construct from ordered pair.

```cpp
 CoinPair(const S & s, const T & t)
```

**Parameters:**

- `s` (const S &)
- `t` (const T &)

## Source

Header: `layer-0/CoinUtils/src/CoinSort.hpp`
