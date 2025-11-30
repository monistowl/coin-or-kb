+++
title = "CoinPresolveMatrix"
description = "Augments CoinPrePostsolveMatrix with information about the problem that is only needed during presolve."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveMatrix.hpp"
api_url = "/api/coinutils/CoinPresolveMatrix.json"
+++

Augments CoinPrePostsolveMatrix with information about the problem that is only needed during presolve.

<div class="api-link"><a href="/api/coinutils/CoinPresolveMatrix.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinPrePostsolveMatrix`

## Description

For problem manipulation, this class adds a row-major matrix representation, linked lists that allow for easy manipulation of the matrix when applying presolve transforms, and vectors to track row and column processing status (changed, needs further processing, change prohibited)
For problem representation, this class adds information about variable type (integer or continuous), an objective offset, and a feasibility tolerance.
NOTE that the anyInteger_ and anyProhibited_ flags are independent of the vectors used to track this information for individual variables (integerType_ and rowChanged_ and colChanged_, respectively).
NOTE also that at the end of presolve the column-major and row-major matrix representations are loosely packed (i.e., there may be gaps between columns in the bulk storage arrays).
NOTE that while you might think that CoinPresolve is prepared to handle minimisation or maximisation, it's unlikely that this still works. This is a good thing: better to convert objective coefficients and duals once, before starting presolve, rather than doing it over and over in each transform that considers dual variables.

## Public Methods

### `change_bias`

Adjust objective function constant offset.

```cpp
void change_bias(double change_amount)
```

**Parameters:**

- `change_amount` (double)

### `statistics`

Say we want statistics - also set time.

```cpp
void statistics()
```

### `feasibilityTolerance`

Return feasibility tolerance.

```cpp
double feasibilityTolerance()
```

### `setFeasibilityTolerance`

Set feasibility tolerance.

```cpp
void setFeasibilityTolerance(double val)
```

**Parameters:**

- `val` (double)

### `status`

Returns problem status (0 = feasible, 1 = infeasible, 2 = unbounded)

```cpp
int status()
```

### `setStatus`

Set problem status.

```cpp
void setStatus(int status)
```

**Parameters:**

- `status` (int)

### `setPass`

Set pass number.

```cpp
void setPass(int pass = 0)
```

**Parameters:**

- `pass` (int)

### `setMaximumSubstitutionLevel`

Set Maximum substitution level (normally 3)

```cpp
void setMaximumSubstitutionLevel(int level)
```

**Parameters:**

- `level` (int)

### `recomputeSums`

Recompute row lhs bounds.

