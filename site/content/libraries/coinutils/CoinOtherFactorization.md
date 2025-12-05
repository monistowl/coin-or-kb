+++
title = "CoinOtherFactorization"
description = "Abstract base class which also has some scalars so can be used from Dense or Simp."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinDenseFactorization.hpp"
api_url = "/api/coinutils/CoinOtherFactorization.json"
+++

Abstract base class which also has some scalars so can be used from Dense or Simp.


Derived classes: `CoinDenseFactorization`, `CoinOslFactorization`, `CoinSimpFactorization`

## Public Methods

### `CoinOtherFactorization`

Default constructor.

```cpp
 CoinOtherFactorization()
```

### `CoinOtherFactorization`

Copy constructor.

```cpp
 CoinOtherFactorization(const CoinOtherFactorization & other)
```

**Parameters:**

- `other` (const CoinOtherFactorization &)

### `~CoinOtherFactorization`

Destructor.

```cpp
 ~CoinOtherFactorization()
```

### `operator=`

= copy

```cpp
CoinOtherFactorization & operator=(const CoinOtherFactorization & other)
```

**Parameters:**

- `other` (const CoinOtherFactorization &)

### `clone`

Clone.

```cpp
CoinOtherFactorization * clone()
```

### `status`

Returns status.

```cpp
int status()
```

### `setStatus`

Sets status.

```cpp
void setStatus(int value)
```

**Parameters:**

- `value` (int)

### `pivots`

Returns number of pivots since factorization.

```cpp
int pivots()
```

### `setPivots`

Sets number of pivots since factorization.

```cpp
void setPivots(int value)
```

**Parameters:**

- `value` (int)

### `setNumberRows`

Set number of Rows after factorization.

```cpp
void setNumberRows(int value)
```

**Parameters:**

- `value` (int)

### `numberRows`

Number of Rows after factorization.

```cpp
int numberRows()
```

### `numberColumns`

Total number of columns in factorization.

```cpp
int numberColumns()
```

### `numberGoodColumns`

Number of good columns in factorization.

```cpp
int numberGoodColumns()
```

### `relaxAccuracyCheck`

Allows change of pivot accuracy check 1.0 == none >1.0 relaxed.

```cpp
void relaxAccuracyCheck(double value)
```

**Parameters:**

- `value` (double)

### `getAccuracyCheck`

```cpp
double getAccuracyCheck()
```

### `maximumPivots`

Maximum number of pivots between factorizations.

```cpp
int maximumPivots()
```

### `maximumPivots`

Set maximum pivots.

```cpp
void maximumPivots(int value)
```

**Parameters:**

- `value` (int)

### `pivotTolerance`

Pivot tolerance.

```cpp
double pivotTolerance()
```

### `pivotTolerance`

```cpp
void pivotTolerance(double value)
```

**Parameters:**

- `value` (double)

### `zeroTolerance`

Zero tolerance.

```cpp
double zeroTolerance()
```

### `zeroTolerance`

```cpp
void zeroTolerance(double value)
```

**Parameters:**

- `value` (double)

### `slackValue`

Whether slack value is +1 or -1.

```cpp
double slackValue()
```

### `slackValue`

```cpp
void slackValue(double value)
```

**Parameters:**

- `value` (double)

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

### `solveMode`

Get solve mode e.g.

```cpp
int solveMode()
```

### `setSolveMode`

Set solve mode e.g.

```cpp
void setSolveMode(int value)
```

**Parameters:**

- `value` (int)

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

### `numberElements`

Total number of elements in factorization.

```cpp
int numberElements()
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

## Source

Header: `layer-0/CoinUtils/src/CoinDenseFactorization.hpp`
