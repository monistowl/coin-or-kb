+++
title = "CoinModelLinkedList"
description = "CoinModelLinkedList class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinModelUseful.hpp"
api_url = "/api/coinutils/CoinModelLinkedList.json"
+++

<div class="api-link"><a href="/api/coinutils/CoinModelLinkedList.json">JSON API</a></div>

## Public Methods

### `CoinModelLinkedList`

Default constructor.

```cpp
 CoinModelLinkedList()
```

### `~CoinModelLinkedList`

Destructor.

```cpp
 ~CoinModelLinkedList()
```

### `CoinModelLinkedList`

The copy constructor.

```cpp
 CoinModelLinkedList(const CoinModelLinkedList & )
```

**Parameters:**

- `` (const CoinModelLinkedList &)

### `operator=`

=

```cpp
CoinModelLinkedList & operator=(const CoinModelLinkedList & )
```

**Parameters:**

- `` (const CoinModelLinkedList &)

### `resize`

Resize list - for row list maxMajor is maximum rows.

```cpp
void resize(int maxMajor, CoinBigIndex maxElements)
```

**Parameters:**

- `maxMajor` (int)
- `maxElements` (CoinBigIndex)

### `create`

Create list - for row list maxMajor is maximum rows.

```cpp
void create(int maxMajor, CoinBigIndex maxElements, int numberMajor, int numberMinor, int type, CoinBigIndex numberElements, const CoinModelTriple * triples)
```

**Parameters:**

- `maxMajor` (int)
- `maxElements` (CoinBigIndex)
- `numberMajor` (int)
- `numberMinor` (int)
- `type` (int)
- `numberElements` (CoinBigIndex)
- `triples` (const CoinModelTriple *)

### `numberMajor`

Number of major items i.e. rows if just row links.

```cpp
int numberMajor()
```

### `maximumMajor`

Maximum number of major items i.e. rows if just row links.

```cpp
int maximumMajor()
```

### `numberElements`

Number of elements.

```cpp
CoinBigIndex numberElements()
```

### `maximumElements`

Maximum number of elements.

```cpp
CoinBigIndex maximumElements()
```

### `firstFree`

First on free chain.

```cpp
CoinBigIndex firstFree()
```

### `lastFree`

Last on free chain.

```cpp
CoinBigIndex lastFree()
```

### `first`

First on chain.

```cpp
CoinBigIndex first(int which)
```

**Parameters:**

- `which` (int)

### `last`

Last on chain.

```cpp
CoinBigIndex last(int which)
```

**Parameters:**

- `which` (int)

### `next`

Next array.

```cpp
const CoinBigIndex * next()
```

### `previous`

Previous array.

```cpp
const CoinBigIndex * previous()
```

### `addEasy`

Adds to list - easy case i.e.

```cpp
CoinBigIndex addEasy(int majorIndex, CoinBigIndex numberOfElements, const int * indices, const double * elements, CoinModelTriple * triples, CoinModelHash2 & hash)
```

**Parameters:**

- `majorIndex` (int)
- `numberOfElements` (CoinBigIndex)
- `indices` (const int *)
- `elements` (const double *)
- `triples` (CoinModelTriple *)
- `hash` (CoinModelHash2 &)

### `addHard`

Adds to list - hard case i.e.

```cpp
void addHard(int minorIndex, CoinBigIndex numberOfElements, const int * indices, const double * elements, CoinModelTriple * triples, CoinModelHash2 & hash)
```

**Parameters:**

- `minorIndex` (int)
- `numberOfElements` (CoinBigIndex)
- `indices` (const int *)
- `elements` (const double *)
- `triples` (CoinModelTriple *)
- `hash` (CoinModelHash2 &)

### `addHard`

Adds to list - hard case i.e.

```cpp
void addHard(CoinBigIndex first, const CoinModelTriple * triples, CoinBigIndex firstFree, CoinBigIndex lastFree, const CoinBigIndex * nextOther)
```

**Parameters:**

- `first` (CoinBigIndex)
- `triples` (const CoinModelTriple *)
- `firstFree` (CoinBigIndex)
- `lastFree` (CoinBigIndex)
- `nextOther` (const CoinBigIndex *)

### `deleteSame`

Deletes from list - same case i.e.

```cpp
void deleteSame(int which, CoinModelTriple * triples, CoinModelHash2 & hash, bool zapTriples)
```

**Parameters:**

- `which` (int)
- `triples` (CoinModelTriple *)
- `hash` (CoinModelHash2 &)
- `zapTriples` (bool)

### `updateDeleted`

Deletes from list - other case i.e.

```cpp
void updateDeleted(int which, CoinModelTriple * triples, CoinModelLinkedList & otherList)
```

**Parameters:**

- `which` (int)
- `triples` (CoinModelTriple *)
- `otherList` (CoinModelLinkedList &)

### `deleteRowOne`

Deletes one element from Row list.

```cpp
void deleteRowOne(CoinBigIndex position, CoinModelTriple * triples, CoinModelHash2 & hash)
```

**Parameters:**

- `position` (CoinBigIndex)
- `triples` (CoinModelTriple *)
- `hash` (CoinModelHash2 &)

### `updateDeletedOne`

Update column list for one element when one element deleted from row copy.

```cpp
void updateDeletedOne(CoinBigIndex position, const CoinModelTriple * triples)
```

**Parameters:**

- `position` (CoinBigIndex)
- `triples` (const CoinModelTriple *)

### `fill`

Fills first,last with -1.

```cpp
void fill(int first, int last)
```

**Parameters:**

- `first` (int)
- `last` (int)

### `synchronize`

Puts in free list from other list.

```cpp
void synchronize(CoinModelLinkedList & other)
```

**Parameters:**

- `other` (CoinModelLinkedList &)

### `validateLinks`

Checks that links are consistent.

```cpp
void validateLinks(const CoinModelTriple * triples)
```

**Parameters:**

- `triples` (const CoinModelTriple *)

## Source

Header: `layer-0/CoinUtils/src/CoinModelUseful.hpp`
