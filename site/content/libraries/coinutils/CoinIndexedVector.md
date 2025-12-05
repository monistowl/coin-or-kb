+++
title = "CoinIndexedVector"
description = "Indexed Vector."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinIndexedVector.hpp"
api_url = "/api/coinutils/CoinIndexedVector.json"
+++

Indexed Vector.


Derived classes: `CoinPartitionedVector`

## Description

This stores values unpacked but apart from that is a bit like CoinPackedVector. It is designed to be lightweight in normal use.
It now has a "packed" mode when it is even more like CoinPackedVector
Indices array has capacity_ extra chars which are zeroed and can be used for any purpose - but must be re-zeroed
Stores vector of indices and associated element values. Supports sorting of indices.
Does not support negative indices.
Does NOT support testing for duplicates getElements is no longer supported Here is a sample usage: const int ne = 4;
    int inx[ne] =   {  1,   4,  0,   2 }
    double el[ne] = { 10., 40., 1., 50. }

    // Create vector and set its valuex1
    CoinIndexedVector r(ne,inx,el);

    // access as a full storage vector
    assert( r[ 0]==1. );
    assert( r[ 1]==10.);
    assert( r[ 2]==50.);
    assert( r[ 3]==0. );
    assert( r[ 4]==40.);

    // sort Elements in increasing order
    r.sortIncrElement();

    // access each index and element
    assert( r.getIndices ()[0]== 0  );
    assert( r.getIndices ()[1]== 1  );
    assert( r.getIndices ()[2]== 4  );
    assert( r.getIndices ()[3]== 2  );

    // access as a full storage vector
    assert( r[ 0]==1. );
    assert( r[ 1]==10.);
    assert( r[ 2]==50.);
    assert( r[ 3]==0. );
    assert( r[ 4]==40.);

    // Tests for equality and equivalence
    CoinIndexedVector r1;
    r1=r;
    assert( r==r1 );
    assert( r.equivalent(r1) );
    r.sortIncrElement();
    assert( r!=r1 );
    assert( r.equivalent(r1) );

    // Add indexed vectors.
    // Similarly for subtraction, multiplication,
    // and division.
    CoinIndexedVector add = r + r1;
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

### `getIndices`

Get element values.

```cpp
int * getIndices()
```

### `denseVector`

Get the vector as a dense vector.

```cpp
double * denseVector()
```

### `setDenseVector`

For very temporary use when user needs to borrow a dense vector.

```cpp
void setDenseVector(double * array)
```

**Parameters:**

- `array` (double *)

### `setIndexVector`

For very temporary use when user needs to borrow an index vector.

```cpp
void setIndexVector(int * array)
```

**Parameters:**

- `array` (int *)

### `operator[]`

Access the i'th element of the full storage vector.

```cpp
double & operator[](int i)
```

**Parameters:**

- `i` (int)

### `setNumElements`

Set the size.

```cpp
void setNumElements(int value)
```

**Parameters:**

- `value` (int)

### `clear`

Reset the vector (as if were just created an empty vector). This leaves arrays!

```cpp
void clear()
```

### `empty`

Reset the vector (as if were just created an empty vector)

```cpp
void empty()
```

### `reallyClear`

Clear even if in a bad way.

```cpp
void reallyClear()
```

### `operator=`

Assignment operator.

```cpp
CoinIndexedVector & operator=(const CoinIndexedVector & )
```

**Parameters:**

- `` (const CoinIndexedVector &)

### `operator=`

Assignment operator from a CoinPackedVectorBase.

