+++
title = "Algorithms"
description = "Cross-reference of algorithms implemented in COIN-OR"
template = "algorithms-index.html"
sort_by = "title"
+++

# Algorithm Index

This page provides a cross-reference of algorithms documented across the COIN-OR libraries.
Click any algorithm to see its mathematical formulation, complexity analysis, and all implementations.

## Presolve Reductions

- **[Bound Tightening](@/algorithms/bound-tightening.md)** (1 impl) - CoinUtils
- **[Branch-and-Bound Node Management](@/algorithms/branch-and-bound-node-management.md)** (1 impl) - Cbc
- **[Branch-and-Bound Tree Search](@/algorithms/branch-and-bound-tree-search.md)** (1 impl) - CoinUtils
- **[Direct MIQCQP branch-and-bound](@/algorithms/direct-miqcqp-branch-and-bound.md)** (1 impl) - SHOT
- **[Doubleton Elimination](@/algorithms/doubleton-elimination.md)** (1 impl) - CoinUtils
- **[Dual Bound Propagation](@/algorithms/dual-bound-propagation.md)** (1 impl) - CoinUtils
- **[Forcing Constraint Detection](@/algorithms/forcing-constraint-detection.md)** (1 impl) - CoinUtils
- **[LP Presolve (Preprocessing)](@/algorithms/lp-presolve-preprocessing.md)** (1 impl) - Clp
- **[LP Presolve - simplifies LP before solving via reversible transforms](@/algorithms/lp-presolve-simplifies-lp-before-solving-via-rever.md)** (1 impl) - CoinUtils
- **[Optimization-Based Bound Tightening](@/algorithms/optimization-based-bound-tightening.md)** (1 impl) - SHOT
- **[Singleton Column/Row Elimination](@/algorithms/singleton-columnrow-elimination.md)** (1 impl) - CoinUtils
- **[Slack Elimination (eliminateSlack)](@/algorithms/slack-elimination-eliminateslack.md)** (1 impl) - Cgl
- **[Tripleton Elimination](@/algorithms/tripleton-elimination.md)** (1 impl) - CoinUtils
- **[Variable Substitution (Non-Singleton)](@/algorithms/variable-substitution-non-singleton.md)** (1 impl) - CoinUtils

## Matrix Factorization

