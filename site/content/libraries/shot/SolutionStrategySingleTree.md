+++
title = "SolutionStrategySingleTree"
description = "Lazy constraint callback strategy (single-tree)"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "src/SolutionStrategy/SolutionStrategySingleTree.h"
+++

Lazy constraint callback strategy (single-tree)

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

## Algorithm

<div class="algorithm-card">

Branch-and-cut with lazy ESH constraints

</div>

## See Also

- MIPSolverCplexSingleTree, MIPSolverGurobiSingleTree

## Source

Header file: {{ link(path="/browser/?library=SHOT&file=src/SolutionStrategy/SolutionStrategySingleTree.h", text="`src/SolutionStrategy/SolutionStrategySingleTree.h`") }}

