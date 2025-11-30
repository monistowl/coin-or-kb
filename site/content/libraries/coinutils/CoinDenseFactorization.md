+++
title = "CoinDenseFactorization"
description = "This deals with Factorization and Updates This is a simple dense version so other people can write a better one."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinDenseFactorization.hpp"
api_url = "/api/coinutils/CoinDenseFactorization.json"
+++

This deals with Factorization and Updates This is a simple dense version so other people can write a better one.

<div class="api-link"><a href="/api/coinutils/CoinDenseFactorization.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinOtherFactorization`

## Description

I am assuming that 32 bits is enough for number of rows or columns, but CoinBigIndex may be redefined to get 64 bits.

## Public Methods

### `CoinDenseFactorization`

Default constructor.

```cpp
 CoinDenseFactorization()
```

### `CoinDenseFactorization`

Copy constructor.

```cpp
 CoinDenseFactorization(const CoinDenseFactorization & other)
```

**Parameters:**

- `other` (const CoinDenseFactorization &)

### `~CoinDenseFactorization`

Destructor.

```cpp
 ~CoinDenseFactorization()
```

### `operator=`

= copy

```cpp
CoinDenseFactorization & operator=(const CoinDenseFactorization & other)
```

**Parameters:**

- `other` (const CoinDenseFactorization &)

### `clone`

Clone.

```cpp
CoinOtherFactorization * clone()
```

### `getAreas`

Gets space for a factorization.

```cpp
void getAreas(int numberRows, int numberColumns, int maximumL, int maximumU)
```

**Parameters:**

- `numberRows` (int)
- `numberColumns` (int)
- `maximumL` (int)
- `maximumU` (int)

### `preProcess`

PreProcesses column ordered copy of basis.

```cpp
void preProcess()
```

### `factor`

Does most of factorization returning status 0 - OK -99 - needs more memory -1 - singular - use numberGoodColumns and redo.

```cpp
int factor()
```

### `postProcess`

Does post processing on valid factorization - putting variables on correct rows.

```cpp
void postProcess(const int * sequence, int * pivotVariable)
```

**Parameters:**

- `sequence` (const int *)
- `pivotVariable` (int *)

### `makeNonSingular`

Makes a non-singular basis by replacing variables.

```cpp
void makeNonSingular(int * sequence, int numberColumns)
```

**Parameters:**

- `sequence` (int *)
- `numberColumns` (int)

### `numberElements`

Total number of elements in factorization.

```cpp
int numberElements()
```

### `maximumCoefficient`

Returns maximum absolute value in factorization.

```cpp
double maximumCoefficient()
```

### `replaceColumn`

Replaces one Column to basis, returns 0=OK, 1=Probably OK, 2=singular, 3=no room If checkBeforeModifying is true will do all accuracy checks before modifying factorization.

```cpp
int replaceColumn(CoinIndexedVector * regionSparse, int pivotRow, double pivotCheck, bool checkBeforeModifying = false, double acceptablePivot = 1.0e-8)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `pivotRow` (int)
- `pivotCheck` (double)
- `checkBeforeModifying` (bool)
- `acceptablePivot` (double)

### `updateColumnFT`

Updates one column (FTRAN) from regionSparse2 Tries to do FT update number returned is negative if no room regionSparse starts as zero and is zero at end.

```cpp
int updateColumnFT(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2, bool  = false)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `regionSparse2` (CoinIndexedVector *)
- `` (bool)

### `updateColumn`

This version has same effect as above with FTUpdate==false so number returned is always >=0.

```cpp
int updateColumn(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2, bool noPermute = false)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `regionSparse2` (CoinIndexedVector *)
- `noPermute` (bool)

### `updateTwoColumnsFT`

does FTRAN on two columns

```cpp
int updateTwoColumnsFT(CoinIndexedVector * regionSparse1, CoinIndexedVector * regionSparse2, CoinIndexedVector * regionSparse3, bool noPermute = false)
```

**Parameters:**

- `regionSparse1` (CoinIndexedVector *)
- `regionSparse2` (CoinIndexedVector *)
- `regionSparse3` (CoinIndexedVector *)
- `noPermute` (bool)

### `updateColumnTranspose`

Updates one column (BTRAN) from regionSparse2 regionSparse starts as zero and is zero at end Note - if regionSparse2 packed on input - will be packed on output.

```cpp
int updateColumnTranspose(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `regionSparse2` (CoinIndexedVector *)

### `clearArrays`

Get rid of all memory.

```cpp
void clearArrays()
```

### `indices`

Returns array to put basis indices in.

```cpp
int * indices()
```

### `permute`

Returns permute in.

```cpp
int * permute()
```

### `gutsOfDestructor`

The real work of desstructor.

```cpp
void gutsOfDestructor()
```

### `gutsOfInitialize`

The real work of constructor.

```cpp
void gutsOfInitialize()
```

### `gutsOfCopy`

The real work of copy.

```cpp
void gutsOfCopy(const CoinDenseFactorization & other)
```

**Parameters:**

- `other` (const CoinDenseFactorization &)

## Source

Header: `layer-0/CoinUtils/src/CoinDenseFactorization.hpp`
