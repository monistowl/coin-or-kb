+++
title = "CoinExternalVectorFirstLess_3"
description = "Function operator."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSort.hpp"
api_url = "/api/coinutils/CoinExternalVectorFirstLess_3.json"
+++

Function operator.


## Description

Compare based on the entries of an external vector, i.e., returns true if vec[t1.first < vec[t2.first] (i.e., increasing wrt. vec). Note that to use this comparison operator .first must be a data type automatically convertible to int.

## Public Methods

### `operator()`

```cpp
bool operator()(const CoinTriple< S, T, U > & t1, const CoinTriple< S, T, U > & t2)
```

**Parameters:**

- `t1` (const CoinTriple< S, T, U > &)
- `t2` (const CoinTriple< S, T, U > &)

### `CoinExternalVectorFirstLess_3`

```cpp
 CoinExternalVectorFirstLess_3(const V * v)
```

**Parameters:**

- `v` (const V *)

## Source

Header: `layer-0/CoinUtils/src/CoinSort.hpp`
