+++
title = "CoinDenseVector"
description = "Dense Vector."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinDenseVector.hpp"
api_url = "/api/coinutils/CoinDenseVector.json"
+++

Dense Vector.

<div class="api-link"><a href="/api/coinutils/CoinDenseVector.json">JSON API</a></div>

## Description

Stores a dense (or expanded) vector of floating point values. Type of vector elements is controlled by templating. (Some working quantities such as accumulated sums are explicitly declared of type double). This allows the components of the vector integer, single or double precision.
Here is a sample usage: const int ne = 4;
    double el[ne] = { 10., 40., 1., 50. }

    // Create vector and set its value
    CoinDenseVector<double> r(ne,el);

    // access each element
    assert( r.getElements()[0]==10. );
    assert( r.getElements()[1]==40. );
    assert( r.getElements()[2]== 1. );
    assert( r.getElements()[3]==50. );

    // Test for equality
    CoinDenseVector<double> r1;
    r1=r;

    // Add dense vectors.
    // Similarly for subtraction, multiplication,
    // and division.
    CoinDenseVector<double> add = r + r1;
    assert( add[0] == 10.+10. );
    assert( add[1] == 40.+40. );
    assert( add[2] ==  1.+ 1. );
    assert( add[3] == 50.+50. );

    assert( r.sum() == 10.+40.+1.+50. );

## Public Methods

### `getNumElements`

Get the size.

```cpp
int getNumElements()
```

### `size`

```cpp
int size()
```

### `getElements`

Get element values.

```cpp
const T * getElements()
```

### `getElements`

Get element values.

```cpp
T * getElements()
```

### `clear`

Reset the vector (i.e. set all elemenets to zero)

```cpp
void clear()
```

### `operator=`

Assignment operator.

```cpp
CoinDenseVector & operator=(const CoinDenseVector & )
```

**Parameters:**

- `` (const CoinDenseVector &)

### `operator[]`

Member of array operator.

```cpp
T & operator[](size_t index)
```

**Parameters:**

- `index` (size_t)

### `operator[]`

Member of array operator.

```cpp
const T & operator[](size_t index)
```

**Parameters:**

- `index` (size_t)

### `setVector`

Set vector size, and elements.

```cpp
void setVector(int size, const T * elems)
```

**Parameters:**

- `size` (int)
- `elems` (const T *)

### `setConstant`

Elements set to have the same scalar value.

```cpp
void setConstant(int size, T elems)
```

**Parameters:**

- `size` (int)
- `elems` (T)

### `setElement`

Set an existing element in the dense vector The first argument is the "index" into the elements() array.

```cpp
void setElement(size_t index, T element)
```

**Parameters:**

- `index` (size_t)
- `element` (T)

### `resize`

Resize the dense vector to be the first newSize elements.

```cpp
void resize(size_t newSize, T fill = T())
```

**Parameters:**

- `newSize` (size_t)
- `fill` (T)

### `append`

Append a dense vector to this dense vector.

```cpp
void append(const CoinDenseVector & )
```

**Parameters:**

- `` (const CoinDenseVector &)

### `oneNorm`

1-norm of vector

```cpp
T oneNorm()
```

### `twoNorm`

2-norm of vector

```cpp
double twoNorm()
```

### `infNorm`

infinity-norm of vector

```cpp
T infNorm()
```

### `sum`

sum of vector elements

```cpp
T sum()
```

### `scale`

scale vector elements

```cpp
void scale(T factor)
```

**Parameters:**

- `factor` (T)

### `operator+=`

add `value` to every entry

```cpp
void operator+=(T value)
```

**Parameters:**

- `value` (T)

### `operator-=`

subtract `value` from every entry

```cpp
void operator-=(T value)
```

**Parameters:**

- `value` (T)

### `operator*=`

multiply every entry by `value`

```cpp
void operator*=(T value)
```

**Parameters:**

- `value` (T)

### `operator/=`

divide every entry by `value`

```cpp
void operator/=(T value)
```

**Parameters:**

- `value` (T)

### `CoinDenseVector`

Default constructor.

```cpp
 CoinDenseVector()
```

### `CoinDenseVector`

Alternate Constructors - set elements to vector of Ts.

```cpp
 CoinDenseVector(size_t size, const T * elems)
```

**Parameters:**

- `size` (size_t)
- `elems` (const T *)

### `CoinDenseVector`

Alternate Constructors - set elements to same scalar value.

```cpp
 CoinDenseVector(size_t size, T element = T())
```

**Parameters:**

- `size` (size_t)
- `element` (T)

### `CoinDenseVector`

Copy constructors.

```cpp
 CoinDenseVector(const CoinDenseVector & )
```

**Parameters:**

- `` (const CoinDenseVector &)

### `~CoinDenseVector`

Destructor.

```cpp
 ~CoinDenseVector()
```

## Source

Header: `layer-0/CoinUtils/src/CoinDenseVector.hpp`
