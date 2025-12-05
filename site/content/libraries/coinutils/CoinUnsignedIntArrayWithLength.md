+++
title = "CoinUnsignedIntArrayWithLength"
description = "unsigned int * version"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinUnsignedIntArrayWithLength.json"
+++

unsigned int * version


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
unsigned int * array()
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
unsigned int * conditionalNew(CoinByteArray sizeWanted)
```

**Parameters:**

- `sizeWanted` (CoinByteArray)

### `CoinUnsignedIntArrayWithLength`

Default constructor - NULL.

```cpp
 CoinUnsignedIntArrayWithLength()
```

### `CoinUnsignedIntArrayWithLength`

Alternate Constructor - length in bytes - size_ -1.

```cpp
 CoinUnsignedIntArrayWithLength(CoinByteArray size)
```

**Parameters:**

- `size` (CoinByteArray)

### `CoinUnsignedIntArrayWithLength`

Alternate Constructor - length in bytes mode - 0 size_ set to size 1 size_ set to size and zeroed.

```cpp
 CoinUnsignedIntArrayWithLength(CoinByteArray size, int mode)
```

**Parameters:**

- `size` (CoinByteArray)
- `mode` (int)

### `CoinUnsignedIntArrayWithLength`

Copy constructor.

```cpp
 CoinUnsignedIntArrayWithLength(const CoinUnsignedIntArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinUnsignedIntArrayWithLength &)

### `CoinUnsignedIntArrayWithLength`

Copy constructor.2.

```cpp
 CoinUnsignedIntArrayWithLength(const CoinUnsignedIntArrayWithLength * rhs)
```

**Parameters:**

- `rhs` (const CoinUnsignedIntArrayWithLength *)

### `operator=`

Assignment operator.

```cpp
CoinUnsignedIntArrayWithLength & operator=(const CoinUnsignedIntArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinUnsignedIntArrayWithLength &)

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
