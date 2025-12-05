+++
title = "CoinWarmStartVectorDiff"
description = "A diff between two CoinWarmStartVector objects."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartVector.hpp"
api_url = "/api/coinutils/CoinWarmStartVectorDiff.json"
+++

A diff between two CoinWarmStartVector objects.


## Inheritance

Inherits from: `CoinWarmStartDiff`

## Description

This class exists in order to hide from the world the details of calculating and representing a diff between two CoinWarmStartVector objects. For convenience, assignment, cloning, and deletion are visible to the world, and default and copy constructors are made available to derived classes. Knowledge of the rest of this structure, and of generating and applying diffs, is restricted to the friend functions CoinWarmStartVector::generateDiff() and CoinWarmStartVector::applyDiff().
The actual data structure is a pair of vectors, diffNdxs_ and diffVals_.

## Public Methods

### `clone`

Virtual constructor

```cpp
CoinWarmStartDiff * clone()
```

### `operator=`

Assignment.

```cpp
CoinWarmStartVectorDiff & operator=(const CoinWarmStartVectorDiff< T > & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartVectorDiff< T > &)

### `~CoinWarmStartVectorDiff`

Destructor.

```cpp
 ~CoinWarmStartVectorDiff()
```

### `swap`

```cpp
void swap(CoinWarmStartVectorDiff & rhs)
```

**Parameters:**

- `rhs` (CoinWarmStartVectorDiff &)

### `CoinWarmStartVectorDiff`

Default constructor.

```cpp
 CoinWarmStartVectorDiff()
```

### `CoinWarmStartVectorDiff`

Copy constructor.

```cpp
 CoinWarmStartVectorDiff(const CoinWarmStartVectorDiff< T > & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartVectorDiff< T > &)

### `CoinWarmStartVectorDiff`

Standard constructor.

```cpp
 CoinWarmStartVectorDiff(int sze, const unsigned int *const diffNdxs, const T *const diffVals)
```

**Parameters:**

- `sze` (int)
- `diffNdxs` (const unsigned int *const)
- `diffVals` (const T *const)

### `clear`

Clear the data.

```cpp
void clear()
```

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartVector.hpp`
