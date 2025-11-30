+++
title = "Feasibility Pump (FP)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Primal Heuristics"
implementation_count = 1
+++

Alternates between LP relaxation and rounding to find feasible MIP solution.

Basic Algorithm:
1. x* ← solve LP relaxation
2. x̄ ← round(x*) (integer point)
3. While x* ≠ x̄ and iterations < max:
   a. x* ← argmin ||x - x̄|| s.t. Ax = b, l ≤ x ≤ u (LP toward x̄)
   b. x̄ ← round(x*)
4. If x* = x̄, return feasible solution

Enhancements:
- Objective blending: min α·c^Tx + (1-α)·||x-x̄|| trades feasibility vs quality
- Cycle detection: Track visited roundings, perturb if cycling
- Randomization: Random flips to escape local minima
- General integers: Auxiliary binary formulation or specialized rounding

## Mathematical Formulation

<div class="math-block">

Distance LP: min Σ_j |x_j - x̄_j| for integer j
Linearized as: min Σ_j d_j s.t. d_j ≥ x_j - x̄_j, d_j ≥ x̄_j - x_j
Or squared Euclidean: uses modified objective coefficients.

</div>

## Complexity

Each iteration: one LP solve, O(n_int) rounding.
Typically 10-100 iterations. Very effective for finding first solution.
Success rate ~80% on MIPLIB instances.

## Implementations

### Cbc

- **[CbcHeuristicFPump.hpp](/browser/?library=Cbc)** - Feasibility Pump heuristic (Fischetti, Glover & Lodi)
Copyright (C) 2004, IBM Corporation and others. All Rights Reserved.
This code is licensed under the terms of the Eclipse Public License (EPL).

## References

- Fischetti, Glover & Lodi, "The feasibility pump",
     Mathematical Programming 104 (2005) 91-104
- Achterberg & Berthold, "Improving the feasibility pump",
     Discrete Optimization 4 (2007) 77-86

CbcHeuristicFPump: Implements the Feasibility Pump algorithm
(Fischetti, Glover & Lodi, 2005) for finding initial MIP solutions.

Algorithm overview:
1. Solve LP relaxation, get fractional x*
2. Round x* to nearest integers -> x_bar
3. Solve LP with objective: minimize distance to x_bar
4. If new x* = x_bar, done (integer feasible)
5. Otherwise round and repeat

Key parameters:
- maximumPasses_: Max iterations before giving up
- initialWeight_: Blend original objective with distance
- defaultRounding_: Threshold for rounding (default 0.5)

Handles cycling through randomization and perturbation.

Also includes CbcDisasterHandler for Clp solver recovery.
