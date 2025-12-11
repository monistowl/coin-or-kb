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

- **[Bound Tightening](/coin-or-kb/algorithms/bound-tightening/)** (1 impl) - CoinUtils
- **[Branch-and-Bound Node Management](/coin-or-kb/algorithms/branch-and-bound-node-management/)** (1 impl) - Cbc
- **[Branch-and-Bound Tree Search](/coin-or-kb/algorithms/branch-and-bound-tree-search/)** (1 impl) - CoinUtils
- **[Direct MIQCQP branch-and-bound](/coin-or-kb/algorithms/direct-miqcqp-branch-and-bound/)** (1 impl) - SHOT
- **[Doubleton Elimination](/coin-or-kb/algorithms/doubleton-elimination/)** (1 impl) - CoinUtils
- **[Dual Bound Propagation](/coin-or-kb/algorithms/dual-bound-propagation/)** (1 impl) - CoinUtils
- **[Forcing Constraint Detection](/coin-or-kb/algorithms/forcing-constraint-detection/)** (1 impl) - CoinUtils
- **[LP Presolve (Preprocessing)](/coin-or-kb/algorithms/lp-presolve-preprocessing/)** (1 impl) - Clp
- **[LP Presolve - simplifies LP before solving via reversible transforms](/coin-or-kb/algorithms/lp-presolve-simplifies-lp-before-solving-via-rever/)** (1 impl) - CoinUtils
- **[Optimization-Based Bound Tightening](/coin-or-kb/algorithms/optimization-based-bound-tightening/)** (1 impl) - SHOT
- **[Singleton Column/Row Elimination](/coin-or-kb/algorithms/singleton-columnrow-elimination/)** (1 impl) - CoinUtils
- **[Slack Elimination (eliminateSlack)](/coin-or-kb/algorithms/slack-elimination-eliminateslack/)** (1 impl) - Cgl
- **[Tripleton Elimination](/coin-or-kb/algorithms/tripleton-elimination/)** (1 impl) - CoinUtils
- **[Variable Substitution (Non-Singleton)](/coin-or-kb/algorithms/variable-substitution-non-singleton/)** (1 impl) - CoinUtils

## Matrix Factorization

