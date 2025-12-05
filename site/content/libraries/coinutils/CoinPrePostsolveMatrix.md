+++
title = "CoinPrePostsolveMatrix"
description = "Collects all the information about the problem that is needed in both presolve and postsolve."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveMatrix.hpp"
api_url = "/api/coinutils/CoinPrePostsolveMatrix.json"
+++

Collects all the information about the problem that is needed in both presolve and postsolve.


Derived classes: `CoinPostsolveMatrix`, `CoinPresolveMatrix`

## Description

In a bit more detail, a column-major representation of the constraint matrix and upper and lower bounds on variables and constraints, plus row and column solutions, reduced costs, and status. There's also a set of arrays holding the original row and column numbers.
As presolve and postsolve transform the matrix, it will occasionally be necessary to expand the number of entries in a column. There are two aspects: During postsolve, the constraint system is expected to grow as the smaller presolved system is transformed back to the original system.
During both pre- and postsolve, transforms can increase the number of coefficients in a row or column. (See the variable substitution, doubleton, and tripleton transforms.)
The first is addressed by the members ncols0_, nrows0_, and nelems0_. These should be set (via constructor parameters) to values large enough for the largest size taken on by the constraint system. Typically, this will be the size of the original constraint system.
The second is addressed by a generous allocation of extra (empty) space for the arrays used to hold coefficients and row indices. When columns must be expanded, they are moved into the empty space. When it is used up, the arrays are compacted. When compaction fails to produce sufficient space, presolve/postsolve will fail.
CoinPrePostsolveMatrix isn't really intended to be used bare  the expectation is that it'll be used through CoinPresolveMatrix or CoinPostsolveMatrix. Some of the functions needed to load a problem are defined in the derived classes.
When CoinPresolve is applied when reoptimising, we need to be prepared to accept a basis and modify it in step with the presolve actions (otherwise we throw away all the advantages of warm start for reoptimization). But other solution components (acts_, rowduals_, sol_, and rcosts_) are needed only for postsolve, where they're used in places to determine the proper action(s) when restoring rows or columns. If presolve is provided with a solution, it will modify it in step with the presolve actions. Moving the solution components from CoinPrePostsolveMatrix to CoinPostsolveMatrix would break a lot of code. It's not clear that it's worth it, and it would preclude upgrades to the presolve side that might make use of any of these.  lh, 080501

## Public Methods

### `CoinPrePostsolveMatrix`

Native constructor

```cpp
 CoinPrePostsolveMatrix(int ncols_alloc, int nrows_alloc, CoinBigIndex nelems_alloc)
```

**Parameters:**

- `ncols_alloc` (int)
- `nrows_alloc` (int)
- `nelems_alloc` (CoinBigIndex)

### `~CoinPrePostsolveMatrix`

Destructor.

```cpp
 ~CoinPrePostsolveMatrix()
```

### `messageHandler`

Return message handler.

```cpp
CoinMessageHandler * messageHandler()
```

### `setMessageHandler`

Set message handler.

```cpp
void setMessageHandler(CoinMessageHandler * handler)
```

**Parameters:**

- `handler` (CoinMessageHandler *)

### `messages`

Return messages.

```cpp
CoinMessages messages()
```

### `setRowStatus`

Set row status (i.e., status of artificial for this row)

```cpp
void setRowStatus(int sequence, Status status)
```

**Parameters:**

- `sequence` (int)
- `status` (Status)

### `getRowStatus`

Get row status.

```cpp
Status getRowStatus(int sequence)
```

**Parameters:**

- `sequence` (int)

### `rowIsBasic`

Check if artificial for this row is basic.

```cpp
bool rowIsBasic(int sequence)
```

**Parameters:**

- `sequence` (int)

### `setColumnStatus`

Set column status (i.e., status of primal variable)

```cpp
void setColumnStatus(int sequence, Status status)
```

**Parameters:**

- `sequence` (int)
- `status` (Status)

### `getColumnStatus`

