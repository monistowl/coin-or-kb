+++
title = "Iterative cutting plane for convex minimax"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

## Implementations

### SHOT

- **{{ link(path="/browser/?library=SHOT", text="NLPSolverCuttingPlaneMinimax.h") }}** - Cutting-plane solver for minimax LP problems

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
