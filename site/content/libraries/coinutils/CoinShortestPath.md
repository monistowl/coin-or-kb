+++
title = "CoinShortestPath"
description = "Class that implements Dijkstra's algorithm for finding the shortest paths between nodes in a graph."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinShortestPath.hpp"
api_url = "/api/coinutils/CoinShortestPath.json"
+++

Class that implements Dijkstra's algorithm for finding the shortest paths between nodes in a graph.

<div class="api-link"><a href="/api/coinutils/CoinShortestPath.json">JSON API</a></div>

## Public Methods

### `CoinShortestPath`

Default constructor.

```cpp
 CoinShortestPath(size_t nodes, size_t arcs, const size_t * arcStart, const size_t * toNode, const double * dist)
```

**Parameters:**

- `nodes` (size_t) - number of nodes in the graph
- `arcs` (size_t) - number of arcs in the graph
- `arcStart` (const size_t *) - array containing the start position of the neighbors of each node
- `toNode` (const size_t *) - array containing the neighbors of all nodes
- `dist` (const double *) - array containing the distance between each node and its neighbors.

### `~CoinShortestPath`

Destructor.

```cpp
 ~CoinShortestPath()
```

### `find`

Execute the shortest path finder using Dijkstra's algorithm.

```cpp
void find(const size_t origin)
```

**Parameters:**

- `origin` (const size_t)

### `find`

Execute the shortest path finder using the Dijkstra algorithm.

```cpp
void find(const size_t origin, const size_t destination)
```

**Parameters:**

- `origin` (const size_t)
- `destination` (const size_t)

### `path`

Fill array indexes with all previous nodes which should be steped to arrive at a given node (this node is not included).

```cpp
size_t path(size_t toNode, size_t * indexes)
```

**Parameters:**

- `toNode` (size_t)
- `indexes` (size_t *)

### `numNodes`

Return the number of nodes in the graph.

```cpp
size_t numNodes()
```

### `numArcs`

Return the number of arcs in the graph.

```cpp
size_t numArcs()
```

### `distance`

Return the length of the shortest path from the origin node (passed in method find) to node.

```cpp
double distance(size_t node)
```

**Parameters:**

- `node` (size_t)

### `previous`

Return the previous node of a given node in the shortest path.

```cpp
size_t previous(size_t node)
```

**Parameters:**

- `node` (size_t)

### `previous`

Return an array containing the previous nodes which should be steped to arrive at a given node.

```cpp
const size_t * previous()
```

## Source

Header: `layer-0/CoinUtils/src/CoinShortestPath.hpp`