- **[ABC (Alternative Basis Code) LU Factorization](/coin-or-kb/algorithms/abc-alternative-basis-code-lu-factorization/)** (1 impl) - Clp
- **[Dense LU Factorization (LAPACK-style)](/coin-or-kb/algorithms/dense-lu-factorization-lapack-style/)** (1 impl) - CoinUtils
- **[LU Factorization with Forrest-Tomlin Updates](/coin-or-kb/algorithms/lu-factorization-with-forrest-tomlin-updates/)** (1 impl) - Clp
- **[LU factorization with Markowitz pivot selection](/coin-or-kb/algorithms/lu-factorization-with-markowitz-pivot-selection/)** (1 impl) - CoinUtils
- **[Left-looking LU with BTF preprocessing and partial pivoting](/coin-or-kb/algorithms/left-looking-lu-with-btf-preprocessing-and-partial/)** (1 impl) - SuiteSparse
- **[Multifrontal LU with threshold partial pivoting](/coin-or-kb/algorithms/multifrontal-lu-with-threshold-partial-pivoting/)** (1 impl) - SuiteSparse
- **[Sparse LDL' factorization (up-looking)](/coin-or-kb/algorithms/sparse-ldl-factorization-up-looking/)** (1 impl) - SuiteSparse
- **[Sparse LU with Markowitz Pivoting](/coin-or-kb/algorithms/sparse-lu-with-markowitz-pivoting/)** (1 impl) - CoinUtils

## Simplex Method

- **[Bron-Kerbosch with pivoting for weighted cliques](/coin-or-kb/algorithms/bron-kerbosch-with-pivoting-for-weighted-cliques/)** (1 impl) - CoinUtils
- **[Dual Simplex Method](/coin-or-kb/algorithms/dual-simplex-method/)** (1 impl) - Clp
- **[Primal Simplex Method](/coin-or-kb/algorithms/primal-simplex-method/)** (1 impl) - Clp
- **[Simplex Basis Warm Start](/coin-or-kb/algorithms/simplex-basis-warm-start/)** (1 impl) - CoinUtils
- **[Simplex Method for Linear Programming](/coin-or-kb/algorithms/simplex-method-for-linear-programming/)** (1 impl) - Clp
- **[Steepest Edge Dual Pivot Selection](/coin-or-kb/algorithms/steepest-edge-dual-pivot-selection/)** (1 impl) - Clp
- **[Steepest Edge and Devex Primal Pivot Selection](/coin-or-kb/algorithms/steepest-edge-and-devex-primal-pivot-selection/)** (1 impl) - Clp

## Interior Point Methods

- **[Direct interior point NLP solve](/coin-or-kb/algorithms/direct-interior-point-nlp-solve/)** (1 impl) - SHOT
- **[Interior Point Method (Barrier Method)](/coin-or-kb/algorithms/interior-point-method-barrier-method/)** (1 impl) - Clp
- **[Interior Point Method via Ipopt](/coin-or-kb/algorithms/interior-point-method-via-ipopt/)** (1 impl) - Gravity

## Branch and Bound

- **[Adaptive Hybrid Node Selection](/coin-or-kb/algorithms/adaptive-hybrid-node-selection/)** (1 impl) - Cbc
- **[Branch-and-Cut (B&C) for Mixed-Integer Programming](/coin-or-kb/algorithms/branch-and-cut-bc-for-mixed-integer-programming/)** (1 impl) - Cbc
- **[Branch-and-cut with lazy ESH constraints](/coin-or-kb/algorithms/branch-and-cut-with-lazy-esh-constraints/)** (1 impl) - SHOT
- **[Branching Variable Selection Strategies](/coin-or-kb/algorithms/branching-variable-selection-strategies/)** (1 impl) - Cbc
- **[Extended Cutting Plane (Westerlund-Pettersson)](/coin-or-kb/algorithms/extended-cutting-plane-westerlund-pettersson/)** (1 impl) - SHOT
- **[Hot-Start Optimization for Strong Branching](/coin-or-kb/algorithms/hot-start-optimization-for-strong-branching/)** (1 impl) - Clp
- **[Iterative cutting plane for convex minimax](/coin-or-kb/algorithms/iterative-cutting-plane-for-convex-minimax/)** (1 impl) - SHOT
- **[Lift-and-Project Cutting Planes](/coin-or-kb/algorithms/lift-and-project-cutting-planes/)** (1 impl) - Cgl
- **[Price-and-Cut Hybrid (generateVars + generateCuts)](/coin-or-kb/algorithms/price-and-cut-hybrid-generatevars-generatecuts/)** (1 impl) - Dip
- **[Root Node vs. Tree Strategy](/coin-or-kb/algorithms/root-node-vs-tree-strategy/)** (1 impl) - Cbc
- **[Search Tree Management with Priority Heap](/coin-or-kb/algorithms/search-tree-management-with-priority-heap/)** (1 impl) - Cbc
- **[Stern-Brocot tree / mediant search for best rational approximation](/coin-or-kb/algorithms/stern-brocot-tree-mediant-search-for-best-rational/)** (1 impl) - CoinUtils

## Primal Heuristics

- **[Feasibility Pump (FP)](/coin-or-kb/algorithms/feasibility-pump-fp/)** (1 impl) - Cbc
- **[Greedy Cover Heuristic (findGreedyCover)](/coin-or-kb/algorithms/greedy-cover-heuristic-findgreedycover/)** (1 impl) - Cgl
- **[MIP Primal Heuristics Framework](/coin-or-kb/algorithms/mip-primal-heuristics-framework/)** (1 impl) - Cbc

## Conflict Analysis

- **[Clique Storage](/coin-or-kb/algorithms/clique-storage/)** (1 impl) - CoinUtils
- **[Conflict Graph Construction](/coin-or-kb/algorithms/conflict-graph-construction/)** (1 impl) - CoinUtils
- **[Greedy Maximal Clique (greedy_maximal_clique)](/coin-or-kb/algorithms/greedy-maximal-clique-greedy_maximal_clique/)** (1 impl) - Cgl

## Data Structures

- **[Compressed Sparse Column/Row (CSC/CSR) format](/coin-or-kb/algorithms/compressed-sparse-columnrow-csccsr-format/)** (1 impl) - CoinUtils
- **[Dense Vector Storage](/coin-or-kb/algorithms/dense-vector-storage/)** (1 impl) - CoinUtils
- **[Hyper-sparse Computation](/coin-or-kb/algorithms/hyper-sparse-computation/)** (1 impl) - HiGHS
- **[Indexed sparse vector - hybrid sparse/dense storage](/coin-or-kb/algorithms/indexed-sparse-vector-hybrid-sparsedense-storage/)** (1 impl) - CoinUtils
- **[Merge-style sparse dot product](/coin-or-kb/algorithms/merge-style-sparse-dot-product/)** (1 impl) - CoinUtils
- **[Sparse Matrix Operations](/coin-or-kb/algorithms/sparse-matrix-operations/)** (1 impl) - SuiteSparse

## File I/O

- **[LP File Parsing](/coin-or-kb/algorithms/lp-file-parsing/)** (1 impl) - CoinUtils
- **[LP Method Selection (LPMethod enum)](/coin-or-kb/algorithms/lp-method-selection-lpmethod-enum/)** (1 impl) - Cbc
- **[MPS File Parsing](/coin-or-kb/algorithms/mps-file-parsing/)** (1 impl) - CoinUtils

## Other Algorithms

- **[Approximate Minimum Degree (AMD)](/coin-or-kb/algorithms/approximate-minimum-degree-amd/)** (1 impl) - SuiteSparse
- **[Convergence Properties](/coin-or-kb/algorithms/convergence-properties/)** (1 impl) - SHOT
- **[Data Layout Optimization](/coin-or-kb/algorithms/data-layout-optimization/)** (1 impl) - Clp
- **[Design Pattern: Abstract Factory + Strategy](/coin-or-kb/algorithms/design-pattern-abstract-factory-strategy/)** (1 impl) - Osi
- **[Duff's device - Tom Duff's loop unrolling technique that uses switch](/coin-or-kb/algorithms/duffs-device-tom-duffs-loop-unrolling-technique-th/)** (1 impl) - CoinUtils
- **[Duplicate Detection via Random Hashing](/coin-or-kb/algorithms/duplicate-detection-via-random-hashing/)** (1 impl) - CoinUtils
- **[Empty Row/Column Removal](/coin-or-kb/algorithms/empty-rowcolumn-removal/)** (1 impl) - CoinUtils
- **[Essential for Extended Supporting Hyperplane (ESH) method](/coin-or-kb/algorithms/essential-for-extended-supporting-hyperplane-esh-m/)** (1 impl) - SHOT
- **[Extended Supporting Hyperplane (ESH) method adds](/coin-or-kb/algorithms/extended-supporting-hyperplane-esh-method-adds/)** (1 impl) - SHOT
- **[Extended Supporting Hyperplane (Kronqvist 2016)](/coin-or-kb/algorithms/extended-supporting-hyperplane-kronqvist-2016/)** (1 impl) - SHOT
- **[Fixed Variable Removal](/coin-or-kb/algorithms/fixed-variable-removal/)** (1 impl) - CoinUtils
- **[Floating-Point Comparison](/coin-or-kb/algorithms/floating-point-comparison/)** (1 impl) - CoinUtils
- **[Forward mode computes derivatives in the direction of inputs.](/coin-or-kb/algorithms/forward-mode-computes-derivatives-in-the-direction/)** (1 impl) - CppAD
- **[Function Pointer Dispatch (scatterStruct)](/coin-or-kb/algorithms/function-pointer-dispatch-scatterstruct/)** (1 impl) - Clp
- **[Implied Free Variable Detection](/coin-or-kb/algorithms/implied-free-variable-detection/)** (1 impl) - CoinUtils
- **[Integrality Distance Threshold (away_)](/coin-or-kb/algorithms/integrality-distance-threshold-away_/)** (1 impl) - Cgl
- **[Linear Solver Selection (SymLinearSolverFactory)](/coin-or-kb/algorithms/linear-solver-selection-symlinearsolverfactory/)** (1 impl) - Ipopt
- **[MIP Solution Pool (getAllVariableSolutions)](/coin-or-kb/algorithms/mip-solution-pool-getallvariablesolutions/)** (1 impl) - SHOT
- **[MIP Solving](/coin-or-kb/algorithms/mip-solving/)** (1 impl) - HiGHS
- **[MIP Start (Warm Starting) (addMIPStart)](/coin-or-kb/algorithms/mip-start-warm-starting-addmipstart/)** (1 impl) - SHOT
- **[Message Handling System](/coin-or-kb/algorithms/message-handling-system/)** (1 impl) - CoinUtils
- **[Model Construction Interface](/coin-or-kb/algorithms/model-construction-interface/)** (1 impl) - CoinUtils
- **[Monotone Min-Heap](/coin-or-kb/algorithms/monotone-min-heap/)** (1 impl) - CoinUtils
- **[Objective Propagation](/coin-or-kb/algorithms/objective-propagation/)** (1 impl) - HiGHS
- **[Online Active Set Strategy](/coin-or-kb/algorithms/online-active-set-strategy/)** (1 impl) - qpOASES
- **[Online Active Set Strategy - works well for model](/coin-or-kb/algorithms/online-active-set-strategy-works-well-for-model/)** (1 impl) - qpOASES
- **[Operator overloading records a "tape" of operations.](/coin-or-kb/algorithms/operator-overloading-records-a-tape-of-operations/)** (1 impl) - CppAD
- **[PAMI - Parallel Minor Iterations (iterateMulti)](/coin-or-kb/algorithms/pami-parallel-minor-iterations-iteratemulti/)** (1 impl) - HiGHS
- **[Parallel Array Sorting](/coin-or-kb/algorithms/parallel-array-sorting/)** (1 impl) - CoinUtils
- **[Preprocessing Pipeline (IPPMode)](/coin-or-kb/algorithms/preprocessing-pipeline-ippmode/)** (1 impl) - Cbc
- **[Reverse mode automatic differentiation](/coin-or-kb/algorithms/reverse-mode-automatic-differentiation/)** (1 impl) - ADOL-C
- **[Row Classification (determineOneRowType)](/coin-or-kb/algorithms/row-classification-determineonerowtype/)** (1 impl) - Cgl
- **[SYMAMD (Symmetric AMD using COLAMD)](/coin-or-kb/algorithms/symamd-symmetric-amd-using-colamd/)** (1 impl) - SuiteSparse
- **[Solves KKT conditions directly when active set is known.](/coin-or-kb/algorithms/solves-kkt-conditions-directly-when-active-set-is-/)** (1 impl) - qpOASES
- **[Sparsification (sparsify)](/coin-or-kb/algorithms/sparsification-sparsify/)** (1 impl) - HiGHS
- **[Sparsity Pattern Extraction (getConstraintsJacobianSparsityPattern)](/coin-or-kb/algorithms/sparsity-pattern-extraction-getconstraintsjacobian/)** (1 impl) - SHOT
- **[Standard ESH outer approximation](/coin-or-kb/algorithms/standard-esh-outer-approximation/)** (1 impl) - SHOT
- **[Tarjan's Strongly Connected Components](/coin-or-kb/algorithms/tarjans-strongly-connected-components/)** (1 impl) - SuiteSparse
- **[Update/Downdate (rank-k modification)](/coin-or-kb/algorithms/updatedowndate-rank-k-modification/)** (1 impl) - SuiteSparse
- **[Warm Starting (setStartingPoint)](/coin-or-kb/algorithms/warm-starting-setstartingpoint/)** (1 impl) - SHOT
- **[Warm-Starting Protocol](/coin-or-kb/algorithms/warm-starting-protocol/)** (1 impl) - Clp
