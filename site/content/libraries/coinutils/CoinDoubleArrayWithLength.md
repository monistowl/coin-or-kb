+++
title = "CoinDoubleArrayWithLength"
description = "double * version"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinDoubleArrayWithLength.json"
+++

double * version

<div class="api-link"><a href="/api/coinutils/CoinDoubleArrayWithLength.json">JSON API</a></div>

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
double * array()
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
double * conditionalNew(CoinByteArray sizeWanted)
```

**Parameters:**

- `sizeWanted` (CoinByteArray)

### `CoinDoubleArrayWithLength`

Default constructor - NULL.

```cpp
 CoinDoubleArrayWithLength()
```

### `CoinDoubleArrayWithLength`

Alternate Constructor - length in bytes - size_ -1.

```cpp
 CoinDoubleArrayWithLength(CoinByteArray size)
```

**Parameters:**

- `size` (CoinByteArray)

### `CoinDoubleArrayWithLength`

Alternate Constructor - length in bytes mode - 0 size_ set to size 1 size_ set to size and zeroed.

```cpp
 CoinDoubleArrayWithLength(CoinByteArray size, int mode)
```

**Parameters:**

- `size` (CoinByteArray)
- `mode` (int)

### `CoinDoubleArrayWithLength`

Copy constructor.

```cpp
 CoinDoubleArrayWithLength(const CoinDoubleArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinDoubleArrayWithLength &)

### `CoinDoubleArrayWithLength`

Copy constructor.2.

```cpp
 CoinDoubleArrayWithLength(const CoinDoubleArrayWithLength * rhs)
```

**Parameters:**

- `rhs` (const CoinDoubleArrayWithLength *)

### `operator=`

Assignment operator.

```cpp
CoinDoubleArrayWithLength & operator=(const CoinDoubleArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinDoubleArrayWithLength &)

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
