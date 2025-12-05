+++
title = "CoinModel"
description = "This is a simple minded model which is stored in a format which makes it easier to construct and modify but not efficient for algorithms."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinModel.hpp"
api_url = "/api/coinutils/CoinModel.json"
+++

This is a simple minded model which is stored in a format which makes it easier to construct and modify but not efficient for algorithms.


## Inheritance

Inherits from: `CoinBaseModel`

## Description

It has to be passed across to ClpModel or OsiSolverInterface by addRows, addCol(umn)s or loadProblem.
It may have up to four parts - 1) A matrix of doubles (or strings - see note A) 2) Column information including integer information and names 3) Row information including names 4) Quadratic objective (not implemented - but see A)
This class is meant to make it more efficient to build a model. It is at its most efficient when all additions are done as addRow or as addCol but not mixed. If only 1 and 2 exist then solver.addColumns may be used to pass to solver, if only 1 and 3 exist then solver.addRows may be used. Otherwise solver.loadProblem must be used.
If addRows and addColumns are mixed or if individual elements are set then the speed will drop to some extent and more memory will be used.
It is also possible to iterate over existing elements and to access columns and rows by name. Again each of these use memory and cpu time. However memory is unlikely to be critical as most algorithms will use much more.
Notes: A) Although this could be used to pass nonlinear information around the only use at present is to have named values e.g. value1 which can then be set to a value after model is created. I have no idea whether that could be useful but I thought it might be fun. Quadratic terms are allowed in strings! A solver could try and use this if so - the convention is that 0.5* quadratic is stored
B) This class could be useful for modeling.

## Public Methods

### `addRow`

add a row - numberInRow may be zero

```cpp
void addRow(int numberInRow, const int * columns, const double * elements, double rowLower = -, double rowUpper, const char * name = NULL)
```

**Parameters:**

- `numberInRow` (int)
- `columns` (const int *)
- `elements` (const double *)
- `rowLower` (double)
- `rowUpper` (double)
- `name` (const char *)

### `addColumn`

add a column - numberInColumn may be zero */

```cpp
void addColumn(int numberInColumn, const int * rows, const double * elements, double columnLower = 0.0, double columnUpper, double objectiveValue = 0.0, const char * name = NULL, bool isInteger = false)
```

**Parameters:**

- `numberInColumn` (int)
- `rows` (const int *)
- `elements` (const double *)
- `columnLower` (double)
- `columnUpper` (double)
- `objectiveValue` (double)
- `name` (const char *)
- `isInteger` (bool)

### `addCol`

add a column - numberInColumn may be zero */

```cpp
void addCol(int numberInColumn, const int * rows, const double * elements, double columnLower = 0.0, double columnUpper, double objectiveValue = 0.0, const char * name = NULL, bool isInteger = false)
```

**Parameters:**

- `numberInColumn` (int)
- `rows` (const int *)
- `elements` (const double *)
- `columnLower` (double)
- `columnUpper` (double)
- `objectiveValue` (double)
- `name` (const char *)
- `isInteger` (bool)

### `operator()`

Sets value for row i and column j.

```cpp
void operator()(int i, int j, double value)
```

**Parameters:**

- `i` (int)
- `j` (int)
- `value` (double)

### `setElement`

Sets value for row i and column j.

```cpp
void setElement(int i, int j, double value)
```

**Parameters:**

- `i` (int)
- `j` (int)
- `value` (double)

### `getRow`

Gets sorted row - user must provide enough space (easiest is allocate number of columns).

```cpp
int getRow(int whichRow, int * column, double * element)
```

**Parameters:**

- `whichRow` (int)
- `column` (int *)
- `element` (double *)

### `getColumn`

Gets sorted column - user must provide enough space (easiest is allocate number of rows).

```cpp
int getColumn(int whichColumn, int * column, double * element)
```

**Parameters:**

- `whichColumn` (int)
- `column` (int *)
- `element` (double *)

### `setQuadraticElement`

Sets quadratic value for column i and j.

```cpp
void setQuadraticElement(int i, int j, double value)
```