Get column (structural variable) status.

```cpp
Status getColumnStatus(int sequence)
```

**Parameters:**

- `sequence` (int)

### `columnIsBasic`

Check if column (structural variable) is basic.

```cpp
bool columnIsBasic(int sequence)
```

**Parameters:**

- `sequence` (int)

### `setRowStatusUsingValue`

Set status of row (artificial variable) to the correct nonbasic status given bounds and current value.

```cpp
void setRowStatusUsingValue(int iRow)
```

**Parameters:**

- `iRow` (int)

### `setColumnStatusUsingValue`

Set status of column (structural variable) to the correct nonbasic status given bounds and current value.

```cpp
void setColumnStatusUsingValue(int iColumn)
```

**Parameters:**

- `iColumn` (int)

### `setStructuralStatus`

Set column (structural variable) status vector.

```cpp
void setStructuralStatus(const char * strucStatus, int lenParam)
```

**Parameters:**

- `strucStatus` (const char *)
- `lenParam` (int)

### `setArtificialStatus`

Set row (artificial variable) status vector.

```cpp
void setArtificialStatus(const char * artifStatus, int lenParam)
```

**Parameters:**

- `artifStatus` (const char *)
- `lenParam` (int)

### `setStatus`

Set the status of all variables from a basis.

```cpp
void setStatus(const CoinWarmStartBasis * basis)
```

**Parameters:**

- `basis` (const CoinWarmStartBasis *)

### `getStatus`

Get status in the form of a CoinWarmStartBasis.

```cpp
CoinWarmStartBasis * getStatus()
```

### `columnStatusString`

Return a print string for status of a column (structural variable)

```cpp
const char * columnStatusString(int j)
```

**Parameters:**

- `j` (int)

### `rowStatusString`

Return a print string for status of a row (artificial variable)

```cpp
const char * rowStatusString(int i)
```

**Parameters:**

- `i` (int)

### `setObjOffset`

Set the objective function offset for the original system.

```cpp
void setObjOffset(double offset)
```

**Parameters:**

- `offset` (double)

### `setObjSense`

Set the objective sense (max/min)

```cpp
void setObjSense(double objSense)
```

**Parameters:**

- `objSense` (double)

### `setPrimalTolerance`

Set the primal feasibility tolerance.

```cpp
void setPrimalTolerance(double primTol)
```

**Parameters:**

- `primTol` (double)

### `setDualTolerance`

Set the dual feasibility tolerance.

```cpp
void setDualTolerance(double dualTol)
```

**Parameters:**

- `dualTol` (double)

### `setColLower`

Set column lower bounds.

```cpp
void setColLower(const double * colLower, int lenParam)
```

**Parameters:**

- `colLower` (const double *)
- `lenParam` (int)

### `setColUpper`

Set column upper bounds.

```cpp
void setColUpper(const double * colUpper, int lenParam)
```

**Parameters:**

- `colUpper` (const double *)
- `lenParam` (int)

### `setColSolution`

Set column solution.

```cpp
void setColSolution(const double * colSol, int lenParam)
```

**Parameters:**

- `colSol` (const double *)
- `lenParam` (int)

### `setCost`

Set objective coefficients.

```cpp
void setCost(const double * cost, int lenParam)
```

**Parameters:**

- `cost` (const double *)
- `lenParam` (int)

### `setReducedCost`

Set reduced costs.

```cpp
void setReducedCost(const double * redCost, int lenParam)
```

**Parameters:**

- `redCost` (const double *)
- `lenParam` (int)

### `setRowLower`

Set row lower bounds.

```cpp
void setRowLower(const double * rowLower, int lenParam)
```

**Parameters:**

- `rowLower` (const double *)
- `lenParam` (int)

### `setRowUpper`

Set row upper bounds.

```cpp
void setRowUpper(const double * rowUpper, int lenParam)
```

**Parameters:**

- `rowUpper` (const double *)
- `lenParam` (int)

