+++
title = "CoinWarmStartBasis"
description = "The default COIN simplex (basis-oriented) warm start class."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinWarmStartBasis.hpp"
api_url = "/api/coinutils/CoinWarmStartBasis.json"
+++

The default COIN simplex (basis-oriented) warm start class.

<div class="api-link"><a href="/api/coinutils/CoinWarmStartBasis.json">JSON API</a></div>

## Inheritance

Inherits from: `CoinWarmStart`

## Description

CoinWarmStartBasis provides for a warm start object which contains the status of each variable (structural and artificial).
TodoModify this class so that the number of status entries per byte and bytes per status vector allocation unit are not hardcoded. At the least, collect this into a couple of macros.
TodoConsider separate fields for allocated capacity and actual basis size. We could avoid some reallocation, at the price of retaining more space than we need. Perhaps more important, we could do much better sanity checks.

## Public Methods

### `getNumStructural`

Return the number of structural variables.

```cpp
int getNumStructural()
```

### `getNumArtificial`

Return the number of artificial variables.

```cpp
int getNumArtificial()
```

### `numberBasicStructurals`

Return the number of basic structurals.

```cpp
int numberBasicStructurals()
```

### `getStructStatus`

Return the status of the specified structural variable.

```cpp
Status getStructStatus(int i)
```

**Parameters:**

- `i` (int)

### `setStructStatus`

Set the status of the specified structural variable.

```cpp
void setStructStatus(int i, Status st)
```

**Parameters:**

- `i` (int)
- `st` (Status)

### `getStructuralStatus`

Return the status array for the structural variables.

```cpp
char * getStructuralStatus()
```

### `getStructuralStatus`

`const` overload for getStructuralStatus()

```cpp
const char * getStructuralStatus()
```

### `getArtificialStatus`

As for getStructuralStatus , but returns the status array for the artificial variables.

```cpp
char * getArtificialStatus()
```

### `getArtifStatus`

Return the status of the specified artificial variable.

```cpp
Status getArtifStatus(int i)
```

**Parameters:**

- `i` (int)

### `setArtifStatus`

Set the status of the specified artificial variable.

```cpp
void setArtifStatus(int i, Status st)
```

**Parameters:**

- `i` (int)
- `st` (Status)

### `getArtificialStatus`

`const` overload for getArtificialStatus()

```cpp
const char * getArtificialStatus()
```

### `generateDiff`

Generate a diff that can convert the warm start basis passed as a parameter to the warm start basis specified by `this`.

```cpp
CoinWarmStartDiff * generateDiff(const CoinWarmStart *const oldCWS)
```

**Parameters:**

- `oldCWS` (const CoinWarmStart *const)

### `applyDiff`

Apply `diff` to this basis.

```cpp
void applyDiff(const CoinWarmStartDiff *const cwsdDiff)
```

**Parameters:**

- `cwsdDiff` (const CoinWarmStartDiff *const)

### `setSize`

Set basis capacity; existing basis is discarded.

```cpp
void setSize(int ns, int na)
```

**Parameters:**

- `ns` (int)
- `na` (int)

### `resize`

Set basis capacity; existing basis is maintained.

```cpp
void resize(int newNumberRows, int newNumberColumns)
```

**Parameters:**

- `newNumberRows` (int)
- `newNumberColumns` (int)

### `compressRows`

Delete a set of rows from the basis.

```cpp
void compressRows(int tgtCnt, const int * tgts)
```

**Parameters:**

- `tgtCnt` (int)
- `tgts` (const int *)

### `deleteRows`

Delete a set of rows from the basis.

```cpp
void deleteRows(int rawTgtCnt, const int * rawTgts)
```

**Parameters:**

- `rawTgtCnt` (int)
- `rawTgts` (const int *)

### `deleteColumns`

Delete a set of columns from the basis.

```cpp
void deleteColumns(int number, const int * which)
```

**Parameters:**

- `number` (int)
- `which` (const int *)

### `mergeBasis`

Merge entries from a source basis into this basis.

```cpp
void mergeBasis(const CoinWarmStartBasis * src, const XferVec * xferRows, const XferVec * xferCols)
```

**Parameters:**

- `src` (const CoinWarmStartBasis *)
- `xferRows` (const XferVec *)
- `xferCols` (const XferVec *)

### `CoinWarmStartBasis`

Default constructor.

```cpp
 CoinWarmStartBasis()
```

### `CoinWarmStartBasis`

Constructs a warm start object with the specified status vectors.

```cpp
 CoinWarmStartBasis(int ns, int na, const char * sStat, const char * aStat)
```

**Parameters:**

- `ns` (int)
- `na` (int)
- `sStat` (const char *)
- `aStat` (const char *)

### `CoinWarmStartBasis`

Copy constructor.

```cpp
 CoinWarmStartBasis(const CoinWarmStartBasis & ws)
```

**Parameters:**

- `ws` (const CoinWarmStartBasis &)

### `clone`

Virtual constructor

```cpp
CoinWarmStart * clone()
```

### `~CoinWarmStartBasis`

Destructor.

```cpp
 ~CoinWarmStartBasis()
```

### `operator=`

Assignment.

```cpp
CoinWarmStartBasis & operator=(const CoinWarmStartBasis & rhs)
```

**Parameters:**

- `rhs` (const CoinWarmStartBasis &)

### `assignBasisStatus`

Assign the status vectors to be the warm start information.

```cpp
void assignBasisStatus(int ns, int na, char *& sStat, char *& aStat)
```

**Parameters:**

- `ns` (int)
- `na` (int)
- `sStat` (char *&)
- `aStat` (char *&)

### `print`

Prints in readable format (for debug)

```cpp
void print()
```

### `fullBasis`

Returns true if full basis (for debug)

```cpp
bool fullBasis()
```

### `fixFullBasis`

Returns true if full basis and fixes up (for debug)

```cpp
bool fixFullBasis()
```

### `getStatus`

Get the status of the specified variable in the given status array.

```cpp
CoinWarmStartBasis::Status getStatus(const char * array, int i)
```

**Parameters:**

- `array` (const char *)
- `i` (int)

### `setStatus`

Set the status of the specified variable in the given status array.

```cpp
void setStatus(char * array, int i, CoinWarmStartBasis::Status st)
```

**Parameters:**

- `array` (char *)
- `i` (int)
- `st` (CoinWarmStartBasis::Status)

### `statusName`

Generate a print string for a status code.

```cpp
const char * statusName(CoinWarmStartBasis::Status status)
```

**Parameters:**

- `status` (CoinWarmStartBasis::Status)

## Source

Header: `layer-0/CoinUtils/src/CoinWarmStartBasis.hpp`