**Parameters:**

- `i` (int)
- `j` (int)
- `value` (double)

### `operator()`

Sets value for row i and column j as string.

```cpp
void operator()(int i, int j, const char * value)
```

**Parameters:**

- `i` (int)
- `j` (int)
- `value` (const char *)

### `setElement`

Sets value for row i and column j as string.

```cpp
void setElement(int i, int j, const char * value)
```

**Parameters:**

- `i` (int)
- `j` (int)
- `value` (const char *)

### `associateElement`

Associates a string with a value. Returns string id (or -1 if does not exist)

```cpp
int associateElement(const char * stringValue, double value)
```

**Parameters:**

- `stringValue` (const char *)
- `value` (double)

### `setRowLower`

Sets rowLower (if row does not exist then all rows up to this are defined with default values and no elements)

```cpp
void setRowLower(int whichRow, double rowLower)
```

**Parameters:**

- `whichRow` (int)
- `rowLower` (double)

### `setRowUpper`

Sets rowUpper (if row does not exist then all rows up to this are defined with default values and no elements)

```cpp
void setRowUpper(int whichRow, double rowUpper)
```

**Parameters:**

- `whichRow` (int)
- `rowUpper` (double)

### `setRowBounds`

Sets rowLower and rowUpper (if row does not exist then all rows up to this are defined with default values and no elements)

```cpp
void setRowBounds(int whichRow, double rowLower, double rowUpper)
```

**Parameters:**

- `whichRow` (int)
- `rowLower` (double)
- `rowUpper` (double)

### `setRowName`

Sets name (if row does not exist then all rows up to this are defined with default values and no elements)

```cpp
void setRowName(int whichRow, const char * rowName)
```

**Parameters:**

- `whichRow` (int)
- `rowName` (const char *)

### `setColumnLower`

