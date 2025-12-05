+++
title = "CoinSnapshot"
description = "NON Abstract Base Class for interfacing with cut generators or branching code or ... It is designed to be snapshot of a problem at a node in tree."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinSnapshot.hpp"
api_url = "/api/coinutils/CoinSnapshot.json"
+++

NON Abstract Base Class for interfacing with cut generators or branching code or ... It is designed to be snapshot of a problem at a node in tree.


## Description

The class may or may not own the arrays - see owned_
Querying a problem that has no data associated with it will result in zeros for the number of rows and columns, and NULL pointers from the methods that return arrays.

## Public Methods

### `getNumCols`

Get number of columns.

```cpp
int getNumCols()
```

### `getNumRows`

Get number of rows.

```cpp
int getNumRows()
```

### `getNumElements`

Get number of nonzero elements.

```cpp
int getNumElements()
```

### `getNumIntegers`

Get number of integer variables.

```cpp
int getNumIntegers()
```

### `getColLower`

Get pointer to array[getNumCols()] of column lower bounds.

```cpp
const double * getColLower()
```

### `getColUpper`

Get pointer to array[getNumCols()] of column upper bounds.

```cpp
const double * getColUpper()
```

### `getRowLower`

Get pointer to array[getNumRows()] of row lower bounds.

```cpp
const double * getRowLower()
```

### `getRowUpper`

Get pointer to array[getNumRows()] of row upper bounds.

```cpp
const double * getRowUpper()
```

### `getRightHandSide`

Get pointer to array[getNumRows()] of row right-hand sides This gives same results as OsiSolverInterface for useful cases If getRowUpper()[i] != infinity then getRightHandSide()[i] == getRowUpper()[i] else getRightHandSide()[i] == getRowLower()[i].

```cpp
const double * getRightHandSide()
```

### `getObjCoefficients`

Get pointer to array[getNumCols()] of objective function coefficients.

```cpp
const double * getObjCoefficients()
```

### `getObjSense`

Get objective function sense (1 for min (default), -1 for max)

```cpp
double getObjSense()
```

### `isContinuous`

Return true if variable is continuous.

```cpp
bool isContinuous(int colIndex)
```

**Parameters:**

- `colIndex` (int)

### `isBinary`

Return true if variable is binary.

```cpp
bool isBinary(int colIndex)
```

**Parameters:**

- `colIndex` (int)

### `isInteger`

Return true if column is integer.

```cpp
bool isInteger(int colIndex)
```

**Parameters:**

- `colIndex` (int)

### `isIntegerNonBinary`

Return true if variable is general integer.

```cpp
bool isIntegerNonBinary(int colIndex)
```

**Parameters:**

- `colIndex` (int)

### `isFreeBinary`

Return true if variable is binary and not fixed at either bound.

```cpp
bool isFreeBinary(int colIndex)
```

**Parameters:**

- `colIndex` (int)

### `getColType`

Get colType array ('B', 'I', or 'C' for Binary, Integer and Continuous)

```cpp
const char * getColType()
```

### `getMatrixByRow`

Get pointer to row-wise copy of current matrix.

```cpp
const CoinPackedMatrix * getMatrixByRow()
```

### `getMatrixByCol`

Get pointer to column-wise copy of current matrix.

```cpp
const CoinPackedMatrix * getMatrixByCol()
```

### `getOriginalMatrixByRow`

Get pointer to row-wise copy of "original" matrix.

```cpp
const CoinPackedMatrix * getOriginalMatrixByRow()
```

### `getOriginalMatrixByCol`

Get pointer to column-wise copy of "original" matrix.

```cpp
const CoinPackedMatrix * getOriginalMatrixByCol()
```

### `getColSolution`

Get pointer to array[getNumCols()] of primal variable values.

```cpp
const double * getColSolution()
```

### `getRowPrice`

Get pointer to array[getNumRows()] of dual variable values.

```cpp
const double * getRowPrice()
```

### `getReducedCost`

