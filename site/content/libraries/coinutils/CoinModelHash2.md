+++
title = "CoinModelHash2"
description = "For int,int hashing."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinModelUseful.hpp"
api_url = "/api/coinutils/CoinModelHash2.json"
+++

For int,int hashing.


## Public Methods

### `CoinModelHash2`

Default constructor.

```cpp
 CoinModelHash2()
```

### `~CoinModelHash2`

Destructor.

```cpp
 ~CoinModelHash2()
```

### `CoinModelHash2`

The copy constructor.

```cpp
 CoinModelHash2(const CoinModelHash2 & )
```

**Parameters:**

- `` (const CoinModelHash2 &)

### `operator=`

=

```cpp
CoinModelHash2 & operator=(const CoinModelHash2 & )
```

**Parameters:**

- `` (const CoinModelHash2 &)

### `resize`

Resize hash (also re-hashs)

```cpp
void resize(CoinBigIndex maxItems, const CoinModelTriple * triples, bool forceReHash = false)
```

**Parameters:**

- `maxItems` (CoinBigIndex)
- `triples` (const CoinModelTriple *)
- `forceReHash` (bool)

### `numberItems`

Number of items.

```cpp
CoinBigIndex numberItems()
```

### `setNumberItems`

Set number of items.

```cpp
void setNumberItems(CoinBigIndex number)
```

**Parameters:**

- `number` (CoinBigIndex)

### `maximumItems`

Maximum number of items.

```cpp
CoinBigIndex maximumItems()
```

### `hash`

Returns index or -1.

```cpp
CoinBigIndex hash(int row, int column, const CoinModelTriple * triples)
```

**Parameters:**

- `row` (int)
- `column` (int)
- `triples` (const CoinModelTriple *)

### `addHash`

Adds to hash.

```cpp
void addHash(CoinBigIndex index, int row, int column, const CoinModelTriple * triples)
```

**Parameters:**

- `index` (CoinBigIndex)
- `row` (int)
- `column` (int)
- `triples` (const CoinModelTriple *)

### `deleteHash`

Deletes from hash.

```cpp
void deleteHash(CoinBigIndex index, int row, int column)
```

**Parameters:**

- `index` (CoinBigIndex)
- `row` (int)
- `column` (int)

## Source

Header: `layer-0/CoinUtils/src/CoinModelUseful.hpp`
