+++
title = "CoinOneMessage"
description = "Class for one massaged message."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinMessageHandler.hpp"
api_url = "/api/coinutils/CoinOneMessage.json"
+++

Class for one massaged message.

<div class="api-link"><a href="/api/coinutils/CoinOneMessage.json">JSON API</a></div>

## Description

A message consists of a text string with formatting codes (message_), an integer identifier (externalNumber_) which also determines the severity level (severity_) of the message, and a detail (logging) level (detail_).
CoinOneMessage is just a container to hold this information. The interpretation is set by CoinMessageHandler, which see.

## Public Methods

### `CoinOneMessage`

Default constructor.

```cpp
 CoinOneMessage()
```

### `CoinOneMessage`

Normal constructor.

```cpp
 CoinOneMessage(int externalNumber, char detail, const char * message)
```

**Parameters:**

- `externalNumber` (int)
- `detail` (char)
- `message` (const char *)

### `~CoinOneMessage`

Destructor.

```cpp
 ~CoinOneMessage()
```

### `CoinOneMessage`

The copy constructor.

```cpp
 CoinOneMessage(const CoinOneMessage & )
```

**Parameters:**

- `` (const CoinOneMessage &)

### `operator=`

assignment operator.

```cpp
CoinOneMessage & operator=(const CoinOneMessage & )
```

**Parameters:**

- `` (const CoinOneMessage &)

### `replaceMessage`

Replace message text (e.g., text in a different language)

```cpp
void replaceMessage(const char * message)
```

**Parameters:**

- `message` (const char *)

### `externalNumber`

Get message ID number.

```cpp
int externalNumber()
```

### `setExternalNumber`

Set message ID number.

```cpp
void setExternalNumber(int number)
```

**Parameters:**

- `number` (int)

### `severity`

Severity.

```cpp
char severity()
```

### `setDetail`

Set detail level.

```cpp
void setDetail(int level)
```

**Parameters:**

- `level` (int)

### `detail`

Get detail level.

```cpp
int detail()
```

### `message`

Return the message text.

```cpp
char * message()
```

## Source

Header: `layer-0/CoinUtils/src/CoinMessageHandler.hpp`
