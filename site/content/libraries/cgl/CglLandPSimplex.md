+++
title = "CglLandPSimplex"
description = "Simplex algorithm for Lift-and-Project cut generation"
template = "page.html"

[extra]
layer = 2
library = "Cgl"
header_file = "src/CglLandP/CglLandPSimplex.hpp"
+++

## Algorithm

<div class="algorithm-card">

Lift-and-Project Cutting Planes:
  Given MIP with integrality on x_j, the L&P disjunction is:
    (x_j ≤ ⌊x*_j⌋) OR (x_j ≥ ⌈x*_j⌉)

  Cut generation via CGLP (Cut Generation LP):
  1. Formulate normalization: ||cut|| = 1 (various norms)
  2. For each disjunction term, lift the LP relaxation
  3. Find cut valid for intersection of lifted polyhedra
  4. Project cut back to original variable space

  This class optimizes the CGLP by pivoting through adjacent bases,
  seeking the most violated intersection cut.

<div class="math">

For source row i with f_i fractional:
Intersection cut: Σ (a_j/f_i if a_j ≥ 0, else a_j/(f_i-1)) x_j ≥ 1
L&P strengthens by optimizing choice of disjunction via pivoting.

</div>

**Complexity:** $O(pivots × m × n)$ where pivots typically $O(m)$.
  Each pivot requires tableau row computation $O(m)$ and ratio test $O(n)$.
  Heuristics limit pivot count to avoid excessive computation.

<div class="refs">

**References:**
- Balas, E. (1979). "Disjunctive Programming". Annals of Discrete   Mathematics 5:3-51. [Theoretical foundation]
- Balas, E. and Perregaard, M. (2003). "A precise correspondence between   lift-and-project cuts, simple disjunctive cuts, and mixed integer   Gomory cuts for 0-1 programming". Math. Programming 94:221-245.

</div>

</div>

## See Also

- CglLandP for the main cut generator interface
- CglLandPTabRow for tableau row structure
- CglLandPValidator for cut acceptance criteria

Date:     21/07/05

Copyright (C) 2005-2009 Pierre Bonami and others.  All Rights Reserved.
This code is licensed under the terms of the Eclipse Public License (EPL).

## Source

Header file: [`src/CglLandP/CglLandPSimplex.hpp`](/browser/?library=Cgl&file=src/CglLandP/CglLandPSimplex.hpp)

