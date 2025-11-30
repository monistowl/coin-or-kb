+++
title = "do_tighten_action"
description = "do_tighten_action class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveTighten.hpp"
api_url = "/api/coinutils/do_tighten_action.json"
+++

<div class="api-link"><a href="/api/coinutils/do_tighten_action.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinPresolveAction`

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

### `~do_tighten_action`

```cpp
 ~do_tighten_action()
```

### `presolve`

```cpp
const CoinPresolveAction * presolve(CoinPresolveMatrix * prob, const CoinPresolveAction * next)
```

**Parameters:**

- `prob` (CoinPresolveMatrix *)
- `next` (const CoinPresolveAction *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveTighten.hpp`
