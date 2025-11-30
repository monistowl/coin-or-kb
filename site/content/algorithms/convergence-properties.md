+++
title = "Convergence Properties"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

## Mathematical Formulation

<div class="math-block">

|R| = O(diam(D)^{q+1}) as domain shrinks
  Higher order q → faster convergence but more coefficients
  Used in global optimization branch-and-bound for bound tightening.

</div>

## Complexity

Bernstein conversion: O(n^q * 2^n) but provides hull property

## Implementations

### SHOT

- **[tmodel.hpp](/coin-or-kb/browser/?library=SHOT)** - Taylor Model Arithmetic for Rigorous Bound Propagation

## References

- Makino & Berz (2003) - Taylor models and validated numerics
- Neumaier (2002) - Taylor forms for global optimization
- Lin & Rokne (1995) - Bernstein form for polynomial bounds
- Sahlodin & Chachuat (2011) - McCormick-Taylor models
- Bompadre et al. (2012) - Convergence of Taylor models
