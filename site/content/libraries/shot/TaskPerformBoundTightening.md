+++
title = "TaskPerformBoundTightening"
description = "Tighten variable bounds via optimization"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "src/Tasks/TaskPerformBoundTightening.h"
+++

Tighten variable bounds via optimization

Uses optimization-based bound tightening (OBBT).

**TaskPerformBoundTightening Class:**
- POASolver: Polyhedral outer approximation solver
- createPOA(): Build relaxed problem for bound tightening

**OBBT Algorithm:**
- For each variable: min/max subject to relaxation
- Tightens bounds beyond constraint propagation
- Improves relaxation quality

## Algorithm

<div class="algorithm-card">

Optimization-Based Bound Tightening

</div>

## See Also

- NLPSolverSHOT.h for POA solver
- [Problem](@/libraries/shot/Problem.md).h for bound storage

## Source

Header file: {{ link(path="/browser/?library=SHOT&file=src/Tasks/TaskPerformBoundTightening.h", text="`src/Tasks/TaskPerformBoundTightening.h`") }}

