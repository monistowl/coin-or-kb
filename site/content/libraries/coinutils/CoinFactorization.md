+++
title = "CoinFactorization"
description = "This deals with Factorization and Updates."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinFactorization.hpp"
api_url = "/api/coinutils/CoinFactorization.json"
+++

This deals with Factorization and Updates.

<div class="api-link"><a href="/api/coinutils/CoinFactorization.json">JSON API</a></div>

## Description

This class started with a parallel simplex code I was writing in the mid 90's. The need for parallelism led to many complications and I have simplified as much as I could to get back to this.
I was aiming at problems where I might get speed-up so I was looking at dense problems or ones with structure. This led to permuting input and output vectors and to increasing the number of rows each rank-one update. This is still in as a minor overhead.
I have also put in handling for hyper-sparsity. I have taken out all outer loop unrolling, dense matrix handling and most of the book-keeping for slacks. Also I always use FTRAN approach to updating even if factorization fairly dense. All these could improve performance.
I blame some of the coding peculiarities on the history of the code but mostly it is just because I can't do elegant code (or useful comments).
I am assuming that 32 bits is enough for number of rows or columns, but CoinBigIndex may be redefined to get 64 bits.

## Algorithms

<div class="algorithm-card">
@algorithm Sparse LU with Markowitz pivot selection @math Chooses pivot (i,j) minimizing (r_i - 1)(c_j - 1) where r_i, c_j are row and column counts in active submatrix. This heuristic minimizes expected fill-in during Gaussian elimination. @complexity O(m^2) worst case, typically O(m * nnz_avg) for sparse matrices
</div>

<div class="algorithm-card">
@algorithm Forrest-Tomlin update (when doForrestTomlin_=true) or PFI @math For basis change B_new = B_old + (a_q - a_p) · e_p': Forrest-Tomlin maintains L and updates U with spike elimination. PFI (Product Form of Inverse) appends eta matrices. @complexity O(nnz(column)) for FT update; PFI grows over iterations
</div>

<div class="algorithm-card">
@algorithm FTRAN with optional Forrest-Tomlin update preparation @math Solves B·x = b where B = L·U: Step 1: Solve L·y = b (forward substitution) Step 2: Solve U·x = y (backward substitution) @complexity O(nnz(L) + nnz(U)) - exploits sparsity
</div>

<div class="algorithm-card">
@algorithm BTRAN using transposed triangular solves @math Solves B'·y = c where B = L·U, so B' = U'·L': Step 1: Solve U'·z = c (forward substitution on U') Step 2: Solve L'·y = z (backward substitution on L') @complexity O(nnz(L) + nnz(U)) - exploits sparsity
</div>

## Public Methods

### `CoinFactorization`

Default constructor.

```cpp
 CoinFactorization()
```

### `CoinFactorization`

Copy constructor.

```cpp
 CoinFactorization(const CoinFactorization & other)
```

**Parameters:**

- `other` (const CoinFactorization &)

### `~CoinFactorization`

Destructor.

```cpp
 ~CoinFactorization()
```

### `almostDestructor`

Delete all stuff (leaves as after CoinFactorization())

```cpp
void almostDestructor()
```

### `show_self`

Debug show object (shows one representation)

```cpp
void show_self()
```

### `saveFactorization`

Debug - save on file - 0 if no error.

```cpp
int saveFactorization(const char * file)
```

**Parameters:**

- `file` (const char *)

### `restoreFactorization`

Debug - restore from file - 0 if no error on file.

```cpp
int restoreFactorization(const char * file, bool factor = false)
```

**Parameters:**

- `file` (const char *)
- `factor` (bool)

### `sort`

Debug - sort so can compare.

```cpp
void sort()
```

### `operator=`

= copy

```cpp
CoinFactorization & operator=(const CoinFactorization & other)
```

**Parameters:**

- `other` (const CoinFactorization &)

### `factorize`

Factorize basis matrix from LP basic variable indicators.