```cpp
int recomputeSums(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `initializeStuff`

Allocate scratch arrays.

```cpp
void initializeStuff()
```

### `deleteStuff`

Free scratch arrays.

```cpp
void deleteStuff()
```

### `setMatrix`

Load the cofficient matrix.

```cpp
void setMatrix(const CoinPackedMatrix * mtx)
```

**Parameters:**

- `mtx` (const CoinPackedMatrix *)

### `countEmptyRows`

Count number of empty rows.

```cpp
int countEmptyRows()
```

### `setVariableType`

Set variable type information for a single variable.

```cpp
void setVariableType(int i, int variableType)
```

**Parameters:**

- `i` (int)
- `variableType` (int)

### `setVariableType`

Set variable type information for all variables.

```cpp
void setVariableType(const unsigned char * variableType, int lenParam)
```

**Parameters:**

- `variableType` (const unsigned char *)
- `lenParam` (int)

### `setVariableType`

Set the type of all variables.

```cpp
void setVariableType(bool allIntegers, int lenParam)
```

**Parameters:**

- `allIntegers` (bool)
- `lenParam` (int)

### `setAnyInteger`

Set a flag for presence (true) or absence (false) of integer variables.

```cpp
void setAnyInteger(bool anyInteger = true)
```

**Parameters:**

- `anyInteger` (bool)

### `getRowStarts`

Get row start vector for row-major packed matrix.

```cpp
const CoinBigIndex * getRowStarts()
```

### `getColIndicesByRow`

Get vector of column indices for row-major packed matrix.

```cpp
const int * getColIndicesByRow()
```

### `getElementsByRow`

Get vector of elements for row-major packed matrix.

```cpp
const double * getElementsByRow()
```

### `isInteger`

Check for integrality of the specified variable.

```cpp
bool isInteger(int i)
```

**Parameters:**

- `i` (int)

### `anyInteger`

Check if there are any integer variables.

```cpp
bool anyInteger()
```

### `presolveOptions`

Picks up any special options.

```cpp
int presolveOptions()
```

### `setPresolveOptions`

Sets any special options (see presolveOptions_)

```cpp
void setPresolveOptions(int value)
```

**Parameters:**

- `value` (int)

### `initColsToDo`

Initialise the column ToDo lists.

```cpp
void initColsToDo()
```

### `stepColsToDo`

Step column ToDo lists.

```cpp
int stepColsToDo()
```

### `numberColsToDo`

Return the number of columns on the colsToDo_ list.

```cpp
int numberColsToDo()
```

### `colChanged`

Has column been changed?

```cpp
bool colChanged(int i)
```

**Parameters:**

- `i` (int)

### `unsetColChanged`

Mark column as not changed.

```cpp
void unsetColChanged(int i)
```

**Parameters:**

- `i` (int)

### `setColChanged`

Mark column as changed.

```cpp
void setColChanged(int i)
```

**Parameters:**

- `i` (int)

### `addCol`

Mark column as changed and add to list of columns to process next.

```cpp
void addCol(int i)
```

**Parameters:**

- `i` (int)

### `colProhibited`

Test if column is eligible for preprocessing.

```cpp
bool colProhibited(int i)
```

**Parameters:**

- `i` (int)

### `colProhibited2`

Test if column is eligible for preprocessing.

```cpp
bool colProhibited2(int i)
```

**Parameters:**

- `i` (int)

### `setColProhibited`

Mark column as ineligible for preprocessing.

```cpp
void setColProhibited(int i)
```

**Parameters:**

- `i` (int)

### `colUsed`

Test if column is marked as used.

```cpp
bool colUsed(int i)
```

**Parameters:**

- `i` (int)

### `setColUsed`

Mark column as used.

```cpp
void setColUsed(int i)
```

**Parameters:**

- `i` (int)

### `unsetColUsed`

Mark column as unused.

```cpp
void unsetColUsed(int i)
```

**Parameters:**

- `i` (int)

### `colInfinite`

Has column infinite ub (originally)

```cpp
bool colInfinite(int i)
```

**Parameters:**

- `i` (int)

### `unsetColInfinite`

Mark column as not infinite ub (originally)

```cpp
void unsetColInfinite(int i)
```

**Parameters:**

- `i` (int)

### `setColInfinite`

Mark column as infinite ub (originally)

```cpp
void setColInfinite(int i)
```

**Parameters:**

- `i` (int)

### `colCanTouch`

Test if column can be touched at all.

```cpp
bool colCanTouch(int i)
```

**Parameters:**

- `i` (int)

### `colCanTouch2`

Test if column can be touched at all.

```cpp
bool colCanTouch2(int i)
```

**Parameters:**

- `i` (int)

### `setColLeaveTotallyAlone`

Mark column as totally ineligible for preprocessing.

```cpp
void setColLeaveTotallyAlone(int i)
```

**Parameters:**

- `i` (int)

### `initRowsToDo`

Initialise the row ToDo lists.

```cpp
void initRowsToDo()
```

### `stepRowsToDo`

Step row ToDo lists.

```cpp
int stepRowsToDo()
```

### `numberRowsToDo`

Return the number of rows on the rowsToDo_ list.

```cpp
int numberRowsToDo()
```

### `rowChanged`

Has row been changed?

```cpp
bool rowChanged(int i)
```

**Parameters:**

- `i` (int)

### `unsetRowChanged`

Mark row as not changed.

```cpp
void unsetRowChanged(int i)
```

**Parameters:**

- `i` (int)

### `setRowChanged`

Mark row as changed.

```cpp
void setRowChanged(int i)
```

**Parameters:**

- `i` (int)

### `addRow`

Mark row as changed and add to list of rows to process next.

```cpp
void addRow(int i)
```

**Parameters:**

- `i` (int)

### `rowProhibited`

Test if row is eligible for preprocessing.

```cpp
bool rowProhibited(int i)
```

**Parameters:**

- `i` (int)

### `rowProhibited2`

Test if row is eligible for preprocessing.

```cpp
bool rowProhibited2(int i)
```

**Parameters:**

- `i` (int)

### `setRowProhibited`

Mark row as ineligible for preprocessing.

```cpp
void setRowProhibited(int i)
```

**Parameters:**

- `i` (int)

### `rowUsed`

Test if row is marked as used.

```cpp
bool rowUsed(int i)
```

**Parameters:**

- `i` (int)

### `setRowUsed`

Mark row as used.

```cpp
void setRowUsed(int i)
```

**Parameters:**

- `i` (int)

### `unsetRowUsed`

Mark row as unused.

```cpp
void unsetRowUsed(int i)
```

**Parameters:**

- `i` (int)

### `anyProhibited`

Check if there are any prohibited rows or columns.

```cpp
bool anyProhibited()
```

### `setAnyProhibited`

Set a flag for presence of prohibited rows or columns.

```cpp
void setAnyProhibited(bool val = true)
```

**Parameters:**

- `val` (bool)

### `CoinPresolveMatrix`

Native constructor

```cpp
 CoinPresolveMatrix(int ncols_alloc, int nrows_alloc, CoinBigIndex nelems_alloc)
