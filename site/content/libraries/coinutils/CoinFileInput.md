+++
title = "CoinFileInput"
description = "Abstract base class for file input classes."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinFileIO.hpp"
api_url = "/api/coinutils/CoinFileInput.json"
+++

Abstract base class for file input classes.

<div class="api-link"><a href="/api/coinutils/CoinFileInput.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinFileIOBase`

Derived classes: `CoinPlainFileInput`

## Public Methods

### `haveGzipSupport`

indicates whether CoinFileInput supports gzip'ed files

```cpp
bool haveGzipSupport()
```

### `haveBzip2Support`

indicates whether CoinFileInput supports bzip2'ed files

```cpp
bool haveBzip2Support()
```

### `create`

Factory method, that creates a CoinFileInput (more precisely a subclass of it) for the file specified.

```cpp
CoinFileInput * create(const std::string & fileName)
```

**Parameters:**

- `fileName` (const std::string &) - The file that should be read.

### `CoinFileInput`

Constructor (don't use this, use the create method instead).

```cpp
 CoinFileInput(const std::string & fileName)
```

**Parameters:**

- `fileName` (const std::string &) - The name of the file used by this object.

### `~CoinFileInput`

Destructor.

```cpp
 ~CoinFileInput()
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

### `fileAbsPath`

Test if the given string looks like an absolute file path.

```cpp
COINUTILSLIB_EXPORT bool fileAbsPath(const std::string & path)
```

**Parameters:**

- `path` (const std::string &)

### `fileCoinReadable`

Test if the file is readable, using likely versions of the file name, and return the name that worked.

```cpp
COINUTILSLIB_EXPORT bool fileCoinReadable(std::string & name, const std::string & dfltPrefix = std::string(""))
```

**Parameters:**

- `name` (std::string &)
- `dfltPrefix` (const std::string &)

## Source

Header: `layer-0/CoinUtils/src/CoinFileIO.hpp`
