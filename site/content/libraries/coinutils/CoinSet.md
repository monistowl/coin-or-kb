+++
title = "CoinSet"
description = "Very simple class for containing data on set."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinMpsIO.hpp"
api_url = "/api/coinutils/CoinSet.json"
+++

Very simple class for containing data on set.

<div class="api-link"><a href="/api/coinutils/CoinSet.json">JSON API</a></div>

Derived classes: `CoinSosSet`

## Public Methods

### `CoinSet`

Default constructor.

```cpp
 CoinSet()
```

### `CoinSet`

Constructor.

```cpp
 CoinSet(int numberEntries, const int * which)
```

**Parameters:**

- `numberEntries` (int)
- `which` (const int *)

### `CoinSet`

Copy constructor.

```cpp
 CoinSet(const CoinSet & )
```

**Parameters:**

- `` (const CoinSet &)

### `operator=`

Assignment operator.

```cpp
CoinSet & operator=(const CoinSet & rhs)
```

**Parameters:**

- `rhs` (const CoinSet &)

### `~CoinSet`

Destructor.

```cpp
 ~CoinSet()
```

### `numberEntries`

Returns number of entries.

```cpp
int numberEntries()
```

### `setNumberEntries`

Sets number of entries.

```cpp
void setNumberEntries(int number)
```

**Parameters:**

- `number` (int)

### `setType`

Returns type of set - 1 =SOS1, 2 =SOS2.

```cpp
int setType()
```

### `setSetType`

Sets type of set - 1 =SOS1, 2 =SOS2.

```cpp
void setSetType(int type)
```

**Parameters:**

- `type` (int)

### `which`

Returns list of variables.

```cpp
const int * which()
```

### `weights`

Returns weights.

```cpp
const double * weights()
```

### `modifiableWhich`

Returns modifiable list of variables.

```cpp
int * modifiableWhich()
```

### `modifiableWeights`

Returns modifiable weights.

```cpp
double * modifiableWeights()
```

## Source

Header: `layer-0/CoinUtils/src/CoinMpsIO.hpp`
