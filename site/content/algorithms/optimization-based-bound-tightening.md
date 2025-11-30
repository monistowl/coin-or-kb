+++
title = "Optimization-Based Bound Tightening"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

## Implementations

### SHOT

- **[TaskPerformBoundTightening.h](/browser/?library=SHOT)** - Tighten variable bounds via optimization

Uses optimization-based bound tightening (OBBT).

**TaskPerformBoundTightening Class:**
- POASolver: Polyhedral outer approximation solver
- createPOA(): Build relaxed problem for bound tightening

**OBBT Algorithm:**
- For each variable: min/max subject to relaxation
- Tightens bounds beyond constraint propagation
- Improves relaxation quality
