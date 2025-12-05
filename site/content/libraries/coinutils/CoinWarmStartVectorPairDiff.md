+++
title = "CoinWarmStartVectorPairDiff"
description = "CoinWarmStartVectorPairDiff class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartVector.hpp"
api_url = "/api/coinutils/CoinWarmStartVectorPairDiff.json"
+++


## Inheritance

Inherits from: `CoinWarmStartDiff`

## Public Methods

### `CoinWarmStartVectorPairDiff`

```cpp
 CoinWarmStartVectorPairDiff()
```

### `CoinWarmStartVectorPairDiff`

```cpp
 CoinWarmStartVectorPairDiff(const CoinWarmStartVectorPairDiff< T, U > & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartVectorPairDiff< T, U > &)

### `~CoinWarmStartVectorPairDiff`

```cpp
 ~CoinWarmStartVectorPairDiff()
```

### `operator=`

```cpp
CoinWarmStartVectorPairDiff & operator=(const CoinWarmStartVectorPairDiff< T, U > & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartVectorPairDiff< T, U > &)

### `clone`

Create a deep copy of this diff object.

```cpp
CoinWarmStartDiff * clone()
```

**Returns:** Pointer to newly allocated copy (caller owns memory)

### `swap`

```cpp
void swap(CoinWarmStartVectorPairDiff< T, U > & rhs)
```

**Parameters:**

- `rhs` (CoinWarmStartVectorPairDiff< T, U > &)

### `clear`

```cpp
void clear()
```

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartVector.hpp`