```cpp
CoinIndexedVector & operator=(const CoinPackedVectorBase & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedVectorBase &)

### `copy`

Copy the contents of one vector into another.

```cpp
void copy(const CoinIndexedVector & rhs, double multiplier = 1.0)
```

**Parameters:**

- `rhs` (const CoinIndexedVector &)
- `multiplier` (double)

### `borrowVector`

Borrow ownership of the arguments to this vector.

```cpp
void borrowVector(int size, int numberIndices, int * inds, double * elems)
```

**Parameters:**

- `size` (int)
- `numberIndices` (int)
- `inds` (int *)
- `elems` (double *)

### `returnVector`

Return ownership of the arguments to this vector.

```cpp
void returnVector()
```

### `setVector`

Set vector numberIndices, indices, and elements.

```cpp
void setVector(int numberIndices, const int * inds, const double * elems)
```

**Parameters:**

- `numberIndices` (int)
- `inds` (const int *)
- `elems` (const double *)

### `setVector`

Set vector size, indices, and elements.

```cpp
void setVector(int size, int numberIndices, const int * inds, const double * elems)
```

**Parameters:**

- `size` (int)
- `numberIndices` (int)
- `inds` (const int *)
- `elems` (const double *)

### `setConstant`

Elements set to have the same scalar value.

```cpp
void setConstant(int size, const int * inds, double elems)
```

**Parameters:**

- `size` (int)
- `inds` (const int *)
- `elems` (double)

### `setFull`

Indices are not specified and are taken to be 0,1,...,size-1.

```cpp
void setFull(int size, const double * elems)
```

**Parameters:**

- `size` (int)
- `elems` (const double *)

### `setElement`

Set an existing element in the indexed vector The first argument is the "index" into the elements() array.

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

### `quickInsert`

Insert a nonzero element into the vector.

```cpp
void quickInsert(int index, double element)
```

**Parameters:**

- `index` (int)
- `element` (double)

### `add`

Insert or if exists add an element into the vector Any resulting zero elements will be made tiny.

```cpp
void add(int index, double element)
```

**Parameters:**

- `index` (int)
- `element` (double)

### `quickAdd`

Insert or if exists add an element into the vector Any resulting zero elements will be made tiny.

```cpp
void quickAdd(int index, double element)
```

**Parameters:**

- `index` (int)
- `element` (double)

### `quickAddNonZero`

Insert or if exists add an element into the vector Any resulting zero elements will be made tiny.

```cpp
void quickAddNonZero(int index, double element)
```

**Parameters:**

- `index` (int)
- `element` (double)

### `zero`

Makes nonzero tiny.

```cpp
void zero(int index)
```

**Parameters:**

- `index` (int)

### `clean`

set all small values to zero and return number remaining

```cpp
int clean(double tolerance)
```

**Parameters:**

- `tolerance` (double)

### `cleanAndPack`

Same but packs down.

```cpp
int cleanAndPack(double tolerance)
```

**Parameters:**

- `tolerance` (double)

### `cleanAndPackSafe`

Same but packs down and is safe (i.e. if order is odd)

```cpp
int cleanAndPackSafe(double tolerance)
```

**Parameters:**

- `tolerance` (double)

### `setPacked`

Mark as packed.

```cpp
void setPacked()
```

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
int scan()
```

### `scan`

Scan dense region from start to < end and set up indices returns number found.

```cpp
int scan(int start, int end)
```

**Parameters:**

- `start` (int)
- `end` (int)

### `scan`

Scan dense region and set up indices (returns number found).

```cpp
int scan(double tolerance)
```

**Parameters:**

- `tolerance` (double)

### `scan`

Scan dense region from start to < end and set up indices returns number found.

```cpp
int scan(int start, int end, double tolerance)
```

**Parameters:**

- `start` (int)
- `end` (int)
- `tolerance` (double)

### `scanAndPack`

These are same but pack down.

```cpp
int scanAndPack()
```

### `scanAndPack`

```cpp
int scanAndPack(int start, int end)
```

**Parameters:**

- `start` (int)
- `end` (int)

### `scanAndPack`

```cpp
int scanAndPack(double tolerance)
```

**Parameters:**

- `tolerance` (double)

### `scanAndPack`

```cpp
int scanAndPack(int start, int end, double tolerance)
```

**Parameters:**

- `start` (int)
- `end` (int)
- `tolerance` (double)

### `createPacked`

Create packed array.

```cpp
void createPacked(int number, const int * indices, const double * elements)
```

**Parameters:**

- `number` (int)
- `indices` (const int *)
- `elements` (const double *)

### `createUnpacked`

Create unpacked array.

```cpp
void createUnpacked(int number, const int * indices, const double * elements)
```

**Parameters:**

- `number` (int)
- `indices` (const int *)
- `elements` (const double *)

### `createOneUnpackedElement`

Create unpacked singleton.

```cpp
void createOneUnpackedElement(int index, double element)
```

**Parameters:**

- `index` (int)
- `element` (double)

### `expand`

This is mainly for testing - goes from packed to indexed.

```cpp
void expand()
```

### `append`

Append a CoinPackedVector to the end.

```cpp
void append(const CoinPackedVectorBase & caboose)
```

**Parameters:**

- `caboose` (const CoinPackedVectorBase &)

### `append`

Append a CoinIndexedVector to the end (with extra space)

```cpp
void append(const CoinIndexedVector & caboose)
```

**Parameters:**

- `caboose` (const CoinIndexedVector &)

### `append`

Append a CoinIndexedVector to the end and modify indices.

```cpp
void append(CoinIndexedVector & other, int adjustIndex, bool zapElements = false)
```

**Parameters:**

- `other` (CoinIndexedVector &)
- `adjustIndex` (int)
- `zapElements` (bool)

### `swap`

Swap values in positions i and j of indices and elements.

```cpp
void swap(int i, int j)
```

**Parameters:**

- `i` (int)
- `j` (int)

### `truncate`

Throw away all entries in rows >= newSize.

```cpp
void truncate(int newSize)
```

**Parameters:**

- `newSize` (int)

### `print`

Print out.

```cpp
void print()
```

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

divide every entry by `value` (** 0 vanishes)

```cpp
void operator/=(double value)
```

**Parameters:**

- `value` (double)

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

