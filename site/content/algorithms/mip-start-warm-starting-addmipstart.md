+++
title = "MIP Start (Warm Starting) (addMIPStart)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Provide known feasible solution to MIP solver:
  - From NLP subproblem solutions in outer approximation
  - Improves primal bound immediately
  - Guides B&B exploration toward good solutions

## Mathematical Formulation

<div class="math-block">

Prune node n if: LP(n) >= z* (current best solution)
  Can be set as hard cutoff or as objective constraint.

</div>

## Implementations

### SHOT

- **{{ link(path="/browser/?library=SHOT", text="IMIPSolver.h") }}** - Abstract interface for MIP solver backends

Pure virtual interface for dual problem MIP solvers.

**Problem Construction:**
- initializeProblem(), finalizeProblem(): Setup/teardown
- addVariable(): With type, bounds, and semi-bounds
- addLinearTermToObjective/Constraint(): Build incrementally
- addQuadraticTermToObjective/Constraint(): For MIQP/MIQCQP

**Solution Methods:**
- solveProblem(): Execute MIP solver
- repairInfeasibility(): Attempt feasibility repair
- getObjectiveValue(), getDualObjectiveValue(): Bounds
- getVariableSolution(), getAllVariableSolutions(): Points

**Hyperplane/Cut Management:**
- createHyperplane(): Add supporting hyperplane linearization
- createInteriorHyperplane(): Interior point cuts
- createIntegerCut(): No-good cuts for integer variables

**Bound Management:**
- setCutOff(): Objective cutoff for pruning
- fixVariable(), unfixVariables(): For integer fixing
- presolveAndUpdateBounds(): Bound tightening

**Implementations:**
- MIPSolverCplex, MIPSolverGurobi, MIPSolverCbc
- SingleTree variants for callback-based cut addition

## References

- Kronqvist et al. (2016) - Extended Supporting Hyperplane Algorithm
- Kelley (1960) - Cutting-plane method for convex programming
- Achterberg et al. (2007) - Conflict analysis in MIP solving
- Achterberg (2007) - SCIP: Solving Constraint Integer Programs
