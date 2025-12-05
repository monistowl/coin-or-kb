+++
title = "Branch-and-Bound Node Management"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Presolve Reductions"
implementation_count = 1
+++

Each CbcNode represents a subproblem (LP relaxation with additional bounds)
in the B&B tree. Key operations:

1. Node Creation: When branching on variable x_j with fractional value f:
   - Down child: add bound x_j ≤ floor(f)
   - Up child: add bound x_j ≥ ceil(f)

2. Variable Selection (chooseBranch):
   - Strong branching: solve LP for each candidate, pick best degradation
   - Pseudo-costs: estimate from historical branching improvements
   - Reliability branching: strong branch until pseudo-costs reliable

3. Node Processing:
   - Reconstruct LP from parent using CbcNodeInfo diffs
   - Solve LP relaxation
   - Apply cuts, check integrality, branch or fathom

## Mathematical Formulation

<div class="math-block">

Strong branching score: score_j = (1-μ)·min(D⁻_j, D⁺_j) + μ·max(D⁻_j, D⁺_j)
where D⁻_j, D⁺_j are objective degradations for down/up branches, μ ∈ [0,1].
Pseudo-cost: ψ⁻_j = ΔZ⁻/(f_j - floor(f_j)), initialized via strong branching.

</div>

## Complexity

Strong branching: O(k·LP) where k candidates evaluated.
Pseudo-costs: O(n) for scoring after initialization. Node reconstruction:
O(depth) to replay bound changes from root.

## Implementations

### Cbc

- **{{ link(path="/browser/?library=Cbc", text="CbcNode.hpp") }}** - Search tree node for branch-and-cut
Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
This code is licensed under the terms of the Eclipse Public License (EPL).

## References

- Land & Doig, "An automatic method for solving discrete programming problems",
     Econometrica 28 (1960) 497-520 (original B&B)
- Achterberg, Koch & Martin, "Branching rules revisited",
     Operations Research Letters 33 (2005) 42-54 (reliability branching)

CbcNode represents a live subproblem in the B&C search tree.
Contains information needed while the node is active:
- Depth in tree, objective value, branching state
- Links to CbcNodeInfo for reconstruction

Lifecycle: Created when branching, deleted when all branches evaluated.
Extends CoinTreeNode for heap-based storage in CbcTree.

Key methods:
- createInfo(): Create CbcNodeInfo for subproblem storage
- branch(): Apply branching and create child subproblem
- chooseBranch(): Select branching variable/object
