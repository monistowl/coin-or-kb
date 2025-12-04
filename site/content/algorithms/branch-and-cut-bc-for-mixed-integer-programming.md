+++
title = "Branch-and-Cut (B&C) for Mixed-Integer Programming"
description = "Algorithm documentation and implementations"
template = "algorithm.html"

[extra]
category = "Branch and Bound"
implementation_count = 1
+++

## Why This Matters

Branch-and-cut is the algorithm behind modern MIP solvers like Cbc, CPLEX, and Gurobi. It combines three powerful ideas:

1. **Branch-and-bound**: Divide the search space systematically
2. **Cutting planes**: Tighten the LP relaxation to reduce the gap
3. **Primal heuristics**: Find good feasible solutions quickly to enable pruning

**Why cuts matter so much**: Without cuts, the LP relaxation may be very weak — meaning a 10% gap between the LP bound and the best integer solution. With good cuts, this gap shrinks dramatically, allowing the solver to prune most of the tree.

**The interplay is subtle**: Cuts improve bounds but slow down LP solves. Branching explores the tree but may miss easy improvements. Heuristics find solutions but may not be optimal. Getting the balance right is what makes a solver fast.

**Key insight**: Cbc doesn't implement one fixed algorithm — it implements a *framework* where you can plug in different branching strategies, cut generators, heuristics, and node selection rules. Understanding the framework is more important than memorizing any single algorithm.

---

1. Solve LP relaxation at root node
  2. While open nodes remain:
     a. Select node from priority queue (best-first or depth-first)
     b. Solve LP relaxation, apply cuts (Gomory, MIR, clique, etc.)
     c. If fractional: branch on integer variable, create child nodes
     d. If integer-feasible: update incumbent if improved
     e. Prune by bound if LP ≥ incumbent
  3. Return optimal solution when tree exhausted

## Complexity

Worst-case O(2^n) where n = number of integer variables.
  Practical performance depends heavily on:
  - Strength of LP relaxation and cutting planes
  - Quality of branching variable selection
  - Effectiveness of primal heuristics
  - Problem structure (e.g., total unimodularity)

## Implementations

### Cbc

- **[CbcModel.hpp](/coin-or-kb/browser/?library=Cbc)** - Main branch-and-cut MIP solver class
Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
This code is licensed under the terms of the Eclipse Public License (EPL).

CbcModel is the central class for COIN-OR branch-and-cut MIP solving.
Key methods:
- initialSolve(): Solve LP relaxation
- branchAndBound(): Run B&C algorithm to optimality

Architecture:
- CbcNode/CbcNodeInfo: Subproblem representation in search tree
- CbcTree: Priority queue of live nodes (heap)
- CbcCutGenerator: Wrapper for CGL cut generators
- CbcHeuristic: Primal heuristics for finding solutions
- CbcBranchingObject: Branching decisions

## References

- Land, A.H. and Doig, A.G. (1960). "An automatic method of solving
  discrete programming problems". Econometrica 28(3):497-520.
  [Original branch-and-bound algorithm]
- Padberg, M. and Rinaldi, G. (1991). "A branch-and-cut algorithm
  for the resolution of large-scale symmetric traveling salesman problems".
  SIAM Review 33(1):60-100. [Branch-and-cut methodology]
- Savelsbergh, M.W.P. (1994). "Preprocessing and probing techniques
        for mixed integer programming problems". ORSA J. Computing 6(4):445-454.

      \todo It remains to work out the cleanest way of getting a solution to
            the original problem at the end. So this is very preliminary.
