+++
title = "OsiSolverInterface"
description = "Abstract base class defining the Open Solver Interface (OSI)"
template = "page.html"

[extra]
layer = 1
library = "Osi"
header_file = "src/Osi/OsiSolverInterface.hpp"
+++

Abstract base class defining the Open Solver Interface (OSI)

OSI provides a uniform API for accessing different LP/MIP solvers
(Clp, CPLEX, Gurobi, GLPK, etc.) through a common interface. This
allows solver-independent application code.

Key capabilities:
- LP relaxation solving (initialSolve, resolve)
- Model query (getColLower, getRowUpper, getObjCoefficients)
- Solution query (getColSolution, getRowPrice, getReducedCost)
- Problem modification (setColBounds, addRow, addCol)
- Warm starting (getWarmStart, setWarmStart)
- Cut management (applyCuts, applyRowCuts)
- MIP support (setInteger, branchAndBound)

Typical workflow:
1. Create solver-specific instance (e.g., OsiClpSolverInterface)
2. Load problem via loadProblem() or readMps()
3. Call initialSolve() for first LP solution
4. Call resolve() after modifications
5. Query solution via getColSolution(), getObjValue()

## Algorithm

<div class="algorithm-card">

Design Pattern: Abstract Factory + Strategy
  - Factory: concrete implementations (OsiClpSolverInterface, etc.)
    instantiate solver-specific backends
  - Strategy: algorithm choice (simplex vs barrier) delegated to
    underlying solver; OSI provides uniform control interface
  - Bridge: decouples client code from solver implementation details

@invariant Solution pointers (getColSolution, getRowPrice, etc.) are
  invalidated by any problem modification or subsequent solve call.
  Client code must copy data if needed across modifications.

@invariant Warm start objects must be compatible with the solver that
  created them. Cross-solver warm starting requires basis translation.

**Complexity:** All query methods (getColSolution, etc.): $O(1)$ pointer return
  initialSolve/resolve: delegated to solver, typically $O(m·n·iterations)$
  applyCuts: $O(cuts × row_length)$ for constraint matrix update

<div class="refs">

**References:**
- Lougee-Heimer et al. (2003). "The Common Optimization INterface   for Operations Research". IBM J. Research & Development 47(1):57-66.

</div>

</div>

## See Also

- [OsiClpSolverInterface](/libraries/clp/osiclpsolverinterface/) for Clp implementation
- OsiCuts for cut pool management
- [CoinPackedMatrix](/libraries/coinutils/coinpackedmatrix/) for constraint matrix format

## Source

Header file: [`src/Osi/OsiSolverInterface.hpp`](/browser/?library=Osi&file=src/Osi/OsiSolverInterface.hpp)

