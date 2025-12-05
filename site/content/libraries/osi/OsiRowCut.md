+++
title = "OsiRowCut"
description = "Row-based cutting plane (linear inequality)"
template = "page.html"

[extra]
layer = 1
library = "Osi"
header_file = "src/Osi/OsiRowCut.hpp"
+++

Row-based cutting plane (linear inequality)

Row cuts are the most common form of cutting planes, representing
a linear inequality constraint: lb <= a'x <= ub

Common cut families that produce row cuts:
- Gomory cuts (from LP tableau)
- Mixed-integer rounding (MIR)
- Knapsack covers
- Clique cuts
- Flow covers

## Mathematics

<div class="math">

lb <= sum(a[i] * x[i]) <= ub

</div>

## See Also

- OsiCut for base class
- OsiCuts for cut pool management
- Cgl (Cut Generation Library) for cut generators
- [CoinPackedVector](/libraries/coinutils/coinpackedvector/) for sparse row representation

## Source

Header file: [`src/Osi/OsiRowCut.hpp`](/browser/?library=Osi&file=src/Osi/OsiRowCut.hpp)

