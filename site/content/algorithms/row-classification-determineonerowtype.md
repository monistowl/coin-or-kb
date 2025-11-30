+++
title = "Row Classification (determineOneRowType)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Categories for cut generation:
  - VARUB/VARLB: Two-variable rows defining variable bounds
  - MIXUB/MIXEQ: Main candidates for flow cover generation
  - NOBINUB: No binary → cannot generate flow cuts

## Mathematical Formulation

<div class="math-block">

VUB enables stronger cuts than simple bounds:
        x_j ≤ u_j vs x_j ≤ u_j d_j gives tighter when d_j = 0
  Stored in vubs_[] array indexed by continuous variable.

</div>

## Complexity

O(nnz) per row for classification

## Implementations

### Cgl

- **[CglFlowCover.hpp](/browser/?library=Cgl)** - Lifted Simple Generalized Flow Cover cuts

## References

- Padberg, Van Roy, Wolsey (1985) - Valid inequalities for 0-1 programs
- Gu, Nemhauser, Savelsbergh (1999) - Lifted flow cover inequalities
