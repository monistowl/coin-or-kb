+++
title = "CoinPackedVector"
description = "Sparse Vector."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPackedVector.hpp"
api_url = "/api/coinutils/CoinPackedVector.json"
+++

Sparse Vector.


## Inheritance

Inherits from: `CoinPackedVectorBase`

## Description

Stores vector of indices and associated element values. Supports sorting of vector while maintaining the original indices.
Here is a sample usage: const int ne = 4;
    int inx[ne] =   {  1,   4,  0,   2 }
    double el[ne] = { 10., 40., 1., 50. }

    // Create vector and set its value
    CoinPackedVector r(ne,inx,el);

    // access each index and element
    assert( r.indices ()[0]== 1  );
    assert( r.elements()[0]==10. );
    assert( r.indices ()[1]== 4  );
    assert( r.elements()[1]==40. );
    assert( r.indices ()[2]== 0  );
    assert( r.elements()[2]== 1. );
    assert( r.indices ()[3]== 2  );
    assert( r.elements()[3]==50. );

    // access original position of index
    assert( r.originalPosition()[0]==0 );
    assert( r.originalPosition()[1]==1 );
    assert( r.originalPosition()[2]==2 );
    assert( r.originalPosition()[3]==3 );

    // access as a full storage vector
    assert( r[ 0]==1. );
    assert( r[ 1]==10.);
    assert( r[ 2]==50.);
    assert( r[ 3]==0. );
    assert( r[ 4]==40.);

    // sort Elements in increasing order
    r.sortIncrElement();

    // access each index and element
    assert( r.indices ()[0]== 0  );
    assert( r.elements()[0]== 1. );
    assert( r.indices ()[1]== 1  );
    assert( r.elements()[1]==10. );
    assert( r.indices ()[2]== 4  );
    assert( r.elements()[2]==40. );
    assert( r.indices ()[3]== 2  );
    assert( r.elements()[3]==50. );    

    // access original position of index    
    assert( r.originalPosition()[0]==2 );
    assert( r.originalPosition()[1]==0 );
    assert( r.originalPosition()[2]==1 );
    assert( r.originalPosition()[3]==3 );

    // access as a full storage vector
    assert( r[ 0]==1. );
    assert( r[ 1]==10.);
    assert( r[ 2]==50.);
    assert( r[ 3]==0. );
    assert( r[ 4]==40.);

    // Restore orignal sort order
    r.sortOriginalOrder();
    
    assert( r.indices ()[0]== 1  );
    assert( r.elements()[0]==10. );
    assert( r.indices ()[1]== 4  );
    assert( r.elements()[1]==40. );
    assert( r.indices ()[2]== 0  );
    assert( r.elements()[2]== 1. );
    assert( r.indices ()[3]== 2  );
    assert( r.elements()[3]==50. );

    // Tests for equality and equivalence
    CoinPackedVector r1;
    r1=r;
    assert( r==r1 );
    assert( r.equivalent(r1) );
    r.sortIncrElement();
    assert( r!=r1 );
    assert( r.equivalent(r1) );

    // Add packed vectors.
    // Similarly for subtraction, multiplication,
    // and division.
    CoinPackedVector add = r + r1;
    assert( add[0] ==  1.+ 1. );
    assert( add[1] == 10.+10. );
    assert( add[2] == 50.+50. );
    assert( add[3] ==  0.+ 0. );
    assert( add[4] == 40.+40. );

    assert( r.sum() == 10.+40.+1.+50. );

## Public Methods

### `getNumElements`

Get the size.

```cpp
int getNumElements()
```

### `getIndices`

Get indices of elements.

```cpp
const int * getIndices()
```

### `getElements`

Get element values.

```cpp
const double * getElements()
```

### `getIndices`

Get indices of elements.

```cpp
int * getIndices()
```

### `getVectorNumElements`

Get the size.

```cpp
int getVectorNumElements()
```

### `getVectorIndices`

Get indices of elements.

```cpp
const int * getVectorIndices()
```

### `getVectorElements`

Get element values.

```cpp
const double * getVectorElements()
```

### `getElements`

Get element values.

```cpp
double * getElements()
```

### `getOriginalPosition`

Get pointer to int * vector of original postions.

```cpp
const int * getOriginalPosition()
```

### `clear`

Reset the vector (as if were just created an empty vector)

```cpp
void clear()
```

### `operator=`

Assignment operator.

```cpp
CoinPackedVector & operator=(const CoinPackedVector & )
```

**Parameters:**

- `` (const CoinPackedVector &)

### `operator=`

Assignment operator from a CoinPackedVectorBase.

