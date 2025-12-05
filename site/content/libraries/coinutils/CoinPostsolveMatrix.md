+++
title = "CoinPostsolveMatrix"
description = "Augments CoinPrePostsolveMatrix with information about the problem that is only needed during postsolve."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveMatrix.hpp"
api_url = "/api/coinutils/CoinPostsolveMatrix.json"
+++

Augments CoinPrePostsolveMatrix with information about the problem that is only needed during postsolve.


## Inheritance

Inherits from: `CoinPrePostsolveMatrix`

## Description

The notable point is that the matrix representation is threaded. The representation is column-major and starts with the standard two pairs of arrays: one pair to hold the row indices and coefficients, the second pair to hold the column starting positions and lengths. But the row indices and coefficients for a column do not necessarily occupy a contiguous block in their respective arrays. Instead, a link array gives the position of the next (row index,coefficient) pair. If the row index and value of a coefficient a<p,j> occupy position kp in their arrays, then the position of the next coefficient a<q,j> is found as kq = link[kp].
This threaded representation allows for efficient expansion of columns as rows are reintroduced during postsolve transformations. The basic packed structures are allocated to the expected size of the postsolved matrix, and as new coefficients are added, their location is simply added to the thread for the column.
There is no provision to convert the threaded representation to a packed representation. In the context of postsolve, it's not required. (You did keep a copy of the original matrix, eh?)

## Public Methods

### `check_nbasic`

debug

```cpp
void check_nbasic()
```

### `CoinPostsolveMatrix`

Native constructor

```cpp
 CoinPostsolveMatrix(int ncols_alloc, int nrows_alloc, CoinBigIndex nelems_alloc, const double * origRL = 0, const double * origRU = 0)
```

**Parameters:**

- `ncols_alloc` (int)
- `nrows_alloc` (int)
- `nelems_alloc` (CoinBigIndex)
- `origRL` (const double *)
- `origRU` (const double *)

### `assignPresolveToPostsolve`

Load an empty CoinPostsolveMatrix from a CoinPresolveMatrix.

```cpp
void assignPresolveToPostsolve(CoinPresolveMatrix *& preObj, const double * origRL = 0, const double * origRU = 0)
```

**Parameters:**

- `preObj` (CoinPresolveMatrix *&)
- `origRL` (const double *)
- `origRU` (const double *)

### `~CoinPostsolveMatrix`

Destructor.

```cpp
 ~CoinPostsolveMatrix()
```

### `presolve_find_col`

Find position of a column in a row in a row-major matrix.

```cpp
CoinBigIndex presolve_find_col(int col, CoinBigIndex krs, CoinBigIndex kre, const int * hcol)
```

**Parameters:**

- `col` (int)
- `krs` (CoinBigIndex)
- `kre` (CoinBigIndex)
- `hcol` (const int *)

### `presolve_find_minor2`

Find position of a minor index in a major vector in a threaded matrix.

```cpp
CoinBigIndex presolve_find_minor2(int tgt, CoinBigIndex ks, int majlen, const int * minndxs, const CoinBigIndex * majlinks)
```

**Parameters:**

- `tgt` (int)
- `ks` (CoinBigIndex)
- `majlen` (int)
- `minndxs` (const int *)
- `majlinks` (const CoinBigIndex *)

### `presolve_find_row2`

Find position of a row in a column in a column-major threaded matrix.

```cpp
CoinBigIndex presolve_find_row2(int row, CoinBigIndex kcs, int collen, const int * hrow, const CoinBigIndex * clinks)
```

**Parameters:**

- `row` (int)
- `kcs` (CoinBigIndex)
- `collen` (int)
- `hrow` (const int *)
- `clinks` (const CoinBigIndex *)

### `presolve_find_minor3`

Find position of a minor index in a major vector in a threaded matrix.

```cpp
CoinBigIndex presolve_find_minor3(int tgt, CoinBigIndex ks, int majlen, const int * minndxs, const CoinBigIndex * majlinks)
```

**Parameters:**

- `tgt` (int)
- `ks` (CoinBigIndex)
- `majlen` (int)
- `minndxs` (const int *)
- `majlinks` (const CoinBigIndex *)

### `presolve_find_row3`

Find position of a row in a column in a column-major threaded matrix.

```cpp
CoinBigIndex presolve_find_row3(int row, CoinBigIndex kcs, int collen, const int * hrow, const CoinBigIndex * clinks)
```

**Parameters:**

- `row` (int)
- `kcs` (CoinBigIndex)
- `collen` (int)
- `hrow` (const int *)
- `clinks` (const CoinBigIndex *)

### `presolve_delete_from_major2`

Delete the entry for a minor index from a major vector in a threaded matrix.

```cpp
void presolve_delete_from_major2(int majndx, int minndx, CoinBigIndex * majstrts, int * majlens, int * minndxs, CoinBigIndex * majlinks, CoinBigIndex * free_listp)
```

**Parameters:**

- `majndx` (int)
- `minndx` (int)
- `majstrts` (CoinBigIndex *)
- `majlens` (int *)
- `minndxs` (int *)
- `majlinks` (CoinBigIndex *)
- `free_listp` (CoinBigIndex *)

### `presolve_delete_from_col2`

Delete the entry for row `row` from column `col` in a column-major threaded matrix.

```cpp
void presolve_delete_from_col2(int row, int col, CoinBigIndex * mcstrt, int * hincol, int * hrow, CoinBigIndex * clinks, CoinBigIndex * free_listp)
```

**Parameters:**

- `row` (int)
- `col` (int)
- `mcstrt` (CoinBigIndex *)
- `hincol` (int *)
- `hrow` (int *)
- `clinks` (CoinBigIndex *)
- `free_listp` (CoinBigIndex *)

### `presolve_check_threads`

Checks that column threads agree with column lengths.

```cpp
void presolve_check_threads(const CoinPostsolveMatrix * obj)
```

**Parameters:**

- `obj` (const CoinPostsolveMatrix *)

### `presolve_check_free_list`

Checks the free list.

```cpp
void presolve_check_free_list(const CoinPostsolveMatrix * obj, bool chkElemCnt = false)
```

**Parameters:**

- `obj` (const CoinPostsolveMatrix *)
- `chkElemCnt` (bool)

### `presolve_check_reduced_costs`

Check stored reduced costs for accuracy and consistency with variable status.

```cpp
void presolve_check_reduced_costs(const CoinPostsolveMatrix * obj)
```

**Parameters:**

- `obj` (const CoinPostsolveMatrix *)

### `presolve_check_duals`

Check the dual variables for consistency with row activity.

```cpp
void presolve_check_duals(const CoinPostsolveMatrix * postObj)
```

**Parameters:**

- `postObj` (const CoinPostsolveMatrix *)

### `presolve_check_sol`

Check primal solution and architectural variable status.

```cpp
void presolve_check_sol(const CoinPostsolveMatrix * postObj, int chkColSol = 2, int chkRowAct = 2, int chkStatus = 1)
```

**Parameters:**

- `postObj` (const CoinPostsolveMatrix *)
- `chkColSol` (int)
- `chkRowAct` (int)
- `chkStatus` (int)

### `presolve_check_nbasic`

Check for the proper number of basic variables.

```cpp
void presolve_check_nbasic(const CoinPostsolveMatrix * postObj)
```

**Parameters:**

- `postObj` (const CoinPostsolveMatrix *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveMatrix.hpp`
