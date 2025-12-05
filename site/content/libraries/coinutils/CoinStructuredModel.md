+++
title = "CoinStructuredModel"
description = "CoinStructuredModel class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinStructuredModel.hpp"
api_url = "/api/coinutils/CoinStructuredModel.json"
+++


## Inheritance

Inherits from: `CoinBaseModel`

## Public Methods

### `addBlock`

add a block from a CoinModel using names given as parameters returns number of errors (e.g.

```cpp
int addBlock(const std::string & rowBlock, const std::string & columnBlock, const CoinBaseModel & block)
```

**Parameters:**

- `rowBlock` (const std::string &)
- `columnBlock` (const std::string &)
- `block` (const CoinBaseModel &)

### `addBlock`

add a block from a CoinModel with names in model returns number of errors (e.g.

```cpp
int addBlock(const CoinBaseModel & block)
```

**Parameters:**

- `block` (const CoinBaseModel &)

### `addBlock`

add a block from a CoinModel using names given as parameters returns number of errors (e.g.

```cpp
int addBlock(const std::string & rowBlock, const std::string & columnBlock, CoinBaseModel * block)
```

**Parameters:**

- `rowBlock` (const std::string &)
- `columnBlock` (const std::string &)
- `block` (CoinBaseModel *)

### `addBlock`

add a block using names

```cpp
int addBlock(const std::string & rowBlock, const std::string & columnBlock, const CoinPackedMatrix & matrix, const double * rowLower, const double * rowUpper, const double * columnLower, const double * columnUpper, const double * objective)
```

**Parameters:**

- `rowBlock` (const std::string &)
- `columnBlock` (const std::string &)
- `matrix` (const CoinPackedMatrix &)
- `rowLower` (const double *)
- `rowUpper` (const double *)
- `columnLower` (const double *)
- `columnUpper` (const double *)
- `objective` (const double *)

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

### `readSmps`

Read SMPS model.

```cpp
int readSmps(const char * filename, bool keepNames = false, bool ignoreErrors = false)
```

**Parameters:**

- `filename` (const char *)
- `keepNames` (bool)
- `ignoreErrors` (bool)

### `decompose`

Decompose a CoinModel 1 - try D-W 2 - try Benders 3 - try Staircase Returns number of blocks or zero if no structure.

```cpp
int decompose(const CoinModel & model, int type, int maxBlocks = 50, const char ** starts = NULL)
```

**Parameters:**

- `model` (const CoinModel &)
- `type` (int)
- `maxBlocks` (int)
- `starts` (const char **)

### `decompose`

Decompose a model specified as arrays + CoinPackedMatrix 1 - try D-W 2 - try Benders 3 - try Staircase Returns number of blocks or zero if no structure.

```cpp
int decompose(const CoinPackedMatrix & matrix, const double * rowLower, const double * rowUpper, const double * columnLower, const double * columnUpper, const double * objective, int type, int maxBlocks = 50, int * starts = NULL, double objectiveOffset = 0.0)
```

**Parameters:**

- `matrix` (const CoinPackedMatrix &)
- `rowLower` (const double *)
- `rowUpper` (const double *)
- `columnLower` (const double *)
- `columnUpper` (const double *)
- `objective` (const double *)
- `type` (int)
- `maxBlocks` (int)
- `starts` (int *)
- `objectiveOffset` (double)

### `numberRowBlocks`

Return number of row blocks.

```cpp
int numberRowBlocks()
```

### `numberColumnBlocks`

Return number of column blocks.

```cpp
int numberColumnBlocks()
```

### `numberElementBlocks`

Return number of elementBlocks.

```cpp
int numberElementBlocks()
```

### `numberElements`

Return number of elements.

```cpp
CoinBigIndex numberElements()
```

### `getRowBlock`

Return the i'th row block name.

```cpp
const std::string & getRowBlock(int i)
```

**Parameters:**

- `i` (int)

### `setRowBlock`

Set i'th row block name.

```cpp
void setRowBlock(int i, const std::string & name)
```

**Parameters:**

- `i` (int)
- `name` (const std::string &)

### `addRowBlock`

Add or check a row block name and number of rows.

```cpp
int addRowBlock(int numberRows, const std::string & name)
```

**Parameters:**

- `numberRows` (int)
- `name` (const std::string &)

### `rowBlock`

Return a row block index given a row block name.

```cpp
int rowBlock(const std::string & name)
```

**Parameters:**

- `name` (const std::string &)

### `getColumnBlock`

Return i'th the column block name.

```cpp
const std::string & getColumnBlock(int i)
```

**Parameters:**

- `i` (int)

### `setColumnBlock`

Set i'th column block name.

```cpp
void setColumnBlock(int i, const std::string & name)
```

**Parameters:**

- `i` (int)
- `name` (const std::string &)

### `addColumnBlock`

Add or check a column block name and number of columns.

```cpp
int addColumnBlock(int numberColumns, const std::string & name)
```

**Parameters:**

- `numberColumns` (int)
- `name` (const std::string &)

### `columnBlock`

Return a column block index given a column block name.

```cpp
int columnBlock(const std::string & name)
```

**Parameters:**

- `name` (const std::string &)

### `blockType`

Return i'th block type.

```cpp
const CoinModelBlockInfo & blockType(int i)
```

**Parameters:**

- `i` (int)

### `block`

Return i'th block.

```cpp
CoinBaseModel * block(int i)
```

**Parameters:**

- `i` (int)

### `block`

Return block corresponding to row and column.

```cpp
const CoinBaseModel * block(int row, int column)
```

**Parameters:**

- `row` (int)
- `column` (int)

### `coinBlock`

Return i'th block as CoinModel (or NULL)

```cpp
CoinModel * coinBlock(int i)
```

**Parameters:**

- `i` (int)

### `coinBlock`

Return block corresponding to row and column as CoinModel.

```cpp
const CoinBaseModel * coinBlock(int row, int column)
```

**Parameters:**

- `row` (int)
- `column` (int)

### `blockIndex`

Return block number corresponding to row and column.

```cpp
int blockIndex(int row, int column)
```

**Parameters:**

- `row` (int)
- `column` (int)

### `coinModelBlock`

Return model as a CoinModel block and fill in info structure and update counts.

```cpp
CoinModel * coinModelBlock(CoinModelBlockInfo & info)
```

**Parameters:**

- `info` (CoinModelBlockInfo &)

### `setCoinModel`

Sets given block into coinModelBlocks_.

```cpp
void setCoinModel(CoinModel * block, int iBlock)
```

**Parameters:**

- `block` (CoinModel *)
- `iBlock` (int)

### `refresh`

Refresh info in blockType_.

```cpp
void refresh(int iBlock)
```

**Parameters:**

- `iBlock` (int)

### `block`

Fill pointers corresponding to row and column.

```cpp
CoinModelBlockInfo block(int row, int column, const double *& rowLower, const double *& rowUpper, const double *& columnLower, const double *& columnUpper, const double *& objective)
```

**Parameters:**

- `row` (int)
- `column` (int)
- `rowLower` (const double *&)
- `rowUpper` (const double *&)
- `columnLower` (const double *&)
- `columnUpper` (const double *&)
- `objective` (const double *&)

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

### `CoinStructuredModel`

Default constructor.

```cpp
 CoinStructuredModel()
```

### `CoinStructuredModel`

Read a problem in MPS format from the given filename.

```cpp
 CoinStructuredModel(const char * fileName, int decompose = 0, int maxBlocks = 50)
```

**Parameters:**

- `fileName` (const char *)
- `decompose` (int)
- `maxBlocks` (int)

### `~CoinStructuredModel`

Destructor.

```cpp
 ~CoinStructuredModel()
```

### `CoinStructuredModel`

The copy constructor.

```cpp
 CoinStructuredModel(const CoinStructuredModel & )
```

**Parameters:**

- `` (const CoinStructuredModel &)

### `operator=`

=

```cpp
CoinStructuredModel & operator=(const CoinStructuredModel & )
```

**Parameters:**

- `` (const CoinStructuredModel &)

### `clone`

Clone.

```cpp
CoinBaseModel * clone()
```

## Source

Header: `layer-0/CoinUtils/src/CoinStructuredModel.hpp`
