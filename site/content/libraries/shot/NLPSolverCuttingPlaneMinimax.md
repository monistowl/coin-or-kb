+++
title = "NLPSolverCuttingPlaneMinimax"
description = "Cutting-plane solver for minimax LP problems"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "src/NLPSolver/NLPSolverCuttingPlaneMinimax.h"
+++

Cutting-plane solver for minimax LP problems

Built-in LP-based solver for simple minimax problems.

**NLPSolverCuttingPlaneMinimax Class:**
- Uses MIP solver (CPLEX/Gurobi/Cbc) as LP engine
- Iteratively adds cutting planes
- No external NLP solver dependency

**Minimax Problem Form:**
- min t
- s.t. f_i(x) <= t for all i

**Use Case:**
- Finding interior points when Ipopt unavailable
- Solving auxiliary minimax subproblems

## Algorithm

<div class="algorithm-card">

Iterative cutting plane for convex minimax

</div>

## Source

Header file: `src/NLPSolver/NLPSolverCuttingPlaneMinimax.h`

