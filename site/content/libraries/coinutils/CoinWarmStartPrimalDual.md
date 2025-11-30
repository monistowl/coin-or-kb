+++
title = "CoinWarmStartPrimalDual"
description = "WarmStart information that is only a dual vector."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartPrimalDual.hpp"
api_url = "/api/coinutils/CoinWarmStartPrimalDual.json"
+++

WarmStart information that is only a dual vector.

<div class="api-link"><a href="/api/coinutils/CoinWarmStartPrimalDual.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinWarmStart`

## Public Methods

### `generateDiff`

Generate a diff that can convert the warm start passed as a parameter to the warm start specified by `this`.

```cpp
CoinWarmStartDiff * generateDiff(const CoinWarmStart *const oldCWS)
```

**Parameters:**

- `oldCWS` (const CoinWarmStart *const)

### `applyDiff`

Apply `diff` to this warm start.

```cpp
void applyDiff(const CoinWarmStartDiff *const cwsdDiff)
```

**Parameters:**

- `cwsdDiff` (const CoinWarmStartDiff *const)

### `dualSize`

return the size of the dual vector

```cpp
int dualSize()
```

### `dual`

return a pointer to the array of duals

```cpp
const double * dual()
```

### `primalSize`

return the size of the primal vector

```cpp
int primalSize()
```

### `primal`

return a pointer to the array of primals

```cpp
const double * primal()
```

### `assign`

Assign the primal/dual vectors to be the warmstart information.

```cpp
void assign(int primalSize, int dualSize, double *& primal, double *& dual)
```

**Parameters:**

- `primalSize` (int)
- `dualSize` (int)
- `primal` (double *&)
- `dual` (double *&)

### `CoinWarmStartPrimalDual`

```cpp
 CoinWarmStartPrimalDual()
```

### `CoinWarmStartPrimalDual`

```cpp
 CoinWarmStartPrimalDual(int primalSize, int dualSize, const double * primal, const double * dual)
```

**Parameters:**

- `primalSize` (int)
- `dualSize` (int)
- `primal` (const double *)
- `dual` (const double *)

### `CoinWarmStartPrimalDual`

```cpp
 CoinWarmStartPrimalDual(const CoinWarmStartPrimalDual & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartPrimalDual &)

### `operator=`

```cpp
CoinWarmStartPrimalDual & operator=(const CoinWarmStartPrimalDual & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartPrimalDual &)

### `clear`

Clear the data.

```cpp
void clear()
```

### `swap`

```cpp
void swap(CoinWarmStartPrimalDual & rhs)
```

**Parameters:**

- `rhs` (CoinWarmStartPrimalDual &)

### `clone`

Virtual constructor

```cpp
CoinWarmStart * clone()
```

### `~CoinWarmStartPrimalDual`

```cpp
 ~CoinWarmStartPrimalDual()
```

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartPrimalDual.hpp`
