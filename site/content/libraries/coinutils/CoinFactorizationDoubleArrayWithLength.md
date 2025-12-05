+++
title = "CoinFactorizationDoubleArrayWithLength"
description = "CoinFactorizationDouble * version."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinFactorizationDoubleArrayWithLength.json"
+++

CoinFactorizationDouble * version.


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
CoinFactorizationDouble * array()
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
CoinFactorizationDouble * conditionalNew(CoinByteArray sizeWanted)
```

**Parameters:**

- `sizeWanted` (CoinByteArray)

### `CoinFactorizationDoubleArrayWithLength`

Default constructor - NULL.

```cpp
 CoinFactorizationDoubleArrayWithLength()
```

### `CoinFactorizationDoubleArrayWithLength`

Alternate Constructor - length in bytes - size_ -1.

```cpp
 CoinFactorizationDoubleArrayWithLength(CoinByteArray size)
```

**Parameters:**

- `size` (CoinByteArray)

### `CoinFactorizationDoubleArrayWithLength`

Alternate Constructor - length in bytes mode - 0 size_ set to size 1 size_ set to size and zeroed.

```cpp
 CoinFactorizationDoubleArrayWithLength(CoinByteArray size, int mode)
```

**Parameters:**

- `size` (CoinByteArray)
- `mode` (int)

### `CoinFactorizationDoubleArrayWithLength`

Copy constructor.

```cpp
 CoinFactorizationDoubleArrayWithLength(const CoinFactorizationDoubleArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinFactorizationDoubleArrayWithLength &)

### `CoinFactorizationDoubleArrayWithLength`

Copy constructor.2.

```cpp
 CoinFactorizationDoubleArrayWithLength(const CoinFactorizationDoubleArrayWithLength * rhs)
```

**Parameters:**

- `rhs` (const CoinFactorizationDoubleArrayWithLength *)

### `operator=`

Assignment operator.

```cpp
CoinFactorizationDoubleArrayWithLength & operator=(const CoinFactorizationDoubleArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinFactorizationDoubleArrayWithLength &)

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
