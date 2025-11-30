+++
title = "CoinMpsCardReader"
description = "Very simple code for reading MPS data."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinMpsIO.hpp"
api_url = "/api/coinutils/CoinMpsCardReader.json"
+++

Very simple code for reading MPS data.

<div class="api-link"><a href="/api/coinutils/CoinMpsCardReader.json">JSON API</a></div>

## Public Methods

### `CoinMpsCardReader`

Constructor expects file to be open This one takes gzFile if fp null.

```cpp
 CoinMpsCardReader(CoinFileInput * input, CoinMpsIO * reader)
```

**Parameters:**

- `input` (CoinFileInput *)
- `reader` (CoinMpsIO *)

### `~CoinMpsCardReader`

Destructor.

```cpp
 ~CoinMpsCardReader()
```

### `readToNextSection`

Read to next section.

```cpp
COINSectionType readToNextSection()
```

### `nextField`

Gets next field and returns section type e.g. COIN_COLUMN_SECTION.

```cpp
COINSectionType nextField()
```

### `nextGmsField`

Gets next field for .gms file and returns type.

```cpp
int nextGmsField(int expectedType)
```

**Parameters:**

- `expectedType` (int)

### `whichSection`

Returns current section type.

```cpp
COINSectionType whichSection()
```

### `setWhichSection`

Sets current section type.

```cpp
void setWhichSection(COINSectionType section)
```

**Parameters:**

- `section` (COINSectionType)

### `freeFormat`

Sees if free format.

```cpp
bool freeFormat()
```

### `setFreeFormat`

Sets whether free format. Mainly for blank RHS etc.

```cpp
void setFreeFormat(bool yesNo)
```

**Parameters:**

- `yesNo` (bool)

### `mpsType`

Only for first field on card otherwise BLANK_COLUMN e.g.

```cpp
COINMpsType mpsType()
```

### `cleanCard`

Reads and cleans card - taking out trailing blanks - return 1 if EOF.

```cpp
int cleanCard()
```

### `rowName`

Returns row name of current field.

```cpp
const char * rowName()
```

### `columnName`

Returns column name of current field.

```cpp
const char * columnName()
```

### `value`

Returns value in current field.

```cpp
double value()
```

### `valueString`

Returns value as string in current field.

```cpp
const char * valueString()
```

### `card`

Whole card (for printing)

```cpp
const char * card()
```

### `mutableCard`

Whole card - so we look at it (not const so nextBlankOr will work for gms reader)

```cpp
char * mutableCard()
```

### `setPosition`

set position (again so gms reader will work)

```cpp
void setPosition(char * position)
```

**Parameters:**

- `position` (char *)

### `getPosition`

get position (again so gms reader will work)

```cpp
char * getPosition()
```

### `cardNumber`

Returns card number.

```cpp
CoinBigIndex cardNumber()
```

### `fileInput`

Returns file input.

```cpp
CoinFileInput * fileInput()
```

### `setStringsAllowed`

Sets whether strings allowed.

```cpp
void setStringsAllowed()
```

### `osi_strtod`

type - 0 normal, 1 INTEL IEEE, 2 other IEEE

```cpp
double osi_strtod(char * ptr, char ** output, int type)
```

**Parameters:**

- `ptr` (char *)
- `output` (char **)
- `type` (int)

### `osi_strtod`

For strings.

```cpp
double osi_strtod(char * ptr, char ** output)
```

**Parameters:**

- `ptr` (char *)
- `output` (char **)

### `strcpyAndCompress`

remove blanks

```cpp
void strcpyAndCompress(char * to, const char * from)
```

**Parameters:**

- `to` (char *)
- `from` (const char *)

### `nextBlankOr`

```cpp
char * nextBlankOr(char * image)
```

**Parameters:**

- `image` (char *)

## Source

Header: `layer-0/CoinUtils/src/CoinMpsIO.hpp`
