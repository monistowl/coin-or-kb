+++
title = "Essential for Extended Supporting Hyperplane (ESH) method"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

## Implementations

### SHOT

- **{{ link(path="/browser/?library=SHOT", text="IRootsearchMethod.h") }}** - Interface for constraint boundary rootsearch algorithms

Finds points on constraint boundaries for ESH hyperplane generation.

**Purpose:**
Given interior point A and exterior point B, find point on boundary
where constraint function equals zero (feasibility boundary).

**Constraint Rootsearch:**
- findZero(ptA, ptB, ...): Search along line segment A→B
- Returns (boundary point, exterior point) pair
- lambdaTol: Tolerance on line parameter
- constrTol: Tolerance on constraint violation

**Objective Rootsearch:**
- findZero(pt, objLB, objUB, ...): Find objective level set
- Used for objective function cuts

**Algorithm:**
- Uses bisection or hybrid methods (TOMS 748)
- Requires f(A) < 0 (feasible) and f(B) > 0 (infeasible)

**Implementations:**
- RootsearchMethodBoost: Boost.Math TOMS 748 or bisection
