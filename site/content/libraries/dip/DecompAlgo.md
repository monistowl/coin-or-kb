+++
title = "DecompAlgo"
description = "Base class for all DIP decomposition algorithms"
template = "page.html"

[extra]
layer = 3
library = "Dip"
header_file = "Dip/src/DecompAlgo.h"
+++

Base class for all DIP decomposition algorithms

DecompAlgo is the algorithmic engine that orchestrates:
- Master problem management (LP relaxation)
- Subproblem solving (pricing/column generation)
- Cut generation and management
- Phase transitions and convergence

**Key Data Members:**
- m_masterSI: Master LP solver interface
- m_app: Pointer to user's DecompApp
- m_modelCore/m_modelRelax: Problem decomposition
- m_vars/m_cuts: Generated columns and cuts
- m_xhat: Current LP solution in original x-space

**Algorithm Phases:**
- PHASE_PRICE1: Feasibility with artificial variables
- PHASE_PRICE2: Optimizing with generated columns
- PHASE_CUT: Adding violated inequalities

**Virtual Methods for Subclasses:**
- createMasterProblem(): Build initial restricted master
- processNode(): Main node processing loop
- generateVars(): Column generation (pricing)
- generateCuts(): Cut separation
- getMasterDualSolution(): Dual values for pricing

**Derived Classes:**
- DecompAlgoPC: Price-and-Cut (Dantzig-Wolfe)
- DecompAlgoC: Cutting plane only
- DecompAlgoRC: Relax-and-Cut (Lagrangian)

## Algorithm

<div class="algorithm-card">

Price-and-Cut Hybrid (generateVars + generateCuts):
  Interleave column generation and cut separation:
  while (improving):
    1. generateVars(): Solve pricing, add columns
    2. generateCuts(): Separate cuts on current x̂
    3. Update master LP, reoptimize
  Cuts added to master affect dual space and pricing.

<div class="math">

$$L(u) = u'b + min_{x} {(c - A'u)'x : x ∈ X}$$
Solve Lagrangian dual: max_u L(u) via subgradient or bundle methods.
$$- Subgradient: u^{t+1} = u^t + step * (b - Ax^t)$$
- L(u) provides lower bound; project x to get upper bound.

</div>

**Complexity:** Column generation: $O(#iterations × pricing_cost)$
  Pricing cost depends on subproblem structure (often NP-hard but small)
  Master LP: $O(m × n × simplex_iterations)$ where n grows with columns

<div class="refs">

**References:**
- Dantzig, G.B. and Wolfe, P. (1960). "Decomposition principle for        linear programs". Operations Research 8(1):101-111.
- Barnhart, C. et al. (1998). "Branch-and-price: Column generation        for solving huge integer programs". Operations Research 46(3).
- Held, M. and Karp, R.M. (1971). "The traveling-salesman problem        and minimum spanning trees: Part II". Math Programming 1(1):6-25.
- Desaulniers, G. et al. (2005). "Column Generation". Springer.

</div>

</div>

## See Also

- DecompAlgoPC.h for Dantzig-Wolfe implementation
- DecompAlgoC.h for cutting plane method
- DecompAlgoRC.h for Lagrangian relaxation
- DecompApp.h for user model definition

## Source

Header file: `Dip/src/DecompAlgo.h`

