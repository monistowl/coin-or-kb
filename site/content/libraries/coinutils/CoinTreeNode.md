+++
title = "CoinTreeNode"
description = "A class from which the real tree nodes should be derived from."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSearchTree.hpp"
api_url = "/api/coinutils/CoinTreeNode.json"
+++

A class from which the real tree nodes should be derived from.

<div class="api-link"><a href="/api/coinutils/CoinTreeNode.json">JSON API</a></div>

## Description

Some of the data that undoubtedly exist in the real tree node is replicated here for fast access. This class is used in the various comparison functions.

## Public Methods

### `~CoinTreeNode`

```cpp
 ~CoinTreeNode()
```

### `getDepth`

```cpp
int getDepth()
```

### `getFractionality`

```cpp
int getFractionality()
```

### `getQuality`

```cpp
double getQuality()
```

### `getTrueLB`

```cpp
double getTrueLB()
```

### `getPreferred`

```cpp
BitVector128 getPreferred()
```

### `setDepth`

```cpp
void setDepth(int d)
```

**Parameters:**

- `d` (int)

### `setFractionality`

```cpp
void setFractionality(int f)
```

**Parameters:**

- `f` (int)

### `setQuality`

```cpp
void setQuality(double q)
```

**Parameters:**

- `q` (double)

### `setTrueLB`

```cpp
void setTrueLB(double tlb)
```

**Parameters:**

- `tlb` (double)

### `setPreferred`

```cpp
void setPreferred(BitVector128 p)
```

**Parameters:**

- `p` (BitVector128)

## Source

Header: `layer-0/CoinUtils/src/CoinSearchTree.hpp`
