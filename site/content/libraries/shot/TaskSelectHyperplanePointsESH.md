+++
title = "TaskSelectHyperplanePointsESH"
description = "Extended Supporting Hyperplane point selection"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "src/Tasks/TaskSelectHyperplanePointsESH.h"
+++

Extended Supporting Hyperplane point selection

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

## Algorithm

<div class="algorithm-card">

Extended Supporting Hyperplane (Kronqvist 2016)

</div>

## See Also

- RootsearchMethod/ for boundary finding
- TaskAddHyperplanes.h for cut addition

## Source

Header file: {{ link(path="/browser/?library=SHOT&file=src/Tasks/TaskSelectHyperplanePointsESH.h", text="`src/Tasks/TaskSelectHyperplanePointsESH.h`") }}

