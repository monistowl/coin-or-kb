+++
title = "qpOASES"
description = "Main include file for qpOASES quadratic programming solver"
template = "page.html"

[extra]
layer = 1
library = "qpOASES"
header_file = "include/qpOASES.hpp"
+++

Main include file for qpOASES quadratic programming solver

qpOASES solves convex quadratic programs (QPs) of the form:

## Algorithm

<div class="algorithm-card">

Online Active Set Strategy - works well for model
           predictive control (MPC) where QPs are solved in sequence

<div class="math">

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

<div class="refs">

**References:**
- Ferreau et al. (2014). "qpOASES: A parametric active-set algorithm      for quadratic programming". Math. Prog. Comp. 6(4):327-363.

</div>

</div>

## See Also

- [QProblem](@/libraries/qpoases/QProblem.md) for general QP solving
- [QProblemB](@/libraries/qpoases/QProblemB.md) for box-constrained QPs (faster)

## Source

Header file: {{ link(path="/browser/?library=qpOASES&file=include/qpOASES.hpp", text="`include/qpOASES.hpp`") }}

