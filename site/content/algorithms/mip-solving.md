+++
title = "MIP Solving"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

- Presolve: probing, clique detection, coefficient strengthening
  - Cuts: Gomory, MIR, clique, zero-half, knapsack cover
  - Branching: reliability branching with pseudocost initialization
  - Heuristics: RINS, local search, rounding, feasibility pump

## Complexity

LP: O(m·n·iterations) simplex, O(n³) per IPM iteration
  MIP: exponential worst-case, highly structure-dependent

## Implementations

### HiGHS

- **[Highs.h](/browser/?library=HiGHS)** - Main HiGHS solver class - high-performance LP/MIP/QP optimization

HiGHS (High-performance Interior point and Gradient descent Solvers) is
an open-source solver for LP, MIP, and convex QP problems.

**Highs Class (Main API):**
Primary interface for model input, solving, and solution retrieval:
- passModel(): Load LP/QP/MIP from HighsModel, HighsLp, or raw arrays
- run(): Solve the incumbent model
- getSolution(), getBasis(): Retrieve solution and basis
- getModelStatus(): Check optimization result

**Solving Capabilities:**
- LP: Dual/primal simplex (HEkk) or interior point (IPX)
- MIP: Branch-and-cut with presolve, cuts, and heuristics
- QP: Convex quadratic programming via interior point or active set

**Model Modification:**
- addCol/addRow, deleteCols/deleteRows: Incremental model building
- changeColBounds, changeRowBounds, changeColCost: Hot-start friendly
- changeCoeff: Modify individual matrix coefficients

**Basis Operations:**
- getBasisInverseRow/Col: Access B^{-1} for advanced use
- getBasisSolve/getBasisTransposeSolve: Solve B*x=b or B'*x=b
- getReducedRow/Col: Compute B^{-1}*A columns

**Options and Info:**
- setOptionValue/getOptionValue: Configure solver behavior
- getInfo: Retrieve solve statistics (iterations, time, etc.)

## References

- Huangfu, Q. and Hall, J.A.J. (2018). "Parallelizing the dual revised
  simplex method". Math. Prog. Computation 10:119-142.
