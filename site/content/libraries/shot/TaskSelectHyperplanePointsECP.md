+++
title = "TaskSelectHyperplanePointsECP"
description = "Extended Cutting Plane point selection"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "src/Tasks/TaskSelectHyperplanePointsECP.h"
+++

Extended Cutting Plane point selection

Classic outer approximation: linearize at infeasible points.

**TaskSelectHyperplanePointsECP Class:**
- run(): Process current MIP solutions
- run(solPoints): Process specific solution points

**ECP Algorithm:**
- Generate gradient cut at infeasible solution
- Simpler than ESH but may converge slower
- Used as fallback when ESH rootsearch fails

## Algorithm

<div class="algorithm-card">

Extended Cutting Plane (Westerlund-Pettersson)

</div>

## See Also

- [TaskSelectHyperplanePointsESH](/libraries/shot/taskselecthyperplanepointsesh/).h for ESH variant
- TaskAddHyperplanes.h for cut addition

## Source

Header file: [`src/Tasks/TaskSelectHyperplanePointsECP.h`](/browser/?library=SHOT&file=src/Tasks/TaskSelectHyperplanePointsECP.h)

