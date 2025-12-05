+++
title = "CoinMpsIO"
description = "MPS IO Interface."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinMpsIO.hpp"
api_url = "/api/coinutils/CoinMpsIO.json"
+++

MPS IO Interface.


## Description

This class can be used to read in mps files without a solver. After reading the file, the CoinMpsIO object contains all relevant data, which may be more than a particular OsiSolverInterface allows for. Items may be deleted to allow for flexibility of data storage.
The implementation makes the CoinMpsIO object look very like a dummy solver, as the same conventions are used.

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
CoinBigIndex getNumElements()
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

### `getRowSense`

Get pointer to array[getNumRows()] of constraint senses.

```cpp
const char * getRowSense()
```

### `getRightHandSide`

Get pointer to array[getNumRows()] of constraint right-hand sides.

```cpp
const double * getRightHandSide()
```

### `getRowRange`

Get pointer to array[getNumRows()] of row ranges.

```cpp
const double * getRowRange()
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

### `getObjCoefficients`

Get pointer to array[getNumCols()] of objective function coefficients.

```cpp
const double * getObjCoefficients()
```

### `getMatrixByRow`

Get pointer to row-wise copy of the coefficient matrix.

```cpp
const CoinPackedMatrix * getMatrixByRow()
```

### `getMatrixByCol`

Get pointer to column-wise copy of the coefficient matrix.

```cpp
const CoinPackedMatrix * getMatrixByCol()
```

### `isContinuous`

Return true if column is a continuous variable.

```cpp
bool isContinuous(int colNumber)
```

**Parameters:**

- `colNumber` (int)

### `isInteger`

Return true if a column is an integer variable.

```cpp
bool isInteger(int columnNumber)
```

**Parameters:**

- `columnNumber` (int)

### `isIntegerOrSemiContinuous`

Return 1 if a column is an integer variable, 2 if semi-continuous.

```cpp
int isIntegerOrSemiContinuous(int columnNumber)
```

**Parameters:**

- `columnNumber` (int)

### `integerColumns`

Returns array[getNumCols()] specifying if a variable is integer.

```cpp
const char * integerColumns()
```

### `rowName`

Returns the row name for the specified index.

```cpp
const char * rowName(int index)
```

**Parameters:**

- `index` (int)

### `columnName`

Returns the column name for the specified index.

```cpp
const char * columnName(int index)
```

**Parameters:**

- `index` (int)

### `rowIndex`

Returns the index for the specified row name.

```cpp
int rowIndex(const char * name)
```

**Parameters:**

- `name` (const char *)

### `columnIndex`

Returns the index for the specified column name.

```cpp
int columnIndex(const char * name)
```

**Parameters:**

- `name` (const char *)

### `objectiveOffset`

Returns the (constant) objective offset.

```cpp
double objectiveOffset()
```

### `setObjectiveOffset`

Set objective offset.

```cpp
void setObjectiveOffset(double value)
```

**Parameters:**

- `value` (double)

### `getProblemName`

Return the problem name.

```cpp
const char * getProblemName()
```

### `getObjectiveName`

Return the objective name.

```cpp
const char * getObjectiveName()
```

### `getRhsName`

Return the RHS vector name.

```cpp
const char * getRhsName()
```

### `getRangeName`

Return the range vector name.

```cpp
const char * getRangeName()
```

### `getBoundName`

Return the bound vector name.

```cpp
const char * getBoundName()
```

### `numberStringElements`

Number of string elements.

```cpp
int numberStringElements()
```

### `stringElement`

String element.

```cpp
const char * stringElement(int i)
```

**Parameters:**

- `i` (int)

### `setMpsData`

Set the problem data.

```cpp
void setMpsData(const CoinPackedMatrix & m, const double infinity, const double * collb, const double * colub, const double * obj, const char * integrality, const double * rowlb, const double * rowub, char const *const *const colnames, char const *const *const rownames)
```

**Parameters:**

- `m` (const CoinPackedMatrix &)
- `infinity` (const double)
- `collb` (const double *)
- `colub` (const double *)
- `obj` (const double *)
- `integrality` (const char *)
- `rowlb` (const double *)
- `rowub` (const double *)
- `colnames` (char const *const *const)
- `rownames` (char const *const *const)

### `setMpsData`

```cpp
void setMpsData(const CoinPackedMatrix & m, const double infinity, const double * collb, const double * colub, const double * obj, const char * integrality, const double * rowlb, const double * rowub, const std::vector< std::string > & colnames, const std::vector< std::string > & rownames)
```

**Parameters:**

- `m` (const CoinPackedMatrix &)
- `infinity` (const double)
- `collb` (const double *)
- `colub` (const double *)
- `obj` (const double *)
- `integrality` (const char *)
- `rowlb` (const double *)
- `rowub` (const double *)
- `colnames` (const std::vector< std::string > &)
- `rownames` (const std::vector< std::string > &)

### `setMpsData`

```cpp
void setMpsData(const CoinPackedMatrix & m, const double infinity, const double * collb, const double * colub, const double * obj, const char * integrality, const char * rowsen, const double * rowrhs, const double * rowrng, char const *const *const colnames, char const *const *const rownames)
```

**Parameters:**

- `m` (const CoinPackedMatrix &)
- `infinity` (const double)
- `collb` (const double *)
- `colub` (const double *)
- `obj` (const double *)
- `integrality` (const char *)
- `rowsen` (const char *)
- `rowrhs` (const double *)
- `rowrng` (const double *)
- `colnames` (char const *const *const)
- `rownames` (char const *const *const)

### `setMpsData`

```cpp
void setMpsData(const CoinPackedMatrix & m, const double infinity, const double * collb, const double * colub, const double * obj, const char * integrality, const char * rowsen, const double * rowrhs, const double * rowrng, const std::vector< std::string > & colnames, const std::vector< std::string > & rownames)
```

**Parameters:**

- `m` (const CoinPackedMatrix &)
- `infinity` (const double)
- `collb` (const double *)
- `colub` (const double *)
- `obj` (const double *)
- `integrality` (const char *)
- `rowsen` (const char *)
- `rowrhs` (const double *)
- `rowrng` (const double *)
- `colnames` (const std::vector< std::string > &)
- `rownames` (const std::vector< std::string > &)

### `copyInIntegerInformation`

Pass in an array[getNumCols()] specifying if a variable is integer.

```cpp
void copyInIntegerInformation(const char * integerInformation)
```

**Parameters:**

- `integerInformation` (const char *)

### `setProblemName`

Set problem name.

```cpp
void setProblemName(const char * name)
```

**Parameters:**

- `name` (const char *)

### `setObjectiveName`

Set objective name.

```cpp
void setObjectiveName(const char * name)
```

**Parameters:**

- `name` (const char *)

### `setInfinity`

Set infinity.

```cpp
void setInfinity(double value)
```

**Parameters:**

- `value` (double)

### `getInfinity`

Get infinity.

```cpp
double getInfinity()
```

### `setDefaultBound`

Set default upper bound for integer variables.

```cpp
void setDefaultBound(int value)
```

**Parameters:**

- `value` (int)

### `getDefaultBound`

Get default upper bound for integer variables.

```cpp
int getDefaultBound()
```

### `allowStringElements`

Whether to allow string elements.

```cpp
int allowStringElements()
```

### `setAllowStringElements`

Whether to allow string elements (0 no, 1 yes, 2 yes and try flip)

```cpp
void setAllowStringElements(int yesNo)
```

**Parameters:**

- `yesNo` (int)

### `getSmallElementValue`

Small element value - elements less than this set to zero on input default is 1.0e-14.

```cpp
double getSmallElementValue()
```

### `setSmallElementValue`

```cpp
void setSmallElementValue(double value)
```

**Parameters:**

- `value` (double)

### `wasMaximization`

Return true if maximization problem reformulated as minimization.

```cpp
bool wasMaximization()
```

### `isMaximization`

Return true if maximization problem and still formulated as maximization.

```cpp
bool isMaximization()
```

### `setFileName`

Set the current file name for the CoinMpsIO object.

```cpp
void setFileName(const char * name)
```

**Parameters:**

- `name` (const char *)

### `getFileName`

Get the current file name for the CoinMpsIO object.

```cpp
const char * getFileName()
```

### `readMps`

Read a problem in MPS format from the given filename.

```cpp
int readMps(const char * filename, const char * extension = "mps")
```

**Parameters:**

- `filename` (const char *)
- `extension` (const char *)

### `readMps`

Read a problem in MPS format from the given filename.

```cpp
int readMps(const char * filename, const char * extension, int & numberSets, CoinSet **& sets)
```

**Parameters:**

- `filename` (const char *)
- `extension` (const char *)
- `numberSets` (int &)
- `sets` (CoinSet **&)

### `readMps`

Read a problem in MPS format from a previously opened file.

```cpp
int readMps()
```

### `readMps`

and

```cpp
int readMps(int & numberSets, CoinSet **& sets)
```

**Parameters:**

- `numberSets` (int &)
- `sets` (CoinSet **&)

### `readBasis`

Read a basis in MPS format from the given filename.

```cpp
int readBasis(const char * filename, const char * extension, double * solution, unsigned char * rowStatus, unsigned char * columnStatus, const std::vector< std::string > & colnames, int numberColumns, const std::vector< std::string > & rownames, int numberRows)
```

**Parameters:**

- `filename` (const char *)
- `extension` (const char *)
- `solution` (double *)
- `rowStatus` (unsigned char *)
- `columnStatus` (unsigned char *)
- `colnames` (const std::vector< std::string > &)
- `numberColumns` (int)
- `rownames` (const std::vector< std::string > &)
- `numberRows` (int)

### `readGms`

Read a problem in GAMS format from the given filename.

```cpp
int readGms(const char * filename, const char * extension = "gms", bool convertObjective = false)
```

**Parameters:**

- `filename` (const char *)
- `extension` (const char *)
- `convertObjective` (bool)

### `readGms`

Read a problem in GAMS format from the given filename.

```cpp
int readGms(const char * filename, const char * extension, int & numberSets, CoinSet **& sets)
```

**Parameters:**

- `filename` (const char *)
- `extension` (const char *)
- `numberSets` (int &)
- `sets` (CoinSet **&)

### `readGms`

Read a problem in GAMS format from a previously opened file.

```cpp
int readGms(int & numberSets, CoinSet **& sets)
```

**Parameters:**

- `numberSets` (int &)
- `sets` (CoinSet **&)

### `writeMps`

Write the problem in MPS format to a file with the given filename.

```cpp
int writeMps(const char * filename, int compression = 0, int formatType = 0, int numberAcross = 2, CoinPackedMatrix * quadratic = NULL, int numberSOS = 0, const CoinSet * setInfo = NULL)
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
- `quadratic` (CoinPackedMatrix *) - specifies quadratic objective to be output
- `numberSOS` (int)
- `setInfo` (const CoinSet *)

