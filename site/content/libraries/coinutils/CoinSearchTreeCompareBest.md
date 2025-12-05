+++
title = "CoinSearchTreeCompareBest"
description = "Best first search."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSearchTree.hpp"
api_url = "/api/coinutils/CoinSearchTreeCompareBest.json"
+++

Best first search.


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