Sets columnLower (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnLower(int whichColumn, double columnLower)
```

**Parameters:**

- `whichColumn` (int)
- `columnLower` (double)

### `setColumnUpper`

Sets columnUpper (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnUpper(int whichColumn, double columnUpper)
```

**Parameters:**

- `whichColumn` (int)
- `columnUpper` (double)

### `setColumnBounds`

Sets columnLower and columnUpper (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnBounds(int whichColumn, double columnLower, double columnUpper)
```

**Parameters:**

- `whichColumn` (int)
- `columnLower` (double)
- `columnUpper` (double)

### `setColumnObjective`

Sets columnObjective (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnObjective(int whichColumn, double columnObjective)
```

**Parameters:**

- `whichColumn` (int)
- `columnObjective` (double)

### `setColumnName`

Sets name (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnName(int whichColumn, const char * columnName)
```

**Parameters:**

- `whichColumn` (int)
- `columnName` (const char *)

### `setColumnIsInteger`

Sets integer state (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnIsInteger(int whichColumn, bool columnIsInteger)
```

**Parameters:**

- `whichColumn` (int)
- `columnIsInteger` (bool)

### `setObjective`

Sets columnObjective (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setObjective(int whichColumn, double columnObjective)
```

**Parameters:**

- `whichColumn` (int)
- `columnObjective` (double)

### `setIsInteger`

Sets integer state (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setIsInteger(int whichColumn, bool columnIsInteger)
```

**Parameters:**

- `whichColumn` (int)
- `columnIsInteger` (bool)

### `setInteger`

Sets integer (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setInteger(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `setContinuous`

Sets continuous (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setContinuous(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `setColLower`

Sets columnLower (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColLower(int whichColumn, double columnLower)
```

**Parameters:**

- `whichColumn` (int)
- `columnLower` (double)

### `setColUpper`

Sets columnUpper (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColUpper(int whichColumn, double columnUpper)
```

**Parameters:**

- `whichColumn` (int)
- `columnUpper` (double)

### `setColBounds`

Sets columnLower and columnUpper (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColBounds(int whichColumn, double columnLower, double columnUpper)
```

**Parameters:**

- `whichColumn` (int)
- `columnLower` (double)
- `columnUpper` (double)

### `setColObjective`

Sets columnObjective (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColObjective(int whichColumn, double columnObjective)
```

**Parameters:**

- `whichColumn` (int)
- `columnObjective` (double)

### `setColName`

Sets name (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColName(int whichColumn, const char * columnName)
```

**Parameters:**

- `whichColumn` (int)
- `columnName` (const char *)

### `Coin8CharacterName`

Create a name in field given a sequence number - allows >10000000.

```cpp
void Coin8CharacterName(char rowColumn, int number, char * field)
```

**Parameters:**

- `rowColumn` (char)
- `number` (int)
- `field` (char *)

### `setColIsInteger`

Sets integer (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColIsInteger(int whichColumn, bool columnIsInteger)
```

**Parameters:**

- `whichColumn` (int)
- `columnIsInteger` (bool)

### `setRowLower`

Sets rowLower (if row does not exist then all rows up to this are defined with default values and no elements)

```cpp
void setRowLower(int whichRow, const char * rowLower)
```

**Parameters:**

- `whichRow` (int)
- `rowLower` (const char *)

### `setRowUpper`

Sets rowUpper (if row does not exist then all rows up to this are defined with default values and no elements)

```cpp
void setRowUpper(int whichRow, const char * rowUpper)
```

**Parameters:**

- `whichRow` (int)
- `rowUpper` (const char *)

### `setColumnLower`

Sets columnLower (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnLower(int whichColumn, const char * columnLower)
```

**Parameters:**

- `whichColumn` (int)
- `columnLower` (const char *)

### `setColumnUpper`

Sets columnUpper (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnUpper(int whichColumn, const char * columnUpper)
```

**Parameters:**

- `whichColumn` (int)
- `columnUpper` (const char *)

### `setColumnObjective`

Sets columnObjective (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnObjective(int whichColumn, const char * columnObjective)
```

**Parameters:**

- `whichColumn` (int)
- `columnObjective` (const char *)

### `setColumnIsInteger`

Sets integer (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setColumnIsInteger(int whichColumn, const char * columnIsInteger)
```

**Parameters:**

- `whichColumn` (int)
- `columnIsInteger` (const char *)

### `setObjective`

Sets columnObjective (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setObjective(int whichColumn, const char * columnObjective)
```

**Parameters:**

- `whichColumn` (int)
- `columnObjective` (const char *)

### `setIsInteger`

Sets integer (if column does not exist then all columns up to this are defined with default values and no elements)

```cpp
void setIsInteger(int whichColumn, const char * columnIsInteger)
```

**Parameters:**

- `whichColumn` (int)
- `columnIsInteger` (const char *)

### `deleteRow`

Deletes all entries in row and bounds.

```cpp
void deleteRow(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `deleteColumn`

Deletes all entries in column and bounds and objective.

```cpp
void deleteColumn(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `deleteCol`

Deletes all entries in column and bounds.

```cpp
void deleteCol(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `deleteElement`

Takes element out of matrix - returning position (<0 if not there);.

```cpp
CoinBigIndex deleteElement(int row, int column)
```

**Parameters:**

- `row` (int)
- `column` (int)

### `deleteThisElement`

Takes element out of matrix when position known.

```cpp
void deleteThisElement(int row, int column, CoinBigIndex position)
```

**Parameters:**

- `row` (int)
- `column` (int)
- `position` (CoinBigIndex)

### `packRows`

Packs down all rows i.e.

```cpp
int packRows()
```

### `packColumns`

Packs down all columns i.e.

```cpp
int packColumns()
```

### `packCols`

Packs down all columns i.e.

```cpp
int packCols()
```

### `pack`

Packs down all rows and columns.

```cpp
int pack()
```

### `setObjective`

Sets columnObjective array.

```cpp
void setObjective(int numberColumns, const double * objective)
```

**Parameters:**

- `numberColumns` (int)
- `objective` (const double *)

### `setColumnLower`

Sets columnLower array.

```cpp
void setColumnLower(int numberColumns, const double * columnLower)
```

**Parameters:**

- `numberColumns` (int)
- `columnLower` (const double *)

### `setColLower`

Sets columnLower array.

```cpp
void setColLower(int numberColumns, const double * columnLower)
```

**Parameters:**

- `numberColumns` (int)
- `columnLower` (const double *)

### `setColumnUpper`

Sets columnUpper array.

```cpp
void setColumnUpper(int numberColumns, const double * columnUpper)
```

**Parameters:**

- `numberColumns` (int)
- `columnUpper` (const double *)

### `setColUpper`

Sets columnUpper array.

```cpp
void setColUpper(int numberColumns, const double * columnUpper)
```

**Parameters:**

- `numberColumns` (int)
- `columnUpper` (const double *)

### `setRowLower`

Sets rowLower array.

```cpp
void setRowLower(int numberRows, const double * rowLower)
```

**Parameters:**

- `numberRows` (int)
- `rowLower` (const double *)

### `setRowUpper`

Sets rowUpper array.

```cpp
void setRowUpper(int numberRows, const double * rowUpper)
```

**Parameters:**

- `numberRows` (int)
- `rowUpper` (const double *)

### `writeMps`

Write the problem in MPS format to a file with the given filename.

```cpp
int writeMps(const char * filename, int compression = 0, int formatType = 0, int numberAcross = 2, bool keepStrings = false)
```

**Parameters:**

- `filename` (const char *)
- `compression` (int) - can be set to three values to indicate what kind of file should be written 0: plain text (default)
1: gzip compressed (.gz is appended to `filename`)
2: bzip2 compressed (.bz2 is appended to `filename`) (TODO)
If the library was not compiled with the requested compression then writeMps falls back to writing a plain text file.
- `formatType` (int) - specifies the precision to used for values in the MPS file 0: normal precision (default)
1: extra accuracy
2: IEEE hex
- `numberAcross` (int) - specifies whether 1 or 2 (default) values should be specified on every data line in the MPS file.
- `keepStrings` (bool)

### `differentModel`

Check two models against each other.

```cpp
int differentModel(CoinModel & other, bool ignoreNames)
```

**Parameters:**

- `other` (CoinModel &)
- `ignoreNames` (bool)

### `passInMatrix`

Pass in CoinPackedMatrix (and switch off element updates)

```cpp
void passInMatrix(const CoinPackedMatrix & matrix)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)

### `convertMatrix`

Convert elements to CoinPackedMatrix (and switch off element updates).

```cpp
int convertMatrix()
```

### `packedMatrix`

Return a pointer to CoinPackedMatrix (or NULL)

```cpp
const CoinPackedMatrix * packedMatrix()
```

### `originalRows`

Return pointers to original rows (for decomposition)

```cpp
const int * originalRows()
```

### `originalColumns`

Return pointers to original columns (for decomposition)

```cpp
const int * originalColumns()
```

### `numberElements`

Return number of elements.

```cpp
CoinBigIndex numberElements()
```

### `elements`

Return elements as triples.

```cpp
const CoinModelTriple * elements()
```

### `operator()`

Returns value for row i and column j.

```cpp
double operator()(int i, int j)
```

**Parameters:**

- `i` (int)
- `j` (int)

### `getElement`

Returns value for row i and column j.

```cpp
double getElement(int i, int j)
```

**Parameters:**

- `i` (int)
- `j` (int)

### `operator()`

Returns value for row rowName and column columnName.

```cpp
double operator()(const char * rowName, const char * columnName)
```

**Parameters:**

- `rowName` (const char *)
- `columnName` (const char *)

### `getElement`

Returns value for row rowName and column columnName.

```cpp
double getElement(const char * rowName, const char * columnName)
```

**Parameters:**

- `rowName` (const char *)
- `columnName` (const char *)

### `getQuadraticElement`

Returns quadratic value for columns i and j.

```cpp
double getQuadraticElement(int i, int j)
```

**Parameters:**

- `i` (int)
- `j` (int)

### `getElementAsString`

Returns value for row i and column j as string.

```cpp
const char * getElementAsString(int i, int j)
```

**Parameters:**

- `i` (int)
- `j` (int)

### `pointer`

Returns pointer to element for row i column j.

```cpp
double * pointer(int i, int j)
```

**Parameters:**

- `i` (int)
- `j` (int)

### `position`

Returns position in elements for row i column j.

```cpp
CoinBigIndex position(int i, int j)
```

**Parameters:**

- `i` (int)
- `j` (int)

### `firstInRow`

Returns first element in given row - index is -1 if none.

```cpp
CoinModelLink firstInRow(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `lastInRow`

Returns last element in given row - index is -1 if none.

```cpp
CoinModelLink lastInRow(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `firstInColumn`

Returns first element in given column - index is -1 if none.

```cpp
CoinModelLink firstInColumn(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `lastInColumn`

Returns last element in given column - index is -1 if none.

```cpp
CoinModelLink lastInColumn(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `next`

Returns next element in current row or column - index is -1 if none.

```cpp
CoinModelLink next(CoinModelLink & current)
```

**Parameters:**

- `current` (CoinModelLink &)

### `previous`

Returns previous element in current row or column - index is -1 if none.

```cpp
CoinModelLink previous(CoinModelLink & current)
```

**Parameters:**

- `current` (CoinModelLink &)

### `firstInQuadraticColumn`

Returns first element in given quadratic column - index is -1 if none.

```cpp
CoinModelLink firstInQuadraticColumn(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `lastInQuadraticColumn`

Returns last element in given quadratic column - index is -1 if none.

```cpp
CoinModelLink lastInQuadraticColumn(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getRowLower`

Gets rowLower (if row does not exist then -COIN_DBL_MAX)

```cpp
double getRowLower(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `getRowUpper`

Gets rowUpper (if row does not exist then +COIN_DBL_MAX)

```cpp
double getRowUpper(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `getRowName`

Gets name (if row does not exist then NULL)

```cpp
const char * getRowName(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `rowLower`

```cpp
double rowLower(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `rowUpper`

Gets rowUpper (if row does not exist then COIN_DBL_MAX)

```cpp
double rowUpper(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `rowName`

Gets name (if row does not exist then NULL)

```cpp
const char * rowName(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `getColumnLower`

Gets columnLower (if column does not exist then 0.0)

```cpp
double getColumnLower(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColumnUpper`

Gets columnUpper (if column does not exist then COIN_DBL_MAX)

```cpp
double getColumnUpper(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColumnObjective`

Gets columnObjective (if column does not exist then 0.0)

```cpp
double getColumnObjective(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColumnName`

Gets name (if column does not exist then NULL)

```cpp
const char * getColumnName(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColumnIsInteger`

Gets if integer (if column does not exist then false)

```cpp
bool getColumnIsInteger(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `columnLower`

Gets columnLower (if column does not exist then 0.0)

```cpp
double columnLower(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `columnUpper`

Gets columnUpper (if column does not exist then COIN_DBL_MAX)

```cpp
double columnUpper(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `columnObjective`

Gets columnObjective (if column does not exist then 0.0)

```cpp
double columnObjective(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `objective`

Gets columnObjective (if column does not exist then 0.0)

```cpp
double objective(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `columnName`

Gets name (if column does not exist then NULL)

```cpp
const char * columnName(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `columnIsInteger`

Gets if integer (if column does not exist then false)

```cpp
bool columnIsInteger(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `isInteger`

Gets if integer (if column does not exist then false)

```cpp
bool isInteger(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColLower`

Gets columnLower (if column does not exist then 0.0)

```cpp
double getColLower(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColUpper`

Gets columnUpper (if column does not exist then COIN_DBL_MAX)

```cpp
double getColUpper(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColObjective`

Gets columnObjective (if column does not exist then 0.0)

```cpp
double getColObjective(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColName`

Gets name (if column does not exist then NULL)

```cpp
const char * getColName(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColIsInteger`

Gets if integer (if column does not exist then false)

```cpp
bool getColIsInteger(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getRowLowerAsString`

Gets rowLower (if row does not exist then -COIN_DBL_MAX)

```cpp
const char * getRowLowerAsString(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `getRowUpperAsString`

Gets rowUpper (if row does not exist then +COIN_DBL_MAX)

```cpp
const char * getRowUpperAsString(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `rowLowerAsString`

```cpp
const char * rowLowerAsString(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `rowUpperAsString`

Gets rowUpper (if row does not exist then COIN_DBL_MAX)

```cpp
const char * rowUpperAsString(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `getColumnLowerAsString`

Gets columnLower (if column does not exist then 0.0)

```cpp
const char * getColumnLowerAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColumnUpperAsString`

Gets columnUpper (if column does not exist then COIN_DBL_MAX)

```cpp
const char * getColumnUpperAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColumnObjectiveAsString`

Gets columnObjective (if column does not exist then 0.0)

```cpp
const char * getColumnObjectiveAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `getColumnIsIntegerAsString`

Gets if integer (if column does not exist then false)

```cpp
const char * getColumnIsIntegerAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `columnLowerAsString`

Gets columnLower (if column does not exist then 0.0)

```cpp
const char * columnLowerAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `columnUpperAsString`

Gets columnUpper (if column does not exist then COIN_DBL_MAX)

```cpp
const char * columnUpperAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `columnObjectiveAsString`

Gets columnObjective (if column does not exist then 0.0)

```cpp
const char * columnObjectiveAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `objectiveAsString`

Gets columnObjective (if column does not exist then 0.0)

```cpp
const char * objectiveAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `columnIsIntegerAsString`

Gets if integer (if column does not exist then false)

```cpp
const char * columnIsIntegerAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `isIntegerAsString`

Gets if integer (if column does not exist then false)

```cpp
const char * isIntegerAsString(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `row`

Row index from row name (-1 if no names or no match)

```cpp
int row(const char * rowName)
```

**Parameters:**

- `rowName` (const char *)

### `column`

Column index from column name (-1 if no names or no match)

```cpp
int column(const char * columnName)
```

**Parameters:**

- `columnName` (const char *)

### `type`

Returns type.

```cpp
int type()
```

### `unsetValue`

returns unset value

```cpp
double unsetValue()
```

### `createPackedMatrix`

Creates a packed matrix - return number of errors.

```cpp
int createPackedMatrix(CoinPackedMatrix & matrix, const double * associated)
```

**Parameters:**

- `matrix` (CoinPackedMatrix &)
- `associated` (const double *)

### `countPlusMinusOne`

Fills in startPositive and startNegative with counts for +-1 matrix.

```cpp
int countPlusMinusOne(CoinBigIndex * startPositive, CoinBigIndex * startNegative, const double * associated)
```

**Parameters:**

- `startPositive` (CoinBigIndex *)
- `startNegative` (CoinBigIndex *)
- `associated` (const double *)

### `createPlusMinusOne`

Creates +-1 matrix given startPositive and startNegative counts for +-1 matrix.

```cpp
void createPlusMinusOne(CoinBigIndex * startPositive, CoinBigIndex * startNegative, int * indices, const double * associated)
```

**Parameters:**

- `startPositive` (CoinBigIndex *)
- `startNegative` (CoinBigIndex *)
- `indices` (int *)
- `associated` (const double *)

### `createArrays`

Creates copies of various arrays - return number of errors.

```cpp
int createArrays(double *& rowLower, double *& rowUpper, double *& columnLower, double *& columnUpper, double *& objective, int *& integerType, double *& associated)
```

**Parameters:**

- `rowLower` (double *&)
- `rowUpper` (double *&)
- `columnLower` (double *&)
- `columnUpper` (double *&)
- `objective` (double *&)
- `integerType` (int *&)
- `associated` (double *&)

### `stringsExist`

Says if strings exist.

```cpp
bool stringsExist()
```

### `stringArray`

Return string array.

```cpp
const CoinModelHash * stringArray()
```

### `associatedArray`

Returns associated array.

```cpp
double * associatedArray()
```

### `rowLowerArray`

Return rowLower array.

```cpp
double * rowLowerArray()
```

### `rowUpperArray`

Return rowUpper array.

```cpp
double * rowUpperArray()
```

### `columnLowerArray`

Return columnLower array.

```cpp
double * columnLowerArray()
```

### `columnUpperArray`

Return columnUpper array.

```cpp
double * columnUpperArray()
```

### `objectiveArray`

Return objective array.

```cpp
double * objectiveArray()
```

### `integerTypeArray`

Return integerType array.

```cpp
int * integerTypeArray()
```

### `rowNames`

Return row names array.

```cpp
const CoinModelHash * rowNames()
```

### `columnNames`

Return column names array.

```cpp
const CoinModelHash * columnNames()
```

### `zapRowNames`

Reset row names.

```cpp
void zapRowNames()
```

### `zapColumnNames`

Reset column names.

```cpp
void zapColumnNames()
```

### `cutMarker`

Returns array of 0 or nonzero if can be a cut (or returns NULL)

```cpp
const int * cutMarker()
```

### `optimizationDirection`

Direction of optimization (1 - minimize, -1 - maximize, 0 - ignore.

```cpp
double optimizationDirection()
```

### `setOptimizationDirection`

Set direction of optimization (1 - minimize, -1 - maximize, 0 - ignore.

```cpp
void setOptimizationDirection(double value)
```

**Parameters:**

- `value` (double)

### `moreInfo`

Return pointer to more information.

```cpp
void * moreInfo()
```

### `setMoreInfo`

Set pointer to more information.

```cpp
void setMoreInfo(void * info)
```

**Parameters:**

- `info` (void *)

### `whatIsSet`

Returns which parts of model are set 1 - matrix 2 - rhs 4 - row names 8 - column bounds and/or objective 16 - column names 32 - integer types.

```cpp
int whatIsSet()
```

### `loadBlock`

Load in a problem by copying the arguments. The constraints on the rows are given by lower and upper bounds.

```cpp
void loadBlock(const CoinPackedMatrix & matrix, const double * collb, const double * colub, const double * obj, const double * rowlb, const double * rowub)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)
- `collb` (const double *)
- `colub` (const double *)
- `obj` (const double *)
- `rowlb` (const double *)
- `rowub` (const double *)

### `loadBlock`

Load in a problem by copying the arguments. The constraints on the rows are given by sense/rhs/range triplets.

```cpp
void loadBlock(const CoinPackedMatrix & matrix, const double * collb, const double * colub, const double * obj, const char * rowsen, const double * rowrhs, const double * rowrng)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)
- `collb` (const double *)
- `colub` (const double *)
- `obj` (const double *)
- `rowsen` (const char *)
- `rowrhs` (const double *)
- `rowrng` (const double *)

### `loadBlock`

Load in a problem by copying the arguments. The constraint matrix is is specified with standard column-major column starts / row indices / coefficients vectors. The constraints on the rows are given by lower and upper bounds.

```cpp
void loadBlock(const int numcols, const int numrows, const CoinBigIndex * start, const int * index, const double * value, const double * collb, const double * colub, const double * obj, const double * rowlb, const double * rowub)
```

**Parameters:**

- `numcols` (const int)
- `numrows` (const int)
- `start` (const CoinBigIndex *)
- `index` (const int *)
- `value` (const double *)
- `collb` (const double *)
- `colub` (const double *)
- `obj` (const double *)
- `rowlb` (const double *)
- `rowub` (const double *)

### `loadBlock`

Load in a problem by copying the arguments. The constraint matrix is is specified with standard column-major column starts / row indices / coefficients vectors. The constraints on the rows are given by sense/rhs/range triplets.

```cpp
void loadBlock(const int numcols, const int numrows, const CoinBigIndex * start, const int * index, const double * value, const double * collb, const double * colub, const double * obj, const char * rowsen, const double * rowrhs, const double * rowrng)
```

**Parameters:**

- `numcols` (const int)
- `numrows` (const int)
- `start` (const CoinBigIndex *)
- `index` (const int *)
- `value` (const double *)
- `collb` (const double *)
- `colub` (const double *)
- `obj` (const double *)
- `rowsen` (const char *)
- `rowrhs` (const double *)
- `rowrng` (const double *)

### `CoinModel`

Default constructor.

```cpp
 CoinModel()
```

### `CoinModel`

Constructor with sizes.

```cpp
 CoinModel(int firstRows, int firstColumns, CoinBigIndex firstElements, bool noNames = false)
```

**Parameters:**

- `firstRows` (int)
- `firstColumns` (int)
- `firstElements` (CoinBigIndex)
- `noNames` (bool)

### `CoinModel`

Read a problem in MPS or GAMS format from the given filename.

```cpp
 CoinModel(const char * fileName, int allowStrings = 0)
```

**Parameters:**

- `fileName` (const char *)
- `allowStrings` (int)

### `CoinModel`

Read a problem from AMPL nl file, if linked against ASL.

```cpp
 CoinModel(int nonLinear, const char * fileName, const void * info)
```

**Parameters:**

- `nonLinear` (int)
- `fileName` (const char *)
- `info` (const void *)

### `CoinModel`

From arrays.

```cpp
 CoinModel(int numberRows, int numberColumns, const CoinPackedMatrix * matrix, const double * rowLower, const double * rowUpper, const double * columnLower, const double * columnUpper, const double * objective)
```

**Parameters:**

- `numberRows` (int)
- `numberColumns` (int)
- `matrix` (const CoinPackedMatrix *)
- `rowLower` (const double *)
- `rowUpper` (const double *)
- `columnLower` (const double *)
- `columnUpper` (const double *)
- `objective` (const double *)

### `clone`

Clone.

```cpp
CoinBaseModel * clone()
```

### `~CoinModel`

Destructor.

```cpp
 ~CoinModel()
```

### `CoinModel`

The copy constructor.

```cpp
 CoinModel(const CoinModel & )
```

**Parameters:**

- `` (const CoinModel &)

### `operator=`

=

```cpp
CoinModel & operator=(const CoinModel & )
```

**Parameters:**

- `` (const CoinModel &)

### `validateLinks`

Checks that links are consistent.

```cpp
void validateLinks()
```

### `computeAssociated`

Fills in all associated - returning number of errors.

```cpp
int computeAssociated(double * associated)
```

**Parameters:**

- `associated` (double *)

### `quadraticRow`

Gets correct form for a quadratic row - user to delete If row is not quadratic then returns which other variables are involved with tiny (1.0e-100) elements and count of total number of variables which could not be put in quadratic form.

```cpp
CoinPackedMatrix * quadraticRow(int rowNumber, double * linear, int & numberBad)
```

**Parameters:**

- `rowNumber` (int)
- `linear` (double *)
- `numberBad` (int &)

### `replaceQuadraticRow`

Replaces a quadratic row.

```cpp
void replaceQuadraticRow(int rowNumber, const double * linear, const CoinPackedMatrix * quadraticPart)
```

**Parameters:**

- `rowNumber` (int)
- `linear` (const double *)
- `quadraticPart` (const CoinPackedMatrix *)

### `reorder`

If possible return a model where if all variables marked nonzero are fixed the problem will be linear.

```cpp
CoinModel * reorder(const char * mark)
```

**Parameters:**

- `mark` (const char *)

### `setCutMarker`

Sets cut marker array.

```cpp
void setCutMarker(int size, const int * marker)
```

**Parameters:**

- `size` (int)
- `marker` (const int *)

### `setPriorities`

Sets priority array.

```cpp
void setPriorities(int size, const int * priorities)
```

**Parameters:**

- `size` (int)
- `priorities` (const int *)

### `priorities`

priorities (given for all columns (-1 if not integer)

```cpp
const int * priorities()
```

### `setOriginalIndices`

For decomposition set original row and column indices.

```cpp
void setOriginalIndices(const int * row, const int * column)
```

**Parameters:**

- `row` (const int *)
- `column` (const int *)

## Source

Header: `layer-0/CoinUtils/src/CoinModel.hpp`