### `operator==`

Equal.

```cpp
bool operator==(const CoinIndexedVector & rhs)
```

**Parameters:**

- `rhs` (const CoinIndexedVector &)

### `operator!=`

Not equal.

```cpp
bool operator!=(const CoinIndexedVector & rhs)
```

**Parameters:**

- `rhs` (const CoinIndexedVector &)

### `isApproximatelyEqual`

Equal with a tolerance (returns -1 or position of inequality).

```cpp
int isApproximatelyEqual(const CoinIndexedVector & rhs, double tolerance = 1.0e-8)
```

**Parameters:**

- `rhs` (const CoinIndexedVector &)
- `tolerance` (double)

### `getMaxIndex`

Get value of maximum index.

```cpp
int getMaxIndex()
```

### `getMinIndex`

Get value of minimum index.

```cpp
int getMinIndex()
```

### `sort`

Sort the indexed storage vector (increasing indices).

```cpp
void sort()
```

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

### `sortPacked`

```cpp
void sortPacked()
```

### `operator+`

Return the sum of two indexed vectors.

```cpp
CoinIndexedVector operator+(const CoinIndexedVector & op2)
```

**Parameters:**

- `op2` (const CoinIndexedVector &)

### `operator-`

Return the difference of two indexed vectors.

```cpp
CoinIndexedVector operator-(const CoinIndexedVector & op2)
```

**Parameters:**

- `op2` (const CoinIndexedVector &)

### `operator*`

Return the element-wise product of two indexed vectors.

```cpp
CoinIndexedVector operator*(const CoinIndexedVector & op2)
```

**Parameters:**

- `op2` (const CoinIndexedVector &)

### `operator/`

Return the element-wise ratio of two indexed vectors (0.0/0.0 => 0.0) (0 vanishes)

```cpp
CoinIndexedVector operator/(const CoinIndexedVector & op2)
```

**Parameters:**

- `op2` (const CoinIndexedVector &)

### `operator+=`

The sum of two indexed vectors.

```cpp
void operator+=(const CoinIndexedVector & op2)
```

**Parameters:**

- `op2` (const CoinIndexedVector &)

### `operator-=`

The difference of two indexed vectors.

```cpp
void operator-=(const CoinIndexedVector & op2)
```

**Parameters:**

- `op2` (const CoinIndexedVector &)

### `operator*=`

The element-wise product of two indexed vectors.

```cpp
void operator*=(const CoinIndexedVector & op2)
```

**Parameters:**

- `op2` (const CoinIndexedVector &)

### `operator/=`

The element-wise ratio of two indexed vectors (0.0/0.0 => 0.0) (0 vanishes)

```cpp
void operator/=(const CoinIndexedVector & op2)
```

**Parameters:**

- `op2` (const CoinIndexedVector &)

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

### `setCapacity`

```cpp
void setCapacity(int value)
```

**Parameters:**

- `value` (int)

### `setPackedMode`

Sets packed mode.

```cpp
void setPackedMode(bool yesNo)
```

**Parameters:**

- `yesNo` (bool)

### `packedMode`

Gets packed mode.

```cpp
bool packedMode()
```

### `CoinIndexedVector`

Default constructor.

```cpp
 CoinIndexedVector()
```

### `CoinIndexedVector`

Alternate Constructors - set elements to vector of doubles.

```cpp
 CoinIndexedVector(int size, const int * inds, const double * elems)
```

**Parameters:**

- `size` (int)
- `inds` (const int *)
- `elems` (const double *)

### `CoinIndexedVector`

Alternate Constructors - set elements to same scalar value.

```cpp
 CoinIndexedVector(int size, const int * inds, double element)
```

**Parameters:**

- `size` (int)
- `inds` (const int *)
- `element` (double)

### `CoinIndexedVector`

Alternate Constructors - construct full storage with indices 0 through size-1.

```cpp
 CoinIndexedVector(int size, const double * elements)
```

**Parameters:**

- `size` (int)
- `elements` (const double *)

### `CoinIndexedVector`

Alternate Constructors - just size.

```cpp
 CoinIndexedVector(int size)
```

**Parameters:**

- `size` (int)

### `CoinIndexedVector`

Copy constructor.

```cpp
 CoinIndexedVector(const CoinIndexedVector & )
```

**Parameters:**

- `` (const CoinIndexedVector &)

### `CoinIndexedVector`

Copy constructor.2.

```cpp
 CoinIndexedVector(const CoinIndexedVector * )
```

**Parameters:**

- `` (const CoinIndexedVector *)

### `CoinIndexedVector`

Copy constructor from a PackedVectorBase.

```cpp
 CoinIndexedVector(const CoinPackedVectorBase & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedVectorBase &)

### `~CoinIndexedVector`

Destructor.

```cpp
 ~CoinIndexedVector()
```

## Source

Header: `layer-0/CoinUtils/src/CoinIndexedVector.hpp`
