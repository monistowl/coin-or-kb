+++
title = "CoinCliqueExtender"
description = "A class to extend cliques."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinCliqueExtender.hpp"
api_url = "/api/coinutils/CoinCliqueExtender.json"
+++

A class to extend cliques.

<div class="api-link"><a href="/api/coinutils/CoinCliqueExtender.json">JSON API</a></div>

## Description

It stores the cliques extended in a clique list.

## Public Methods

### `CoinCliqueExtender`

Default constructor.

```cpp
 CoinCliqueExtender(const CoinConflictGraph * cgraph, size_t extMethod = 4, const double * rc = NULL, const double maxRC = 100.0)
```

**Parameters:**

- `cgraph` (const CoinConflictGraph *) - conflict graph
- `extMethod` (size_t) - method used to extend cliques (optional). Values: 0 = no extension; 1 = random; 2 = max degree; 3 = max modified degree; 4 = reduced cost (inversely proportional); 5 = reduced cost (inversely proportional) + modified degree.
- `rc` (const double *) - reduced cost (optional)
- `maxRC` (const double)

### `~CoinCliqueExtender`

Destructor.

```cpp
 ~CoinCliqueExtender()
```

### `extendClique`

Try to extend a clique.

```cpp
bool extendClique(const size_t * clqIdxs, const size_t clqSize)
```

**Parameters:**

- `clqIdxs` (const size_t *) - indexes of the clique to be extended
- `clqSize` (const size_t) - size of the clique to be extended

### `nCliques`

Return the number of cliques stored in the list of cliques extended.

```cpp
size_t nCliques()
```

### `getClique`

Return the i-th clique extended.

```cpp
const size_t * getClique(const size_t i)
```

**Parameters:**

- `i` (const size_t)

### `getCliqueSize`

Return the size of the i-th clique extended.

```cpp
size_t getCliqueSize(const size_t i)
```

**Parameters:**

- `i` (const size_t)

### `setMaxCandidates`

Set the maximum number of candidates to enter a clique.

```cpp
void setMaxCandidates(const size_t maxCandidates)
```

**Parameters:**

- `maxCandidates` (const size_t)

## Source

Header: `layer-0/CoinUtils/src/CoinCliqueExtender.hpp`
