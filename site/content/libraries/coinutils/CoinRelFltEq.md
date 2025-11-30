+++
title = "CoinRelFltEq"
description = "Equality to a scaled (relative) tolerance."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinFloatEqual.hpp"
api_url = "/api/coinutils/CoinRelFltEq.json"
+++

Equality to a scaled (relative) tolerance.

<div class="api-link"><a href="/api/coinutils/CoinRelFltEq.json">JSON API</a></div>

## Description

Operands are considered equal if their difference is within a scaled epsilon calculated as epsilon_*(1+max(|f1|,|f2|)).
This is preferred over absolute tolerance when comparing values that span many orders of magnitude.

## Public Methods

### `CoinRelFltEq`

```cpp
 CoinRelFltEq()
```

### `CoinRelFltEq`

Alternate constructor with epsilon as a parameter.

```cpp
 CoinRelFltEq(const double epsilon)
```

**Parameters:**

- `epsilon` (const double)

### `~CoinRelFltEq`

Destructor.

```cpp
 ~CoinRelFltEq()
```

### `CoinRelFltEq`

Copy constructor.

```cpp
 CoinRelFltEq(const CoinRelFltEq & src)
```

**Parameters:**

- `src` (const CoinRelFltEq &)

### `operator=`

Assignment.

```cpp
CoinRelFltEq & operator=(const CoinRelFltEq & rhs)
```

**Parameters:**

- `rhs` (const CoinRelFltEq &)

### `operator()`

Compare function.

```cpp
bool operator()(const double f1, const double f2)
```

**Parameters:**

- `f1` (const double)
- `f2` (const double)

## Source

Header: `layer-0/CoinUtils/src/CoinFloatEqual.hpp`