### `reader`

Return card reader object so can see what last card was e.g. QUADOBJ.

```cpp
const CoinMpsCardReader * reader()
```

### `readQuadraticMps`

Read in a quadratic objective from the given filename.

```cpp
int readQuadraticMps(const char * filename, CoinBigIndex *& columnStart, int *& column, double *& elements, int checkSymmetry)
```

**Parameters:**

- `filename` (const char *)
- `columnStart` (CoinBigIndex *&)
- `column` (int *&)
- `elements` (double *&)
- `checkSymmetry` (int)

### `readConicMps`

Read in a list of cones from the given filename.

```cpp
int readConicMps(const char * filename, int *& columnStart, int *& column, int *& coneType, int & numberCones)
```

**Parameters:**

- `filename` (const char *)
- `columnStart` (int *&)
- `column` (int *&)
- `coneType` (int *&)
- `numberCones` (int &)

### `setConvertObjective`

Set whether to move objective from matrix.

```cpp
void setConvertObjective(bool trueFalse)
```

**Parameters:**

- `trueFalse` (bool)

### `copyStringElements`

copies in strings from a CoinModel - returns number

```cpp
int copyStringElements(const CoinModel * model)
```

**Parameters:**

- `model` (const CoinModel *)

### `CoinMpsIO`

