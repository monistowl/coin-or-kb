+++
title = "CoinFileOutput"
description = "Abstract base class for file output classes."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinFileIO.hpp"
api_url = "/api/coinutils/CoinFileOutput.json"
+++

Abstract base class for file output classes.


## Inheritance

Inherits from: `CoinFileIOBase`

## Public Methods

### `compressionSupported`

Returns whether the specified compression method is supported (i.e.

```cpp
bool compressionSupported(Compression compression)
```

**Parameters:**

- `compression` (Compression)

### `create`

Factory method, that creates a CoinFileOutput (more precisely a subclass of it) for the file specified.

```cpp
CoinFileOutput * create(const std::string & fileName, Compression compression)
```

**Parameters:**

- `fileName` (const std::string &) - The file that should be read.
- `compression` (Compression) - Compression method used.

### `CoinFileOutput`

Constructor (don't use this, use the create method instead).

```cpp
 CoinFileOutput(const std::string & fileName)
```

**Parameters:**

- `fileName` (const std::string &) - The name of the file used by this object.

### `~CoinFileOutput`

Destructor.

```cpp
 ~CoinFileOutput()
```

### `write`

Write a block of data to the file, similar to fwrite.

```cpp
int write(const void * buffer, int size)
```

**Parameters:**

- `buffer` (const void *) - Address of a buffer containing the data to be written.
- `size` (int) - Number of bytes to write.

**Returns:** Number of bytes written.

### `puts`

Write a string to the file (like fputs).

```cpp
bool puts(const char * s)
```

**Parameters:**

- `s` (const char *) - The zero terminated string to be written.

**Returns:** true on success, false on error.

### `puts`

Convenience method: just a 'puts(s.c_str())'.

```cpp
bool puts(const std::string & s)
```

**Parameters:**

- `s` (const std::string &)

## Source

Header: `layer-0/CoinUtils/src/CoinFileIO.hpp`
