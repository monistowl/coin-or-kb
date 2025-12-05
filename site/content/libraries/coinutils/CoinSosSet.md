+++
title = "CoinSosSet"
description = "Very simple class for containing SOS set."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinMpsIO.hpp"
api_url = "/api/coinutils/CoinSosSet.json"
+++

Very simple class for containing SOS set.


## Inheritance

Inherits from: `CoinSet`

## Public Methods

### `CoinSosSet`

Constructor.

```cpp
 CoinSosSet(int numberEntries, const int * which, const double * weights, int type)
```

**Parameters:**

- `numberEntries` (int)
- `which` (const int *)
- `weights` (const double *)
- `type` (int)

### `~CoinSosSet`

Destructor.

```cpp
 ~CoinSosSet()
```

## Source

Header: `layer-0/CoinUtils/src/CoinMpsIO.hpp`
