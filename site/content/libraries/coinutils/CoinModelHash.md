+++
title = "CoinModelHash"
description = "CoinModelHash class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinModelUseful.hpp"
api_url = "/api/coinutils/CoinModelHash.json"
+++


## Public Methods

### `CoinModelHash`

Default constructor.

```cpp
 CoinModelHash()
```

### `~CoinModelHash`

Destructor.

```cpp
 ~CoinModelHash()
```

### `CoinModelHash`

The copy constructor.

```cpp
 CoinModelHash(const CoinModelHash & )
```

**Parameters:**

- `` (const CoinModelHash &)

### `operator=`

=

```cpp
CoinModelHash & operator=(const CoinModelHash & )
```

**Parameters:**

- `` (const CoinModelHash &)

### `resize`

Resize hash (also re-hashs)

```cpp
void resize(int maxItems, bool forceReHash = false)
```

**Parameters:**

- `maxItems` (int)
- `forceReHash` (bool)

### `numberItems`

Number of items i.e. rows if just row names.

```cpp
int numberItems()
```

### `setNumberItems`

Set number of items.

```cpp
void setNumberItems(int number)
```

**Parameters:**

- `number` (int)

### `maximumItems`

Maximum number of items.

```cpp
int maximumItems()
```

### `names`

Names.

```cpp
const char *const * names()
```

### `hash`

Returns index or -1.

```cpp
int hash(const char * name)
```

**Parameters:**

- `name` (const char *)

### `addHash`

Adds to hash.

```cpp
void addHash(int index, const char * name)
```

**Parameters:**

- `index` (int)
- `name` (const char *)

### `deleteHash`

Deletes from hash.

```cpp
void deleteHash(int index)
```

**Parameters:**

- `index` (int)

### `name`

Returns name at position (or NULL)

```cpp
const char * name(int which)
```

**Parameters:**

- `which` (int)

### `getName`

Returns non const name at position (or NULL)

```cpp
char * getName(int which)
```

**Parameters:**

- `which` (int)

### `setName`

Sets name at position (does not create)

```cpp
void setName(int which, char * name)
```

**Parameters:**

- `which` (int)
- `name` (char *)

### `validateHash`

Validates.

```cpp
void validateHash()
```

## Source

Header: `layer-0/CoinUtils/src/CoinModelUseful.hpp`
