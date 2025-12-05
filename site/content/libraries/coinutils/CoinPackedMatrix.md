+++
title = "CoinPackedMatrix"
description = "Sparse Matrix Base Class."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPackedMatrix.hpp"
api_url = "/api/coinutils/CoinPackedMatrix.json"
+++

Sparse Matrix Base Class.


## Description

This class is intended to represent sparse matrices using row-major or column-major ordering. The representation is very efficient for adding, deleting, or retrieving major-dimension vectors. Adding a minor-dimension vector is less efficient, but can be helped by providing "extra" space as described in the next paragraph. Deleting a minor-dimension vector requires inspecting all coefficients in the matrix. Retrieving a minor-dimension vector would incur the same cost and is not supported (except in the sense that you can write a loop to retrieve all coefficients one at a time). Consider physically transposing the matrix, or keeping a second copy with the other major-vector ordering.
The sparse represention can be completely compact or it can have "extra" space available at the end of each major vector. Incorporating extra space into the sparse matrix representation can improve performance in cases where new data needs to be inserted into the packed matrix against the major-vector orientation (e.g, inserting a row into a matrix stored in column-major order).
For example if the matrix: 3  1  0   -2   -1  0  0   -1                 
   0  2  1.1  0    0  0  0    0                       
   0  0  1    0    0  1  0    0         
   0  0  0    2.8  0  0 -1.2  0   
 5.6  0  0    0    1  0  0    1.9

was stored by rows (with no extra space) in 
CoinPackedMatrix r then: 
  r.getElements() returns a vector containing: 
    3 1 -2 -1 -1 2 1.1 1 1 2.8 -1.2 5.6 1 1.9 
  r.getIndices() returns a vector containing: 
    0 1  3  4  7 1 2   2 5 3    6   0   4 7 
  r.getVectorStarts() returns a vector containing: 
    0 5 7 9 11 14 
  r.getNumElements() returns 14. 
  r.getMajorDim() returns 5. 
  r.getVectorSize(0) returns 5. 
  r.getVectorSize(1) returns 2. 
  r.getVectorSize(2) returns 2. 
  r.getVectorSize(3) returns 2. 
  r.getVectorSize(4) returns 3. 

If stored by columns (with no extra space) then: 
  c.getElements() returns a vector containing: 
    3 5.6 1 2 1.1 1 -2 2.8 -1 1 1 -1.2 -1 1.9 
  c.getIndices() returns a vector containing: 
    0  4  0 1 1   2  0 3    0 4 2  3    0 4 
  c.getVectorStarts() returns a vector containing: 
    0 2 4 6 8 10 11 12 14 
  c.getNumElements() returns 14. 
  c.getMajorDim() returns 8.
Compiling this class with CLP_NO_VECTOR defined will excise all methods which use CoinPackedVectorBase, CoinPackedVector, or CoinShallowPackedVector as parameters or return types.
Compiling this class with COIN_FAST_CODE defined removes index range checks.

## Public Methods

### `getExtraGap`

Return the current setting of the extra gap.

```cpp
double getExtraGap()
```

### `getExtraMajor`

Return the current setting of the extra major.

```cpp
double getExtraMajor()
```

### `reserve`

Reserve sufficient space for appending major-ordered vectors.

```cpp
void reserve(const int newMaxMajorDim, const CoinBigIndex newMaxSize, bool create = false)
```

**Parameters:**

- `newMaxMajorDim` (const int)
- `newMaxSize` (const CoinBigIndex)
- `create` (bool)

### `clear`

Clear the data, but do not free any arrays.

```cpp
void clear()
```

### `isColOrdered`

Whether the packed matrix is column major ordered or not.

```cpp
bool isColOrdered()
```

### `hasGaps`

Whether the packed matrix has gaps or not.

```cpp
bool hasGaps()
```

### `getNumElements`

Number of entries in the packed matrix.

```cpp
CoinBigIndex getNumElements()
```

### `getNumCols`

Number of columns.

```cpp
int getNumCols()
```

### `getNumRows`

Number of rows.

```cpp
int getNumRows()
```

### `getElements`

