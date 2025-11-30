+++
title = "CoinOslFactorization"
description = "CoinOslFactorization class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinOslFactorization.hpp"
api_url = "/api/coinutils/CoinOslFactorization.json"
+++

<div class="api-link"><a href="/api/coinutils/CoinOslFactorization.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinOtherFactorization`

## Public Methods

### `CoinOslFactorization`

Default constructor.

```cpp
 CoinOslFactorization()
```

### `CoinOslFactorization`

Copy constructor.

```cpp
 CoinOslFactorization(const CoinOslFactorization & other)
```

**Parameters:**

- `other` (const CoinOslFactorization &)

### `~CoinOslFactorization`

Destructor.

```cpp
 ~CoinOslFactorization()
```

### `operator=`

= copy

```cpp
CoinOslFactorization & operator=(const CoinOslFactorization & other)
```

**Parameters:**

- `other` (const CoinOslFactorization &)

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

### `factorize`

When part of LP - given by basic variables.

```cpp
int factorize(const CoinPackedMatrix & matrix, int rowIsBasic, int columnIsBasic, double areaFactor = 0.0)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)
- `rowIsBasic` (int)
- `columnIsBasic` (int)
- `areaFactor` (double)

### `numberElements`

Total number of elements in factorization.

```cpp
int numberElements()
```

### `elements`

Returns array to put basis elements in.

```cpp
CoinFactorizationDouble2 * elements()
```

### `pivotRow`

Returns pivot row.

```cpp
int * pivotRow()
```

### `workArea`

Returns work area.

```cpp
CoinFactorizationDouble2 * workArea()
```

### `intWorkArea`

Returns int work area.

```cpp
int * intWorkArea()
```

### `numberInRow`

Number of entries in each row.

```cpp
int * numberInRow()
```

### `numberInColumn`

Number of entries in each column.

```cpp
int * numberInColumn()
```

### `starts`

Returns array to put basis starts in.

```cpp
int * starts()
```

### `permuteBack`

Returns permute back.

```cpp
int * permuteBack()
```

### `wantsTableauColumn`

Returns true if wants tableauColumn in replaceColumn.

```cpp
bool wantsTableauColumn()
```

### `setUsefulInformation`

Useful information for factorization 0 - iteration number whereFrom is 0 for factorize and 1 for replaceColumn.

```cpp
void setUsefulInformation(const int * info, int whereFrom)
```

**Parameters:**

- `info` (const int *)
- `whereFrom` (int)

### `maximumPivots`

Set maximum pivots.

```cpp
void maximumPivots(int value)
```

**Parameters:**

- `value` (int)

### `maximumCoefficient`

Returns maximum absolute value in factorization.

```cpp
double maximumCoefficient()
```

### `conditionNumber`

Condition number - product of pivots after factorization.

```cpp
double conditionNumber()
```

### `clearArrays`

Get rid of all memory.

```cpp
void clearArrays()
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
int updateColumnFT(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2, bool noPermute = false)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `regionSparse2` (CoinIndexedVector *)
- `noPermute` (bool)

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

### `indices`

Get rid of all memory.

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
void gutsOfDestructor(bool clearFact = true)
```

**Parameters:**

- `clearFact` (bool)

### `gutsOfInitialize`

The real work of constructor.

```cpp
void gutsOfInitialize(bool zapFact = true)
```

**Parameters:**

- `zapFact` (bool)

### `gutsOfCopy`

The real work of copy.

```cpp
void gutsOfCopy(const CoinOslFactorization & other)
```

**Parameters:**

- `other` (const CoinOslFactorization &)

## Source

Header: `layer-0/CoinUtils/src/CoinOslFactorization.hpp`