```cpp
int factorize(const CoinPackedMatrix & matrix, int rowIsBasic, int columnIsBasic, double areaFactor = 0.0)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &) - Full constraint matrix A
- `rowIsBasic` (int) - Array marking basic rows (>=0 means basic)
- `columnIsBasic` (int) - Array marking basic columns (>=0 means basic)
- `areaFactor` (double) - Multiplier for memory allocation (0 = auto)

**Returns:** 0 = success, -1 = singular, -2 = too many basic, -99 = memory

<div class="method-card">
**Algorithm:** @algorithm Sparse LU with Markowitz pivot selection @math Chooses pivot (i,j) minimizing (r_i - 1)(c_j - 1) where r_i, c_j are row and column counts in active submatrix. This heuristic minimizes expected fill-in during Gaussian elimination. @complexity O(m^2) worst case, typically O(m * nnz_avg) for sparse matrices
</div>

### `factorize`

When given as triplets.

```cpp
int factorize(int numberRows, int numberColumns, int numberElements, int maximumL, int maximumU, const int indicesRow, const int indicesColumn, const double elements, int permutation, double areaFactor = 0.0)
```

**Parameters:**

- `numberRows` (int)
- `numberColumns` (int)
- `numberElements` (int)
- `maximumL` (int)
- `maximumU` (int)
- `indicesRow` (const int)
- `indicesColumn` (const int)
- `elements` (const double)
- `permutation` (int)
- `areaFactor` (double)

### `factorizePart1`

Two part version for maximum flexibility This part creates arrays for user to fill.

```cpp
int factorizePart1(int numberRows, int numberColumns, int estimateNumberElements, int *COIN_RESTRICT indicesRow, int *COIN_RESTRICT indicesColumn, CoinFactorizationDouble *COIN_RESTRICT elements, double areaFactor = 0.0)
```

**Parameters:**

- `numberRows` (int)
- `numberColumns` (int)
- `estimateNumberElements` (int)
- `indicesRow` (int *COIN_RESTRICT)
- `indicesColumn` (int *COIN_RESTRICT)
- `elements` (CoinFactorizationDouble *COIN_RESTRICT)
- `areaFactor` (double)

### `factorizePart2`

This is part two of factorization Arrays belong to factorization and were returned by part 1 If status okay, permutation has pivot rows - this is only needed If status is singular, then basic variables have pivot row and ones thrown out have -1 returns 0 -okay, -1 singular, -99 memory.

```cpp
int factorizePart2(int permutation, int exactNumberElements)
```

**Parameters:**

- `permutation` (int)
- `exactNumberElements` (int)

### `conditionNumber`

Condition number - product of pivots after factorization.

```cpp
double conditionNumber()
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

### `permute`

Returns address of permute region.

```cpp
int * permute()
```

### `pivotColumn`

Returns address of pivotColumn region (also used for permuting)

```cpp
int * pivotColumn()
```

### `pivotRegion`

Returns address of pivot region.

```cpp
CoinFactorizationDouble * pivotRegion()
```

### `permuteBack`

Returns address of permuteBack region.

```cpp
int * permuteBack()
```

### `lastRow`

Returns address of lastRow region.

```cpp
int * lastRow()
```

### `pivotColumnBack`

Returns address of pivotColumnBack region (also used for permuting) Now uses firstCount to save memory allocation.

```cpp
int * pivotColumnBack()
```

### `startRowL`

Start of each row in L.

```cpp
int * startRowL()
```

### `startColumnL`

Start of each column in L.

```cpp
int * startColumnL()
```

### `indexColumnL`

Index of column in row for L.

```cpp
int * indexColumnL()
```

### `indexRowL`

Row indices of L.

```cpp
int * indexRowL()
```

### `elementByRowL`

Elements in L (row copy)

```cpp
CoinFactorizationDouble * elementByRowL()
```

### `numberRowsExtra`

Number of Rows after iterating.

```cpp
int numberRowsExtra()
```

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

### `numberL`

Number in L.

```cpp
int numberL()
```

### `baseL`

Base of L.

```cpp
int baseL()
```

