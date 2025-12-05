+++
title = "CoinArrayWithLength"
description = "Pointer with length in bytes."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinArrayWithLength.json"
+++

Pointer with length in bytes.


Derived classes: `CoinArbitraryArrayWithLength`, `CoinBigIndexArrayWithLength`, `CoinDoubleArrayWithLength`, `CoinFactorizationDoubleArrayWithLength`, `CoinFactorizationLongDoubleArrayWithLength`, `CoinIntArrayWithLength`, `CoinUnsignedIntArrayWithLength`, `CoinVoidStarArrayWithLength`

## Description

This has a pointer to an array and the number of bytes in array. If number of bytes==-1 then CoinConditionalNew deletes existing pointer and returns new pointer of correct size (and number bytes still -1). CoinConditionalDelete deletes existing pointer and NULLs it. So behavior is as normal (apart from New deleting pointer which will have no effect with good coding practices. If number of bytes >=0 then CoinConditionalNew just returns existing pointer if array big enough otherwise deletes existing pointer, allocates array with spare 1%+64 bytes and updates number of bytes CoinConditionalDelete sets number of bytes = -size-2 and then array returns NULL

## Public Methods

### `getSize`

Get the size.

```cpp
CoinBigIndex getSize()
```

### `rawSize`

Get the size.

```cpp
CoinBigIndex rawSize()
```

### `switchedOn`

See if persistence already on.

```cpp
bool switchedOn()
```

### `capacity`

Get the capacity (just read it)

```cpp
CoinBigIndex capacity()
```

### `setCapacity`

Set the capacity to >=0 if <=-2.

```cpp
void setCapacity()
```

### `array`

Get Array.

```cpp
const char * array()
```

### `setSize`

Set the size.

```cpp
void setSize(CoinByteArray value)
```

**Parameters:**

- `value` (CoinByteArray)

### `switchOff`

Set the size to -1.

```cpp
void switchOff()
```

### `switchOn`

Set the size to -2 and alignment.

```cpp
void switchOn(int alignment = 3)
```

**Parameters:**

- `alignment` (int)

### `setPersistence`

Does what is needed to set persistence.

```cpp
void setPersistence(int flag, CoinByteArray currentLength)
```

**Parameters:**

- `flag` (int)
- `currentLength` (CoinByteArray)

### `clear`

Zero out array.

```cpp
void clear()
```

### `swap`

Swaps memory between two members.

```cpp
void swap(CoinArrayWithLength & other)
```

**Parameters:**

- `other` (CoinArrayWithLength &)

### `extend`

Extend a persistent array keeping data (size in bytes)

```cpp
void extend(CoinByteArray newSize)
```

**Parameters:**

- `newSize` (CoinByteArray)

### `conditionalNew`

Conditionally gets new array.

```cpp
char * conditionalNew(CoinByteArray sizeWanted)
```

**Parameters:**

- `sizeWanted` (CoinByteArray)

### `conditionalDelete`

Conditionally deletes.

```cpp
void conditionalDelete()
```

### `CoinArrayWithLength`

Default constructor - NULL.

```cpp
 CoinArrayWithLength()
```

### `CoinArrayWithLength`

Alternate Constructor - length in bytes - size_ -1.

```cpp
 CoinArrayWithLength(CoinByteArray size)
```

**Parameters:**

- `size` (CoinByteArray)

### `CoinArrayWithLength`

Alternate Constructor - length in bytes mode - 0 size_ set to size mode>0 size_ set to size and zeroed if size<=0 just does alignment If abs(mode) >2 then align on that as power of 2.

```cpp
 CoinArrayWithLength(CoinByteArray size, int mode)
```

**Parameters:**

- `size` (CoinByteArray)
- `mode` (int)

### `CoinArrayWithLength`

Copy constructor.

```cpp
 CoinArrayWithLength(const CoinArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinArrayWithLength &)

### `CoinArrayWithLength`

Copy constructor.2.

```cpp
 CoinArrayWithLength(const CoinArrayWithLength * rhs)
```

**Parameters:**

- `rhs` (const CoinArrayWithLength *)

### `operator=`

Assignment operator.

```cpp
CoinArrayWithLength & operator=(const CoinArrayWithLength & rhs)
```

**Parameters:**

- `rhs` (const CoinArrayWithLength &)

### `copy`

Assignment with length (if -1 use internal length)

```cpp
void copy(const CoinArrayWithLength & rhs, CoinByteArray numberBytes = -1)
```

**Parameters:**

- `rhs` (const CoinArrayWithLength &)
- `numberBytes` (CoinByteArray)

### `allocate`

Assignment with length - does not copy.

```cpp
void allocate(const CoinArrayWithLength & rhs, CoinByteArray numberBytes)
```

**Parameters:**

- `rhs` (const CoinArrayWithLength &)
- `numberBytes` (CoinByteArray)

### `~CoinArrayWithLength`

Destructor.

```cpp
 ~CoinArrayWithLength()
```

### `getArray`

Get array with alignment.

```cpp
void getArray(CoinByteArray size)
```

**Parameters:**

- `size` (CoinByteArray)

### `reallyFreeArray`

Really get rid of array with alignment.

```cpp
void reallyFreeArray()
```

### `getCapacity`

Get enough space (if more needed then do at least needed)

```cpp
void getCapacity(CoinByteArray numberBytes, CoinByteArray numberIfNeeded = -1)
```

**Parameters:**

- `numberBytes` (CoinByteArray)
- `numberIfNeeded` (CoinByteArray)

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
