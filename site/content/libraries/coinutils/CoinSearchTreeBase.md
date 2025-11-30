+++
title = "CoinSearchTreeBase"
description = "CoinSearchTreeBase class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSearchTree.hpp"
api_url = "/api/coinutils/CoinSearchTreeBase.json"
+++

<div class="api-link"><a href="/api/coinutils/CoinSearchTreeBase.json">JSON API</a></div>

Derived classes: `CoinSearchTree< Comp >`

## Public Methods

### `~CoinSearchTreeBase`

```cpp
 ~CoinSearchTreeBase()
```

### `compName`

```cpp
const char * compName()
```

### `getCandidates`

```cpp
const std::vector< CoinTreeSiblings * > & getCandidates()
```

### `empty`

```cpp
bool empty()
```

### `size`

```cpp
int size()
```

### `numInserted`

```cpp
int numInserted()
```

### `top`

```cpp
CoinTreeNode * top()
```

### `pop`

pop will advance the `next` pointer among the siblings on the top and then moves the top to its correct position.

```cpp
void pop()
```

### `push`

```cpp
void push(int numNodes, CoinTreeNode ** nodes, const bool incrInserted = true)
```

**Parameters:**

- `numNodes` (int)
- `nodes` (CoinTreeNode **)
- `incrInserted` (const bool)

### `push`

```cpp
void push(const CoinTreeSiblings & sib, const bool incrInserted = true)
```

**Parameters:**

- `sib` (const CoinTreeSiblings &)
- `incrInserted` (const bool)

## Source

Header: `layer-0/CoinUtils/src/CoinSearchTree.hpp`
