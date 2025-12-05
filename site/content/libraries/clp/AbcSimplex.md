+++
title = "AbcSimplex"
description = "AVX/SIMD-optimized simplex solver (\"A Better Clp\")"
template = "page.html"

[extra]
layer = 1
library = "Clp"
header_file = "src/AbcSimplex.hpp"
+++

## Algorithm

<div class="algorithm-card">

Data Layout Optimization:
      All arrays use [structural|slack] layout instead of separate storage.
      This improves cache locality during basis updates. Key arrays:
      - abcSolution_[0..n+m]: primal solution values
      - abcDj_[0..n+m]: reduced costs (dual solution)
      - abcLower_/abcUpper_[0..n+m]: variable bounds

**Complexity:** Same asymptotic complexity as ClpSimplex:
      Per-iteration: $O(m²)$ average for basis update
      Practical speedup: 2-4x from SIMD, additional from parallelism

<div class="refs">

**References:**
- Forrest, J.J. and Goldfarb, D. (1992). "Steepest-edge simplex       algorithms for linear programming". Math. Programming 57:341-374.

</div>

</div>

## See Also

- [ClpSimplex](/libraries/clp/clpsimplex/) for the standard (non-AVX) implementation
- AbcSimplexDual for AVX-optimized dual simplex
- AbcSimplexPrimal for AVX-optimized primal simplex
- AbcMatrix for the optimized matrix class

## Source

Header file: [`src/AbcSimplex.hpp`](/browser/?library=Clp&file=src/AbcSimplex.hpp)

