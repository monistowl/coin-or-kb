+++
title = "CoinFirstAbsGreater_3"
description = "Function operator."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSort.hpp"
api_url = "/api/coinutils/CoinFirstAbsGreater_3.json"
+++

Function operator.


## Description

Returns true if abs(t1.first) > abs(t2.first) (i.e., decreasing).

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
