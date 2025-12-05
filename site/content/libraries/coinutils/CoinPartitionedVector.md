+++
title = "CoinPartitionedVector"
description = "CoinPartitionedVector class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinPartitionedVector.json"
+++


## Inheritance

Inherits from: `CoinIndexedVector`

## Public Methods

### `getNumElements`

Get the size of a partition.

```cpp
int getNumElements(int partition)
```

**Parameters:**

- `partition` (int)

### `getNumPartitions`

Get number of partitions.

```cpp
int getNumPartitions()
```

### `getNumElements`

Get the size.

```cpp
int getNumElements()
```

### `startPartition`

Get starts.

```cpp
int startPartition(int partition)
```

**Parameters:**

- `partition` (int)

### `startPartitions`

Get starts.

```cpp
const int * startPartitions()
```

### `setNumElementsPartition`

Set the size of a partition.

```cpp
void setNumElementsPartition(int partition, int value)
```

**Parameters:**

- `partition` (int)
- `value` (int)

### `setTempNumElementsPartition`

Set the size of a partition (just for a tiny while)

```cpp
void setTempNumElementsPartition(int partition, int value)
```

**Parameters:**

- `partition` (int)
- `value` (int)

### `computeNumberElements`

Add up number of elements in partitions.

```cpp
void computeNumberElements()
```

### `compact`

Add up number of elements in partitions and pack and get rid of partitions.

```cpp
void compact()
```

### `reserve`

Reserve space.

```cpp
void reserve(int n)
```

**Parameters:**

- `n` (int)

### `setPartitions`

Setup partitions (needs end as well)

```cpp
void setPartitions(int number, const int * starts)
```

**Parameters:**

- `number` (int)
- `starts` (const int *)

### `clearAndReset`

Reset the vector (as if were just created an empty vector). Gets rid of partitions.

```cpp
void clearAndReset()
```

### `clearAndKeep`

Reset the vector (as if were just created an empty vector). Keeps partitions.

```cpp
void clearAndKeep()
```

### `clearPartition`

Clear a partition.

```cpp
void clearPartition(int partition)
```

**Parameters:**

- `partition` (int)

### `checkClear`

For debug check vector is clear i.e. no elements.

```cpp
void checkClear()
```

### `checkClean`

For debug check vector is clean i.e. elements match indices.

```cpp
void checkClean()
```

### `scan`

Scan dense region and set up indices (returns number found)

```cpp
int scan(int partition, double tolerance = 0.0)
```

**Parameters:**

- `partition` (int)
- `tolerance` (double)

### `print`

Scan dense region from start to < end and set up indices returns number found.

```cpp
void print()
```

### `sort`

Sort the indexed storage vector (increasing indices).

```cpp
void sort()
```

### `CoinPartitionedVector`

Default constructor.

```cpp
 CoinPartitionedVector()
```

### `CoinPartitionedVector`

Alternate Constructors - set elements to vector of doubles.

```cpp
 CoinPartitionedVector(int size, const int * inds, const double * elems)
```

**Parameters:**

- `size` (int)
- `inds` (const int *)
- `elems` (const double *)

### `CoinPartitionedVector`

Alternate Constructors - set elements to same scalar value.

```cpp
 CoinPartitionedVector(int size, const int * inds, double element)
```

**Parameters:**

- `size` (int)
- `inds` (const int *)
- `element` (double)

### `CoinPartitionedVector`

Alternate Constructors - construct full storage with indices 0 through size-1.

```cpp
 CoinPartitionedVector(int size, const double * elements)
```

**Parameters:**

- `size` (int)
- `elements` (const double *)

### `CoinPartitionedVector`

Alternate Constructors - just size.

```cpp
 CoinPartitionedVector(int size)
```

**Parameters:**

- `size` (int)

### `CoinPartitionedVector`

Copy constructor.

```cpp
 CoinPartitionedVector(const CoinPartitionedVector & )
```

**Parameters:**

- `` (const CoinPartitionedVector &)

### `CoinPartitionedVector`

Copy constructor.2.

```cpp
 CoinPartitionedVector(const CoinPartitionedVector * )
```

**Parameters:**

- `` (const CoinPartitionedVector *)

### `operator=`

Assignment operator.

```cpp
CoinPartitionedVector & operator=(const CoinPartitionedVector & )
```

**Parameters:**

- `` (const CoinPartitionedVector &)

### `~CoinPartitionedVector`

Destructor.

```cpp
 ~CoinPartitionedVector()
```

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
