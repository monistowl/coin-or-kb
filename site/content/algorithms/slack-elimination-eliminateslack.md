+++
title = "Slack Elimination (eliminateSlack)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

GMI from tableau uses slack variables; convert to original:

## Mathematical Formulation

<div class="math-block">

Substitute s_i = b_i - a_i'x using original constraint
  Produces cut in terms of structural variables only.

</div>

## Complexity

O(nnz * log(maxdenom)) for rational approximation

## Implementations

### Cgl

- **{{ link(path="/browser/?library=Cgl", text="CglGMI.hpp") }}** - Gomory Mixed-Integer cuts with numerical safety testing

## References

- Gomory (1960) - An algorithm for mixed-integer problems
- Cornuéjols (2008) - Valid inequalities for MIP
- Cook, Kannan, Schrijver (1990) - Chvátal closures
- Continued fraction algorithm for rational approximation