A vector containing the elements in the packed matrix.

```cpp
const double * getElements()
```

### `getIndices`

A vector containing the minor indices of the elements in the packed matrix.

```cpp
const int * getIndices()
```

### `getSizeVectorStarts`

The size of the `vectorStarts` array.

```cpp
int getSizeVectorStarts()
```

### `getSizeVectorLengths`

The size of the `vectorLengths` array.

```cpp
int getSizeVectorLengths()
```

### `getVectorStarts`

The positions where the major-dimension vectors start in elements and indices.

```cpp
const CoinBigIndex * getVectorStarts()
```

### `getVectorLengths`

The lengths of the major-dimension vectors.

```cpp
const int * getVectorLengths()
```

### `getVectorFirst`

The position of the first element in the i'th major-dimension vector.

```cpp
CoinBigIndex getVectorFirst(const int i)
```

**Parameters:**

- `i` (const int)

### `getVectorLast`

The position of the last element (well, one entry past the last) in the i'th major-dimension vector.

```cpp
CoinBigIndex getVectorLast(const int i)
```

**Parameters:**

- `i` (const int)

### `getVectorSize`

The length of i'th vector.

```cpp
int getVectorSize(const int i)
```

**Parameters:**

- `i` (const int)

### `getVector`

Return the i'th vector in matrix.

```cpp
const CoinShallowPackedVector getVector(int i)
```

**Parameters:**

- `i` (int)

### `getMajorIndices`

Returns an array containing major indices.

```cpp
int * getMajorIndices()
```

### `setDimensions`

Set the dimensions of the matrix.

```cpp
void setDimensions(int numrows, int numcols)
```

**Parameters:**

- `numrows` (int)
- `numcols` (int)

### `setExtraGap`

Set the extra gap to be allocated to the specified value.

```cpp
void setExtraGap(const double newGap)
```

**Parameters:**

- `newGap` (const double)

### `setExtraMajor`

Set the extra major to be allocated to the specified value.

```cpp
void setExtraMajor(const double newMajor)
```

**Parameters:**

- `newMajor` (const double)

### `appendCol`

```cpp
void appendCol(const CoinPackedVectorBase & vec)
```

**Parameters:**

- `vec` (const CoinPackedVectorBase &)

### `appendCol`

```cpp
void appendCol(const int vecsize, const int * vecind, const double * vecelem)
```

**Parameters:**

- `vecsize` (const int)
- `vecind` (const int *)
- `vecelem` (const double *)

### `appendCols`

```cpp
void appendCols(const int numcols, const CoinPackedVectorBase *const * cols)
```

**Parameters:**

- `numcols` (const int)
- `cols` (const CoinPackedVectorBase *const *)

### `appendCols`

```cpp
int appendCols(const int numcols, const CoinBigIndex * columnStarts, const int * row, const double * element, int numberRows = -1)
```

**Parameters:**

- `numcols` (const int)
- `columnStarts` (const CoinBigIndex *)
- `row` (const int *)
- `element` (const double *)
- `numberRows` (int)

### `appendRow`

```cpp
void appendRow(const CoinPackedVectorBase & vec)
```

**Parameters:**

- `vec` (const CoinPackedVectorBase &)

### `appendRow`

```cpp
void appendRow(const int vecsize, const int * vecind, const double * vecelem)
```

**Parameters:**

- `vecsize` (const int)
- `vecind` (const int *)
- `vecelem` (const double *)

### `appendRows`

```cpp
void appendRows(const int numrows, const CoinPackedVectorBase *const * rows)
```

**Parameters:**

- `numrows` (const int)
- `rows` (const CoinPackedVectorBase *const *)

### `appendRows`

```cpp
int appendRows(const int numrows, const CoinBigIndex * rowStarts, const int * column, const double * element, int numberColumns = -1)
```

**Parameters:**

- `numrows` (const int)
- `rowStarts` (const CoinBigIndex *)
- `column` (const int *)
- `element` (const double *)
- `numberColumns` (int)

### `rightAppendPackedMatrix`

Append the argument to the "right" of the current matrix.