### `maximumRowsExtra`

Maximum of Rows after iterating.

```cpp
int maximumRowsExtra()
```

### `numberColumns`

Total number of columns in factorization.

```cpp
int numberColumns()
```

### `numberElements`

Total number of elements in factorization.

```cpp
int numberElements()
```

### `numberForrestTomlin`

Length of FT vector.

```cpp
int numberForrestTomlin()
```

### `numberGoodColumns`

Number of good columns in factorization.

```cpp
int numberGoodColumns()
```

### `areaFactor`

Whether larger areas needed.

```cpp
double areaFactor()
```

### `areaFactor`

```cpp
void areaFactor(double value)
```

**Parameters:**

- `value` (double)

### `adjustedAreaFactor`

Returns areaFactor but adjusted for dense.

```cpp
double adjustedAreaFactor()
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

### `messageLevel`

Level of detail of messages.

```cpp
int messageLevel()
```

### `messageLevel`

```cpp
void messageLevel(int value)
```

**Parameters:**

- `value` (int)

### `maximumPivots`

Maximum number of pivots between factorizations.

```cpp
int maximumPivots()
```

### `maximumPivots`

```cpp
void maximumPivots(int value)
```

**Parameters:**

- `value` (int)

### `denseThreshold`

Gets dense threshold.

```cpp
int denseThreshold()
```

### `setDenseThreshold`

Sets dense threshold.

```cpp
void setDenseThreshold(int value)
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

### `maximumCoefficient`

Returns maximum absolute value in factorization.

```cpp
double maximumCoefficient()
```

### `forrestTomlin`

true if Forrest Tomlin update, false if PFI

```cpp
bool forrestTomlin()
```

### `setForrestTomlin`

```cpp
void setForrestTomlin(bool value)
```

**Parameters:**

- `value` (bool)

### `spaceForForrestTomlin`

True if FT update and space.

```cpp
bool spaceForForrestTomlin()
```

### `numberDense`

Returns number of dense rows.

```cpp
int numberDense()
```

### `numberElementsU`

Returns number in U area.

```cpp
int numberElementsU()
```

### `setNumberElementsU`

Setss number in U area.

```cpp
void setNumberElementsU(int value)
```

**Parameters:**

- `value` (int)

### `lengthAreaU`

Returns length of U area.

```cpp
int lengthAreaU()
```

### `numberElementsL`

Returns number in L area.

```cpp
int numberElementsL()
```

### `lengthAreaL`

Returns length of L area.

```cpp
int lengthAreaL()
```

### `numberElementsR`

Returns number in R area.

```cpp
int numberElementsR()
```

### `numberCompressions`

Number of compressions done.

```cpp
int numberCompressions()
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

### `elementU`

Elements of U.

```cpp
CoinFactorizationDouble * elementU()
```

### `indexRowU`

Row indices of U.

```cpp
int * indexRowU()
```

### `startColumnU`

Start of each column in U.

```cpp
int * startColumnU()
```

### `maximumColumnsExtra`

Maximum number of Columns after iterating.

```cpp
int maximumColumnsExtra()
```

### `biasLU`

L to U bias 0 - U bias, 1 - some U bias, 2 some L bias, 3 L bias.

```cpp
int biasLU()
```

### `setBiasLU`

```cpp
void setBiasLU(int value)
```

**Parameters:**

- `value` (int)

### `persistenceFlag`

Array persistence flag If 0 then as now (delete/new) 1 then only do arrays if bigger needed 2 as 1 but give a bit extra if bigger needed.

```cpp
int persistenceFlag()
```

### `setPersistenceFlag`

```cpp
void setPersistenceFlag(int value)
```

**Parameters:**

- `value` (int)

### `replaceColumn`

Update factorization after basis change (rank-one update)

```cpp
int replaceColumn(CoinIndexedVector * regionSparse, int pivotRow, double pivotCheck, bool checkBeforeModifying = false, double acceptablePivot = 1.0e-8)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *) - The column entering the basis (after FTRAN)
- `pivotRow` (int) - Row index of the leaving variable
- `pivotCheck` (double) - Expected pivot value for accuracy verification
- `checkBeforeModifying` (bool) - If true, validate before modifying factors
- `acceptablePivot` (double) - Minimum acceptable |pivot| for stability

