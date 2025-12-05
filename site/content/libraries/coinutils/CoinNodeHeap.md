+++
title = "CoinNodeHeap"
description = "Monotone heap."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinNodeHeap.hpp"
api_url = "/api/coinutils/CoinNodeHeap.json"
+++

Monotone heap.


## Description

Updates MUST always decrease costs.

## Public Methods

### `CoinNodeHeap`

Default Constructor.

```cpp
 CoinNodeHeap(size_t numNodes)
```

**Parameters:**

- `numNodes` (size_t)

### `~CoinNodeHeap`

Destructor.

```cpp
 ~CoinNodeHeap()
```

### `reset`

Reset the values in the heap.

```cpp
void reset()
```

### `update`

Update, always in decreasing order, the cost of a node.

```cpp
void update(size_t node, double cost)
```

**Parameters:**

- `node` (size_t)
- `cost` (double)

### `removeFirst`

Remove the next element, returning its cost.

```cpp
double removeFirst(size_t * node)
```

**Parameters:**

- `node` (size_t *) - used to store the element that was removed

### `isEmpty`

Check if the cost of the nodes are set to infinity.

```cpp
bool isEmpty()
```

## Source

Header: `layer-0/CoinUtils/src/CoinNodeHeap.hpp`