```cpp
void rightAppendPackedMatrix(const CoinPackedMatrix & matrix)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)

### `bottomAppendPackedMatrix`

Append the argument to the "bottom" of the current matrix.

```cpp
void bottomAppendPackedMatrix(const CoinPackedMatrix & matrix)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)

### `deleteCols`

Delete the columns whose indices are listed in `indDel`.

```cpp
void deleteCols(const int numDel, const int * indDel)
```

**Parameters:**

- `numDel` (const int)
- `indDel` (const int *)

### `deleteRows`

Delete the rows whose indices are listed in `indDel`.

```cpp
void deleteRows(const int numDel, const int * indDel)
```

**Parameters:**

- `numDel` (const int)
- `indDel` (const int *)

### `replaceVector`

Replace the elements of a vector.

```cpp
void replaceVector(const int index, const int numReplace, const double * newElements)
```

**Parameters:**

- `index` (const int)
- `numReplace` (const int)
- `newElements` (const double *)

### `modifyCoefficient`

Modify one element of packed matrix.

```cpp
void modifyCoefficient(int row, int column, double newElement, bool keepZero = false)
```

**Parameters:**

- `row` (int)
- `column` (int)
- `newElement` (double)
- `keepZero` (bool)

### `getCoefficient`

Return one element of packed matrix.

```cpp
double getCoefficient(int row, int column)
```

**Parameters:**

- `row` (int)
- `column` (int)

### `compress`

Eliminate all elements in matrix whose absolute value is less than threshold.

```cpp
CoinBigIndex compress(double threshold)
```

**Parameters:**

- `threshold` (double)

### `eliminateDuplicates`

Eliminate all duplicate AND small elements in matrix The column starts are not affected.

```cpp
CoinBigIndex eliminateDuplicates(double threshold)
```

**Parameters:**

- `threshold` (double)

### `orderMatrix`

Sort all columns so indices are increasing.in each column.

```cpp
void orderMatrix()
```

### `cleanMatrix`

Really clean up matrix.

```cpp
CoinBigIndex cleanMatrix(double threshold = 1.0e-20)
```

**Parameters:**

- `threshold` (double)

### `removeGaps`

Remove the gaps from the matrix if there were any Can also remove small elements fabs() <= removeValue.

```cpp
void removeGaps(double removeValue = -1.0)
```

**Parameters:**

- `removeValue` (double)

### `submatrixOf`

Extract a submatrix from matrix.

```cpp
void submatrixOf(const CoinPackedMatrix & matrix, const int numMajor, const int * indMajor)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)
- `numMajor` (const int)
- `indMajor` (const int *)

### `submatrixOfWithDuplicates`

Extract a submatrix from matrix.

```cpp
void submatrixOfWithDuplicates(const CoinPackedMatrix & matrix, const int numMajor, const int * indMajor)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)
- `numMajor` (const int)
- `indMajor` (const int *)

### `copyOf`

Copy method.

```cpp
void copyOf(const CoinPackedMatrix & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedMatrix &)

### `copyOf`

Copy the arguments to the matrix.

```cpp
void copyOf(const bool colordered, const int minor, const int major, const CoinBigIndex numels, const double * elem, const int * ind, const CoinBigIndex * start, const int * len, const double extraMajor = 0.0, const double extraGap = 0.0)
```

**Parameters:**

- `colordered` (const bool)
- `minor` (const int)
- `major` (const int)
- `numels` (const CoinBigIndex)
- `elem` (const double *)
- `ind` (const int *)
- `start` (const CoinBigIndex *)
- `len` (const int *)
- `extraMajor` (const double)
- `extraGap` (const double)

### `copyReuseArrays`

Copy method.

```cpp
void copyReuseArrays(const CoinPackedMatrix & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedMatrix &)

### `reverseOrderedCopyOf`

Make a reverse-ordered copy.