```cpp
CoinPackedVector & operator=(const CoinPackedVectorBase & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedVectorBase &)

### `assignVector`

Assign the ownership of the arguments to this vector.

```cpp
void assignVector(int size, int *& inds, double *& elems, bool testForDuplicateIndex)
```

**Parameters:**

- `size` (int)
- `inds` (int *&)
- `elems` (double *&)
- `testForDuplicateIndex` (bool)

### `setVector`

Set vector size, indices, and elements.

```cpp
void setVector(int size, const int * inds, const double * elems, bool testForDuplicateIndex)
```

**Parameters:**

- `size` (int)
- `inds` (const int *)
- `elems` (const double *)
- `testForDuplicateIndex` (bool)

### `setConstant`

Elements set to have the same scalar value.

```cpp
void setConstant(int size, const int * inds, double elems, bool testForDuplicateIndex)
```

**Parameters:**

- `size` (int)
- `inds` (const int *)
- `elems` (double)
- `testForDuplicateIndex` (bool)

### `setFull`

Indices are not specified and are taken to be 0,1,...,size-1.

```cpp
void setFull(int size, const double * elems, bool testForDuplicateIndex)
```

**Parameters:**

- `size` (int)
- `elems` (const double *)
- `testForDuplicateIndex` (bool)

### `setFullNonZero`

Indices are not specified and are taken to be 0,1,...,size-1, but only where non zero.

```cpp
void setFullNonZero(int size, const double * elems, bool testForDuplicateIndex)
```

**Parameters:**

- `size` (int)
- `elems` (const double *)
- `testForDuplicateIndex` (bool)

### `setElement`

Set an existing element in the packed vector The first argument is the "index" into the elements() array.

```cpp
void setElement(int index, double element)
```

**Parameters:**

- `index` (int)
- `element` (double)

### `insert`

Insert an element into the vector.

```cpp
void insert(int index, double element)
```

**Parameters:**

- `index` (int)
- `element` (double)

### `append`

Append a CoinPackedVector to the end.

```cpp
void append(const CoinPackedVectorBase & caboose)
```

**Parameters:**

- `caboose` (const CoinPackedVectorBase &)

### `swap`

Swap values in positions i and j of indices and elements.

```cpp
void swap(int i, int j)
```

**Parameters:**

- `i` (int)
- `j` (int)

### `truncate`

Resize the packed vector to be the first newSize elements.

```cpp
void truncate(int newSize)
```

**Parameters:**

- `newSize` (int)

### `operator+=`

add `value` to every entry

```cpp
void operator+=(double value)
```

**Parameters:**

- `value` (double)

### `operator-=`

subtract `value` from every entry

```cpp
void operator-=(double value)
```

**Parameters:**

- `value` (double)

### `operator*=`

multiply every entry by `value`

```cpp
void operator*=(double value)
```

**Parameters:**

- `value` (double)

### `operator/=`

divide every entry by `value`

```cpp
void operator/=(double value)
```

**Parameters:**

- `value` (double)

### `sort`

Sort the packed storage vector.

```cpp
void sort(const CoinCompare3 & tc)
```

**Parameters:**

- `tc` (const CoinCompare3 &)

### `sortIncrIndex`

```cpp
void sortIncrIndex()
```

### `sortDecrIndex`

```cpp
void sortDecrIndex()
```

### `sortIncrElement`

```cpp
void sortIncrElement()
```

### `sortDecrElement`

```cpp
void sortDecrElement()
```

### `sortOriginalOrder`

Sort in original order.

```cpp
void sortOriginalOrder()
```

### `reserve`

Reserve space.

```cpp
void reserve(int n)
```

**Parameters:**

- `n` (int)

### `capacity`

capacity returns the size which could be accomodated without having to reallocate storage.

```cpp
int capacity()
```

### `CoinPackedVector`

Default constructor.

```cpp
 CoinPackedVector(bool testForDuplicateIndex)
```

**Parameters:**

- `testForDuplicateIndex` (bool)

### `CoinPackedVector`

Alternate Constructors - set elements to vector of doubles.

```cpp
 CoinPackedVector(int size, const int * inds, const double * elems, bool testForDuplicateIndex)
```

**Parameters:**

- `size` (int)
- `inds` (const int *)
- `elems` (const double *)
- `testForDuplicateIndex` (bool)

### `CoinPackedVector`

Alternate Constructors - set elements to vector of doubles.

```cpp
 CoinPackedVector(int capacity, int size, int *& inds, double *& elems, bool testForDuplicateIndex)
```

**Parameters:**

- `capacity` (int)
- `size` (int)
- `inds` (int *&)
- `elems` (double *&)
- `testForDuplicateIndex` (bool)

### `CoinPackedVector`

Alternate Constructors - set elements to same scalar value.

```cpp
 CoinPackedVector(int size, const int * inds, double element, bool testForDuplicateIndex)
```

**Parameters:**

- `size` (int)
- `inds` (const int *)
- `element` (double)
- `testForDuplicateIndex` (bool)

### `CoinPackedVector`

Alternate Constructors - construct full storage with indices 0 through size-1.

```cpp
 CoinPackedVector(int size, const double * elements, bool testForDuplicateIndex)
```

**Parameters:**

- `size` (int)
- `elements` (const double *)
- `testForDuplicateIndex` (bool)

### `CoinPackedVector`

Copy constructor.

```cpp
 CoinPackedVector(const CoinPackedVector & )
```

**Parameters:**

- `` (const CoinPackedVector &)

### `CoinPackedVector`

Copy constructor from a PackedVectorBase.

```cpp
 CoinPackedVector(const CoinPackedVectorBase & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedVectorBase &)

### `~CoinPackedVector`

Destructor.

```cpp
 ~CoinPackedVector()
```

## Source

Header: `layer-0/CoinUtils/src/CoinPackedVector.hpp`
