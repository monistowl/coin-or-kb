+++
title = "CoinMessages"
description = "Class to hold and manipulate an array of massaged messages."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinMessageHandler.hpp"
api_url = "/api/coinutils/CoinMessages.json"
+++

Class to hold and manipulate an array of massaged messages.

<div class="api-link"><a href="/api/coinutils/CoinMessages.json">JSON API</a></div>

Derived classes: `CoinMessage`

## Description

Note that the message index used to reference a message in the array of messages is completely distinct from the external ID number stored with the message.

## Public Methods

### `CoinMessages`

Constructor with number of messages.

```cpp
 CoinMessages(int numberMessages = 0)
```

**Parameters:**

- `numberMessages` (int)

### `~CoinMessages`

Destructor.

```cpp
 ~CoinMessages()
```

### `CoinMessages`

The copy constructor.

```cpp
 CoinMessages(const CoinMessages & )
```

**Parameters:**

- `` (const CoinMessages &)

### `operator=`

assignment operator.

```cpp
CoinMessages & operator=(const CoinMessages & )
```

**Parameters:**

- `` (const CoinMessages &)

### `addMessage`

Installs a new message in the specified index position.

```cpp
void addMessage(int messageNumber, const CoinOneMessage & message)
```

**Parameters:**

- `messageNumber` (int)
- `message` (const CoinOneMessage &)

### `replaceMessage`

Replaces the text of the specified message.

```cpp
void replaceMessage(int messageNumber, const char * message)
```

**Parameters:**

- `messageNumber` (int)
- `message` (const char *)

### `language`

Language.

```cpp
Language language()
```

### `setLanguage`

Set language.

```cpp
void setLanguage(Language newlanguage)
```

**Parameters:**

- `newlanguage` (Language)

### `setDetailMessage`

Change detail level for one message.

```cpp
void setDetailMessage(int newLevel, int messageNumber)
```

**Parameters:**

- `newLevel` (int)
- `messageNumber` (int)

### `setDetailMessages`

Change detail level for several messages.

```cpp
void setDetailMessages(int newLevel, int numberMessages, int * messageNumbers)
```

**Parameters:**

- `newLevel` (int)
- `numberMessages` (int)
- `messageNumbers` (int *)

### `setDetailMessages`

Change detail level for all messages with low <= ID number < high.

```cpp
void setDetailMessages(int newLevel, int low, int high)
```

**Parameters:**

- `newLevel` (int)
- `low` (int)
- `high` (int)

### `getClass`

Returns class.

```cpp
int getClass()
```

### `toCompact`

Moves to compact format.

```cpp
void toCompact()
```

### `fromCompact`

Moves from compact format.

```cpp
void fromCompact()
```

## Source

Header: `layer-0/CoinUtils/src/CoinMessageHandler.hpp`
