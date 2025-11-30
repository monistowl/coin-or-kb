+++
title = "CoinWarmStartPrimalDualDiff"
description = "A diff between two CoinWarmStartPrimalDual objects."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartPrimalDual.hpp"
api_url = "/api/coinutils/CoinWarmStartPrimalDualDiff.json"
+++

A diff between two CoinWarmStartPrimalDual objects.

<div class="api-link"><a href="/api/coinutils/CoinWarmStartPrimalDualDiff.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinWarmStartDiff`

## Description

This class exists in order to hide from the world the details of calculating and representing a diff between two CoinWarmStartPrimalDual objects. For convenience, assignment, cloning, and deletion are visible to the world, and default and copy constructors are made available to derived classes. Knowledge of the rest of this structure, and of generating and applying diffs, is restricted to the friend functions CoinWarmStartPrimalDual::generateDiff() and CoinWarmStartPrimalDual::applyDiff().
The actual data structure is a pair of vectors, #diffNdxs_ and #diffVals_.

## Public Methods

### `clone`

Virtual constructor. To be used when retaining polymorphism is important

```cpp
CoinWarmStartDiff * clone()
```

### `~CoinWarmStartPrimalDualDiff`

Destructor.

```cpp
 ~CoinWarmStartPrimalDualDiff()
```

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartPrimalDual.hpp`
