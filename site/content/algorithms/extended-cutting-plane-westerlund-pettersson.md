+++
title = "Extended Cutting Plane (Westerlund-Pettersson)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

## Implementations

### SHOT

- **{{ link(path="/browser/?library=SHOT", text="TaskSelectHyperplanePointsECP.h") }}** - Extended Cutting Plane point selection

Classic outer approximation: linearize at infeasible points.

**TaskSelectHyperplanePointsECP Class:**
- run(): Process current MIP solutions
- run(solPoints): Process specific solution points

**ECP Algorithm:**
- Generate gradient cut at infeasible solution
- Simpler than ESH but may converge slower
- Used as fallback when ESH rootsearch fails
