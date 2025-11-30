+++
title = "CoinMessage"
description = "The standard set of Coin messages."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinMessage.hpp"
api_url = "/api/coinutils/CoinMessage.json"
+++

The standard set of Coin messages.

<div class="api-link"><a href="/api/coinutils/CoinMessage.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinMessages`

## Description

This class provides convenient access to the standard set of Coin messages. In a nutshell, it's a CoinMessages object with a constructor that preloads the standard Coin messages.

## Public Methods

### `CoinMessage`

Constructor.

```cpp
 CoinMessage(Language language)
```

**Parameters:**

- `language` (Language)

## Source

Header: `layer-0/CoinUtils/src/CoinMessage.hpp`
