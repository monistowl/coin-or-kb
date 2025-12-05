+++
title = "CoinPresolveMonitor"
description = "Monitor a row or column for modification."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveMonitor.hpp"
api_url = "/api/coinutils/CoinPresolveMonitor.json"
+++

Monitor a row or column for modification.


## Description

The purpose of this class is to monitor a row or column for modifications during presolve and postsolve. Each object can monitor one row or column. The initial copy of the row or column is loaded by the constructor. Each subsequent call to checkAndTell() compares the current state of the row or column with the stored state and reports any modifications.
Internally the row or column is held as a CoinPackedVector so that it's possible to follow a row or column through presolve (CoinPresolveMatrix) and postsolve (CoinPostsolveMatrix).
Do not underestimate the amount of work required here. Extracting a row from the CoinPostsolve matrix requires a scan of every element in the matrix. That's one scan by the constructor and one scan with every call to modify. But that's precisely why it's virtually impossible to debug presolve without aids.
Parameter overloads for CoinPresolveMatrix and CoinPostsolveMatrix are a little clumsy, but not a problem in use. The alternative is to add methods to the CoinPresolveMatrix and CoinPostsolveMatrix classes that will only be used for debugging. That's not too attractive either.

## Public Methods

### `CoinPresolveMonitor`

Default constructor.

```cpp
 CoinPresolveMonitor()
```

### `CoinPresolveMonitor`

Initialise from a CoinPresolveMatrix.

```cpp
 CoinPresolveMonitor(const CoinPresolveMatrix * mtx, bool isRow, int k)
```

**Parameters:**

- `mtx` (const CoinPresolveMatrix *)
- `isRow` (bool)
- `k` (int)

### `CoinPresolveMonitor`

Initialise from a CoinPostsolveMatrix.

```cpp
 CoinPresolveMonitor(const CoinPostsolveMatrix * mtx, bool isRow, int k)
```

**Parameters:**

- `mtx` (const CoinPostsolveMatrix *)
- `isRow` (bool)
- `k` (int)

### `checkAndTell`

Compare the present row or column against the stored copy and report differences.

```cpp
void checkAndTell(const CoinPresolveMatrix * mtx)
```

**Parameters:**

- `mtx` (const CoinPresolveMatrix *)

### `checkAndTell`

Compare the present row or column against the stored copy and report differences.

```cpp
void checkAndTell(const CoinPostsolveMatrix * mtx)
```

**Parameters:**

- `mtx` (const CoinPostsolveMatrix *)

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveMonitor.hpp`
