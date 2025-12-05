+++
title = "CoinShallowPackedVector"
description = "Shallow Sparse Vector."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinShallowPackedVector.hpp"
api_url = "/api/coinutils/CoinShallowPackedVector.json"
+++

Shallow Sparse Vector.


## Inheritance

Inherits from: `CoinPackedVectorBase`

## Description

This class is for sparse vectors where the indices and elements are stored elsewhere. This class only maintains pointers to the indices and elements. Since this class does not own the index and element data it provides read only access to to the data. An CoinSparsePackedVector must be used when the sparse vector's data will be altered.
This class stores pointers to the vectors. It does not actually contain the vectors.
Here is a sample usage: const int ne = 4; 
   int inx[ne] =   {  1,   4,  0,   2 }; 
   double el[ne] = { 10., 40., 1., 50. }; 
 
   // Create vector and set its value 
   CoinShallowPackedVector r(ne,inx,el); 
 
   // access each index and element 
   assert( r.indices ()[0]== 1  ); 
   assert( r.elements()[0]==10. ); 
   assert( r.indices ()[1]== 4  ); 
   assert( r.elements()[1]==40. ); 
   assert( r.indices ()[2]== 0  ); 
   assert( r.elements()[2]== 1. ); 
   assert( r.indices ()[3]== 2  ); 
   assert( r.elements()[3]==50. ); 
 
   // access as a full storage vector 
   assert( r[ 0]==1. ); 
   assert( r[ 1]==10.); 
   assert( r[ 2]==50.); 
   assert( r[ 3]==0. ); 
   assert( r[ 4]==40.); 
 
   // Tests for equality and equivalence
   CoinShallowPackedVector r1; 
   r1=r; 
   assert( r==r1 ); 
   r.sort(CoinIncrElementOrdered()); 
   assert( r!=r1 ); 
 
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

Get length of indices and elements vectors.

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

### `clear`

Reset the vector (as if were just created an empty vector)

```cpp
void clear()
```

### `operator=`

Assignment operator.

```cpp
CoinShallowPackedVector & operator=(const CoinShallowPackedVector & x)
```

**Parameters:**

- `x` (const CoinShallowPackedVector &)

### `operator=`

Assignment operator from a CoinPackedVectorBase.

```cpp
CoinShallowPackedVector & operator=(const CoinPackedVectorBase & x)
```

**Parameters:**

- `x` (const CoinPackedVectorBase &)

### `setVector`

just like the explicit constructor

```cpp
void setVector(int size, const int * indices, const double * elements, bool testForDuplicateIndex = true)
```

**Parameters:**

- `size` (int)
- `indices` (const int *)
- `elements` (const double *)
- `testForDuplicateIndex` (bool)

### `CoinShallowPackedVector`

Default constructor.

```cpp
 CoinShallowPackedVector(bool testForDuplicateIndex = true)
```

**Parameters:**

- `testForDuplicateIndex` (bool)

### `CoinShallowPackedVector`

Explicit Constructor.

```cpp
 CoinShallowPackedVector(int size, const int * indices, const double * elements, bool testForDuplicateIndex = true)
```

**Parameters:**

- `size` (int)
- `indices` (const int *)
- `elements` (const double *)
- `testForDuplicateIndex` (bool)

### `CoinShallowPackedVector`

Copy constructor from the base class.

```cpp
 CoinShallowPackedVector(const CoinPackedVectorBase & )
```

**Parameters:**

- `` (const CoinPackedVectorBase &)

### `CoinShallowPackedVector`

Copy constructor.

```cpp
 CoinShallowPackedVector(const CoinShallowPackedVector & )
```

**Parameters:**

- `` (const CoinShallowPackedVector &)

### `~CoinShallowPackedVector`

Destructor.

```cpp
 ~CoinShallowPackedVector()
```

### `print`

Print vector information.

```cpp
void print()
```

## Source

Header: `layer-0/CoinUtils/src/CoinShallowPackedVector.hpp`
