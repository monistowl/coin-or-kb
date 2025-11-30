+++
title = "Root Node vs. Tree Strategy"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

- Root: Aggressive cuts (high whenCutGenerator_, all generators active)
  - Tree: Selective cuts (numberActiveCutsAtRoot_ guides which to keep)
  - Deep tree: Often disable most generators (computational cost)
  Trade-off: Stronger root LP → fewer nodes vs. more time per node.

## Complexity

generateCuts: O(generator_cost × frequency)
  Generator costs vary: Clique O(n), Gomory O(n²), Probing O(n × LP_solve)
  Overall B&C impact: cuts reduce nodes but add per-node overhead

## Implementations

### Cbc

- **[CbcCutGenerator.hpp](/browser/?library=Cbc)** - Interface between Cbc and Cut Generation Library (CGL)
Copyright (C) 2003, IBM Corporation and others. All Rights Reserved.
This code is licensed under the terms of the Eclipse Public License (EPL).

CbcCutGenerator: Wraps a CglCutGenerator with Cbc-specific controls.
Manages when and how cut generation is called during B&C search.

Key control parameters:
- whenCutGenerator_: Frequency (every N nodes, -100=disabled, -99=root only)
- depthCutGenerator_: Depth-based triggering
- switches_: Bit flags for various options (normal, atSolution, timing, etc.)

Statistics tracked:
- numberTimes_: Times generator was called
- numberCuts_: Total cuts generated
- numberCutsActive_: Cuts still binding at end
- timeInCutGenerator_: CPU time spent

Supports adaptive behavior:
- Can be switched off if ineffective
- Tracks cuts at root vs tree
- Global cuts and Lagrangean relaxation support

## References

- Cornuejols, G. (2008). "Valid Inequalities for Mixed Integer
       Linear Programs". Math. Programming 112(1):3-44.
