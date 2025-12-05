+++
title = "doubleton_action"
description = "Solve ax+by=c for y and substitute y out of the problem."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveDoubleton.hpp"
api_url = "/api/coinutils/doubleton_action.json"
+++

Solve ax+by=c for y and substitute y out of the problem.


## Inheritance

Inherits from: `CoinPresolveAction`

## Description

This moves the bounds information for y onto x, making y free and allowing us to substitute it away. a x + b y = c
     l1 <= x <= u1
     l2 <= y <= u2  ==>
    
     l2 <= (c - a x) / b <= u2
     b/-a > 0 ==> (b l2 - c) / -a <= x <= (b u2 - c) / -a
     b/-a < 0 ==> (b u2 - c) / -a <= x <= (b l2 - c) / -a

## Public Methods

### `name`

A name for debug printing.

```cpp
const char * name()
```

### `postsolve`

Apply the postsolve transformation for this particular presolve action.

```cpp
void postsolve(CoinPostsolveMatrix * prob)
```

**Parameters:**

- `prob` (CoinPostsolveMatrix *)

### `~doubleton_action`

```cpp
 ~doubleton_action()
```

### `presolve`

```cpp
const CoinPresolveAction * presolve(CoinPresolveMatrix * , const CoinPresolveAction * next)
```

**Parameters:**

- `` (CoinPresolveMatrix *)
- `next` (const CoinPresolveAction *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveDoubleton.hpp`
