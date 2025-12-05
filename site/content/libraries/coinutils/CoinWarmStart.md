+++
title = "CoinWarmStart"
description = "Abstract base class for warm start information."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStart.hpp"
api_url = "/api/coinutils/CoinWarmStart.json"
+++

Abstract base class for warm start information.


Derived classes: `CoinWarmStartVector< double >`, `CoinWarmStartVector< U >`, `CoinWarmStartBasis`, `CoinWarmStartDual`, `CoinWarmStartPrimalDual`, `CoinWarmStartVector< T >`, `CoinWarmStartVectorPair< T, U >`

## Description

Provides the interface for warm start objects that store solver state enabling faster re-optimization. Derived classes implement solver-specific storage (e.g., variable/constraint basis status for simplex methods).
The class supports a diff mechanism for efficient incremental updates:generateDiff() computes changes from another warm startapplyDiff() applies a diff to update this warm start

## Public Methods

### `~CoinWarmStart`

Virtual destructor for proper cleanup of derived classes.

```cpp
 ~CoinWarmStart()
```

### `clone`

Create a deep copy of this warm start object.

```cpp
CoinWarmStart * clone()
```

**Returns:** Pointer to newly allocated copy (caller owns memory)

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

Header: `layer-0/CoinUtils/src/CoinWarmStart.hpp`
