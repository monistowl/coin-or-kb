+++
title = "CoinSearchTreeCompareDepth"
description = "Depth First Search."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSearchTree.hpp"
api_url = "/api/coinutils/CoinSearchTreeCompareDepth.json"
+++

Depth First Search.

<div class="api-link"><a href="/api/coinutils/CoinSearchTreeCompareDepth.json">JSON API</a></div>

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
