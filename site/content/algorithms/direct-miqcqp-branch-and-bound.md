+++
title = "Direct MIQCQP branch-and-bound"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

## Implementations

### SHOT

- **{{ link(path="/browser/?library=SHOT", text="SolutionStrategyMIQCQP.h") }}** - Direct MIQCQP solver for convex quadratic problems

Bypasses ESH for problems solvable by CPLEX/Gurobi MIQCQP.

**SolutionStrategyMIQCQP Class:**
- initializeStrategy(): Configure for direct MIQCQP solve
- solveProblem(): Single solver call, no outer approximation

**Use Case:**
- Convex MIQCQP (quadratic constraints, convex)
- CPLEX and Gurobi support convex QCQP natively
- Faster than iterative linearization for small problems

**Problem Classification:**
- All constraints must be convex quadratic
- Solver must support QCQP (supportsQuadraticConstraints)
