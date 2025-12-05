+++
title = "CoinPresolveAction"
description = "Abstract base class of all presolve routines."
template = "page.html"
[extra]
layer = 0
library = "CoinUtils"
header_file = "layer-0/CoinUtils/src/CoinPresolveMatrix.hpp"
api_url = "/api/coinutils/CoinPresolveAction.json"
+++

Abstract base class of all presolve routines.


Derived classes: `do_tighten_action`, `doubleton_action`, `drop_empty_cols_action`, `drop_empty_rows_action`, `drop_zero_coefficients_action`, `dupcol_action`, `duprow3_action`, `duprow_action`, `forcing_constraint_action`, `gubrow_action`, `implied_free_action`, `isolated_constraint_action`, `make_fixed_action`, `remove_dual_action`, `remove_fixed_action`, `slack_doubleton_action`, `slack_singleton_action`, `subst_constraint_action`, `tripleton_action`, `twoxtwo_action`, `useless_constraint_action`

## Description

The details will make more sense after a quick overview of the grand plan: A presolve object is handed a problem object, which it is expected to modify in some useful way. Assuming that it succeeds, the presolve object should create a postsolve object, i.e., an object that contains instructions for backing out the presolve transform to recover the original problem. These postsolve objects are accumulated in a linked list, with each successive presolve action adding its postsolve action to the head of the list. The end result of all this is a presolved problem object, and a list of postsolve objects. The presolved problem object is then handed to a solver for optimization, and the problem object augmented with the results. The list of postsolve objects is then traversed. Each of them (un)modifies the problem object, with the end result being the original problem, augmented with solution information.
The problem object representation is CoinPrePostsolveMatrix and subclasses. Check there for details. The `` class and subclasses represent the presolve and postsolve objects.
In spite of the name, the only information held in a `` object is the information needed to postsolve (i.e., the information needed to back out the presolve transformation). This information is not expected to change, so the fields are all `const`.
A subclass of ``, implementing a specific pre/postsolve action, is expected to declare a static function that attempts to perform a presolve transformation. This function will be handed a CoinPresolveMatrix to transform, and a pointer to the head of the list of postsolve objects. If the transform is successful, the function will create a new `` object, link it at the head of the list of postsolve objects, and return a pointer to the postsolve object it has just created. Otherwise, it should return 0. It is expected that these static functions will be the only things that can create new `` objects; this is expressed by making each subclass' constructor(s) private.
Every subclass must also define a `postsolve` method. This function will be handed a CoinPostsolveMatrix to transform.
It is the client's responsibility to implement presolve and postsolve driver routines. See OsiPresolve for examples.

## Public Methods

### `throwCoinError`

Stub routine to throw exceptions.

```cpp
void throwCoinError(const char * error, const char * ps_routine)
```

**Parameters:**

- `error` (const char *)
- `ps_routine` (const char *)

### `CoinPresolveAction`

Construct a postsolve object and add it to the transformation list.

```cpp
 CoinPresolveAction(const CoinPresolveAction * next)
```

**Parameters:**

- `next` (const CoinPresolveAction *)

### `setNext`

modify next (when building rather than passing)

```cpp
void setNext(const CoinPresolveAction * nextAction)
```

**Parameters:**

- `nextAction` (const CoinPresolveAction *)

### `name`

A name for debug printing.

```cpp
const char * name()
```

### `postsolve`

Apply the postsolve transformation for this particular presolve action.

```cpp
void postsolve(CoinPostsolveMatrix * prob)
```

**Parameters:**

- `prob` (CoinPostsolveMatrix *)

### `~CoinPresolveAction`

Virtual destructor.

```cpp
 ~CoinPresolveAction()
```

## Source

Header: `layer-0/CoinUtils/src/CoinPresolveMatrix.hpp`
