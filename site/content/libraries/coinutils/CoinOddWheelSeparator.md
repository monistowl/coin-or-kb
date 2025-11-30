+++
title = "CoinOddWheelSeparator"
description = "Class for separating violated odd-cycles."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinOddWheelSeparator.hpp"
api_url = "/api/coinutils/CoinOddWheelSeparator.json"
+++

Class for separating violated odd-cycles.

<div class="api-link"><a href="/api/coinutils/CoinOddWheelSeparator.json">JSON API</a></div>

## Description

It contains a lifting module that tries to transform the odd-cycles into odd-wheels.

## Public Methods

### `CoinOddWheelSeparator`

Default constructor.

```cpp
 CoinOddWheelSeparator(const CoinConflictGraph * cgraph, const double * x, const double * rc, size_t extMethod)
```

**Parameters:**

- `cgraph` (const CoinConflictGraph *) - conflict graph
- `x` (const double *) - current solution of the LP relaxation of the MILP
- `rc` (const double *) - reduced cost of the variables in the LP relaxation of the MILP
- `extMethod` (size_t) - strategy that will be used to lift odd cycles, transforming them into odd wheels: 0 = no lifting, 1 = only one variable as wheel center, 2 = a clique as wheel center.

### `~CoinOddWheelSeparator`

Destructor.

```cpp
 ~CoinOddWheelSeparator()
```

### `searchOddWheels`

Find odd wheels that correspond to violated cuts.

```cpp
void searchOddWheels()
```

### `oddHole`

Return the elements of the i-th odd hole.

```cpp
const size_t * oddHole(size_t idxOH)
```

**Parameters:**

- `idxOH` (size_t)

### `oddHoleSize`

Return the size of the i-th discovered odd hole.

```cpp
size_t oddHoleSize(size_t idxOH)
```

**Parameters:**

- `idxOH` (size_t)

### `oddWheelRHS`

Return the right-hand side of the i-th violated cut.

```cpp
double oddWheelRHS(size_t idxOH)
```

**Parameters:**

- `idxOH` (size_t)

### `numOddWheels`

Return the number of cuts separated.

```cpp
size_t numOddWheels()
```

### `wheelCenter`

The inequality for a discovered odd hole may be extended with the addition of wheel centers.

```cpp
const size_t * wheelCenter(const size_t idxOH)
```

**Parameters:**

- `idxOH` (const size_t)

### `wheelCenterSize`

Return the size of the wheel center found for the i-th discovered odd hole.

```cpp
size_t wheelCenterSize(const size_t idxOH)
```

**Parameters:**

- `idxOH` (const size_t)

## Source

Header: `layer-0/CoinUtils/src/CoinOddWheelSeparator.hpp`
