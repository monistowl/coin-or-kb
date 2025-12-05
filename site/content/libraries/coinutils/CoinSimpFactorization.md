+++
title = "CoinSimpFactorization"
description = "CoinSimpFactorization class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSimpFactorization.hpp"
api_url = "/api/coinutils/CoinSimpFactorization.json"
+++


## Inheritance

Inherits from: `CoinOtherFactorization`

## Public Methods

### `CoinSimpFactorization`

Default constructor.

```cpp
 CoinSimpFactorization()
```

### `CoinSimpFactorization`

Copy constructor.

```cpp
 CoinSimpFactorization(const CoinSimpFactorization & other)
```

**Parameters:**

- `other` (const CoinSimpFactorization &)

### `~CoinSimpFactorization`

Destructor.

```cpp
 ~CoinSimpFactorization()
```

### `operator=`

= copy

```cpp
CoinSimpFactorization & operator=(const CoinSimpFactorization & other)
```

**Parameters:**

- `other` (const CoinSimpFactorization &)

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

### `upColumn`

does updatecolumn if save==true keeps column for replace column

```cpp
int upColumn(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2, bool noPermute = false, bool save = false)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `regionSparse2` (CoinIndexedVector *)
- `noPermute` (bool)
- `save` (bool)

### `updateColumnTranspose`

Updates one column (BTRAN) from regionSparse2 regionSparse starts as zero and is zero at end Note - if regionSparse2 packed on input - will be packed on output.

```cpp
int updateColumnTranspose(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `regionSparse2` (CoinIndexedVector *)

### `upColumnTranspose`

does updateColumnTranspose, the other is a wrapper

```cpp
int upColumnTranspose(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2)
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

The real work of destructor.

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
void gutsOfCopy(const CoinSimpFactorization & other)
```

**Parameters:**

- `other` (const CoinSimpFactorization &)

### `factorize`

calls factorization

```cpp
void factorize(int numberOfRows, int numberOfColumns, const int colStarts, const int indicesRow, const double elements)
```

**Parameters:**

- `numberOfRows` (int)
- `numberOfColumns` (int)
- `colStarts` (const int)
- `indicesRow` (const int)
- `elements` (const double)

### `mainLoopFactor`

main loop of factorization

```cpp
int mainLoopFactor(FactorPointers & pointers)
```

**Parameters:**

- `pointers` (FactorPointers &)

### `copyLbyRows`

copies L by rows

```cpp
void copyLbyRows()
```

### `copyUbyColumns`

copies U by columns

```cpp
void copyUbyColumns()
```

### `findPivot`

finds a pivot element using Markowitz count

```cpp
int findPivot(FactorPointers & pointers, int & r, int & s, bool & ifSlack)
```

**Parameters:**

- `pointers` (FactorPointers &)
- `r` (int &)
- `s` (int &)
- `ifSlack` (bool &)

### `findPivotShCol`

finds a pivot in a shortest column

```cpp
int findPivotShCol(FactorPointers & pointers, int & r, int & s)
```

**Parameters:**

- `pointers` (FactorPointers &)
- `r` (int &)
- `s` (int &)

### `findPivotSimp`

finds a pivot in the first column available

```cpp
int findPivotSimp(FactorPointers & pointers, int & r, int & s)
```

**Parameters:**

- `pointers` (FactorPointers &)
- `r` (int &)
- `s` (int &)

### `GaussEliminate`

does Gauss elimination

```cpp
void GaussEliminate(FactorPointers & pointers, int & r, int & s)
```

**Parameters:**

- `pointers` (FactorPointers &)
- `r` (int &)
- `s` (int &)

### `findShortRow`

finds short row that intersects a given column

```cpp
int findShortRow(const int column, const int length, int & minRow, int & minRowLength, FactorPointers & pointers)
```

**Parameters:**

- `column` (const int)
- `length` (const int)
- `minRow` (int &)
- `minRowLength` (int &)
- `pointers` (FactorPointers &)

### `findShortColumn`

finds short column that intersects a given row

```cpp
int findShortColumn(const int row, const int length, int & minCol, int & minColLength, FactorPointers & pointers)
```

**Parameters:**

- `row` (const int)
- `length` (const int)
- `minCol` (int &)
- `minColLength` (int &)
- `pointers` (FactorPointers &)

### `findMaxInRrow`

finds maximum absolute value in a row

```cpp
double findMaxInRrow(const int row, FactorPointers & pointers)
```

**Parameters:**

- `row` (const int)
- `pointers` (FactorPointers &)

### `pivoting`

does pivoting

```cpp
void pivoting(const int pivotRow, const int pivotColumn, const double invPivot, FactorPointers & pointers)
```

**Parameters:**

- `pivotRow` (const int)
- `pivotColumn` (const int)
- `invPivot` (const double)
- `pointers` (FactorPointers &)

### `updateCurrentRow`

part of pivoting

```cpp
void updateCurrentRow(const int pivotRow, const int row, const double multiplier, FactorPointers & pointers, int & newNonZeros)
```

**Parameters:**

- `pivotRow` (const int)
- `row` (const int)
- `multiplier` (const double)
- `pointers` (FactorPointers &)
- `newNonZeros` (int &)

### `increaseLsize`

allocates more space for L

```cpp
void increaseLsize()
```

### `increaseRowSize`

allocates more space for a row of U

```cpp
void increaseRowSize(const int row, const int newSize)
```

**Parameters:**

- `row` (const int)
- `newSize` (const int)

### `increaseColSize`

allocates more space for a column of U

```cpp
void increaseColSize(const int column, const int newSize, const bool b)
```

**Parameters:**

- `column` (const int)
- `newSize` (const int)
- `b` (const bool)

### `enlargeUrow`

allocates more space for rows of U

```cpp
void enlargeUrow(const int numNewElements)
```

**Parameters:**

- `numNewElements` (const int)

### `enlargeUcol`

allocates more space for columns of U

```cpp
void enlargeUcol(const int numNewElements, const bool b)
```

**Parameters:**

- `numNewElements` (const int)
- `b` (const bool)

### `findInRow`

finds a given row in a column

```cpp
int findInRow(const int row, const int column)
```

**Parameters:**

- `row` (const int)
- `column` (const int)

### `findInColumn`

finds a given column in a row

```cpp
int findInColumn(const int column, const int row)
```

**Parameters:**

- `column` (const int)
- `row` (const int)

### `removeRowFromActSet`

declares a row inactive

```cpp
void removeRowFromActSet(const int row, FactorPointers & pointers)
```

**Parameters:**

- `row` (const int)
- `pointers` (FactorPointers &)

### `removeColumnFromActSet`

declares a column inactive

```cpp
void removeColumnFromActSet(const int column, FactorPointers & pointers)
```

**Parameters:**

- `column` (const int)
- `pointers` (FactorPointers &)

### `allocateSpaceForU`

allocates space for U

```cpp
void allocateSpaceForU()
```

### `allocateSomeArrays`

allocates several working arrays

```cpp
void allocateSomeArrays()
```

### `initialSomeNumbers`

initializes some numbers

```cpp
void initialSomeNumbers()
```

### `Lxeqb`

solves L x = b

```cpp
void Lxeqb(double * b)
```

**Parameters:**

- `b` (double *)

### `Lxeqb2`

same as above but with two rhs

```cpp
void Lxeqb2(double * b1, double * b2)
```

**Parameters:**

- `b1` (double *)
- `b2` (double *)

### `Uxeqb`

solves U x = b

```cpp
void Uxeqb(double * b, double * sol)
```

**Parameters:**

- `b` (double *)
- `sol` (double *)

### `Uxeqb2`

same as above but with two rhs

```cpp
void Uxeqb2(double * b1, double * sol1, double * sol2, double * b2)
```

**Parameters:**

- `b1` (double *)
- `sol1` (double *)
- `sol2` (double *)
- `b2` (double *)

### `xLeqb`

solves x L = b

```cpp
void xLeqb(double * b)
```

**Parameters:**

- `b` (double *)

### `xUeqb`

solves x U = b

```cpp
void xUeqb(double * b, double * sol)
```

**Parameters:**

- `b` (double *)
- `sol` (double *)

### `LUupdate`

updates factorization after a Simplex iteration

```cpp
int LUupdate(int newBasicCol)
```

**Parameters:**

- `newBasicCol` (int)

### `newEta`

creates a new eta vector

```cpp
void newEta(int row, int numNewElements)
```

**Parameters:**

- `row` (int)
- `numNewElements` (int)

### `copyRowPermutations`

makes a copy of row permutations

```cpp
void copyRowPermutations()
```

### `Hxeqb`

solves H x = b, where H is a product of eta matrices

```cpp
void Hxeqb(double * b)
```

**Parameters:**

- `b` (double *)

### `Hxeqb2`

same as above but with two rhs

```cpp
void Hxeqb2(double * b1, double * b2)
```

**Parameters:**

- `b1` (double *)
- `b2` (double *)

### `xHeqb`

solves x H = b

```cpp
void xHeqb(double * b)
```

**Parameters:**

- `b` (double *)

### `ftran`

does FTRAN

```cpp
void ftran(double * b, double * sol, bool save)
```

**Parameters:**

- `b` (double *)
- `sol` (double *)
- `save` (bool)

### `ftran2`

same as above but with two columns

```cpp
void ftran2(double * b1, double * sol1, double * b2, double * sol2)
```

**Parameters:**

- `b1` (double *)
- `sol1` (double *)
- `b2` (double *)
- `sol2` (double *)

### `btran`

does BTRAN

```cpp
void btran(double * b, double * sol)
```

**Parameters:**

- `b` (double *)
- `sol` (double *)

## Source

Header: `layer-0/CoinUtils/src/CoinSimpFactorization.hpp`
