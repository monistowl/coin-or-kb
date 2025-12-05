+++
title = "CoinWarmStartDualDiff"
description = "A diff between two CoinWarmStartDual objects."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartDual.hpp"
api_url = "/api/coinutils/CoinWarmStartDualDiff.json"
+++

A diff between two CoinWarmStartDual objects.


## Inheritance

Inherits from: `CoinWarmStartDiff`

## Description

This class exists in order to hide from the world the details of calculating and representing a diff between two CoinWarmStartDual objects. For convenience, assignment, cloning, and deletion are visible to the world, and default and copy constructors are made available to derived classes. Knowledge of the rest of this structure, and of generating and applying diffs, is restricted to the friend functions CoinWarmStartDual::generateDiff() and CoinWarmStartDual::applyDiff().
The actual data structure is a pair of vectors, #diffNdxs_ and #diffVals_.

## Public Methods

### `clone`

Virtual constructor

```cpp
CoinWarmStartDiff * clone()
```

### `operator=`

Assignment.

```cpp
CoinWarmStartDualDiff & operator=(const CoinWarmStartDualDiff & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartDualDiff &)

### `~CoinWarmStartDualDiff`

Destructor.

```cpp
 ~CoinWarmStartDualDiff()
```

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartDual.hpp`