```

**Parameters:**

- `ncols_alloc` (int)
- `nrows_alloc` (int)
- `nelems_alloc` (CoinBigIndex)

### `~CoinPresolveMatrix`

Destructor.

```cpp
 ~CoinPresolveMatrix()
```

### `presolve_no_dups`

Check column-major and/or row-major matrices for duplicate entries in the major vectors.

```cpp
void presolve_no_dups(const CoinPresolveMatrix * preObj, bool doCol = true, bool doRow = true)
```

**Parameters:**

- `preObj` (const CoinPresolveMatrix *)
- `doCol` (bool)
- `doRow` (bool)

### `presolve_links_ok`

Check the links which track storage order for major vectors in the bulk storage area.

```cpp
void presolve_links_ok(const CoinPresolveMatrix * preObj, bool doCol = true, bool doRow = true)
```

**Parameters:**

- `preObj` (const CoinPresolveMatrix *)
- `doCol` (bool)
- `doRow` (bool)

### `presolve_no_zeros`

Check for explicit zeros in the column- and/or row-major matrices.

```cpp
void presolve_no_zeros(const CoinPresolveMatrix * preObj, bool doCol = true, bool doRow = true)
```

**Parameters:**

- `preObj` (const CoinPresolveMatrix *)
- `doCol` (bool)
- `doRow` (bool)

### `presolve_consistent`

Checks for equivalence of the column- and row-major matrices.

```cpp
void presolve_consistent(const CoinPresolveMatrix * preObj, bool chkvals = true)
```

**Parameters:**

- `preObj` (const CoinPresolveMatrix *)
- `chkvals` (bool)

### `presolve_check_sol`

Check primal solution and architectural variable status.

```cpp
void presolve_check_sol(const CoinPresolveMatrix * preObj, int chkColSol = 2, int chkRowAct = 1, int chkStatus = 1)
```

**Parameters:**

- `preObj` (const CoinPresolveMatrix *)
- `chkColSol` (int)
- `chkRowAct` (int)
- `chkStatus` (int)

### `presolve_check_nbasic`

Check for the proper number of basic variables.

```cpp
void presolve_check_nbasic(const CoinPresolveMatrix * preObj)
```

**Parameters:**

- `preObj` (const CoinPresolveMatrix *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveMatrix.hpp`
