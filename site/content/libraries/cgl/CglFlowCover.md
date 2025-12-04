+++
title = "CglFlowCover"
description = "Lifted Simple Generalized Flow Cover cuts"
template = "page.html"

[extra]
layer = 2
library = "Cgl"
header_file = "src/CglFlowCover/CglFlowCover.hpp"
+++

## Algorithm

<div class="algorithm-card">

Row Classification (determineOneRowType):
  Categories for cut generation:
  - VARUB/VARLB: Two-variable rows defining variable bounds
  - MIXUB/MIXEQ: Main candidates for flow cover generation
  - NOBINUB: No binary → cannot generate flow cuts

<div class="math">

VUB enables stronger cuts than simple bounds:
        x_j ≤ u_j vs x_j ≤ u_j d_j gives tighter when d_j = 0
  Stored in vubs_[] array indexed by continuous variable.

</div>

**Complexity:** O(nnz) per row for classification

<div class="refs">

**References:**
- Padberg, Van Roy, Wolsey (1985) - Valid inequalities for 0-1 programs
- Gu, Nemhauser, Savelsbergh (1999) - Lifted flow cover inequalities

</div>

</div>

## See Also

- CglMixedIntegerRounding for general MIR approach
- CglKnapsackCover for simpler cover cuts

## Source

Header file: `src/CglFlowCover/CglFlowCover.hpp`