```cpp
void reverseOrderedCopyOf(const CoinPackedMatrix & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedMatrix &)

### `assignMatrix`

Assign the arguments to the matrix.

```cpp
void assignMatrix(const bool colordered, const int minor, const int major, const CoinBigIndex numels, double *& elem, int *& ind, CoinBigIndex *& start, int *& len, const int maxmajor = -1, const CoinBigIndex maxsize = -1)
```

**Parameters:**

- `colordered` (const bool)
- `minor` (const int)
- `major` (const int)
- `numels` (const CoinBigIndex)
- `elem` (double *&)
- `ind` (int *&)
- `start` (CoinBigIndex *&)
- `len` (int *&)
- `maxmajor` (const int)
- `maxsize` (const CoinBigIndex)

### `operator=`

Assignment operator.

```cpp
CoinPackedMatrix & operator=(const CoinPackedMatrix & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedMatrix &)

### `reverseOrdering`

Reverse the ordering of the packed matrix.

```cpp
void reverseOrdering()
```

### `transpose`

Transpose the matrix.

```cpp
void transpose()
```

### `swap`

Swap the content of two packed matrices.

```cpp
void swap(CoinPackedMatrix & matrix)
```

**Parameters:**

- `matrix` (CoinPackedMatrix &)

### `times`

Return `A * x` in `y`.

```cpp
void times(const double * x, double * y)
```

**Parameters:**

- `x` (const double *)
- `y` (double *)

### `times`

Return `A * x` in `y`.

```cpp
void times(const CoinPackedVectorBase & x, double * y)
```

**Parameters:**

- `x` (const CoinPackedVectorBase &)
- `y` (double *)

### `transposeTimes`

Return `x * A` in `y`.

```cpp
void transposeTimes(const double * x, double * y)
```

**Parameters:**

- `x` (const double *)
- `y` (double *)

### `transposeTimes`

Return `x * A` in `y`.

```cpp
void transposeTimes(const CoinPackedVectorBase & x, double * y)
```

**Parameters:**

- `x` (const CoinPackedVectorBase &)
- `y` (double *)

### `countOrthoLength`

Count the number of entries in every minor-dimension vector and return an array containing these lengths.

```cpp
int * countOrthoLength()
```

### `countOrthoLength`

Count the number of entries in every minor-dimension vector and fill in an array containing these lengths.

```cpp
void countOrthoLength(int * counts)
```

**Parameters:**

- `counts` (int *)

### `getMajorDim`

Major dimension.

```cpp
int getMajorDim()
```

### `setMajorDim`

Set major dimension.

```cpp
void setMajorDim(int value)
```

**Parameters:**

- `value` (int)

### `getMinorDim`

Minor dimension.

```cpp
int getMinorDim()
```

### `setMinorDim`

Set minor dimension.

```cpp
void setMinorDim(int value)
```

**Parameters:**

- `value` (int)

### `getMaxMajorDim`

Current maximum for major dimension.

```cpp
int getMaxMajorDim()
```

### `dumpMatrix`

Dump the matrix on stdout.

```cpp
void dumpMatrix(const char * fname = NULL)
```

**Parameters:**

- `fname` (const char *)

### `printMatrixElement`

Print a single matrix element.

```cpp
void printMatrixElement(const int row_val, const int col_val)
```

**Parameters:**

- `row_val` (const int)
- `col_val` (const int)

### `appendMajorVector`

Append a major-dimension vector to the end of the matrix.

```cpp
void appendMajorVector(const CoinPackedVectorBase & vec)
```

**Parameters:**

- `vec` (const CoinPackedVectorBase &)

### `appendMajorVector`

Append a major-dimension vector to the end of the matrix.

```cpp
void appendMajorVector(const int vecsize, const int * vecind, const double * vecelem)
```

**Parameters:**

- `vecsize` (const int)
- `vecind` (const int *)
- `vecelem` (const double *)

### `appendMajorVectors`

Append several major-dimensonvectors to the end of the matrix.

```cpp
void appendMajorVectors(const int numvecs, const CoinPackedVectorBase *const * vecs)
```

**Parameters:**

- `numvecs` (const int)
- `vecs` (const CoinPackedVectorBase *const *)

### `appendMinorVector`

Append a minor-dimension vector to the end of the matrix.

```cpp
void appendMinorVector(const CoinPackedVectorBase & vec)
```

**Parameters:**

- `vec` (const CoinPackedVectorBase &)

### `appendMinorVector`

