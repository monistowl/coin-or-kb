+++
title = "CoinCliqueList"
description = "A class to store a sequential list of cliques."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinCliqueList.hpp"
api_url = "/api/coinutils/CoinCliqueList.json"
+++

A class to store a sequential list of cliques.


Derived classes: `CoinCliqueSet`

## Description

Optionally computes occurrence of nodes in cliques.

## Public Methods

### `CoinCliqueList`

Default constructor.

```cpp
 CoinCliqueList(size_t _iniClqCap, size_t _iniClqElCap)
```

**Parameters:**

- `_iniClqCap` (size_t) - initial capacity to store cliques
- `_iniClqElCap` (size_t) - initial capacity of the elements of the cliques

### `~CoinCliqueList`

Destructor.

```cpp
 ~CoinCliqueList()
```

### `addClique`

Insert a clique in the list.

```cpp
void addClique(size_t size, const size_t els)
```

**Parameters:**

- `size` (size_t)
- `els` (const size_t)

### `nCliques`

Return the number of cliques stored in the list.

```cpp
size_t nCliques()
```

### `cliqueSize`

Return the size of a clique.

```cpp
size_t cliqueSize(size_t idxClq)
```

**Parameters:**

- `idxClq` (size_t) - index of a clique.

### `cliqueElements`

Return the elements of a clique.

```cpp
const size_t * cliqueElements(size_t idxClq)
```

**Parameters:**

- `idxClq` (size_t) - index of a clique.

### `totalElements`

Return the total number of elements considering all cliques.

```cpp
size_t totalElements()
```

### `computeNodeOccurrences`

Fill the data structures indicating in which clique each node appears.

```cpp
void computeNodeOccurrences(size_t nNodes)
```

**Parameters:**

- `nNodes` (size_t)

### `nNodeOccurrences`

Return the number of cliques in which a node appears.

```cpp
size_t nNodeOccurrences(size_t idxNode)
```

**Parameters:**

- `idxNode` (size_t) - index of the node

### `nodeOccurrences`

Return the indexes of the cliques in which a node appears.

```cpp
const size_t * nodeOccurrences(size_t idxNode)
```

**Parameters:**

- `idxNode` (size_t) - index of the node

### `nDifferentNodes`

Return the number of different nodes that are stored in the clique list.

```cpp
size_t nDifferentNodes()
```

### `differentNodes`

Return the nodes (without duplicates) that are stored in the clique list.

```cpp
const size_t * differentNodes()
```

## Source

Header: `layer-0/CoinUtils/src/CoinCliqueList.hpp`