- **[ABC (Alternative Basis Code) LU Factorization](@/algorithms/abc-alternative-basis-code-lu-factorization.md)** (1 impl) - Clp
- **[Dense LU Factorization (LAPACK-style)](@/algorithms/dense-lu-factorization-lapack-style.md)** (1 impl) - CoinUtils
- **[LU Factorization with Forrest-Tomlin Updates](@/algorithms/lu-factorization-with-forrest-tomlin-updates.md)** (1 impl) - Clp
- **[LU factorization with Markowitz pivot selection](@/algorithms/lu-factorization-with-markowitz-pivot-selection.md)** (1 impl) - CoinUtils
- **[Left-looking LU with BTF preprocessing and partial pivoting](@/algorithms/left-looking-lu-with-btf-preprocessing-and-partial.md)** (1 impl) - SuiteSparse
- **[Multifrontal LU with threshold partial pivoting](@/algorithms/multifrontal-lu-with-threshold-partial-pivoting.md)** (1 impl) - SuiteSparse
- **[Sparse LDL' factorization (up-looking)](@/algorithms/sparse-ldl-factorization-up-looking.md)** (1 impl) - SuiteSparse
- **[Sparse LU with Markowitz Pivoting](@/algorithms/sparse-lu-with-markowitz-pivoting.md)** (1 impl) - CoinUtils

## Simplex Method

- **[Bron-Kerbosch with pivoting for weighted cliques](@/algorithms/bron-kerbosch-with-pivoting-for-weighted-cliques.md)** (1 impl) - CoinUtils
- **[Dual Simplex Method](@/algorithms/dual-simplex-method.md)** (1 impl) - Clp
- **[Primal Simplex Method](@/algorithms/primal-simplex-method.md)** (1 impl) - Clp
- **[Simplex Basis Warm Start](@/algorithms/simplex-basis-warm-start.md)** (1 impl) - CoinUtils
- **[Simplex Method for Linear Programming](@/algorithms/simplex-method-for-linear-programming.md)** (1 impl) - Clp
- **[Steepest Edge Dual Pivot Selection](@/algorithms/steepest-edge-dual-pivot-selection.md)** (1 impl) - Clp
- **[Steepest Edge and Devex Primal Pivot Selection](@/algorithms/steepest-edge-and-devex-primal-pivot-selection.md)** (1 impl) - Clp

## Interior Point Methods

- **[Direct interior point NLP solve](@/algorithms/direct-interior-point-nlp-solve.md)** (1 impl) - SHOT
- **[Interior Point Method (Barrier Method)](@/algorithms/interior-point-method-barrier-method.md)** (1 impl) - Clp
- **[Interior Point Method via Ipopt](@/algorithms/interior-point-method-via-ipopt.md)** (1 impl) - Gravity

## Branch and Bound

- **[Adaptive Hybrid Node Selection](@/algorithms/adaptive-hybrid-node-selection.md)** (1 impl) - Cbc
- **[Branch-and-Cut (B&C) for Mixed-Integer Programming](@/algorithms/branch-and-cut-bc-for-mixed-integer-programming.md)** (1 impl) - Cbc
- **[Branch-and-cut with lazy ESH constraints](@/algorithms/branch-and-cut-with-lazy-esh-constraints.md)** (1 impl) - SHOT
- **[Branching Variable Selection Strategies](@/algorithms/branching-variable-selection-strategies.md)** (1 impl) - Cbc
- **[Extended Cutting Plane (Westerlund-Pettersson)](@/algorithms/extended-cutting-plane-westerlund-pettersson.md)** (1 impl) - SHOT
- **[Hot-Start Optimization for Strong Branching](@/algorithms/hot-start-optimization-for-strong-branching.md)** (1 impl) - Clp
- **[Iterative cutting plane for convex minimax](@/algorithms/iterative-cutting-plane-for-convex-minimax.md)** (1 impl) - SHOT
- **[Lift-and-Project Cutting Planes](@/algorithms/lift-and-project-cutting-planes.md)** (1 impl) - Cgl
- **[Price-and-Cut Hybrid (generateVars + generateCuts)](@/algorithms/price-and-cut-hybrid-generatevars-generatecuts.md)** (1 impl) - Dip
- **[Root Node vs. Tree Strategy](@/algorithms/root-node-vs-tree-strategy.md)** (1 impl) - Cbc
- **[Search Tree Management with Priority Heap](@/algorithms/search-tree-management-with-priority-heap.md)** (1 impl) - Cbc
- **[Stern-Brocot tree / mediant search for best rational approximation](@/algorithms/stern-brocot-tree-mediant-search-for-best-rational.md)** (1 impl) - CoinUtils

## Primal Heuristics

- **[Feasibility Pump (FP)](@/algorithms/feasibility-pump-fp.md)** (1 impl) - Cbc
- **[Greedy Cover Heuristic (findGreedyCover)](@/algorithms/greedy-cover-heuristic-findgreedycover.md)** (1 impl) - Cgl
- **[MIP Primal Heuristics Framework](@/algorithms/mip-primal-heuristics-framework.md)** (1 impl) - Cbc

## Conflict Analysis

- **[Clique Storage](@/algorithms/clique-storage.md)** (1 impl) - CoinUtils
- **[Conflict Graph Construction](@/algorithms/conflict-graph-construction.md)** (1 impl) - CoinUtils
- **[Greedy Maximal Clique (greedy_maximal_clique)](@/algorithms/greedy-maximal-clique-greedy_maximal_clique.md)** (1 impl) - Cgl

## Data Structures

- **[Compressed Sparse Column/Row (CSC/CSR) format](@/algorithms/compressed-sparse-columnrow-csccsr-format.md)** (1 impl) - CoinUtils
- **[Dense Vector Storage](@/algorithms/dense-vector-storage.md)** (1 impl) - CoinUtils
- **[Hyper-sparse Computation](@/algorithms/hyper-sparse-computation.md)** (1 impl) - HiGHS
- **[Indexed sparse vector - hybrid sparse/dense storage](@/algorithms/indexed-sparse-vector-hybrid-sparsedense-storage.md)** (1 impl) - CoinUtils
- **[Merge-style sparse dot product](@/algorithms/merge-style-sparse-dot-product.md)** (1 impl) - CoinUtils
- **[Sparse Matrix Operations](@/algorithms/sparse-matrix-operations.md)** (1 impl) - SuiteSparse

## File I/O

- **[LP File Parsing](@/algorithms/lp-file-parsing.md)** (1 impl) - CoinUtils
- **[LP Method Selection (LPMethod enum)](@/algorithms/lp-method-selection-lpmethod-enum.md)** (1 impl) - Cbc
- **[MPS File Parsing](@/algorithms/mps-file-parsing.md)** (1 impl) - CoinUtils

## Other Algorithms

- **[Approximate Minimum Degree (AMD)](@/algorithms/approximate-minimum-degree-amd.md)** (1 impl) - SuiteSparse
- **[Convergence Properties](@/algorithms/convergence-properties.md)** (1 impl) - SHOT
- **[Data Layout Optimization](@/algorithms/data-layout-optimization.md)** (1 impl) - Clp
- **[Design Pattern: Abstract Factory + Strategy](@/algorithms/design-pattern-abstract-factory-strategy.md)** (1 impl) - Osi
- **[Duff's device - Tom Duff's loop unrolling technique that uses switch](@/algorithms/duffs-device-tom-duffs-loop-unrolling-technique-th.md)** (1 impl) - CoinUtils
- **[Duplicate Detection via Random Hashing](@/algorithms/duplicate-detection-via-random-hashing.md)** (1 impl) - CoinUtils
- **[Empty Row/Column Removal](@/algorithms/empty-rowcolumn-removal.md)** (1 impl) - CoinUtils
- **[Essential for Extended Supporting Hyperplane (ESH) method](@/algorithms/essential-for-extended-supporting-hyperplane-esh-m.md)** (1 impl) - SHOT
- **[Extended Supporting Hyperplane (ESH) method adds](@/algorithms/extended-supporting-hyperplane-esh-method-adds.md)** (1 impl) - SHOT
- **[Extended Supporting Hyperplane (Kronqvist 2016)](@/algorithms/extended-supporting-hyperplane-kronqvist-2016.md)** (1 impl) - SHOT
- **[Fixed Variable Removal](@/algorithms/fixed-variable-removal.md)** (1 impl) - CoinUtils
- **[Floating-Point Comparison](@/algorithms/floating-point-comparison.md)** (1 impl) - CoinUtils
- **[Forward mode computes derivatives in the direction of inputs.](@/algorithms/forward-mode-computes-derivatives-in-the-direction.md)** (1 impl) - CppAD
- **[Function Pointer Dispatch (scatterStruct)](@/algorithms/function-pointer-dispatch-scatterstruct.md)** (1 impl) - Clp
- **[Implied Free Variable Detection](@/algorithms/implied-free-variable-detection.md)** (1 impl) - CoinUtils
- **[Integrality Distance Threshold (away_)](@/algorithms/integrality-distance-threshold-away_.md)** (1 impl) - Cgl
- **[Linear Solver Selection (SymLinearSolverFactory)](@/algorithms/linear-solver-selection-symlinearsolverfactory.md)** (1 impl) - Ipopt
- **[MIP Solution Pool (getAllVariableSolutions)](@/algorithms/mip-solution-pool-getallvariablesolutions.md)** (1 impl) - SHOT
- **[MIP Solving](@/algorithms/mip-solving.md)** (1 impl) - HiGHS
- **[MIP Start (Warm Starting) (addMIPStart)](@/algorithms/mip-start-warm-starting-addmipstart.md)** (1 impl) - SHOT
- **[Message Handling System](@/algorithms/message-handling-system.md)** (1 impl) - CoinUtils
- **[Model Construction Interface](@/algorithms/model-construction-interface.md)** (1 impl) - CoinUtils
- **[Monotone Min-Heap](@/algorithms/monotone-min-heap.md)** (1 impl) - CoinUtils
- **[Objective Propagation](@/algorithms/objective-propagation.md)** (1 impl) - HiGHS
- **[Online Active Set Strategy](@/algorithms/online-active-set-strategy.md)** (1 impl) - qpOASES
- **[Online Active Set Strategy - works well for model](@/algorithms/online-active-set-strategy-works-well-for-model.md)** (1 impl) - qpOASES
- **[Operator overloading records a "tape" of operations.](@/algorithms/operator-overloading-records-a-tape-of-operations.md)** (1 impl) - CppAD
- **[PAMI - Parallel Minor Iterations (iterateMulti)](@/algorithms/pami-parallel-minor-iterations-iteratemulti.md)** (1 impl) - HiGHS
- **[Parallel Array Sorting](@/algorithms/parallel-array-sorting.md)** (1 impl) - CoinUtils
- **[Preprocessing Pipeline (IPPMode)](@/algorithms/preprocessing-pipeline-ippmode.md)** (1 impl) - Cbc
- **[Reverse mode automatic differentiation](@/algorithms/reverse-mode-automatic-differentiation.md)** (1 impl) - ADOL-C
- **[Row Classification (determineOneRowType)](@/algorithms/row-classification-determineonerowtype.md)** (1 impl) - Cgl
- **[SYMAMD (Symmetric AMD using COLAMD)](@/algorithms/symamd-symmetric-amd-using-colamd.md)** (1 impl) - SuiteSparse
- **[Solves KKT conditions directly when active set is known.](@/algorithms/solves-kkt-conditions-directly-when-active-set-is-.md)** (1 impl) - qpOASES
- **[Sparsification (sparsify)](@/algorithms/sparsification-sparsify.md)** (1 impl) - HiGHS
- **[Sparsity Pattern Extraction (getConstraintsJacobianSparsityPattern)](@/algorithms/sparsity-pattern-extraction-getconstraintsjacobian.md)** (1 impl) - SHOT
- **[Standard ESH outer approximation](@/algorithms/standard-esh-outer-approximation.md)** (1 impl) - SHOT
- **[Tarjan's Strongly Connected Components](@/algorithms/tarjans-strongly-connected-components.md)** (1 impl) - SuiteSparse
- **[Update/Downdate (rank-k modification)](@/algorithms/updatedowndate-rank-k-modification.md)** (1 impl) - SuiteSparse
- **[Warm Starting (setStartingPoint)](@/algorithms/warm-starting-setstartingpoint.md)** (1 impl) - SHOT
- **[Warm-Starting Protocol](@/algorithms/warm-starting-protocol.md)** (1 impl) - Clp
