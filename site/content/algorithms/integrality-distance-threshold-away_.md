+++
title = "Integrality Distance Threshold (away_)"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

Skip variables near-integer to avoid numerical issues:

## Mathematical Formulation

<div class="math-block">

Generate cut only if away_ ≤ f_0 ≤ 1 - away_
  Default 0.05; tighter at root for more cuts.

</div>

## Complexity

O(m) per cut for m nonzeros in tableau row

## Implementations

### Cgl

- **[CglGomory.hpp](/browser/?library=Cgl)** - Gomory mixed-integer cuts from optimal LP basis

Generates Gomory fractional cuts, the classic MIP cutting planes
derived by Ralph Gomory in the 1950s-60s. For each fractional basic
variable, derives a valid inequality from the simplex tableau row.

Algorithm:
1. Requires optimal LP basis (needsOptimalBasis() = true)
2. For each basic integer variable with fractional value:
   - Get tableau row: x_i + sum_j a_ij * x_j = b_i
   - Apply fractional parts: sum_j f(a_ij)*x_j >= f(b_i)
   - For mixed-integer: separate continuous/integer coefficients
3. Strengthen using integrality of non-basic integers

Key parameters:
- limit_/limitAtRoot_: Max nonzeros in cut (dense cuts are expensive)
- away_/awayAtRoot_: Min distance from integrality to generate cut
- conditionNumberMultiplier_: Relax cut if basis is ill-conditioned
- gomoryType_: 0=normal, 1=add original, 2=replace with original matrix

Numerical considerations:
- Basis condition number affects cut reliability
- largestFactorMultiplier_ controls cut relaxation for stability
- alternateFactorization_ uses different factorization for accuracy

Gomory cuts are finite and can solve pure integer programs in theory,
but numerically fragile. Modern solvers combine with other cuts.

## References

- Gomory (1958) - Outline of an algorithm for integer solutions
- Cornuéjols (2007) - Revival of GMI cuts in MIP
- Cook et al. (2009) - Numerically safe GMI cuts