**Returns:** 0=OK, 1=Probably OK, 2=singular, 3=no room

<div class="method-card">
**Algorithm:** @algorithm Forrest-Tomlin update (when doForrestTomlin_=true) or PFI @math For basis change B_new = B_old + (a_q - a_p) · e_p': Forrest-Tomlin maintains L and updates U with spike elimination. PFI (Product Form of Inverse) appends eta matrices. @complexity O(nnz(column)) for FT update; PFI grows over iterations
</div>

### `replaceColumnU`

Combines BtranU and delete elements If deleted is NULL then delete elements otherwise store where elements are.

```cpp
void replaceColumnU(CoinIndexedVector * regionSparse, int *COIN_RESTRICT deleted, int internalPivotRow)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `deleted` (int *COIN_RESTRICT)
- `internalPivotRow` (int)

### `updateColumnFT`

Forward transformation (FTRAN): solve Bx = b.

```cpp
int updateColumnFT(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *) - Work vector (must start as zero, returns zero)
- `regionSparse2` (CoinIndexedVector *) - Right-hand side b on input, solution x on output

**Returns:** Number of nonzeros in result, negative if no room for FT update

<div class="method-card">
**Algorithm:** @algorithm FTRAN with optional Forrest-Tomlin update preparation @math Solves B·x = b where B = L·U: Step 1: Solve L·y = b (forward substitution) Step 2: Solve U·x = y (backward substitution) @complexity O(nnz(L) + nnz(U)) - exploits sparsity
</div>

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

Updates one column (FTRAN) from region2 Tries to do FT update number returned is negative if no room.

```cpp
int updateTwoColumnsFT(CoinIndexedVector * regionSparse1, CoinIndexedVector * regionSparse2, CoinIndexedVector * regionSparse3, bool noPermuteRegion3 = false)
```

**Parameters:**

- `regionSparse1` (CoinIndexedVector *)
- `regionSparse2` (CoinIndexedVector *)
- `regionSparse3` (CoinIndexedVector *)
- `noPermuteRegion3` (bool)

### `updateColumnTranspose`

Backward transformation (BTRAN): solve B'y = c.

```cpp
int updateColumnTranspose(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *) - Work vector (must start as zero, returns zero)
- `regionSparse2` (CoinIndexedVector *) - Right-hand side c on input, solution y on output

**Returns:** Number of nonzeros in result

<div class="method-card">
**Algorithm:** @algorithm BTRAN using transposed triangular solves @math Solves B'·y = c where B = L·U, so B' = U'·L': Step 1: Solve U'·z = c (forward substitution on U') Step 2: Solve L'·y = z (backward substitution on L') @complexity O(nnz(L) + nnz(U)) - exploits sparsity
</div>

### `updateOneColumnTranspose`

Part of twocolumnsTranspose.

```cpp
void updateOneColumnTranspose(CoinIndexedVector * regionWork, int & statistics)
```

**Parameters:**

- `regionWork` (CoinIndexedVector *)
- `statistics` (int &)

### `updateTwoColumnsTranspose`

Updates two columns (BTRAN) from regionSparse2 and 3 regionSparse starts as zero and is zero at end Note - if regionSparse2 packed on input - will be packed on output - same for 3.

```cpp
void updateTwoColumnsTranspose(CoinIndexedVector * regionSparse, CoinIndexedVector * regionSparse2, CoinIndexedVector * regionSparse3, int type)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `regionSparse2` (CoinIndexedVector *)
- `regionSparse3` (CoinIndexedVector *)
- `type` (int)

### `goSparse`

makes a row copy of L for speed and to allow very sparse problems

```cpp
void goSparse()
```

### `sparseThreshold`

get sparse threshold

```cpp
int sparseThreshold()
```

