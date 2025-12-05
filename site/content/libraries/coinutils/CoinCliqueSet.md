+++
title = "CoinCliqueSet"
description = "CoinCliqueSet class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinCliqueSet.hpp"
api_url = "/api/coinutils/CoinCliqueSet.json"
+++


## Inheritance

Inherits from: `CoinCliqueList`

## Public Methods

### `CoinCliqueSet`

Default constructor.

```cpp
 CoinCliqueSet(size_t _iniClqCap, size_t _iniClqElCap)
```

**Parameters:**

- `_iniClqCap` (size_t) - initial capacity to store cliques
- `_iniClqElCap` (size_t) - initial capacity of the elements of the cliques

### `~CoinCliqueSet`

Destructor.

```cpp
 ~CoinCliqueSet()
```

### `insertIfNotDuplicate`

Try to insert a clique in the set.

```cpp
bool insertIfNotDuplicate(size_t size, const size_t els)
```

**Parameters:**

- `size` (size_t) - size of the clique to be added
- `els` (const size_t) - indexes of the clique to be added

## Source

Header: `layer-0/CoinUtils/src/CoinCliqueSet.hpp`
