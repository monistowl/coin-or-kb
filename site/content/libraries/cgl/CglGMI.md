+++
title = "CglGMI"
description = "Gomory Mixed-Integer cuts with numerical safety testing"
template = "page.html"

[extra]
layer = 2
library = "Cgl"
header_file = "src/CglGMI/CglGMI.hpp"
+++

## Algorithm

<div class="algorithm-card">

Slack Elimination (eliminateSlack):
  GMI from tableau uses slack variables; convert to original:

<div class="math">

$$Substitute s_{i} = b_{i} - a_{i}'x using original constraint$$
Produces cut in terms of structural variables only.

</div>

**Complexity:** $O(nnz * log(maxdenom)$) for rational approximation

<div class="refs">

**References:**
- Gomory (1960) - An algorithm for mixed-integer problems
- Cornuéjols (2008) - Valid inequalities for MIP
- Cook, Kannan, Schrijver (1990) - Chvátal closures
- Continued fraction algorithm for rational approximation

</div>

</div>

## See Also

- CglGMIParam for parameter settings
- [CglGomory](/libraries/cgl/cglgomory/) for simpler Gomory implementation

## Source

Header file: [`src/CglGMI/CglGMI.hpp`](/browser/?library=Cgl&file=src/CglGMI/CglGMI.hpp)

