+++
title = "CoinLpIO"
description = "Class to read and write Lp files."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinLpIO.hpp"
api_url = "/api/coinutils/CoinLpIO.json"
+++

Class to read and write Lp files.

<div class="api-link"><a href="/api/coinutils/CoinLpIO.json">JSON API</a></div>

## Description

Lp file format:
/ this is a comment 
 \ this too 
 Min
 obj: x0 + x1 + 3 x2 - 4.5 xyr + 1 
 s.t. 
 cons1: x0 - x2 - 2.3 x4 <= 4.2 / this is another comment 
 c2: x1 + x2 >= 1 
 cc: x1 + x2 + xyr = 2 
 Bounds 
 0 <= x1 <= 3 
 1 >= x2 
 x3 = 1 
 -2 <= x4 <= Inf 
 xyr free 
 Integers 
 x0 
 Generals 
 x1 xyr 
 Binaries 
 x2 
 End
Notes: Keywords are: Min, Max, Minimize, Maximize, s.t., Subject To, Bounds, Integers, Generals, Binaries, Semis, End, Free, Inf.
Keywords are not case sensitive and may be in plural or singular form. They should not be used as objective, row or column names.
Bounds, Integers, Generals, Binaries sections are optional.
Generals and Integers are synonymous.
Bounds section (if any) must come before Integers, Generals, and Binaries sections.
Row names must be followed by ':' without blank space. Row names are optional. If row names are present, they must be distinct (if the k-th constraint has no given name, its name is set automatically to "consk" for k=0,...,). For valid row names, see the method is_invalid_name().
Column names must be followed by a blank space. They must be distinct. For valid column names, see the method is_invalid_name().
Multiple objectives may be specified, but when there are multiple objectives, they must have names (to indicate where each one starts).
The objective function names must be followed by ':' without blank space. If there is a single objective, the objective function name is optional. If no name is given, the name is set to "obj" by default. For valid objective function names, see the method is_invalid_name().
Ranged constraints are written as two constraints. If a name is given for a ranged constraint, the upper bound constraint has that name and the lower bound constraint has that name with "_low" as suffix. This should be kept in mind when assigning names to ranged constraint, as the resulting name must be distinct from all the other names and be considered valid by the method is_invalid_name().
At most one term related to any single variable may appear in the objective function; if more than one term are present, only the last one is taken into account. At most one constant term may appear in the objective function; if present, it must appear last.
Default bounds are 0 for lower bound and +infinity for upper bound.
Free variables get default lower bound -infinity and default upper bound +infinity. Writing "x0 Free" in an LP file means "set lower bound on x0 to -infinity".
If more than one upper (resp. lower) bound on a variable appears in the Bounds section, the last one is the one taken into account. The bounds for a binary variable are set to 0/1 only if this bound is stronger than the bound obtained from the Bounds section.
Numbers larger than DBL_MAX (or larger than 1e+400) in the input file might crash the code.
A comment must start with '\' or '/'. That symbol must either be the first character of a line or be preceded by a blank space. The comment ends at the end of the line. Comments are skipped while reading an Lp file and they may be inserted anywhere.

## Public Methods

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

### `CoinLpIO`

Default Constructor.

```cpp
 CoinLpIO()
```

### `gutsOfDestructor`

Does the heavy lifting for destruct and assignment.

```cpp
void gutsOfDestructor()
```

### `gutsOfCopy`

Does the heavy lifting for copy and assignment.

```cpp
void gutsOfCopy(const CoinLpIO & )
```

**Parameters:**

- `` (const CoinLpIO &)

### `operator=`

assignment operator

```cpp
CoinLpIO & operator=(const CoinLpIO & rhs)
```

**Parameters:**

- `rhs` (const CoinLpIO &)

### `CoinLpIO`

Copy constructor.

```cpp
 CoinLpIO(const CoinLpIO & )
```

**Parameters:**

- `` (const CoinLpIO &)

### `~CoinLpIO`

Destructor.

```cpp
 ~CoinLpIO()
```

### `freePreviousNames`

Free the vector previous_names_[section] and set card_previous_names_[section] to 0.

```cpp
void freePreviousNames(const int section)
```

**Parameters:**

- `section` (const int)

### `freeAll`

Free all memory (except memory related to hash tables and objName_).

```cpp
void freeAll()
```

### `convertBoundToSense`

A quick inlined function to convert from lb/ub style constraint definition to sense/rhs/range style.

```cpp
void convertBoundToSense(const double lower, const double upper, char & sense, double & right, double & range)
```

**Parameters:**

- `lower` (const double)
- `upper` (const double)
- `sense` (char &)
- `right` (double &)
- `range` (double &)

### `getProblemName`

Get the problem name.

```cpp
const char * getProblemName()
```

### `setProblemName`

Set problem name.

```cpp
void setProblemName(const char * name)
```

**Parameters:**

