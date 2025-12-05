+++
title = "CoinCut"
description = "Class for representing a cut."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinCutPool.hpp"
api_url = "/api/coinutils/CoinCut.json"
+++

Class for representing a cut.


## Public Methods

### `CoinCut`

Default constructor.

```cpp
 CoinCut(const int * idxs, const double * coefs, size_t nz, double rhs)
```

**Parameters:**

- `idxs` (const int *) - indexes of variables of the cut
- `coefs` (const double *) - coefficients of the variables the cut
- `nz` (size_t) - size of the cut
- `rhs` (double) - right-hand side of the cut

### `~CoinCut`

Destructor.

```cpp
 ~CoinCut()
```

### `idxs`

Return the indexes of the variables of the cut.

```cpp
const int * idxs()
```

### `coefs`

Return the coefficients of the variables of the cut.

```cpp
const double * coefs()
```

### `size`

Return the size of the cut.

```cpp
int size()
```

### `rhs`

Return the right-hand side of the cut.

```cpp
double rhs()
```

### `dominates`

Check if the cut dominates another one.

```cpp
bool dominates(const CoinCut * other)
```

**Parameters:**

- `other` (const CoinCut *) - cut to be checked.

## Source

Header: `layer-0/CoinUtils/src/CoinCutPool.hpp`
