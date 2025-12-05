+++
title = "CoinPlainFileInput"
description = "This reads plain text files."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinFileIO.hpp"
api_url = "/api/coinutils/CoinPlainFileInput.json"
+++

This reads plain text files.


## Inheritance

Inherits from: `CoinFileInput`

## Public Methods

### `CoinPlainFileInput`

```cpp
 CoinPlainFileInput(const std::string & fileName)
```

**Parameters:**

- `fileName` (const std::string &)

### `CoinPlainFileInput`

When already opened.

```cpp
 CoinPlainFileInput(FILE * fp)
```

**Parameters:**

- `fp` (FILE *)

### `~CoinPlainFileInput`

```cpp
 ~CoinPlainFileInput()
```

### `read`

Read a block of data from the file, similar to fread.

```cpp
int read(void * buffer, int size)
```

**Parameters:**

- `buffer` (void *) - Address of a buffer to store the data into.
- `size` (int) - Number of bytes to read (buffer should be large enough).

**Returns:** Number of bytes read.

### `gets`

Reads up to (size-1) characters an stores them into the buffer, similar to fgets.

```cpp
char * gets(char * buffer, int size)
```

**Parameters:**

- `buffer` (char *) - The buffer to put the string into.
- `size` (int) - The size of the buffer in characters.

**Returns:** buffer on success, or 0 if no characters have been read.

## Source

Header: `layer-0/CoinUtils/src/CoinFileIO.hpp`