### `setRowPrice`

Set row solution.

```cpp
void setRowPrice(const double * rowSol, int lenParam)
```

**Parameters:**

- `rowSol` (const double *)
- `lenParam` (int)

### `setRowActivity`

Set row activity.

```cpp
void setRowActivity(const double * rowAct, int lenParam)
```

**Parameters:**

- `rowAct` (const double *)
- `lenParam` (int)

### `getNumCols`

Get current number of columns.

```cpp
int getNumCols()
```

### `getNumRows`

Get current number of rows.

```cpp
int getNumRows()
```

### `getNumElems`

Get current number of non-zero coefficients.

```cpp
CoinBigIndex getNumElems()
```

### `getColStarts`

Get column start vector for column-major packed matrix.

```cpp
const CoinBigIndex * getColStarts()
```

### `getColLengths`

Get column length vector for column-major packed matrix.

```cpp
const int * getColLengths()
```

### `getRowIndicesByCol`

Get vector of row indices for column-major packed matrix.

```cpp
const int * getRowIndicesByCol()
```

### `getElementsByCol`

Get vector of elements for column-major packed matrix.

```cpp
const double * getElementsByCol()
```

### `getColLower`

Get column lower bounds.

```cpp
const double * getColLower()
```

### `getColUpper`

Get column upper bounds.

```cpp
const double * getColUpper()
```

### `getCost`

Get objective coefficients.

```cpp
const double * getCost()
```

### `getRowLower`

Get row lower bounds.

```cpp
const double * getRowLower()
```

### `getRowUpper`

Get row upper bounds.

```cpp
const double * getRowUpper()
```

### `getColSolution`

Get column solution (primal variable values)

```cpp
const double * getColSolution()
```

### `getRowActivity`

Get row activity (constraint lhs values)

```cpp
const double * getRowActivity()
```

### `getRowPrice`

Get row solution (dual variables)

```cpp
const double * getRowPrice()
```

### `getReducedCost`

Get reduced costs.

```cpp
const double * getReducedCost()
```

### `countEmptyCols`

Count empty columns.

```cpp
int countEmptyCols()
```

### `statusName`

Generate a print string for a status code.

```cpp
const char * statusName(CoinPrePostsolveMatrix::Status status)
```

**Parameters:**

- `status` (CoinPrePostsolveMatrix::Status)

### `presolve_make_memlists`

Initialise linked list for major vector order in bulk storage.

```cpp
COINUTILSLIB_EXPORT void presolve_make_memlists(int * lengths, presolvehlink * link, int n)
```

**Parameters:**

- `lengths` (int *)
- `link` (presolvehlink *)
- `n` (int)

### `presolve_expand_major`

Make sure a major-dimension vector k has room for one more coefficient.

```cpp
bool presolve_expand_major(CoinBigIndex * majstrts, double * majels, int * minndxs, int * majlens, presolvehlink * majlinks, int nmaj, int k)
```

**Parameters:**

- `majstrts` (CoinBigIndex *)
- `majels` (double *)
- `minndxs` (int *)
- `majlens` (int *)
- `majlinks` (presolvehlink *)
- `nmaj` (int)
- `k` (int)

### `presolve_expand_col`

Make sure a column (colx) in a column-major matrix has room for one more coefficient.

```cpp
bool presolve_expand_col(CoinBigIndex * mcstrt, double * colels, int * hrow, int * hincol, presolvehlink * clink, int ncols, int colx)
```

**Parameters:**

- `mcstrt` (CoinBigIndex *)
- `colels` (double *)
- `hrow` (int *)
- `hincol` (int *)
- `clink` (presolvehlink *)
- `ncols` (int)
- `colx` (int)

### `presolve_expand_row`

Make sure a row (rowx) in a row-major matrix has room for one more coefficient.

```cpp
bool presolve_expand_row(CoinBigIndex * mrstrt, double * rowels, int * hcol, int * hinrow, presolvehlink * rlink, int nrows, int rowx)
```

