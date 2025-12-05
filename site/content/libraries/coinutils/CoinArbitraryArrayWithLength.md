+++
title = "CoinArbitraryArrayWithLength"
description = "arbitrary version"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinArbitraryArrayWithLength.json"
+++

arbitrary version


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
void ** array()
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
char * conditionalNew(int length, CoinByteArray sizeWanted)
```

**Parameters:**

- `length` (int)
- `sizeWanted` (CoinByteArray)

### `CoinArbitraryArrayWithLength`

Default constructor - NULL.

```cpp
 CoinArbitraryArrayWithLength(int length = 1)
```

**Parameters:**

- `length` (int)

### `CoinArbitraryArrayWithLength`

Alternate Constructor - length in bytes - size_ -1.

```cpp
 CoinArbitraryArrayWithLength(int length, CoinByteArray size)
```

**Parameters:**

- `length` (int)
- `size` (CoinByteArray)

### `CoinArbitraryArrayWithLength`

Alternate Constructor - length in bytes mode - 0 size_ set to size 1 size_ set to size and zeroed.

```cpp
 CoinArbitraryArrayWithLength(int length, CoinByteArray size, int mode)
```

**Parameters:**

- `length` (int)
- `size` (CoinByteArray)
- `mode` (int)

### `CoinArbitraryArrayWithLength`

Copy constructor.

```cpp
 CoinArbitraryArrayWithLength(const CoinArbitraryArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinArbitraryArrayWithLength &)

### `CoinArbitraryArrayWithLength`

Copy constructor.2.

```cpp
 CoinArbitraryArrayWithLength(const CoinArbitraryArrayWithLength * rhs)
```

**Parameters:**

- `rhs` (const CoinArbitraryArrayWithLength *)

### `operator=`

Assignment operator.

```cpp
CoinArbitraryArrayWithLength & operator=(const CoinArbitraryArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinArbitraryArrayWithLength &)

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
