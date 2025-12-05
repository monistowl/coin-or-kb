+++
title = "Cbc_C_Interface"
description = "Creates an empty problem"
template = "page.html"

[extra]
layer = 2
library = "Cbc"
header_file = "src/Cbc_C_Interface.h"
+++

## Algorithm

<div class="algorithm-card">

LP Method Selection (LPMethod enum):
  - LPM_Dual: Dual simplex (default, best for warm starts)
  - LPM_Primal: Primal simplex
  - LPM_Barrier: Interior-point with crossover to basis
  - LPM_BarrierNoCross: IPM without crossover (for large LPs)

**Complexity:** MIP: Exponential worst-case, highly structure-dependent
  Each LP solve: $O(m·n·iterations)$ for simplex

<div class="refs">

**References:**
- Land, A.H. and Doig, A.G. (1960). "An automatic method of solving   discrete programming problems". Econometrica 28(3):497-520.

</div>

</div>

## Source

Header file: [`src/Cbc_C_Interface.h`](/browser/?library=Cbc&file=src/Cbc_C_Interface.h)