**Parameters:**

- `mrstrt` (CoinBigIndex *)
- `rowels` (double *)
- `hcol` (int *)
- `hinrow` (int *)
- `rlink` (presolvehlink *)
- `nrows` (int)
- `rowx` (int)

### `presolve_find_minor`

Find position of a minor index in a major vector.

```cpp
CoinBigIndex presolve_find_minor(int tgt, CoinBigIndex ks, CoinBigIndex ke, const int * minndxs)
```

**Parameters:**

- `tgt` (int)
- `ks` (CoinBigIndex)
- `ke` (CoinBigIndex)
- `minndxs` (const int *)

### `presolve_find_row`

Find position of a row in a column in a column-major matrix.

```cpp
CoinBigIndex presolve_find_row(int row, CoinBigIndex kcs, CoinBigIndex kce, const int * hrow)
```

**Parameters:**

- `row` (int)
- `kcs` (CoinBigIndex)
- `kce` (CoinBigIndex)
- `hrow` (const int *)

### `presolve_find_minor1`

Find position of a minor index in a major vector.

```cpp
CoinBigIndex presolve_find_minor1(int tgt, CoinBigIndex ks, CoinBigIndex ke, const int * minndxs)
```

**Parameters:**

- `tgt` (int)
- `ks` (CoinBigIndex)
- `ke` (CoinBigIndex)
- `minndxs` (const int *)

### `presolve_find_row1`

Find position of a row in a column in a column-major matrix.

```cpp
CoinBigIndex presolve_find_row1(int row, CoinBigIndex kcs, CoinBigIndex kce, const int * hrow)
```

**Parameters:**

- `row` (int)
- `kcs` (CoinBigIndex)
- `kce` (CoinBigIndex)
- `hrow` (const int *)

### `presolve_find_col1`

Find position of a column in a row in a row-major matrix.

```cpp
CoinBigIndex presolve_find_col1(int col, CoinBigIndex krs, CoinBigIndex kre, const int * hcol)
```

**Parameters:**

- `col` (int)
- `krs` (CoinBigIndex)
- `kre` (CoinBigIndex)
- `hcol` (const int *)

### `presolve_delete_from_major`

Delete the entry for a minor index from a major vector.

```cpp
void presolve_delete_from_major(int majndx, int minndx, const CoinBigIndex * majstrts, int * majlens, int * minndxs, double * els)
```

**Parameters:**

- `majndx` (int)
- `minndx` (int)
- `majstrts` (const CoinBigIndex *)
- `majlens` (int *)
- `minndxs` (int *)
- `els` (double *)

### `presolve_delete_many_from_major`

Delete marked entries.

```cpp
void presolve_delete_many_from_major(int majndx, char * marked, const CoinBigIndex * majstrts, int * majlens, int * minndxs, double * els)
```

**Parameters:**

- `majndx` (int)
- `marked` (char *)
- `majstrts` (const CoinBigIndex *)
- `majlens` (int *)
- `minndxs` (int *)
- `els` (double *)

### `presolve_delete_from_col`

Delete the entry for row `row` from column `col` in a column-major matrix.

```cpp
void presolve_delete_from_col(int row, int col, const CoinBigIndex * mcstrt, int * hincol, int * hrow, double * colels)
```

**Parameters:**

- `row` (int)
- `col` (int)
- `mcstrt` (const CoinBigIndex *)
- `hincol` (int *)
- `hrow` (int *)
- `colels` (double *)

### `presolve_delete_from_row`

Delete the entry for column `col` from row `row` in a row-major matrix.

```cpp
void presolve_delete_from_row(int row, int col, const CoinBigIndex * mrstrt, int * hinrow, int * hcol, double * rowels)
```

**Parameters:**

- `row` (int)
- `col` (int)
- `mrstrt` (const CoinBigIndex *)
- `hinrow` (int *)
- `hcol` (int *)
- `rowels` (double *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveMatrix.hpp`
