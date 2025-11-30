+++
title = "LP Method Selection (LPMethod enum)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "File I/O"
implementation_count = 1
+++

- LPM_Dual: Dual simplex (default, best for warm starts)
  - LPM_Primal: Primal simplex
  - LPM_Barrier: Interior-point with crossover to basis
  - LPM_BarrierNoCross: IPM without crossover (for large LPs)

## Complexity

MIP: Exponential worst-case, highly structure-dependent
  Each LP solve: O(m·n·iterations) for simplex

## Implementations

### Cbc

- **[Cbc_C_Interface.h](/browser/?library=Cbc)** - Creates an empty problem

## References

- Land, A.H. and Doig, A.G. (1960). "An automatic method of solving
  discrete programming problems". Econometrica 28(3):497-520.
