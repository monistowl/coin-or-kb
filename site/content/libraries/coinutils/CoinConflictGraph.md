+++
title = "CoinConflictGraph"
description = "Base class for Conflict Graph: a conflict graph is a structure that stores conflicts between binary variables."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinConflictGraph.hpp"
api_url = "/api/coinutils/CoinConflictGraph.json"
+++

Base class for Conflict Graph: a conflict graph is a structure that stores conflicts between binary variables.


Derived classes: `CoinDynamicConflictGraph`, `CoinStaticConflictGraph`

## Description

These conflicts can involve the original problem variables or complementary variables.

## Public Methods

### `CoinConflictGraph`

```cpp
 CoinConflictGraph()
```

### `CoinConflictGraph`

Default constructor.

```cpp
 CoinConflictGraph(size_t _size)
```

**Parameters:**

- `_size` (size_t)

### `CoinConflictGraph`

Default constructor.

```cpp
 CoinConflictGraph(const CoinConflictGraph * other)
```

**Parameters:**

- `other` (const CoinConflictGraph *) - conflict graph to be copied

### `~CoinConflictGraph`

Destructor.

```cpp
 ~CoinConflictGraph()
```

### `conflicting`

Checks for conflicts between two nodes.

```cpp
bool conflicting(size_t n1, size_t n2)
```

**Parameters:**

- `n1` (size_t) - node index
- `n2` (size_t) - node index

**Returns:** true if there is an edge between n1 and n2 in the conflict graph, 0 otherwise.

### `conflictingNodes`

Queries all nodes conflicting with a given node.

```cpp
std::pair< size_t, const size_t * > conflictingNodes(size_t node, size_t * temp, char * iv)
```

**Parameters:**

- `node` (size_t) - node index
- `temp` (size_t *) - temporary storage area for storing conflicts, should have space for all elements in the graph (size())
- `iv` (char *) - auxiliary incidence array used to eliminate duplicates. It should have the size of the graph (size()) and all elements shoud be initialized as false.

**Returns:** pair containing (number of conflicting nodes, array of conflicting nodes), the array may be a pointer to temp if the temporary storage area was used or a pointer to an array in the conflict graph itself.

### `density`

Density of the conflict graph: (nConflicts / maxConflicts)

```cpp
double density()
```

### `size`

Number of nodes in the conflict graph.

```cpp
size_t size()
```

### `degree`

Degree of a given node.

```cpp
size_t degree(const size_t node)
```

**Parameters:**

- `node` (const size_t)

### `modifiedDegree`

Modified degree of a given node.

```cpp
size_t modifiedDegree(const size_t node)
```

**Parameters:**

- `node` (const size_t)

### `minDegree`

Minimum node degree.

```cpp
size_t minDegree()
```

### `maxDegree`

Maximum node degree.

```cpp
size_t maxDegree()
```

### `nCliques`

Number of cliques stored explicitly.

```cpp
size_t nCliques()
```

### `cliqueSize`

Size of the i-th clique stored explicitly.

```cpp
size_t cliqueSize(size_t idxClique)
```

**Parameters:**

- `idxClique` (size_t)

### `cliqueElements`

Contents of the i-th clique stored explicitly.

```cpp
const size_t * cliqueElements(size_t idxClique)
```

**Parameters:**

- `idxClique` (size_t)

### `nNodeCliques`

Return how many explicit cliques a node appears.

```cpp
size_t nNodeCliques(size_t idxClique)
```

**Parameters:**

- `idxClique` (size_t)

### `nodeCliques`

Return which cliques a node appears.

```cpp
const size_t * nodeCliques(size_t idxClique)
```

**Parameters:**

- `idxClique` (size_t)

### `nDirectConflicts`

Return the number of pairwise conflicts stored for a node.

```cpp
size_t nDirectConflicts(size_t idxNode)
```

**Parameters:**

- `idxNode` (size_t)

### `directConflicts`

List of pairwise conflicts (not stored as cliques) for a node.

```cpp
const size_t * directConflicts(size_t idxNode)
```

**Parameters:**

- `idxNode` (size_t)

### `recomputeDegree`

Recompute the degree of each node of the graph.

```cpp
void recomputeDegree()
```

### `computeModifiedDegree`

Recompute the modified degree of each node of the graph.

```cpp
void computeModifiedDegree()
```

### `nTotalDirectConflicts`

Total number of conflicts stored directly.

```cpp
size_t nTotalDirectConflicts()
```

### `nTotalCliqueElements`

Total number of clique elements stored.

```cpp
size_t nTotalCliqueElements()
```

### `printSummary`

Print summarized information about the conflict graph.

```cpp
void printSummary()
```

### `setMinCliqueRow`

Set the the minimum size of a clique to be explicitly stored as a clique (not pairwise).

```cpp
void setMinCliqueRow(size_t minClqRow)
```

**Parameters:**

- `minClqRow` (size_t)

### `getMinCliqueRow`

Return the the minimum size of a clique to be explicitly stored as a clique (not pairwise).

```cpp
size_t getMinCliqueRow()
```

## Source

Header: `layer-0/CoinUtils/src/CoinConflictGraph.hpp`
