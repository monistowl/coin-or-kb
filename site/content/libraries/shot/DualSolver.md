+++
title = "DualSolver"
description = "MIP-based dual bound computation via supporting hyperplanes"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "src/DualSolver.h"
+++

MIP-based dual bound computation via supporting hyperplanes

Manages the linearization-based dual problem.

**DualSolver Class:**
- MIPSolver: Backend MIP solver (CPLEX/Gurobi/CBC/HiGHS)
- generatedHyperplanes: All cutting planes added
- hyperplaneWaitingList: Pending cuts to add

**Hyperplane Management:**
- addHyperplane(): Add supporting hyperplane cut
- addGeneratedHyperplane(): Record a hyperplane
- hasHyperplaneBeenAdded(): Avoid duplicate cuts

**Integer Cuts:**
- addIntegerCut(): Add no-good cuts for MINLP
- generatedIntegerCuts: All integer cuts

**Interior Points:**
- interiorPointCandidates: Candidate interior points
- interiorPts: Verified interior points for ESH

## Algorithm

<div class="algorithm-card">

Extended Supporting Hyperplane (ESH) method adds
           linearizations at boundary and interior points

</div>

## See Also

- PrimalSolver.h for primal bound computation
- MIPSolver/ for backend implementations

## Source

Header file: `src/DualSolver.h`