### `sparseThreshold`

set sparse threshold

```cpp
void sparseThreshold(int value)
```

**Parameters:**

- `value` (int)

### `clearArrays`

Get rid of all memory.

```cpp
void clearArrays()
```

### `add`

Adds given elements to Basis and updates factorization, can increase size of basis.

```cpp
int add(int numberElements, int indicesRow, int indicesColumn, double elements)
```

**Parameters:**

- `numberElements` (int)
- `indicesRow` (int)
- `indicesColumn` (int)
- `elements` (double)

### `addColumn`

Adds one Column to basis, can increase size of basis.

```cpp
int addColumn(int numberElements, int indicesRow, double elements)
```

**Parameters:**

- `numberElements` (int)
- `indicesRow` (int)
- `elements` (double)

### `addRow`

Adds one Row to basis, can increase size of basis.

```cpp
int addRow(int numberElements, int indicesColumn, double elements)
```

**Parameters:**

- `numberElements` (int)
- `indicesColumn` (int)
- `elements` (double)

### `deleteColumn`

Deletes one Column from basis, returns rank.

```cpp
int deleteColumn(int Row)
```

**Parameters:**

- `Row` (int)

### `deleteRow`

Deletes one Row from basis, returns rank.

```cpp
int deleteRow(int Row)
```

**Parameters:**

- `Row` (int)

### `replaceRow`

Replaces one Row in basis, At present assumes just a singleton on row is in basis returns 0=OK, 1=Probably OK, 2=singular, 3 no space.

```cpp
int replaceRow(int whichRow, int numberElements, const int indicesColumn, const double elements)
```

**Parameters:**

- `whichRow` (int)
- `numberElements` (int)
- `indicesColumn` (const int)
- `elements` (const double)

### `emptyRows`

Takes out all entries for given rows.

```cpp
void emptyRows(int numberToEmpty, const int which)
```

**Parameters:**

- `numberToEmpty` (int)
- `which` (const int)

### `checkSparse`

See if worth going sparse.

```cpp
void checkSparse()
```

### `collectStatistics`

For statistics.

```cpp
bool collectStatistics()
```

### `setCollectStatistics`

For statistics.

```cpp
void setCollectStatistics(bool onOff)
```

**Parameters:**

- `onOff` (bool)

### `gutsOfDestructor`

The real work of constructors etc 0 just scalars, 1 bit normal.

```cpp
void gutsOfDestructor(int type = 1)
```

**Parameters:**

- `type` (int)

### `gutsOfInitialize`

1 bit - tolerances etc, 2 more, 4 dummy arrays

```cpp
void gutsOfInitialize(int type)
```

**Parameters:**

- `type` (int)

### `gutsOfCopy`

```cpp
void gutsOfCopy(const CoinFactorization & other)
```

**Parameters:**

- `other` (const CoinFactorization &)

### `resetStatistics`

Reset all sparsity etc statistics.

```cpp
void resetStatistics()
```

### `getAreas`

Gets space for a factorization, called by constructors.

```cpp
void getAreas(int numberRows, int numberColumns, int maximumL, int maximumU)
```

**Parameters:**

- `numberRows` (int)
- `numberColumns` (int)
- `maximumL` (int)
- `maximumU` (int)

### `preProcess`

PreProcesses raw triplet data.

```cpp
void preProcess(int state, int possibleDuplicates = -1)
```

**Parameters:**

- `state` (int)
- `possibleDuplicates` (int)

### `factor`

Does most of factorization.

```cpp
int factor()
```

### `replaceColumnPFI`

Replaces one Column to basis for PFI returns 0=OK, 1=Probably OK, 2=singular, 3=no room.

```cpp
int replaceColumnPFI(CoinIndexedVector * regionSparse, int pivotRow, double alpha)
```

**Parameters:**

- `regionSparse` (CoinIndexedVector *)
- `pivotRow` (int)
- `alpha` (double)

## Source

Header: `layer-0/CoinUtils/src/CoinFactorization.hpp`
