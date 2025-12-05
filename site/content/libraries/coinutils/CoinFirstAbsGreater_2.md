+++
title = "CoinFirstAbsGreater_2"
description = "Function operator."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSort.hpp"
api_url = "/api/coinutils/CoinFirstAbsGreater_2.json"
+++

Function operator.


## Description

Returns true if abs(t1.first) > abs(t2.first) (i.e., decreasing).

## Public Methods

### `operator()`

Compare function.

```cpp
bool operator()(CoinPair< S, T > t1, CoinPair< S, T > t2)
```

**Parameters:**

- `t1` (CoinPair< S, T >)
- `t2` (CoinPair< S, T >)

## Source

Header: `layer-0/CoinUtils/src/CoinSort.hpp`
