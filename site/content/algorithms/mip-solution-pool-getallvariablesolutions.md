+++
title = "MIP Solution Pool (getAllVariableSolutions)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

CBC can return multiple feasible integer solutions.
  SHOT uses these as candidate points for NLP evaluation:
  - More solutions = more chances to find primal feasible point
  - Controlled by setSolutionLimit()

## Mathematical Formulation

<div class="math-block">

For binary x with solution x̂ ∈ {0,1}ⁿ:
        ∑(x_j : x̂_j=1) - ∑(x_j : x̂_j=0) <= |{j: x̂_j=1}| - 1
  Prevents cycling when NLP subproblem fails or solution is infeasible.

</div>

## Complexity

Each MIP solve is NP-hard; CBC uses B&C with CGL cuts

## Implementations

### SHOT

- **[MIPSolverCbc.h](/browser/?library=SHOT)** - COIN-OR Cbc implementation of IMIPSolver interface

Provides open-source MIP solving using Cbc branch-and-cut solver.

**MIPSolverCbc Class:**
- Implements IMIPSolver interface
- Uses OsiClpSolverInterface for LP subproblems
- CbcModel for branch-and-cut
- CoinModel for problem construction

**Key Data Structures:**
- osiInterface: OSI LP solver (Clp)
- cbcModel: MIP solver model
- coinModel: Problem builder
- objectiveLinearExpression: CoinPackedVector

**CbcMessageHandler:**
- Custom message handler for SHOT logging
- Routes Cbc output through SHOT's Output system

**Limitations:**
- supportsQuadraticObjective(): No
- supportsQuadraticConstraints(): No
- LP/MIP only (no MIQP/QCQP)

@note Default open-source MIP solver, no license required

## References

- Duran & Grossmann (1986) - Outer Approximation for MINLP
- Kronqvist et al. (2019) - SHOT solver description
- Kelley's cutting-plane method (1960)
- Solution pool heuristics in MIP solvers
