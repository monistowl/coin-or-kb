+++
title = "CoinWarmStartVectorPair"
description = "CoinWarmStartVectorPair class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartVector.hpp"
api_url = "/api/coinutils/CoinWarmStartVectorPair.json"
+++


## Inheritance

Inherits from: `CoinWarmStart`

## Public Methods

### `size0`

```cpp
int size0()
```

### `size1`

```cpp
int size1()
```

### `values0`

```cpp
const T * values0()
```

### `values1`

```cpp
const U * values1()
```

### `assignVector0`

```cpp
void assignVector0(int size, T *& vec)
```

**Parameters:**

- `size` (int)
- `vec` (T *&)

### `assignVector1`

```cpp
void assignVector1(int size, U *& vec)
```

**Parameters:**

- `size` (int)
- `vec` (U *&)

### `CoinWarmStartVectorPair`

```cpp
 CoinWarmStartVectorPair()
```

### `CoinWarmStartVectorPair`

```cpp
 CoinWarmStartVectorPair(int s0, const T * v0, int s1, const U * v1)
```

**Parameters:**

- `s0` (int)
- `v0` (const T *)
- `s1` (int)
- `v1` (const U *)

### `CoinWarmStartVectorPair`

```cpp
 CoinWarmStartVectorPair(const CoinWarmStartVectorPair< T, U > & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartVectorPair< T, U > &)

### `operator=`

```cpp
CoinWarmStartVectorPair & operator=(const CoinWarmStartVectorPair< T, U > & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartVectorPair< T, U > &)

### `swap`

```cpp
void swap(CoinWarmStartVectorPair< T, U > & rhs)
```

**Parameters:**

- `rhs` (CoinWarmStartVectorPair< T, U > &)

### `clone`

Create a deep copy of this warm start object.

```cpp
CoinWarmStart * clone()
```

**Returns:** Pointer to newly allocated copy (caller owns memory)

### `~CoinWarmStartVectorPair`

```cpp
 ~CoinWarmStartVectorPair()
```

### `clear`

```cpp
void clear()
```

### `generateDiff`

Generate a diff representing changes from another warm start.

```cpp
CoinWarmStartDiff * generateDiff(const CoinWarmStart *const oldWarmStart)
```

**Parameters:**

- `oldWarmStart` (const CoinWarmStart *const) - The baseline warm start to compare against

**Returns:** Pointer to diff object (caller owns memory), or nullptr if not supported

### `applyDiff`

Apply a diff to update this warm start.

```cpp
void applyDiff(const CoinWarmStartDiff *const diff)
```

**Parameters:**

- `diff` (const CoinWarmStartDiff *const) - The diff to apply

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartVector.hpp`
