+++
title = "Online Active Set Strategy - works well for model"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

predictive control (MPC) where QPs are solved in sequence

## Mathematical Formulation

<div class="math-block">

lbx <= x <= ubx    (bounds)

Key features:
- Online active set strategy (efficient for parametric QPs)
- Hot-starting from previous solutions
- Handles dense and sparse problems
- Real-time capable (bounded iteration counts)

Main classes:
- QProblemB: QP with only box constraints (no A matrix)
- QProblem: Full QP with linear constraints
- SQProblem: Sequential QP with varying Hessian

</div>

## Implementations

### qpOASES

- **[qpOASES.hpp](/browser/?library=qpOASES)** - Main include file for qpOASES quadratic programming solver

qpOASES solves convex quadratic programs (QPs) of the form:

## References

- Ferreau et al. (2014). "qpOASES: A parametric active-set algorithm
     for quadratic programming". Math. Prog. Comp. 6(4):327-363.