Get a pointer to array[getNumCols()] of reduced costs.

```cpp
const double * getReducedCost()
```

### `getRowActivity`

Get pointer to array[getNumRows()] of row activity levels (constraint matrix times the solution vector).

```cpp
const double * getRowActivity()
```

### `getDoNotSeparateThis`

Get pointer to array[getNumCols()] of primal variable values which should not be separated (for debug)

```cpp
const double * getDoNotSeparateThis()
```

### `getInfinity`

Get solver's value for infinity.

```cpp
double getInfinity()
```

### `getObjValue`

Get objective function value - includinbg any offset i.e.

```cpp
double getObjValue()
```

### `getObjOffset`

Get objective offset i.e. sum c sub j * x subj -objValue = objOffset.

```cpp
double getObjOffset()
```

### `getDualTolerance`

Get dual tolerance.

```cpp
double getDualTolerance()
```

### `getPrimalTolerance`

Get primal tolerance.

```cpp
double getPrimalTolerance()
```

### `getIntegerTolerance`

Get integer tolerance.

```cpp
double getIntegerTolerance()
```

### `getIntegerUpperBound`

Get integer upper bound i.e. best solution * getObjSense.

```cpp
double getIntegerUpperBound()
```

### `getIntegerLowerBound`

Get integer lower bound i.e. best possible solution * getObjSense.

```cpp
double getIntegerLowerBound()
```

### `loadProblem`

Load in an problem by copying the arguments (the constraints on the rows are given by lower and upper bounds).

