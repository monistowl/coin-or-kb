+++
title = "CoinModelLink"
description = "This is for various structures/classes needed by CoinModel."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinModelUseful.hpp"
api_url = "/api/coinutils/CoinModelLink.json"
+++

This is for various structures/classes needed by CoinModel.


## Description

CoinModelLink CoinModelLinkedList CoinModelHash for going through row or column

## Public Methods

### `CoinModelLink`

Default constructor.

```cpp
 CoinModelLink()
```

### `~CoinModelLink`

Destructor.

```cpp
 ~CoinModelLink()
```

### `CoinModelLink`

The copy constructor.

```cpp
 CoinModelLink(const CoinModelLink & )
```

**Parameters:**

- `` (const CoinModelLink &)

### `operator=`

=

```cpp
CoinModelLink & operator=(const CoinModelLink & )
```

**Parameters:**

- `` (const CoinModelLink &)

### `row`

Get row.

```cpp
int row()
```

### `column`

Get column.

```cpp
int column()
```

### `value`

Get value.

```cpp
double value()
```

### `element`

Get value.

```cpp
double element()
```

### `position`

Get position.

```cpp
CoinBigIndex position()
```

### `onRow`

Get onRow.

```cpp
bool onRow()
```

### `setRow`

Set row.

```cpp
void setRow(int row)
```

**Parameters:**

- `row` (int)

### `setColumn`

Set column.

```cpp
void setColumn(int column)
```

**Parameters:**

- `column` (int)

### `setValue`

Set value.

```cpp
void setValue(double value)
```

**Parameters:**

- `value` (double)

### `setElement`

Set value.

```cpp
void setElement(double value)
```

**Parameters:**

- `value` (double)

### `setPosition`

Set position.

```cpp
void setPosition(CoinBigIndex position)
```

**Parameters:**

- `position` (CoinBigIndex)

### `setOnRow`

Set onRow.

```cpp
void setOnRow(bool onRow)
```

**Parameters:**

- `onRow` (bool)

## Source

Header: `layer-0/CoinUtils/src/CoinModelUseful.hpp`
