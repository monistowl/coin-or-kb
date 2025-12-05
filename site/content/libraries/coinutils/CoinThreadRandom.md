+++
title = "CoinThreadRandom"
description = "Thread-local random number generator."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinHelperFunctions.hpp"
api_url = "/api/coinutils/CoinThreadRandom.json"
+++

Thread-local random number generator.


## Description

Each instance maintains its own seed state, making it safe for multi-threaded use when each thread has its own instance. Uses a linear congruential generator for platform-independent reproducible sequences.

## Public Methods

### `CoinThreadRandom`

Default constructor.

```cpp
 CoinThreadRandom()
```

### `CoinThreadRandom`

Constructor wih seed.

```cpp
 CoinThreadRandom(unsigned int seed)
```

**Parameters:**

- `seed` (unsigned int)

### `~CoinThreadRandom`

Destructor.

```cpp
 ~CoinThreadRandom()
```

### `CoinThreadRandom`

```cpp
 CoinThreadRandom(const CoinThreadRandom & rhs)
```

**Parameters:**

- `rhs` (const CoinThreadRandom &)

### `operator=`

```cpp
CoinThreadRandom & operator=(const CoinThreadRandom & rhs)
```

**Parameters:**

- `rhs` (const CoinThreadRandom &)

### `setSeed`

Set seed.

```cpp
void setSeed(unsigned int seed)
```

**Parameters:**

- `seed` (unsigned int)

### `getSeed`

Get seed.

```cpp
unsigned int getSeed()
```

### `randomDouble`

return a random number

```cpp
double randomDouble()
```

### `randomize`

make more random (i.e. for startup)

```cpp
void randomize(int n = 0)
```

**Parameters:**

- `n` (int)

## Source

Header: `layer-0/CoinUtils/src/CoinHelperFunctions.hpp`
