+++
title = "CoinStaticConflictGraph"
description = "Static conflict graph, optimized for memory usage and query speed, not modifiable."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinStaticConflictGraph.hpp"
api_url = "/api/coinutils/CoinStaticConflictGraph.json"
+++

Static conflict graph, optimized for memory usage and query speed, not modifiable.

<div class="api-link"><a href="/api/coinutils/CoinStaticConflictGraph.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinConflictGraph`

## Public Methods

### `CoinStaticConflictGraph`

Default constructor.

```cpp
 CoinStaticConflictGraph(const CoinConflictGraph * cgraph)
```

**Parameters:**

- `cgraph` (const CoinConflictGraph *)

### `CoinStaticConflictGraph`

Default constructor.

```cpp
 CoinStaticConflictGraph(const int numCols, const char * colType, const double * colLB, const double * colUB, const CoinPackedMatrix * matrixByRow, const char * sense, const double * rowRHS, const double * rowRange)
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

### `clone`

Clone a conflict graph.

```cpp
CoinStaticConflictGraph * clone()
```

### `CoinStaticConflictGraph`

Constructor to create an induced subgraph.

```cpp
 CoinStaticConflictGraph(const CoinConflictGraph * cgraph, const size_t n, const size_t elements)
```

**Parameters:**

- `cgraph` (const CoinConflictGraph *) - conflict graph
- `n` (const size_t) - number of elements in the induced subgraph
- `elements` (const size_t) - indexes of nodes in the induced subgraph

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

degree of a given node

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

### `~CoinStaticConflictGraph`

Destructor.

```cpp
 ~CoinStaticConflictGraph()
```

### `updatedBounds`

Recommended tighter bounds for some variables.

```cpp
const std::vector< std::pair< size_t, std::pair< double, double > > > & updatedBounds()
```

**Returns:** a vector of updated bounds with the format (idx, (lb, ub))

## Source

Header: `layer-0/CoinUtils/src/CoinStaticConflictGraph.hpp`
