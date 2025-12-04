+++
title = "SolutionStrategyMIQCQP"
description = "Direct MIQCQP solver for convex quadratic problems"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "src/SolutionStrategy/SolutionStrategyMIQCQP.h"
+++

Direct MIQCQP solver for convex quadratic problems

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

## Algorithm

<div class="algorithm-card">

Direct MIQCQP branch-and-bound

</div>

## See Also

- SolutionStrategyMultiTree.h for general MINLP

## Source

Header file: `src/SolutionStrategy/SolutionStrategyMIQCQP.h`