- `name` (const char *)

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

### `getNumObjectives`

Get pointer to array[getNumCols()] of objective function coefficients.

```cpp
const int getNumObjectives()
```

### `getObjCoefficients`

Get pointer to array[getNumCols()] of objective function coefficients.

```cpp
const double * getObjCoefficients()
```

### `getObjCoefficients`

Get pointer to array[getNumCols()] of objective function coefficients for objective j.

```cpp
const double * getObjCoefficients(int j)
```

**Parameters:**

- `j` (int)

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

### `getQuadraticObjective`

Get pointer to quadratic objective (or NULL)

```cpp
CoinPackedMatrix * getQuadraticObjective()
```

### `setQuadraticObjective`

copy in quadratic objective

```cpp
void setQuadraticObjective(CoinPackedMatrix * matrix)
```

**Parameters:**

- `matrix` (CoinPackedMatrix *)

### `getObjName`

Get objective function name.

```cpp
const char * getObjName()
```

### `getObjName`

Get objective function name for objective j.

```cpp
const char * getObjName(int j)
```

**Parameters:**

- `j` (int)

### `getPreviousRowNames`

Get pointer to array[*card_prev] of previous row names.

```cpp
void getPreviousRowNames(char const *const * prev, int * card_prev)
```

**Parameters:**

- `prev` (char const *const *)
- `card_prev` (int *)

### `getPreviousColNames`

Get pointer to array[*card_prev] of previous column names.

```cpp
void getPreviousColNames(char const *const * prev, int * card_prev)
```

**Parameters:**

- `prev` (char const *const *)
- `card_prev` (int *)

### `getRowNames`

Get pointer to array[getNumRows()+1] of row names, including objective function name as last entry.

```cpp
char const *const * getRowNames()
```

### `getColNames`

Get pointer to array[getNumCols()] of column names.

```cpp
char const *const * getColNames()
```

### `rowName`

Return the row name for the specified index.

```cpp
const char * rowName(int index)
```

**Parameters:**

- `index` (int)

### `columnName`

Return the column name for the specified index.

```cpp
const char * columnName(int index)
```

**Parameters:**

- `index` (int)

### `rowIndex`

Return the index for the specified row name.

```cpp
int rowIndex(const char * name)
```

**Parameters:**

- `name` (const char *)

### `columnIndex`

Return the index for the specified column name.

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

### `objectiveOffset`

Returns the (constant) objective offset for objective j.

```cpp
double objectiveOffset(int j)
```

**Parameters:**

- `j` (int)

### `setObjectiveOffset`

Set objective offset.

```cpp
void setObjectiveOffset(double value)
```

**Parameters:**

- `value` (double)

### `wasMaximization`

Return true if maximization problem reformulated as minimization.

```cpp
bool wasMaximization()
```

### `setObjectiveOffset`

Set objective offset.

```cpp
void setObjectiveOffset(double value, int j)
```

**Parameters:**

- `value` (double)
- `j` (int)

### `isInteger`

Return true if a column is an integer (binary or general integer) variable.

```cpp
bool isInteger(int columnNumber)
```

**Parameters:**

- `columnNumber` (int)

### `integerColumns`

Get characteristic vector of integer variables.

```cpp
const char * integerColumns()
```

### `getInfinity`

Get infinity.

```cpp
double getInfinity()
```

### `setInfinity`

Set infinity.

```cpp
void setInfinity(const double )
```

**Parameters:**

- `` (const double)

### `getEpsilon`

Get epsilon.

```cpp
double getEpsilon()
```

### `setEpsilon`

Set epsilon.

```cpp
void setEpsilon(const double )
```

**Parameters:**

- `` (const double)

### `getNumberAcross`

Get numberAcross, the number of monomials to be printed per line.

```cpp
int getNumberAcross()
```

### `setNumberAcross`

Set numberAcross.

```cpp
void setNumberAcross(const int )
```

**Parameters:**

- `` (const int)

### `getDecimals`

Get decimals, the number of digits to write after the decimal point.

```cpp
int getDecimals()
```

### `setDecimals`

Set decimals.

```cpp
void setDecimals(const int )
```

**Parameters:**

- `` (const int)

### `setLpDataWithoutRowAndColNames`

Set the data of the object.

```cpp
void setLpDataWithoutRowAndColNames(const CoinPackedMatrix & m, const double * collb, const double * colub, const double * obj_coeff, const char * integrality, const double * rowlb, const double * rowub)
```

**Parameters:**

- `m` (const CoinPackedMatrix &)
- `collb` (const double *)
- `colub` (const double *)
- `obj_coeff` (const double *)
- `integrality` (const char *)
- `rowlb` (const double *)
- `rowub` (const double *)

### `setLpDataWithoutRowAndColNames`

```cpp
void setLpDataWithoutRowAndColNames(const CoinPackedMatrix & m, const double * collb, const double * colub, const double * obj_coeff, int num_objectives, const char * integrality, const double * rowlb, const double * rowub)
```

