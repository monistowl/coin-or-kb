+++
title = "CoinWarmStartBasisDiff"
description = "A diff between two CoinWarmStartBasis objects."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartBasis.hpp"
api_url = "/api/coinutils/CoinWarmStartBasisDiff.json"
+++

A diff between two CoinWarmStartBasis objects.

<div class="api-link"><a href="/api/coinutils/CoinWarmStartBasisDiff.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinWarmStartDiff`

## Description

This class exists in order to hide from the world the details of calculating and representing a diff between two CoinWarmStartBasis objects. For convenience, assignment, cloning, and deletion are visible to the world, and default and copy constructors are made available to derived classes. Knowledge of the rest of this structure, and of generating and applying diffs, is restricted to the friend functions CoinWarmStartBasis::generateDiff() and CoinWarmStartBasis::applyDiff().
The actual data structure is an unsigned int vector, difference_ which starts with indices of changed and then has values starting after sze_
TodoThis is a pretty generic structure, and vector diff is a pretty generic activity. We should be able to convert this to a template.
TodoUsing unsigned int as the data type for the diff vectors might help to contain the damage when this code is inevitably compiled for 64 bit architectures. But the notion of int as 4 bytes is hardwired into CoinWarmStartBasis, so changes are definitely required.

## Public Methods

### `clone`

Virtual constructor

```cpp
CoinWarmStartDiff * clone()
```

### `operator=`

Assignment.

```cpp
CoinWarmStartBasisDiff & operator=(const CoinWarmStartBasisDiff & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartBasisDiff &)

### `~CoinWarmStartBasisDiff`

Destructor.

```cpp
 ~CoinWarmStartBasisDiff()
```

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartBasis.hpp`
