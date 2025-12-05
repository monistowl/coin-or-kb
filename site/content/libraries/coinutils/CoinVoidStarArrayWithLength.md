+++
title = "CoinVoidStarArrayWithLength"
description = "void * version"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinVoidStarArrayWithLength.json"
+++

void * version


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
void ** conditionalNew(CoinByteArray sizeWanted)
```

**Parameters:**

- `sizeWanted` (CoinByteArray)

### `CoinVoidStarArrayWithLength`

Default constructor - NULL.

```cpp
 CoinVoidStarArrayWithLength()
```

### `CoinVoidStarArrayWithLength`

Alternate Constructor - length in bytes - size_ -1.

```cpp
 CoinVoidStarArrayWithLength(CoinByteArray size)
```

**Parameters:**

- `size` (CoinByteArray)

### `CoinVoidStarArrayWithLength`

Alternate Constructor - length in bytes mode - 0 size_ set to size 1 size_ set to size and zeroed.

```cpp
 CoinVoidStarArrayWithLength(CoinByteArray size, int mode)
```

**Parameters:**

- `size` (CoinByteArray)
- `mode` (int)

### `CoinVoidStarArrayWithLength`

Copy constructor.

```cpp
 CoinVoidStarArrayWithLength(const CoinVoidStarArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinVoidStarArrayWithLength &)

### `CoinVoidStarArrayWithLength`

Copy constructor.2.

```cpp
 CoinVoidStarArrayWithLength(const CoinVoidStarArrayWithLength * rhs)
```

**Parameters:**

- `rhs` (const CoinVoidStarArrayWithLength *)

### `operator=`

Assignment operator.

```cpp
CoinVoidStarArrayWithLength & operator=(const CoinVoidStarArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinVoidStarArrayWithLength &)

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
