+++
title = "CoinWarmStartDiff"
description = "Abstract base class for warm start diff objects."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStart.hpp"
api_url = "/api/coinutils/CoinWarmStartDiff.json"
+++

Abstract base class for warm start diff objects.

<div class="api-link"><a href="/api/coinutils/CoinWarmStartDiff.json">JSON API</a></div>

Derived classes: `CoinWarmStartVectorDiff< double >`, `CoinWarmStartVectorDiff< U >`, `CoinWarmStartBasisDiff`, `CoinWarmStartDualDiff`, `CoinWarmStartPrimalDualDiff`, `CoinWarmStartVectorDiff< T >`, `CoinWarmStartVectorPairDiff< T, U >`

## Description

Represents the difference between two warm start states. Used for efficient incremental updates when the warm start changes only slightly between solves (common in branch-and-bound or sensitivity analysis).

## Public Methods

### `~CoinWarmStartDiff`

Virtual destructor for proper cleanup of derived classes.

```cpp
 ~CoinWarmStartDiff()
```

### `clone`

Create a deep copy of this diff object.

```cpp
CoinWarmStartDiff * clone()
```

**Returns:** Pointer to newly allocated copy (caller owns memory)

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStart.hpp`
