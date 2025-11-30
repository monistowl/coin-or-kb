+++
title = "CoinFileIOBase"
description = "Base class for FileIO classes."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinFileIO.hpp"
api_url = "/api/coinutils/CoinFileIOBase.json"
+++

Base class for FileIO classes.

<div class="api-link"><a href="/api/coinutils/CoinFileIOBase.json">JSON API</a></div>

Derived classes: `CoinFileInput`, `CoinFileOutput`

## Public Methods

### `CoinFileIOBase`

Constructor.

```cpp
 CoinFileIOBase(const std::string & fileName)
```

**Parameters:**

- `fileName` (const std::string &) - The name of the file used by this object.

### `~CoinFileIOBase`

Destructor.

```cpp
 ~CoinFileIOBase()
```

### `getFileName`

Return the name of the file used by this object.

```cpp
const char * getFileName()
```

### `getReadType`

Return the method of reading being used.

```cpp
std::string getReadType()
```

## Source

Header: `layer-0/CoinUtils/src/CoinFileIO.hpp`