Append a minor-dimension vector to the end of the matrix.

```cpp
void appendMinorVector(const int vecsize, const int * vecind, const double * vecelem)
```

**Parameters:**

- `vecsize` (const int)
- `vecind` (const int *)
- `vecelem` (const double *)

### `appendMinorVectors`

Append several minor-dimension vectors to the end of the matrix.

```cpp
void appendMinorVectors(const int numvecs, const CoinPackedVectorBase *const * vecs)
```

**Parameters:**

- `numvecs` (const int)
- `vecs` (const CoinPackedVectorBase *const *)

### `appendMinorFast`

Append a set of rows (columns) to the end of a column (row) ordered matrix.

```cpp
void appendMinorFast(const int number, const CoinBigIndex * starts, const int * index, const double * element)
```

**Parameters:**

- `number` (const int)
- `starts` (const CoinBigIndex *)
- `index` (const int *)
- `element` (const double *)

### `majorAppendSameOrdered`

Append the columns of the argument to the right end of this matrix.

```cpp
void majorAppendSameOrdered(const CoinPackedMatrix & matrix)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)

### `minorAppendSameOrdered`

Append the columns of the argument to the bottom end of this matrix.

```cpp
void minorAppendSameOrdered(const CoinPackedMatrix & matrix)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)

### `majorAppendOrthoOrdered`

Append the rows of the argument to the right end of this matrix.

```cpp
void majorAppendOrthoOrdered(const CoinPackedMatrix & matrix)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)

### `minorAppendOrthoOrdered`

Append the rows of the argument to the bottom end of this matrix.

```cpp
void minorAppendOrthoOrdered(const CoinPackedMatrix & matrix)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)

### `deleteMajorVectors`

Delete the major-dimension vectors whose indices are listed in `indDel`.

```cpp
void deleteMajorVectors(const int numDel, const int * indDel)
```

**Parameters:**

- `numDel` (const int)
- `indDel` (const int *)

### `deleteMinorVectors`

Delete the minor-dimension vectors whose indices are listed in `indDel`.

```cpp
void deleteMinorVectors(const int numDel, const int * indDel)
```

**Parameters:**

- `numDel` (const int)
- `indDel` (const int *)

### `timesMajor`

Return `A * x` (multiplied from the "right" direction) in `y`.

```cpp
void timesMajor(const double * x, double * y)
```

**Parameters:**

- `x` (const double *)
- `y` (double *)

### `timesMajor`

Return `A * x` (multiplied from the "right" direction) in `y`.

```cpp
void timesMajor(const CoinPackedVectorBase & x, double * y)
```

**Parameters:**

- `x` (const CoinPackedVectorBase &)
- `y` (double *)

### `timesMinor`

Return `A * x` (multiplied from the "right" direction) in `y`.

```cpp
void timesMinor(const double * x, double * y)
```

**Parameters:**

- `x` (const double *)
- `y` (double *)

### `timesMinor`

Return `A * x` (multiplied from the "right" direction) in `y`.

```cpp
void timesMinor(const CoinPackedVectorBase & x, double * y)
```

**Parameters:**

- `x` (const CoinPackedVectorBase &)
- `y` (double *)

### `isEquivalent`

Test for equivalence.

```cpp
bool isEquivalent(const CoinPackedMatrix & rhs, const FloatEqual & eq)
```

**Parameters:**

- `rhs` (const CoinPackedMatrix &)
- `eq` (const FloatEqual &)

### `isEquivalent2`

Test for equivalence and report differences.

