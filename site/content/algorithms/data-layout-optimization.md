+++
title = "Data Layout Optimization"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Other Algorithms"
implementation_count = 1
+++

All arrays use [structural|slack] layout instead of separate storage.
      This improves cache locality during basis updates. Key arrays:
      - abcSolution_[0..n+m]: primal solution values
      - abcDj_[0..n+m]: reduced costs (dual solution)
      - abcLower_/abcUpper_[0..n+m]: variable bounds

## Complexity

Same asymptotic complexity as ClpSimplex:
      Per-iteration: O(m²) average for basis update
      Practical speedup: 2-4x from SIMD, additional from parallelism

## Implementations

### Clp

- **[AbcSimplex.hpp](/coin-or-kb/browser/?library=Clp)** - AVX/SIMD-optimized simplex solver ("A Better Clp")
  - [View source on GitHub](https://github.com/monistowl/coin-or-kb/blob/master/layer-1/Clp/src/AbcSimplex.hpp)

## References

- Forrest, J.J. and Goldfarb, D. (1992). "Steepest-edge simplex
      algorithms for linear programming". Math. Programming 57:341-374.
