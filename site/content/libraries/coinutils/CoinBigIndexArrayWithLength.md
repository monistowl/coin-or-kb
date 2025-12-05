+++
title = "CoinBigIndexArrayWithLength"
description = "CoinBigIndex * version."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinBigIndexArrayWithLength.json"
+++

CoinBigIndex * version.


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
CoinBigIndex * array()
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
CoinBigIndex * conditionalNew(CoinByteArray sizeWanted)
```

**Parameters:**

- `sizeWanted` (CoinByteArray)

### `CoinBigIndexArrayWithLength`

Default constructor - NULL.

```cpp
 CoinBigIndexArrayWithLength()
```

### `CoinBigIndexArrayWithLength`

Alternate Constructor - length in bytes - size_ -1.

```cpp
 CoinBigIndexArrayWithLength(CoinByteArray size)
```

**Parameters:**

- `size` (CoinByteArray)

### `CoinBigIndexArrayWithLength`

Alternate Constructor - length in bytes mode - 0 size_ set to size 1 size_ set to size and zeroed.

```cpp
 CoinBigIndexArrayWithLength(CoinByteArray size, int mode)
```

**Parameters:**

- `size` (CoinByteArray)
- `mode` (int)

### `CoinBigIndexArrayWithLength`

Copy constructor.

```cpp
 CoinBigIndexArrayWithLength(const CoinBigIndexArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinBigIndexArrayWithLength &)

### `CoinBigIndexArrayWithLength`

Copy constructor.2.

```cpp
 CoinBigIndexArrayWithLength(const CoinBigIndexArrayWithLength * rhs)
```

**Parameters:**

- `rhs` (const CoinBigIndexArrayWithLength *)

### `operator=`

Assignment operator.

```cpp
CoinBigIndexArrayWithLength & operator=(const CoinBigIndexArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinBigIndexArrayWithLength &)

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