```cpp
bool isEquivalent2(const CoinPackedMatrix & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedMatrix &)

### `isEquivalent`

Test for equivalence.

```cpp
bool isEquivalent(const CoinPackedMatrix & rhs)
```

**Parameters:**

- `rhs` (const CoinPackedMatrix &)

### `getMutableElements`

A vector containing the elements in the packed matrix.

```cpp
double * getMutableElements()
```

### `getMutableIndices`

A vector containing the minor indices of the elements in the packed matrix.

```cpp
int * getMutableIndices()
```

### `getMutableVectorStarts`

The positions where the major-dimension vectors start in element_ and index_.

```cpp
CoinBigIndex * getMutableVectorStarts()
```

### `getMutableVectorLengths`

The lengths of the major-dimension vectors.

```cpp
int * getMutableVectorLengths()
```

### `setNumElements`

Change the size of the bulk store after modifying - be careful.

```cpp
void setNumElements(CoinBigIndex value)
```

**Parameters:**

- `value` (CoinBigIndex)

### `nullElementArray`

```cpp
void nullElementArray()
```

### `nullStartArray`

```cpp
void nullStartArray()
```

### `nullLengthArray`

```cpp
void nullLengthArray()
```

### `nullIndexArray`

```cpp
void nullIndexArray()
```

### `CoinPackedMatrix`

Default Constructor creates an empty column ordered packed matrix.

```cpp
 CoinPackedMatrix()
```

### `CoinPackedMatrix`

A constructor where the ordering and the gaps are specified.

```cpp
 CoinPackedMatrix(const bool colordered, const double extraMajor, const double extraGap)
```

**Parameters:**

- `colordered` (const bool)
- `extraMajor` (const double)
- `extraGap` (const double)

### `CoinPackedMatrix`

```cpp
 CoinPackedMatrix(const bool colordered, const int minor, const int major, const CoinBigIndex numels, const double * elem, const int * ind, const CoinBigIndex * start, const int * len, const double extraMajor, const double extraGap)
```

**Parameters:**

- `colordered` (const bool)
- `minor` (const int)
- `major` (const int)
- `numels` (const CoinBigIndex)
- `elem` (const double *)
- `ind` (const int *)
- `start` (const CoinBigIndex *)
- `len` (const int *)
- `extraMajor` (const double)
- `extraGap` (const double)

### `CoinPackedMatrix`

```cpp
 CoinPackedMatrix(const bool colordered, const int minor, const int major, const CoinBigIndex numels, const double * elem, const int * ind, const CoinBigIndex * start, const int * len)
```

**Parameters:**

- `colordered` (const bool)
- `minor` (const int)
- `major` (const int)
- `numels` (const CoinBigIndex)
- `elem` (const double *)
- `ind` (const int *)
- `start` (const CoinBigIndex *)
- `len` (const int *)

### `CoinPackedMatrix`

Create packed matrix from triples.

```cpp
 CoinPackedMatrix(const bool colordered, const int * rowIndices, const int * colIndices, const double * elements, CoinBigIndex numels)
```

**Parameters:**

- `colordered` (const bool)
- `rowIndices` (const int *)
- `colIndices` (const int *)
- `elements` (const double *)
- `numels` (CoinBigIndex)

### `CoinPackedMatrix`

Copy constructor.

```cpp
 CoinPackedMatrix(const CoinPackedMatrix & m)
```

**Parameters:**

- `m` (const CoinPackedMatrix &)

### `CoinPackedMatrix`

Copy constructor with fine tuning.

```cpp
 CoinPackedMatrix(const CoinPackedMatrix & m, int extraForMajor, int extraElements, bool reverseOrdering = false)
```

**Parameters:**

- `m` (const CoinPackedMatrix &)
- `extraForMajor` (int)
- `extraElements` (int)
- `reverseOrdering` (bool)

### `CoinPackedMatrix`

Subset constructor (without gaps).

```cpp
 CoinPackedMatrix(const CoinPackedMatrix & wholeModel, int numberRows, const int * whichRows, int numberColumns, const int * whichColumns)
```

**Parameters:**

- `wholeModel` (const CoinPackedMatrix &)
- `numberRows` (int)
- `whichRows` (const int *)
- `numberColumns` (int)
- `whichColumns` (const int *)

### `~CoinPackedMatrix`

Destructor.

```cpp
 ~CoinPackedMatrix()
```

### `verifyMtx`

Scan the matrix for anomalies.

```cpp
int verifyMtx(int verbosity = 1, bool zeroesAreError = false)
```

**Parameters:**

- `verbosity` (int)
- `zeroesAreError` (bool)

## Source

Header: `layer-0/CoinUtils/src/CoinPackedMatrix.hpp`
