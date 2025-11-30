+++
title = "CoinExternalVectorFirstGreater_2"
description = "Function operator."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSort.hpp"
api_url = "/api/coinutils/CoinExternalVectorFirstGreater_2.json"
+++

Function operator.

<div class="api-link"><a href="/api/coinutils/CoinExternalVectorFirstGreater_2.json">JSON API</a></div>

## Description

Compare based on the entries of an external vector, i.e., returns true if vec[t1.first > vec[t2.first] (i.e., decreasing wrt. vec). Note that to use this comparison operator .first must be a data type automatically convertible to int.

## Public Methods

### `operator()`

```cpp
bool operator()(const CoinPair< S, T > & t1, const CoinPair< S, T > & t2)
```

**Parameters:**

- `t1` (const CoinPair< S, T > &)
- `t2` (const CoinPair< S, T > &)

### `CoinExternalVectorFirstGreater_2`

```cpp
 CoinExternalVectorFirstGreater_2(const V * v)
```

**Parameters:**

- `v` (const V *)

## Source

Header: `layer-0/CoinUtils/src/CoinSort.hpp`
