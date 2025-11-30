+++
title = "CoinWarmStartDual"
description = "WarmStart information that is only a dual vector."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartDual.hpp"
api_url = "/api/coinutils/CoinWarmStartDual.json"
+++

WarmStart information that is only a dual vector.

<div class="api-link"><a href="/api/coinutils/CoinWarmStartDual.json">JSON API</a></div>

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

### `size`

return the size of the dual vector

```cpp
int size()
```

### `dual`

return a pointer to the array of duals

```cpp
const double * dual()
```

### `assignDual`

Assign the dual vector to be the warmstart information.

```cpp
void assignDual(int size, double *& dual)
```

**Parameters:**

- `size` (int)
- `dual` (double *&)

### `CoinWarmStartDual`

```cpp
 CoinWarmStartDual()
```

### `CoinWarmStartDual`

```cpp
 CoinWarmStartDual(int size, const double * dual)
```

**Parameters:**

- `size` (int)
- `dual` (const double *)

### `CoinWarmStartDual`

```cpp
 CoinWarmStartDual(const CoinWarmStartDual & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartDual &)

### `operator=`

```cpp
CoinWarmStartDual & operator=(const CoinWarmStartDual & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartDual &)

### `clone`

Virtual constructor

```cpp
CoinWarmStart * clone()
```

### `~CoinWarmStartDual`

```cpp
 ~CoinWarmStartDual()
```

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartDual.hpp`
