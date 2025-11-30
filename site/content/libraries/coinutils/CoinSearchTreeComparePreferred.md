+++
title = "CoinSearchTreeComparePreferred"
description = "Function objects to compare search tree nodes."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSearchTree.hpp"
api_url = "/api/coinutils/CoinSearchTreeComparePreferred.json"
+++

Function objects to compare search tree nodes.

<div class="api-link"><a href="/api/coinutils/CoinSearchTreeComparePreferred.json">JSON API</a></div>

## Description

The comparison function must return true if the first argument is "better" than the second one, i.e., it should be processed first. Depth First Search.

## Public Methods

### `name`

```cpp
const char * name()
```

### `operator()`

```cpp
bool operator()(const CoinTreeSiblings * x, const CoinTreeSiblings * y)
```

**Parameters:**

- `x` (const CoinTreeSiblings *)
- `y` (const CoinTreeSiblings *)

## Source

Header: `layer-0/CoinUtils/src/CoinSearchTree.hpp`
