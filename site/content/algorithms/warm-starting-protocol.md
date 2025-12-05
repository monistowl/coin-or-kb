+++
title = "Warm-Starting Protocol"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

1. Solve initial LP: Clp_initialSolve()
  2. Modify problem (bounds, RHS, etc.)
  3. Re-solve from basis: Clp_dual() or Clp_primal()
  Warm start typically requires O(k) iterations where k << m+n.

## Complexity

Same as underlying ClpSimplex methods:
  Per-iteration: O(m²) average, O(m³) worst-case for factorization
  Total: O(m·n·iterations) for complete solve

## Implementations

### Clp

- **[Clp_C_Interface.h](/browser/?library=Clp)** - C language interface to Clp solver

Pure C API for embedding Clp in C programs or creating language bindings.
Design follows OSL V3 conventions for familiarity.

Opaque handles:
- Clp_Simplex: Pointer to internal ClpSimplex object
- Clp_Solve: Pointer to ClpSolve options object

Naming convention: C++ method foo() becomes Clp_foo(model, ...)
where model is the first parameter.

Key function groups:
- Construction: Clp_newModel(), Clp_deleteModel()
- Problem setup: Clp_loadProblem(), Clp_readMps()
- Solving: Clp_dual(), Clp_primal(), Clp_initialSolve()
- Solution access: Clp_getColSolution(), Clp_getRowActivity()
- Parameters: Clp_setLogLevel(), Clp_setMaximumIterations()

Callback support: clp_callback typedef for user message handling.

Thread safety: Each Clp_Simplex is independent; do not share across threads.
