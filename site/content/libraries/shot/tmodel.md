+++
title = "tmodel"
description = "Taylor Model Arithmetic for Rigorous Bound Propagation"
template = "page.html"

[extra]
layer = 4
library = "SHOT"
header_file = "ThirdParty/mc++/include/tmodel.hpp"
+++

## Algorithm

<div class="algorithm-card">

Convergence Properties:

<div class="math">

|R| = $O(diam(D)$^{q+1}) as domain shrinks
  Higher order q → faster convergence but more coefficients
  Used in global optimization branch-and-bound for bound tightening.

</div>

**Complexity:** Bernstein conversion: $O($n^{q}$ * $2^{n}$)$ but provides hull property

<div class="refs">

**References:**
- Makino & Berz (2003) - Taylor models and validated numerics
- Neumaier (2002) - Taylor forms for global optimization
- Lin & Rokne (1995) - Bernstein form for polynomial bounds
- Sahlodin & Chachuat (2011) - McCormick-Taylor models
- Bompadre et al. (2012) - Convergence of Taylor models

</div>

</div>

## Source

Header file: `ThirdParty/mc++/include/tmodel.hpp`

