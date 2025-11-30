+++
title = "CoinFactorizationLongDoubleArrayWithLength"
description = "CoinFactorizationLongDouble * version."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinFactorizationLongDoubleArrayWithLength.json"
+++

CoinFactorizationLongDouble * version.

<div class="api-link"><a href="/api/coinutils/CoinFactorizationLongDoubleArrayWithLength.json">JSON API</a></div>

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
long double * array()
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
long double * conditionalNew(CoinByteArray sizeWanted)
```

**Parameters:**

- `sizeWanted` (CoinByteArray)

### `CoinFactorizationLongDoubleArrayWithLength`

Default constructor - NULL.

```cpp
 CoinFactorizationLongDoubleArrayWithLength()
```

### `CoinFactorizationLongDoubleArrayWithLength`

Alternate Constructor - length in bytes - size_ -1.

```cpp
 CoinFactorizationLongDoubleArrayWithLength(CoinByteArray size)
```

**Parameters:**

- `size` (CoinByteArray)

### `CoinFactorizationLongDoubleArrayWithLength`

Alternate Constructor - length in bytes mode - 0 size_ set to size 1 size_ set to size and zeroed.

```cpp
 CoinFactorizationLongDoubleArrayWithLength(CoinByteArray size, int mode)
```

**Parameters:**

- `size` (CoinByteArray)
- `mode` (int)

### `CoinFactorizationLongDoubleArrayWithLength`

Copy constructor.

```cpp
 CoinFactorizationLongDoubleArrayWithLength(const CoinFactorizationLongDoubleArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinFactorizationLongDoubleArrayWithLength &)

### `CoinFactorizationLongDoubleArrayWithLength`

Copy constructor.2.

```cpp
 CoinFactorizationLongDoubleArrayWithLength(const CoinFactorizationLongDoubleArrayWithLength * rhs)
```

**Parameters:**

- `rhs` (const CoinFactorizationLongDoubleArrayWithLength *)

### `operator=`

Assignment operator.

```cpp
CoinFactorizationLongDoubleArrayWithLength & operator=(const CoinFactorizationLongDoubleArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinFactorizationLongDoubleArrayWithLength &)

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
