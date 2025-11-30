+++
title = "CoinCutPool"
description = "Class for storing a pool of cuts, removing the repeated and dominated ones."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinCutPool.hpp"
api_url = "/api/coinutils/CoinCutPool.json"
+++

Class for storing a pool of cuts, removing the repeated and dominated ones.

<div class="api-link"><a href="/api/coinutils/CoinCutPool.json">JSON API</a></div>

## Description

It also filters the cuts according to their scores.

## Public Methods

### `CoinCutPool`

Default constructor.

```cpp
 CoinCutPool(const double * x, int numCols)
```

**Parameters:**

- `x` (const double *) - current solution of the LP relaxation of the MILP.
- `numCols` (int) - number of variables of the MILP.

### `~CoinCutPool`

Destructor.

```cpp
 ~CoinCutPool()
```

### `numCuts`

Return the number of cuts in the pool.

```cpp
size_t numCuts()
```

### `cutIdxs`

Return the indexes of the variables of the i-th cut in the pool.

```cpp
const int * cutIdxs(size_t i)
```

**Parameters:**

- `i` (size_t)

### `cutCoefs`

Return the coefficients of the variables of the i-th cut in the pool.

```cpp
const double * cutCoefs(size_t i)
```

**Parameters:**

- `i` (size_t)

### `cutSize`

Return the size of the i-th cut in the pool.

```cpp
int cutSize(size_t i)
```

**Parameters:**

- `i` (size_t)

### `cutRHS`

Return the right-hand side of the i-th cut in the pool.

```cpp
double cutRHS(size_t i)
```

**Parameters:**

- `i` (size_t)

### `add`

Try to add a cut in the pool.

```cpp
bool add(const int * idxs, const double * coefs, int nz, double rhs)
```

**Parameters:**

- `idxs` (const int *) - indexes of the variables of the cut to be added.
- `coefs` (const double *) - coefficients of the variables of the cut to be added.
- `nz` (int) - size of the cut to be added
- `rhs` (double) - right-hand side of the cut to be added

### `removeDominated`

Remove dominated cuts.

```cpp
void removeDominated()
```

### `removeNullCuts`

Remove cuts that are previous deleted.

```cpp
void removeNullCuts()
```

## Source

Header: `layer-0/CoinUtils/src/CoinCutPool.hpp`
