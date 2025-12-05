+++
title = "CoinExternalVectorFirstLess_2"
description = "Function operator."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSort.hpp"
api_url = "/api/coinutils/CoinExternalVectorFirstLess_2.json"
+++

Function operator.


## Description

Compare based on the entries of an external vector, i.e., returns true if vec[t1.first < vec[t2.first] (i.e., increasing wrt. vec). Note that to use this comparison operator .first must be a data type automatically convertible to int.

## Public Methods

### `operator()`

```cpp
bool operator()(const CoinPair< S, T > & t1, const CoinPair< S, T > & t2)
```

**Parameters:**

- `t1` (const CoinPair< S, T > &)
- `t2` (const CoinPair< S, T > &)

### `CoinExternalVectorFirstLess_2`

```cpp
 CoinExternalVectorFirstLess_2(const V * v)
```

**Parameters:**

- `v` (const V *)

## Source

Header: `layer-0/CoinUtils/src/CoinSort.hpp`
