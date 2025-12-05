+++
title = "CoinWarmStartVector"
description = "WarmStart information that is only a vector."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartVector.hpp"
api_url = "/api/coinutils/CoinWarmStartVector.json"
+++

WarmStart information that is only a vector.


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

return the size of the vector

```cpp
int size()
```

### `values`

return a pointer to the array of vectors

```cpp
const T * values()
```

### `assignVector`

Assign the vector to be the warmstart information.

```cpp
void assignVector(int size, T *& vec)
```

**Parameters:**

- `size` (int)
- `vec` (T *&)

### `CoinWarmStartVector`

```cpp
 CoinWarmStartVector()
```

### `CoinWarmStartVector`

```cpp
 CoinWarmStartVector(int size, const T * vec)
```

**Parameters:**

- `size` (int)
- `vec` (const T *)

### `CoinWarmStartVector`

```cpp
 CoinWarmStartVector(const CoinWarmStartVector & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartVector &)

### `operator=`

```cpp
CoinWarmStartVector & operator=(const CoinWarmStartVector & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartVector &)

### `swap`

```cpp
void swap(CoinWarmStartVector & rhs)
```

**Parameters:**

- `rhs` (CoinWarmStartVector &)

### `clone`

Virtual constructor

```cpp
CoinWarmStart * clone()
```

### `~CoinWarmStartVector`

```cpp
 ~CoinWarmStartVector()
```

### `clear`

Clear the data.

```cpp
void clear()
```

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartVector.hpp`