**Parameters:**

- `m` (const CoinPackedMatrix &)
- `collb` (const double *)
- `colub` (const double *)
- `obj_coeff` (const double *)
- `num_objectives` (int)
- `integrality` (const char *)
- `rowlb` (const double *)
- `rowub` (const double *)

### `is_invalid_name`

Return 0 if buff is a valid name for a row, a column or objective function, return a positive number otherwise.

```cpp
int is_invalid_name(const char * buff, const bool ranged)
```

**Parameters:**

- `buff` (const char *)
- `ranged` (const bool)

### `are_invalid_names`

Return 0 if each of the card_vnames entries of vnames is a valid name, return a positive number otherwise.

```cpp
int are_invalid_names(char const *const * vnames, const int card_vnames, const bool check_ranged)
```

**Parameters:**

- `vnames` (char const *const *)
- `card_vnames` (const int)
- `check_ranged` (const bool)

### `setDefaultRowNames`

Set objective function name to the default "obj" and row names to the default "cons0", "cons1", ...

```cpp
void setDefaultRowNames()
```

### `setDefaultColNames`

Set column names to the default "x0", "x1", ...

```cpp
void setDefaultColNames()
```

### `setLpDataRowAndColNames`

Set the row and column names.

```cpp
void setLpDataRowAndColNames(char const *const *const rownames, char const *const *const colnames)
```

**Parameters:**

- `rownames` (char const *const *const)
- `colnames` (char const *const *const)

### `writeLp`

Write the data in Lp format in the file with name filename.

```cpp
int writeLp(const char * filename, const double epsilon, const int numberAcross, const int decimals, const bool useRowNames = true)
```

**Parameters:**

- `filename` (const char *)
- `epsilon` (const double)
- `numberAcross` (const int)
- `decimals` (const int)
- `useRowNames` (const bool)

### `writeLp`

Write the data in Lp format in the file pointed to by the paramater fp.

```cpp
int writeLp(FILE * fp, const double epsilon, const int numberAcross, const int decimals, const bool useRowNames = true)
```

**Parameters:**

- `fp` (FILE *)
- `epsilon` (const double)
- `numberAcross` (const int)
- `decimals` (const int)
- `useRowNames` (const bool)

### `writeLp`

Write the data in Lp format in the file with name filename.

```cpp
int writeLp(const char * filename, const bool useRowNames = true)
```

**Parameters:**

- `filename` (const char *)
- `useRowNames` (const bool)

### `writeLp`

Write the data in Lp format in the file pointed to by the parameter fp.

```cpp
int writeLp(FILE * fp, const bool useRowNames = true)
```

**Parameters:**

- `fp` (FILE *)
- `useRowNames` (const bool)

### `readLp`

Read the data in Lp format from the file with name filename, using the given value for epsilon.

```cpp
void readLp(const char * filename, const double epsilon)
```

**Parameters:**

- `filename` (const char *)
- `epsilon` (const double)

### `readLp`

Read the data in Lp format from the file with name filename.

```cpp
void readLp(const char * filename)
```

**Parameters:**

- `filename` (const char *)

### `readLp`

Read the data in Lp format from the file stream, using the given value for epsilon.

```cpp
void readLp(FILE * fp, const double epsilon)
```

**Parameters:**

- `fp` (FILE *)
- `epsilon` (const double)

### `readLp`

Read the data in Lp format from the file stream.

```cpp
void readLp(FILE * fp)
```

**Parameters:**

- `fp` (FILE *)

### `readLp`

Does work of readLp.

```cpp
void readLp()
```

### `print`

Dump the data. Low level method for debugging.

```cpp
void print()
```

### `throwError`

Throw an error after printing message.

```cpp
void throwError(const char * str, const char * methodName, const char * className, const char * fileName, int line)
```

**Parameters:**

- `str` (const char *)
- `methodName` (const char *)
- `className` (const char *)
- `fileName` (const char *)
- `line` (int)

### `warnError`

```cpp
void warnError(const char * printBuffer, int line = 1)
```

**Parameters:**

- `printBuffer` (const char *)
- `line` (int)

### `loadSOS`

Load in SOS stuff.

```cpp
void loadSOS(int numberSets, const CoinSet * sets)
```

**Parameters:**

- `numberSets` (int)
- `sets` (const CoinSet *)

### `loadSOS`

Load in SOS stuff.

```cpp
void loadSOS(int numberSets, const CoinSet ** sets)
```

**Parameters:**

- `numberSets` (int)
- `sets` (const CoinSet **)

### `numberSets`

Number of SOS sets.

```cpp
int numberSets()
```

### `setInformation`

Set information.

```cpp
CoinSet ** setInformation()
```

## Source

Header: `layer-0/CoinUtils/src/CoinLpIO.hpp`
