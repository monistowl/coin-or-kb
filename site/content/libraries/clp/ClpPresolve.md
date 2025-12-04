+++
title = "ClpPresolve"
description = "Clp interface to CoinPresolve for LP preprocessing"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/ClpPresolve.hpp"
+++

## Algorithm

<div class="algorithm-card">

LP Presolve (Preprocessing):
Applies reversible transformations to simplify LP before solving:
- Singleton rows/columns: substitute and eliminate
- Doubleton: eliminate free column in 2-element row
- Forcing/dominated constraints: fix variables
- Duplicate rows/columns: merge or eliminate
- Implied free: detect columns with implied bounds from constraints
- Bound tightening: propagate bounds through constraints

Transformations saved as list of CoinPresolveAction objects.
After solving presolved model, postsolve applies actions in reverse
to recover solution to original model.

Multiple passes until no more reductions. Each transformation must
preserve optimal solution recovery.

<div class="math">

Presolve operations:
$$Singleton row a_{j} x_{j} = b: fix x_{j} = b/a_{j}, eliminate row$$
$$Doubleton col in a_{i} x_{i} + a_{j} x_{j} = b with x_{j} free: x_{j} = (b - a_{i} x_{i})/a_{j}$$
Forcing: if all coeffs same sign and bound known, may fix variables
Implied free: if x_j bounded by constraints, can treat as free
$$Bound tightening: l_{x} = max{l_{j} : a_ij > 0} helps detect fixed vars$$

</div>

**Complexity:** Each pass $O(nnz)$ for most transformations. Total typically
$O(passes × nnz)$ with 3-10 passes common. Can reduce problem size 50-90%.

<div class="refs">

**References:**
- Andersen & Andersen, "Presolving in LP", Mathematical Programming 71 (1995)
- Gondzio, "Presolve analysis of LP problems prior to IPM",      Optimization Methods and Software 10 (1997)  Wraps the CoinPresolve framework for use with Clp models. Presolve simplifies an LP before solving by applying reversible transformations: removing fixed variables, empty rows/columns, redundant constraints, etc.  The typical workflow is: 1. presolvedModel() - create simplified model 2. Solve the presolved model 3. postsolve() - recover solution to original model

</div>

</div>

## See Also

- [CoinPresolveMatrix](/coin-or-kb/libraries/coinutils/coinpresolvematrix/) in CoinUtils for the transformation framework
- [ClpSimplex](/coin-or-kb/libraries/clp/clpsimplex/)::initialSolve() which can invoke presolve automatically

## Source

Header file: [`src/ClpPresolve.hpp`](/coin-or-kb/browser/?library=Clp&file=src/ClpPresolve.hpp)

