+++
title = "CoinBuild"
description = "In many cases it is natural to build a model by adding one row at a time."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinBuild.hpp"
api_url = "/api/coinutils/CoinBuild.json"
+++

In many cases it is natural to build a model by adding one row at a time.

<div class="api-link"><a href="/api/coinutils/CoinBuild.json">JSON API</a></div>

## Description

In Coin this is inefficient so this class gives some help. An instance of CoinBuild can be built up more efficiently and then added to the Clp/OsiModel in one go.
It may be more efficient to have fewer arrays and re-allocate them but this should give a large gain over addRow.
I have now extended it to columns.

## Public Methods

### `addRow`

add a row

```cpp
void addRow(int numberInRow, const int * columns, const double * elements, double rowLower = -, double rowUpper)
```

**Parameters:**

- `numberInRow` (int)
- `columns` (const int *)
- `elements` (const double *)
- `rowLower` (double)
- `rowUpper` (double)

### `addColumn`

add a column

```cpp
void addColumn(int numberInColumn, const int * rows, const double * elements, double columnLower = 0.0, double columnUpper, double objectiveValue = 0.0)
```

**Parameters:**

- `numberInColumn` (int)
- `rows` (const int *)
- `elements` (const double *)
- `columnLower` (double)
- `columnUpper` (double)
- `objectiveValue` (double)

### `addCol`

add a column

```cpp
void addCol(int numberInColumn, const int * rows, const double * elements, double columnLower = 0.0, double columnUpper, double objectiveValue = 0.0)
```

**Parameters:**

- `numberInColumn` (int)
- `rows` (const int *)
- `elements` (const double *)
- `columnLower` (double)
- `columnUpper` (double)
- `objectiveValue` (double)

### `numberRows`

Return number of rows or maximum found so far.

```cpp
int numberRows()
```

### `numberColumns`

Return number of columns or maximum found so far.

```cpp
int numberColumns()
```

### `numberElements`

Return number of elements.

```cpp
CoinBigIndex numberElements()
```

### `row`

Returns number of elements in a row and information in row.

```cpp
int row(int whichRow, double & rowLower, double & rowUpper, const int *& indices, const double *& elements)
```

**Parameters:**

- `whichRow` (int)
- `rowLower` (double &)
- `rowUpper` (double &)
- `indices` (const int *&)
- `elements` (const double *&)

### `currentRow`

Returns number of elements in current row and information in row Used as rows may be stored in a chain.

```cpp
int currentRow(double & rowLower, double & rowUpper, const int *& indices, const double *& elements)
```

**Parameters:**

- `rowLower` (double &)
- `rowUpper` (double &)
- `indices` (const int *&)
- `elements` (const double *&)

### `setCurrentRow`

Set current row.

```cpp
void setCurrentRow(int whichRow)
```

**Parameters:**

- `whichRow` (int)

### `currentRow`

Returns current row number.

```cpp
int currentRow()
```

### `column`

Returns number of elements in a column and information in column.

```cpp
int column(int whichColumn, double & columnLower, double & columnUpper, double & objectiveValue, const int *& indices, const double *& elements)
```

**Parameters:**

- `whichColumn` (int)
- `columnLower` (double &)
- `columnUpper` (double &)
- `objectiveValue` (double &)
- `indices` (const int *&)
- `elements` (const double *&)

### `currentColumn`

Returns number of elements in current column and information in column Used as columns may be stored in a chain.

```cpp
int currentColumn(double & columnLower, double & columnUpper, double & objectiveValue, const int *& indices, const double *& elements)
```

**Parameters:**

- `columnLower` (double &)
- `columnUpper` (double &)
- `objectiveValue` (double &)
- `indices` (const int *&)
- `elements` (const double *&)

### `setCurrentColumn`

Set current column.

```cpp
void setCurrentColumn(int whichColumn)
```

**Parameters:**

- `whichColumn` (int)

### `currentColumn`

Returns current column number.

```cpp
int currentColumn()
```

### `type`

Returns type.

```cpp
Type type()
```

### `CoinBuild`

Default constructor.

```cpp
 CoinBuild()
```

### `CoinBuild`

Constructor with type Type::Row == for addRow, Type::Column == for addColumn.

```cpp
 CoinBuild(Type type)
```

**Parameters:**

- `type` (Type)

### `~CoinBuild`

Destructor.

```cpp
 ~CoinBuild()
```

### `CoinBuild`

The copy constructor.

```cpp
 CoinBuild(const CoinBuild & )
```

**Parameters:**

- `` (const CoinBuild &)

### `operator=`

=

```cpp
CoinBuild & operator=(const CoinBuild & )
```

**Parameters:**

- `` (const CoinBuild &)

## Source

Header: `layer-0/CoinUtils/src/CoinBuild.hpp`
