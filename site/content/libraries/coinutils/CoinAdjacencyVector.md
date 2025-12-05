+++
title = "CoinAdjacencyVector"
description = "A class to store a (growable) list of neighbors for each node in a conflict graph."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinAdjacencyVector.hpp"
api_url = "/api/coinutils/CoinAdjacencyVector.json"
+++

A class to store a (growable) list of neighbors for each node in a conflict graph.


## Public Methods

### `CoinAdjacencyVector`

Default constructor.

```cpp
 CoinAdjacencyVector(size_t _nRows, size_t _iniRowSize)
```

**Parameters:**

- `_nRows` (size_t)
- `_iniRowSize` (size_t)

### `getRow`

Return the contents of a given row.

```cpp
const size_t * getRow(size_t idxRow)
```

**Parameters:**

- `idxRow` (size_t) - row index

### `rowSize`

Return the size of a given row.

```cpp
size_t rowSize(size_t idxRow)
```

**Parameters:**

- `idxRow` (size_t) - row index

### `isNeighbor`

Check if a node is included as neighbor of another node.

```cpp
bool isNeighbor(size_t idxNode, size_t idxNeigh)
```

**Parameters:**

- `idxNode` (size_t) - graph node
- `idxNeigh` (size_t) - neighbor that will be searched

### `addNeighbor`

Add a new neighbor to a node.

```cpp
void addNeighbor(size_t idxNode, size_t idxNeigh, bool addReverse = false)
```

**Parameters:**

- `idxNode` (size_t) - graph node
- `idxNeigh` (size_t) - neighbor that will be added to idxNode
- `addReverse` (bool)

### `fastAddNeighbor`

Add a new neighbor to a node without checking for repeated entries or sorting.

```cpp
void fastAddNeighbor(size_t idxNode, size_t idxNeigh)
```

**Parameters:**

- `idxNode` (size_t) - graph node
- `idxNeigh` (size_t) - neighbor that will be added to idxNode

### `addNeighborsBuffer`

Add elements without checking for repeated entries or sorting later.

```cpp
void addNeighborsBuffer(size_t idxNode, size_t n, const size_t elements)
```

**Parameters:**

- `idxNode` (size_t) - graph node
- `n` (size_t) - number of neighbors that will be added to idxNode
- `elements` (const size_t) - neighbors that will be added to idxNode

### `sort`

Sort all neighbors of all elements.

```cpp
void sort()
```

### `flush`

Sort all neighbors of all elements and remove duplicates.

```cpp
void flush()
```

### `sort`

Sort all neighbors of idxRow.

```cpp
void sort(size_t idxRow)
```

**Parameters:**

- `idxRow` (size_t)

### `~CoinAdjacencyVector`

Destructor.

```cpp
 ~CoinAdjacencyVector()
```

### `totalElements`

Return the total number of elements.

```cpp
size_t totalElements()
```

### `tryAddElementSortedVector`

Try to add an element to a sorted vector, keeping it sorted.

```cpp
bool tryAddElementSortedVector(std::vector< size_t > & el, size_t newEl)
```

**Parameters:**

- `el` (std::vector< size_t > &) - sorted vector
- `newEl` (size_t) - element to be added to the sorted vector

## Source

Header: `layer-0/CoinUtils/src/CoinAdjacencyVector.hpp`