Default Constructor.

```cpp
 CoinMpsIO()
```

### `CoinMpsIO`

Copy constructor.

```cpp
 CoinMpsIO(const CoinMpsIO & )
```

**Parameters:**

- `` (const CoinMpsIO &)

### `operator=`

Assignment operator.

```cpp
CoinMpsIO & operator=(const CoinMpsIO & rhs)
```

**Parameters:**

- `rhs` (const CoinMpsIO &)

### `~CoinMpsIO`

Destructor.

```cpp
 ~CoinMpsIO()
```

### `passInMessageHandler`

Pass in Message handler.

```cpp
void passInMessageHandler(CoinMessageHandler * handler)
```

**Parameters:**

- `handler` (CoinMessageHandler *)

### `newLanguage`

Set the language for messages.

```cpp
void newLanguage(CoinMessages::Language language)
```

**Parameters:**

- `language` (CoinMessages::Language)

### `setLanguage`

Set the language for messages.

```cpp
void setLanguage(CoinMessages::Language language)
```

**Parameters:**

- `language` (CoinMessages::Language)

### `messageHandler`

Return the message handler.

```cpp
CoinMessageHandler * messageHandler()
```

### `messages`

Return the messages.

```cpp
CoinMessages messages()
```

### `messagesPointer`

Return the messages pointer.

```cpp
CoinMessages * messagesPointer()
```

### `releaseRedundantInformation`

Release all information which can be re-calculated.

```cpp
void releaseRedundantInformation()
```

### `releaseRowInformation`

Release all row information (lower, upper)

```cpp
void releaseRowInformation()
```

### `releaseColumnInformation`

Release all column information (lower, upper, objective)

```cpp
void releaseColumnInformation()
```

### `releaseIntegerInformation`

Release integer information.

```cpp
void releaseIntegerInformation()
```

### `releaseRowNames`

Release row names.

```cpp
void releaseRowNames()
```

### `releaseColumnNames`

Release column names.

```cpp
void releaseColumnNames()
```

### `releaseMatrixInformation`

Release matrix information.

```cpp
void releaseMatrixInformation()
```

## Source

Header: `layer-0/CoinUtils/src/CoinMpsIO.hpp`
