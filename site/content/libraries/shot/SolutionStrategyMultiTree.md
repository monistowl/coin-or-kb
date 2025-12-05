+++
title = "SolutionStrategyMultiTree"
description = "Iterative outer approximation strategy (multi-tree)"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "src/SolutionStrategy/SolutionStrategyMultiTree.h"
+++

Iterative outer approximation strategy (multi-tree)

Classic outer approximation loop for convex MINLP.

**Algorithm Pattern:**
1. Solve MIP relaxation to get candidate point
2. Generate supporting hyperplanes at violated points
3. Add cuts to MIP and resolve
4. Repeat until convergence or termination

**Task Flow (initializeStrategy):**
- CreateDualProblem → SolveIteration → SelectHyperplanes
- AddHyperplanes → CheckTermination → loop

**Advantages:**
- No callback complexity
- Can use any MIP solver
- Easier debugging/logging

**Disadvantages:**
- Multiple MIP solves
- May regenerate same B&B tree work

## Algorithm

<div class="algorithm-card">

Standard ESH outer approximation

</div>

## See Also

- [SolutionStrategySingleTree](@/libraries/shot/SolutionStrategySingleTree.md) for callback-based variant

## Source

Header file: {{ link(path="/browser/?library=SHOT&file=src/SolutionStrategy/SolutionStrategyMultiTree.h", text="`src/SolutionStrategy/SolutionStrategyMultiTree.h`") }}

