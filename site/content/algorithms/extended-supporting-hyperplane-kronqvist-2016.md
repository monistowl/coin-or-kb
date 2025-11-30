+++
title = "Extended Supporting Hyperplane (Kronqvist 2016)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

## Implementations

### SHOT

- **[TaskSelectHyperplanePointsESH.h](/coin-or-kb/browser/?library=SHOT)** - Extended Supporting Hyperplane point selection

Core ESH algorithm: finds boundary points for hyperplane generation.

**TaskSelectHyperplanePointsESH Class:**
- run(): Process current MIP solutions
- run(solPoints): Process specific solution points

**ESH Algorithm:**
1. Take infeasible MIP solution point
2. Use rootsearch to find boundary with feasible region
3. Generate supporting hyperplane at boundary

**Extends ECP:**
- ESH uses interior point + rootsearch
- ECP generates cuts at infeasible point directly