```cpp
void loadProblem(const CoinPackedMatrix & matrix, const double * collb, const double * colub, const double * obj, const double * rowlb, const double * rowub, bool makeRowCopy = false)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)
- `collb` (const double *)
- `colub` (const double *)
- `obj` (const double *)
- `rowlb` (const double *)
- `rowub` (const double *)
- `makeRowCopy` (bool)

### `setNumCols`

Set number of columns.

```cpp
void setNumCols(int value)
```

**Parameters:**

- `value` (int)

### `setNumRows`

Set number of rows.

```cpp
void setNumRows(int value)
```

**Parameters:**

- `value` (int)

### `setNumElements`

Set number of nonzero elements.

```cpp
void setNumElements(int value)
```

**Parameters:**

- `value` (int)

### `setNumIntegers`

Set number of integer variables.

```cpp
void setNumIntegers(int value)
```

**Parameters:**

- `value` (int)

### `setColLower`

Set pointer to array[getNumCols()] of column lower bounds.

```cpp
void setColLower(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setColUpper`

Set pointer to array[getNumCols()] of column upper bounds.

```cpp
void setColUpper(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setRowLower`

Set pointer to array[getNumRows()] of row lower bounds.

```cpp
void setRowLower(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setRowUpper`

Set pointer to array[getNumRows()] of row upper bounds.

```cpp
void setRowUpper(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setRightHandSide`

Set pointer to array[getNumRows()] of row right-hand sides This gives same results as OsiSolverInterface for useful cases If getRowUpper()[i] != infinity then getRightHandSide()[i] == getRowUpper()[i] else getRightHandSide()[i] == getRowLower()[i].

```cpp
void setRightHandSide(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `createRightHandSide`

Create array[getNumRows()] of row right-hand sides using existing information This gives same results as OsiSolverInterface for useful cases If getRowUpper()[i] != infinity then getRightHandSide()[i] == getRowUpper()[i] else getRightHandSide()[i] == getRowLower()[i].

```cpp
void createRightHandSide()
```

### `setObjCoefficients`

Set pointer to array[getNumCols()] of objective function coefficients.

```cpp
void setObjCoefficients(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setObjSense`

Set objective function sense (1 for min (default), -1 for max)

```cpp
void setObjSense(double value)
```

**Parameters:**

- `value` (double)

### `setColType`

Set colType array ('B', 'I', or 'C' for Binary, Integer and Continuous)

```cpp
void setColType(const char * array, bool copyIn = true)
```

**Parameters:**

- `array` (const char *)
- `copyIn` (bool)

### `setMatrixByRow`

Set pointer to row-wise copy of current matrix.

```cpp
void setMatrixByRow(const CoinPackedMatrix * matrix, bool copyIn = true)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix *)
- `copyIn` (bool)

### `createMatrixByRow`

Create row-wise copy from MatrixByCol.

```cpp
void createMatrixByRow()
```

### `setMatrixByCol`

Set pointer to column-wise copy of current matrix.

```cpp
void setMatrixByCol(const CoinPackedMatrix * matrix, bool copyIn = true)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix *)
- `copyIn` (bool)

### `setOriginalMatrixByRow`

Set pointer to row-wise copy of "original" matrix.

```cpp
void setOriginalMatrixByRow(const CoinPackedMatrix * matrix, bool copyIn = true)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix *)
- `copyIn` (bool)

### `setOriginalMatrixByCol`

Set pointer to column-wise copy of "original" matrix.

```cpp
void setOriginalMatrixByCol(const CoinPackedMatrix * matrix, bool copyIn = true)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix *)
- `copyIn` (bool)

### `setColSolution`

Set pointer to array[getNumCols()] of primal variable values.

```cpp
void setColSolution(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setRowPrice`

Set pointer to array[getNumRows()] of dual variable values.

```cpp
void setRowPrice(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setReducedCost`

Set a pointer to array[getNumCols()] of reduced costs.

```cpp
void setReducedCost(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setRowActivity`

Set pointer to array[getNumRows()] of row activity levels (constraint matrix times the solution vector).

```cpp
void setRowActivity(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setDoNotSeparateThis`

Set pointer to array[getNumCols()] of primal variable values which should not be separated (for debug)

```cpp
void setDoNotSeparateThis(const double * array, bool copyIn = true)
```

**Parameters:**

- `array` (const double *)
- `copyIn` (bool)

### `setInfinity`

Set solver's value for infinity.

```cpp
void setInfinity(double value)
```

**Parameters:**

- `value` (double)

### `setObjValue`

Set objective function value (including any rhs offset)

```cpp
void setObjValue(double value)
```

**Parameters:**

- `value` (double)

### `setObjOffset`

Set objective offset i.e. sum c sub j * x subj -objValue = objOffset.

```cpp
void setObjOffset(double value)
```

**Parameters:**

- `value` (double)

### `setDualTolerance`

Set dual tolerance.

```cpp
void setDualTolerance(double value)
```

**Parameters:**

- `value` (double)

### `setPrimalTolerance`

Set primal tolerance.

```cpp
void setPrimalTolerance(double value)
```

**Parameters:**

- `value` (double)

### `setIntegerTolerance`

Set integer tolerance.

```cpp
void setIntegerTolerance(double value)
```

**Parameters:**

- `value` (double)

### `setIntegerUpperBound`

Set integer upper bound i.e. best solution * getObjSense.

```cpp
void setIntegerUpperBound(double value)
```

**Parameters:**

- `value` (double)

### `setIntegerLowerBound`

Set integer lower bound i.e. best possible solution * getObjSense.

```cpp
void setIntegerLowerBound(double value)
```

**Parameters:**

- `value` (double)

### `CoinSnapshot`

Default Constructor.

```cpp
 CoinSnapshot()
```

### `CoinSnapshot`

Copy constructor.

```cpp
 CoinSnapshot(const CoinSnapshot & )
```

**Parameters:**

- `` (const CoinSnapshot &)

### `operator=`

Assignment operator.

```cpp
CoinSnapshot & operator=(const CoinSnapshot & rhs)
```

**Parameters:**

- `rhs` (const CoinSnapshot &)

### `~CoinSnapshot`

Destructor.

```cpp
 ~CoinSnapshot()
```

## Source

Header: `layer-0/CoinUtils/src/CoinSnapshot.hpp`
