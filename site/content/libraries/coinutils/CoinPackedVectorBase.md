+++
title = "CoinPackedVectorBase"
description = "Abstract base class providing read-only access to sparse vectors."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPackedVectorBase.hpp"
api_url = "/api/coinutils/CoinPackedVectorBase.json"
+++

Abstract base class providing read-only access to sparse vectors.

<div class="api-link"><a href="/api/coinutils/CoinPackedVectorBase.json">JSON API</a></div>

Derived classes: `CoinPackedVector`, `CoinShallowPackedVector`

## Description

Since this class is abstract, no object of this type can be created. The sole purpose is to provide const access to sparse vector data. Sparse vectors store only non-zero elements as parallel arrays of indices and values.

## Public Methods

### `getNumElements`

Get the number of stored (non-zero) elements.

```cpp
int getNumElements()
```

**Returns:** Count of index/value pairs

### `getIndices`

Get pointer to array of element indices.

```cpp
const int * getIndices()
```

**Returns:** Pointer to indices array (may be null if empty)

### `getElements`

Get pointer to array of element values.

```cpp
const double * getElements()
```

**Returns:** Pointer to values array (may be null if empty)

### `setTestForDuplicateIndex`

Set to the argument value whether to test for duplicate indices in the vector whenever they can occur.

```cpp
void setTestForDuplicateIndex(bool test)
```

**Parameters:**

- `test` (bool)

### `setTestForDuplicateIndexWhenTrue`

Set to the argument value whether to test for duplicate indices in the vector whenever they can occur BUT we know that right now the vector has no duplicate indices.

```cpp
void setTestForDuplicateIndexWhenTrue(bool test)
```

**Parameters:**

- `test` (bool)

### `testForDuplicateIndex`

Check if duplicate index testing is enabled.

```cpp
bool testForDuplicateIndex()
```

**Returns:** true if vector will be tested for duplicates when they can occur

### `setTestsOff`

Disable all duplicate checking without exception handling.

```cpp
void setTestsOff()
```

### `denseVector`

Convert sparse vector to dense format.

```cpp
double * denseVector(int denseSize)
```

**Parameters:**

- `denseSize` (int) - Length of the dense vector to create

**Returns:** Newly allocated dense array (caller must delete[])

### `operator[]`

Access element by dense index.

```cpp
double operator[](int i)
```

**Parameters:**

- `i` (int) - Index in the conceptual dense vector

**Returns:** Value at index i, or zero if not stored

### `getMaxIndex`

Get the largest index in the sparse vector.

```cpp
int getMaxIndex()
```

**Returns:** Maximum index value, or -infinity if empty

### `getMinIndex`

Get the smallest index in the sparse vector.

```cpp
int getMinIndex()
```

**Returns:** Minimum index value, or +infinity if empty

### `duplicateIndex`

Throw CoinError if duplicate indices exist.

```cpp
void duplicateIndex(const char * methodName = NULL, const char * className = NULL)
```

**Parameters:**

- `methodName` (const char *) - Name of calling method (for error message)
- `className` (const char *) - Name of calling class (for error message)

### `isExistingIndex`

Check if an index exists in the sparse vector.

```cpp
bool isExistingIndex(int i)
```

**Parameters:**

- `i` (int) - Index to search for

**Returns:** true if index i is stored

### `findIndex`

Find position of an index in the sparse storage.

```cpp
int findIndex(int i)
```

**Parameters:**

- `i` (int) - Index to search for

**Returns:** Position in indices/elements arrays, or -1 if not found

### `operator==`

Equal.

```cpp
bool operator==(const CoinPackedVectorBase & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedVectorBase &)

### `operator!=`

Not equal.

```cpp
bool operator!=(const CoinPackedVectorBase & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedVectorBase &)

### `compare`

This method establishes an ordering on packed vectors.

```cpp
int compare(const CoinPackedVectorBase & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedVectorBase &)

### `isEquivalent`

equivalent - If shallow packed vector A & B are equivalent, then they are still equivalent no matter how they are sorted.

```cpp
bool isEquivalent(const CoinPackedVectorBase & rhs, const FloatEqual & eq)
```

**Parameters:**

- `rhs` (const CoinPackedVectorBase &)
- `eq` (const FloatEqual &)

### `isEquivalent`

```cpp
bool isEquivalent(const CoinPackedVectorBase & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedVectorBase &)

### `dotProduct`

Compute dot product with a dense vector.

```cpp
double dotProduct(const double * dense)
```

**Parameters:**

- `dense` (const double *) - Pointer to dense vector (must have length >= max index + 1)

**Returns:** Sum of element[i] * dense[index[i]] for all stored elements

### `oneNorm`

Compute the 1-norm (sum of absolute values)

```cpp
double oneNorm()
```

**Returns:** Sum of |element[i]| for all stored elements

### `normSquare`

Compute the squared 2-norm.

```cpp
double normSquare()
```

**Returns:** Sum of element[i]^2 for all stored elements

### `twoNorm`

Compute the 2-norm (Euclidean length)

```cpp
double twoNorm()
```

**Returns:** Square root of normSquare()

### `infNorm`

Compute the infinity-norm (maximum absolute value)

```cpp
double infNorm()
```

**Returns:** Maximum |element[i]| across all stored elements

### `sum`

Compute the sum of all elements.

```cpp
double sum()
```

**Returns:** Sum of element[i] for all stored elements

### `~CoinPackedVectorBase`

Destructor.

```cpp
 ~CoinPackedVectorBase()
```

## Source

Header: `layer-0/CoinUtils/src/CoinPackedVectorBase.hpp`
