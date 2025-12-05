+++
title = "CoinSearchTreeManager"
description = "CoinSearchTreeManager class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSearchTree.hpp"
api_url = "/api/coinutils/CoinSearchTreeManager.json"
+++


## Public Methods

### `CoinSearchTreeManager`

```cpp
 CoinSearchTreeManager()
```

### `~CoinSearchTreeManager`

```cpp
 ~CoinSearchTreeManager()
```

### `setTree`

```cpp
void setTree(CoinSearchTreeBase * t)
```

**Parameters:**

- `t` (CoinSearchTreeBase *)

### `getTree`

```cpp
CoinSearchTreeBase * getTree()
```

### `empty`

```cpp
bool empty()
```

### `size`

```cpp
size_t size()
```

### `numInserted`

```cpp
size_t numInserted()
```

### `top`

```cpp
CoinTreeNode * top()
```

### `pop`

```cpp
void pop()
```

### `push`

```cpp
void push(CoinTreeNode * node, const bool incrInserted = true)
```

**Parameters:**

- `node` (CoinTreeNode *)
- `incrInserted` (const bool)

### `push`

```cpp
void push(const CoinTreeSiblings & s, const bool incrInserted = true)
```

**Parameters:**

- `s` (const CoinTreeSiblings &)
- `incrInserted` (const bool)

### `push`

```cpp
void push(const int n, CoinTreeNode ** nodes, const bool incrInserted = true)
```

**Parameters:**

- `n` (const int)
- `nodes` (CoinTreeNode **)
- `incrInserted` (const bool)

### `bestQualityCandidate`

```cpp
CoinTreeNode * bestQualityCandidate()
```

### `bestQuality`

```cpp
double bestQuality()
```

### `newSolution`

```cpp
void newSolution(double solValue)
```

**Parameters:**

- `solValue` (double)

### `reevaluateSearchStrategy`

```cpp
void reevaluateSearchStrategy()
```

## Source

Header: `layer-0/CoinUtils/src/CoinSearchTree.hpp`
