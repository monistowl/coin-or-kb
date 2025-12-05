+++
title = "CoinBaseModel"
description = "CoinBaseModel class documentation"
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinModel.hpp"
api_url = "/api/coinutils/CoinBaseModel.json"
+++


Derived classes: `CoinModel`, `CoinStructuredModel`

## Public Methods

### `CoinBaseModel`

Default Constructor.

```cpp
 CoinBaseModel()
```

### `CoinBaseModel`

Copy constructor.

```cpp
 CoinBaseModel(const CoinBaseModel & rhs)
```

**Parameters:**

- `rhs` (const CoinBaseModel &)

### `operator=`

Assignment operator.

```cpp
CoinBaseModel & operator=(const CoinBaseModel & rhs)
```

**Parameters:**

- `rhs` (const CoinBaseModel &)

### `clone`

Clone.

```cpp
CoinBaseModel * clone()
```

### `~CoinBaseModel`

Destructor.

```cpp
 ~CoinBaseModel()
```

### `numberRows`

Return number of rows.

```cpp
int numberRows()
```

### `numberColumns`

Return number of columns.

```cpp
int numberColumns()
```

### `numberElements`

Return number of elements.

```cpp
CoinBigIndex numberElements()
```

### `objectiveOffset`

Returns the (constant) objective offset This is the RHS entry for the objective row.

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

### `logLevel`

Get print level 0 - off, 1 - errors, 2 - more.

```cpp
int logLevel()
```

### `setLogLevel`

Set print level 0 - off, 1 - errors, 2 - more.

```cpp
void setLogLevel(int value)
```

**Parameters:**

- `value` (int)

### `getProblemName`

Return the problem name.

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

### `setProblemName`

Set problem name.

```cpp
void setProblemName(const std::string & name)
```

**Parameters:**

- `name` (const std::string &)

### `getRowBlock`

Return the row block name.

```cpp
const std::string & getRowBlock()
```

### `setRowBlock`

Set row block name.

```cpp
void setRowBlock(const std::string & name)
```

**Parameters:**

- `name` (const std::string &)

### `getColumnBlock`

Return the column block name.

```cpp
const std::string & getColumnBlock()
```

### `setColumnBlock`

Set column block name.

```cpp
void setColumnBlock(const std::string & name)
```

**Parameters:**

- `name` (const std::string &)

### `setMessageHandler`

Pass in message handler.

```cpp
void setMessageHandler(CoinMessageHandler * handler)
```

**Parameters:**

- `handler` (CoinMessageHandler *)

## Source

Header: `layer-0/CoinUtils/src/CoinModel.hpp`
