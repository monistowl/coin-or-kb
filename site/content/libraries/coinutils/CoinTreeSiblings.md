+++
title = "CoinTreeSiblings"
description = "CoinTreeSiblings class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSearchTree.hpp"
api_url = "/api/coinutils/CoinTreeSiblings.json"
+++

<div class="api-link"><a href="/api/coinutils/CoinTreeSiblings.json">JSON API</a></div>

## Public Methods

### `CoinTreeSiblings`

```cpp
 CoinTreeSiblings(const int n, CoinTreeNode ** nodes)
```

**Parameters:**

- `n` (const int)
- `nodes` (CoinTreeNode **)

### `CoinTreeSiblings`

```cpp
 CoinTreeSiblings(const CoinTreeSiblings & s)
```

**Parameters:**

- `s` (const CoinTreeSiblings &)

### `~CoinTreeSiblings`

```cpp
 ~CoinTreeSiblings()
```

### `currentNode`

```cpp
CoinTreeNode * currentNode()
```

### `advanceNode`

returns false if cannot be advanced

```cpp
bool advanceNode()
```

### `toProcess`

```cpp
int toProcess()
```

### `size`

```cpp
int size()
```

### `printPref`

```cpp
void printPref()
```

## Source

Header: `layer-0/CoinUtils/src/CoinSearchTree.hpp`
