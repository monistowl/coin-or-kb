+++
title = "CoinBronKerbosch"
description = "Class responsible for finding cliques with weights greater than a certain threshold."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinBronKerbosch.hpp"
api_url = "/api/coinutils/CoinBronKerbosch.json"
+++

Class responsible for finding cliques with weights greater than a certain threshold.


## Description

It implements the Bron-Kerbosch Algorithm.

## Public Methods

### `CoinBronKerbosch`

Default constructor.

```cpp
 CoinBronKerbosch(const CoinConflictGraph * cgraph, const double * weights, PivotingStrategy pivotingStrategy)
```

**Parameters:**

- `cgraph` (const CoinConflictGraph *) - conflict graph
- `weights` (const double *) - array containing the weights for each vertex
- `pivotingStrategy` (PivotingStrategy) - pivoting strategy used in BK algorithm.

### `~CoinBronKerbosch`

Destructor.

```cpp
 ~CoinBronKerbosch()
```

### `findCliques`

Perform BK algorithm for finding cliques with weights greater than a certain threshold.

```cpp
void findCliques()
```

### `nCliques`

Return the number of cliques found by BK algorithm.

```cpp
size_t nCliques()
```

### `getClique`

Return the i-th clique found by BK algorithm.

```cpp
const size_t * getClique(const size_t i)
```

**Parameters:**

- `i` (const size_t)

### `getCliqueSize`

Return the size of the i-th clique found by BK algorithm.

```cpp
size_t getCliqueSize(const size_t i)
```

**Parameters:**

- `i` (const size_t)

### `getCliqueWeight`

Return the weight of the i-th clique found by BK algorithm.

```cpp
double getCliqueWeight(const size_t i)
```

**Parameters:**

- `i` (const size_t)

### `setMinWeight`

Set the minimum weight that a clique must have to be detected and stored by BK algorithm.

```cpp
void setMinWeight(double minWeight)
```

**Parameters:**

- `minWeight` (double)

### `setMaxCalls`

Set the maximum number of recursive calls of BK algorithm.

```cpp
void setMaxCalls(size_t maxCalls)
```

**Parameters:**

- `maxCalls` (size_t)

### `completedSearch`

Return true if BK algorithm ran completely, without stopping by the maximum number of recursive calls.

```cpp
bool completedSearch()
```

### `numCalls`

Return the number of calls made by BK algorithm.

```cpp
size_t numCalls()
```

## Source

Header: `layer-0/CoinUtils/src/CoinBronKerbosch.hpp`
