+++
title = "CbcModel"
description = "Main branch-and-cut MIP solver class"
template = "page.html"

[extra]
layer = 2
library = "Cbc"
header_file = "src/CbcModel.hpp"
+++

Main branch-and-cut MIP solver class
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

## Algorithm

<div class="algorithm-card">

Branch-and-Cut (B&C) for Mixed-Integer Programming:
  1. Solve LP relaxation at root node
  2. While open nodes remain:
     a. Select node from priority queue (best-first or depth-first)
     b. Solve LP relaxation, apply cuts (Gomory, MIR, clique, etc.)
     c. If fractional: branch on integer variable, create child nodes
     d. If integer-feasible: update incumbent if improved
     e. Prune by bound if LP ≥ incumbent
  3. Return optimal solution when tree exhausted

**Complexity:** Worst-case $O(2^n)$ where n = number of integer variables.
  Practical performance depends heavily on:
  - Strength of LP relaxation and cutting planes
  - Quality of branching variable selection
  - Effectiveness of primal heuristics
  - Problem structure (e.g., total unimodularity)

<div class="refs">

**References:**
- Land, A.H. and Doig, A.G. (1960). "An automatic method of solving   discrete programming problems". Econometrica 28(3):497-520.   [Original branch-and-bound algorithm]
- Padberg, M. and Rinaldi, G. (1991). "A branch-and-cut algorithm   for the resolution of large-scale symmetric traveling salesman problems".   SIAM Review 33(1):60-100. [Branch-and-cut methodology]
- Savelsbergh, M.W.P. (1994). "Preprocessing and probing techniques         for mixed integer programming problems". ORSA J. Computing 6(4):445-454.        \todo It remains to work out the cleanest way of getting a solution to             the original problem at the end. So this is very preliminary.

</div>

</div>

## See Also

- CbcNode for search tree node representation
- CbcTree for node selection/storage
- [CbcCutGenerator](/libraries/cbc/cbccutgenerator/) for cutting plane management
- CbcHeuristic for primal heuristics
- [OsiSolverInterface](/libraries/osi/osisolverinterface/) for underlying LP solver

## Source

Header file: [`src/CbcModel.hpp`](/browser/?library=Cbc&file=src/CbcModel.hpp)

