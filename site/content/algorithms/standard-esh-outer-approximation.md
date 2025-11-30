+++
title = "Standard ESH outer approximation"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

## Implementations

### SHOT

- **[SolutionStrategyMultiTree.h](/browser/?library=SHOT)** - Iterative outer approximation strategy (multi-tree)

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
