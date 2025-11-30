+++
title = "CoinAbsFltEq"
description = "Equality to an absolute tolerance."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinFloatEqual.hpp"
api_url = "/api/coinutils/CoinAbsFltEq.json"
+++

Equality to an absolute tolerance.

<div class="api-link"><a href="/api/coinutils/CoinAbsFltEq.json">JSON API</a></div>

## Description

Operands are considered equal if their difference is within an epsilon ; the test does not consider the relative magnitude of the operands.

## Public Methods

### `CoinAbsFltEq`

Default constructor.

```cpp
 CoinAbsFltEq()
```

### `CoinAbsFltEq`

Alternate constructor with epsilon as a parameter.

```cpp
 CoinAbsFltEq(const double epsilon)
```

**Parameters:**

- `epsilon` (const double)

### `~CoinAbsFltEq`

Destructor.

```cpp
 ~CoinAbsFltEq()
```

### `CoinAbsFltEq`

Copy constructor.

```cpp
 CoinAbsFltEq(const CoinAbsFltEq & src)
```

**Parameters:**

- `src` (const CoinAbsFltEq &)

### `operator=`

Assignment.

```cpp
CoinAbsFltEq & operator=(const CoinAbsFltEq & rhs)
```

**Parameters:**

- `rhs` (const CoinAbsFltEq &)

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
