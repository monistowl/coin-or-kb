+++
title = "CoinIntArrayWithLength"
description = "int * version"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinIntArrayWithLength.json"
+++

int * version

<div class="api-link"><a href="/api/coinutils/CoinIntArrayWithLength.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinArrayWithLength`

## Public Methods

### `getSize`

Get the size.

```cpp
CoinBigIndex getSize()
```

### `array`

Get Array.

```cpp
int * array()
```

### `setSize`

Set the size.

```cpp
void setSize(CoinByteArray value)
```

**Parameters:**

- `value` (CoinByteArray)

### `conditionalNew`

Conditionally gets new array.

```cpp
int * conditionalNew(CoinByteArray sizeWanted)
```

**Parameters:**

- `sizeWanted` (CoinByteArray)

### `CoinIntArrayWithLength`

Default constructor - NULL.

```cpp
 CoinIntArrayWithLength()
```

### `CoinIntArrayWithLength`

Alternate Constructor - length in bytes - size_ -1.

```cpp
 CoinIntArrayWithLength(CoinByteArray size)
```

**Parameters:**

- `size` (CoinByteArray)

### `CoinIntArrayWithLength`

Alternate Constructor - length in bytes mode - 0 size_ set to size 1 size_ set to size and zeroed.

```cpp
 CoinIntArrayWithLength(CoinByteArray size, int mode)
```

**Parameters:**

- `size` (CoinByteArray)
- `mode` (int)

### `CoinIntArrayWithLength`

Copy constructor.

```cpp
 CoinIntArrayWithLength(const CoinIntArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinIntArrayWithLength &)

### `CoinIntArrayWithLength`

Copy constructor.2.

```cpp
 CoinIntArrayWithLength(const CoinIntArrayWithLength * rhs)
```

**Parameters:**

- `rhs` (const CoinIntArrayWithLength *)

### `operator=`

Assignment operator.

```cpp
CoinIntArrayWithLength & operator=(const CoinIntArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinIntArrayWithLength &)

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
