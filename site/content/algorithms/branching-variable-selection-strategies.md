+++
title = "Branching Variable Selection Strategies"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

After identifying fractional variables, must choose which to branch on.
Different strategies trade off computational cost vs tree size.

Common Scoring Functions:
- Most infeasible: max |x_j - round(x_j)| - cheap but often poor
- Product score: score_j = max(D⁺_j·D⁻_j, ε) where D are degradations
- Hybrid: (1-μ)·min(D⁺,D⁻) + μ·max(D⁺,D⁻), μ typically 1/6
- Pseudo-costs: ψ⁺_j·(⌈x_j⌉-x_j) × ψ⁻_j·(x_j-⌊x_j⌋)

Strong branching workflow:
1. Select k candidates (most fractional or pseudocost-based)
2. For each candidate, solve LP for both branches (with iteration limit)
3. Record D⁺_j = z⁺_j - z, D⁻_j = z⁻_j - z (or infeasible/cutoff)
4. Score candidates, pick best
5. Update pseudo-costs from observed degradations

## Mathematical Formulation

<div class="math-block">

Reliability branching: Use pseudo-costs ψ_j unless branched on
variable < η_rel times, then strong branch to improve estimate.
Balances accuracy vs cost of strong branching.

</div>

## Complexity

Strong branching: O(k × LP_iterations) per node.
Pseudo-costs: O(n) after warmup. Reliability: adaptive O(k') where k' ≤ k.

## Implementations

### Cbc

- **[CbcBranchDecision.hpp](/coin-or-kb/browser/?library=Cbc)** - Abstract base for branching variable selection
Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
This code is licensed under the terms of the Eclipse Public License (EPL).

## References

- Achterberg, Koch & Martin, "Branching rules revisited",
     Operations Research Letters 33 (2005) 42-54

CbcBranchDecision defines HOW TO CHOOSE between branching candidates:
- betterBranch(): Compare two CbcBranchingObjects after strong branching
- bestBranch(): Compare N candidates and return best index

Used after strong branching evaluates candidates. Decision considers:
- changeUp/changeDown: Objective change estimates
- numInfeasibilitiesUp/Down: Remaining infeasibilities
