+++
title = "CoinDynamicConflictGraph"
description = "This a a conflict graph where conflicts can be added on the fly, not optimized for memory usage."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinDynamicConflictGraph.hpp"
api_url = "/api/coinutils/CoinDynamicConflictGraph.json"
+++

This a a conflict graph where conflicts can be added on the fly, not optimized for memory usage.

<div class="api-link"><a href="/api/coinutils/CoinDynamicConflictGraph.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinConflictGraph`

## Public Methods

### `CoinDynamicConflictGraph`

Default constructor.

```cpp
 CoinDynamicConflictGraph(size_t _size)
```

**Parameters:**

- `_size` (size_t) - number of vertices of the conflict graph

### `CoinDynamicConflictGraph`

Creates a conflict graph from a MILP.

```cpp
 CoinDynamicConflictGraph(const int numCols, const char * colType, const double * colLB, const double * colUB, const CoinPackedMatrix * matrixByRow, const char * sense, const double * rowRHS, const double * rowRange)
```

**Parameters:**

- `numCols` (const int) - number of variables
- `colType` (const char *) - column types
- `colLB` (const double *) - column lower bounds
- `colUB` (const double *) - column upper bounds
- `matrixByRow` (const CoinPackedMatrix *) - row-wise constraint matrix
- `sense` (const char *) - row sense
- `rowRHS` (const double *) - row right hand side
- `rowRange` (const double *) - row ranges

### `~CoinDynamicConflictGraph`

Destructor.

```cpp
 ~CoinDynamicConflictGraph()
```

### `addNodeConflicts`

Add conflicts to a node to be stored directly (not as cliques).

```cpp
void addNodeConflicts(const size_t node, const size_t nodeConflicts, const size_t nConflicts)
```

**Parameters:**

- `node` (const size_t) - index
- `nodeConflicts` (const size_t) - conflicts to be added
- `nConflicts` (const size_t) - number of conflicts to be added

### `addClique`

Add a clique (it will be stored explicitly as a clique).

```cpp
void addClique(size_t size, const size_t elements)
```

**Parameters:**

- `size` (size_t)
- `elements` (const size_t)

### `nCliques`

Return the number of cliques stored explicitly.

```cpp
size_t nCliques()
```

### `cliqueElements`

Return the contents of the i-th clique stored explicitly.

```cpp
const size_t * cliqueElements(size_t idxClique)
```

**Parameters:**

- `idxClique` (size_t)

### `cliqueSize`

Return the size of the i-th clique stored explicitly.

```cpp
size_t cliqueSize(size_t idxClique)
```

**Parameters:**

- `idxClique` (size_t)

### `nNodeCliques`

Return how many explicit cliques a node appears.

```cpp
size_t nNodeCliques(size_t idxNode)
```

**Parameters:**

- `idxNode` (size_t)

### `nodeCliques`

Return which cliques a node appears.

```cpp
const size_t * nodeCliques(size_t idxNode)
```

**Parameters:**

- `idxNode` (size_t)

### `degree`

Return the degree of a given node.

```cpp
size_t degree(const size_t node)
```

**Parameters:**

- `node` (const size_t)

### `modifiedDegree`

Return the modified degree of a given node.

```cpp
size_t modifiedDegree(const size_t node)
```

**Parameters:**

- `node` (const size_t)

### `nTotalCliqueElements`

Total number of clique elements stored.

```cpp
size_t nTotalCliqueElements()
```

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

### `nTotalDirectConflicts`

Total number of conflicts stored directly.

```cpp
size_t nTotalDirectConflicts()
```

### `addCliqueAsNormalConflicts`

Add a clique as pairwise conflicts.

```cpp
void addCliqueAsNormalConflicts(const size_t idxs, const size_t len)
```

**Parameters:**

- `idxs` (const size_t)
- `len` (const size_t)

### `updatedBounds`

Recommended tighter bounds for some variables.

```cpp
const std::vector< std::pair< size_t, std::pair< double, double > > > & updatedBounds()
```

**Returns:** a vector of updated bounds with the format (idx, (lb, ub))

### `printInfo`

Print information about the conflict graph.

```cpp
void printInfo()
```

## Source

Header: `layer-0/CoinUtils/src/CoinDynamicConflictGraph.hpp`
