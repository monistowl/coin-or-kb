+++
title = "CoinError"
description = "Exception class carrying context about where and why an error occurred."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinError.hpp"
api_url = "/api/coinutils/CoinError.json"
+++

Exception class carrying context about where and why an error occurred.

<div class="api-link"><a href="/api/coinutils/CoinError.json">JSON API</a></div>

## Description

CoinError is thrown by COIN-OR code when an error condition is detected. It captures rich context for debugging:message: Description of what went wrongmethod: Name of the function that detected the errorclass: Name of the class (or a hint string for assertions)file: Source file name (for assertions)lineNumber: Source line (for assertions, -1 otherwise)
Typical usage: throwCoinError("Matrixissingular","solve","CoinFactorization");

## Public Methods

### `message`

Get the error message text.

```cpp
const std::string & message()
```

**Returns:** Description of what went wrong

### `methodName`

Get the name of the method that threw this error.

```cpp
const std::string & methodName()
```

**Returns:** Method/function name string

### `className`

Get the class name or hint string.

```cpp
const std::string & className()
```

**Returns:** Class name for regular errors, hint for assertions

### `fileName`

Get the source file name (assertions only)

```cpp
const std::string & fileName()
```

**Returns:** File name where assertion failed, empty for regular errors

### `lineNumber`

Get the source line number (assertions only)

```cpp
int lineNumber()
```

**Returns:** Line number where assertion failed, -1 for regular errors

### `print`

Print error details to stdout.

```cpp
void print(bool doPrint = true)
```

**Parameters:**

- `doPrint` (bool) - If false, do nothing (default true)

### `CoinError`

Construct a CoinError with full context.

```cpp
 CoinError(std::string message__, std::string methodName__, std::string className__, std::string fileName_ = std::string(), int line = -1)
```

**Parameters:**

- `message__` (std::string) - Description of the error condition
- `methodName__` (std::string) - Name of the method detecting the error
- `className__` (std::string) - Name of the class (or hint string for assertions)
- `fileName_` (std::string) - Source file name (optional, for assertions)
- `line` (int) - Source line number (optional, -1 if not an assertion)

### `CoinError`

Copy constructor.

```cpp
 CoinError(const CoinError & source)
```

**Parameters:**

- `source` (const CoinError &) - CoinError to copy from

### `operator=`

Assignment operator.

```cpp
CoinError & operator=(const CoinError & rhs)
```

**Parameters:**

- `rhs` (const CoinError &) - CoinError to copy from

**Returns:** Reference to this object

### `~CoinError`

Destructor.

```cpp
 ~CoinError()
```

## Source

Header: `layer-0/CoinUtils/src/CoinError.hpp`
