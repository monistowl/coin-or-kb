+++
title = "Extended Supporting Hyperplane (ESH) method adds"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

linearizations at boundary and interior points

## Implementations

### SHOT

- **{{ link(path="/browser/?library=SHOT", text="DualSolver.h") }}** - MIP-based dual bound computation via supporting hyperplanes

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
