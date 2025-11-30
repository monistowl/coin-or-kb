+++
title = "Branch-and-cut with lazy ESH constraints"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

## Implementations

### SHOT

- **[SolutionStrategySingleTree.h](/browser/?library=SHOT)** - Lazy constraint callback strategy (single-tree)

Callback-based outer approximation within single B&B tree.

**Algorithm Pattern:**
1. Solve MIP with lazy constraint callback
2. Callback checks integer solutions for feasibility
3. Generate hyperplanes for violated constraints
4. Add as lazy constraints, solver continues

**Task Flow (initializeStrategy):**
- CreateDualProblem → ConfigureCallback → SolveProblem
- (cuts added via callback during solve)

**Advantages:**
- Single B&B tree exploration
- Potentially fewer node evaluations
- Better integration with MIP solver

**Disadvantages:**
- Requires solver callback support
- Limited to CPLEX/Gurobi
- More complex debugging
