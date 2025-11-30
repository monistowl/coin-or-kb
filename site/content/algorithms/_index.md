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

- **[Bound Tightening](/algorithms/bound-tightening/)** (1 impl) - CoinUtils
- **[Branch-and-Bound Node Management](/algorithms/branch-and-bound-node-management/)** (1 impl) - Cbc
- **[Branch-and-Bound Tree Search](/algorithms/branch-and-bound-tree-search/)** (1 impl) - CoinUtils
- **[Direct MIQCQP branch-and-bound](/algorithms/direct-miqcqp-branch-and-bound/)** (1 impl) - SHOT
- **[Doubleton Elimination](/algorithms/doubleton-elimination/)** (1 impl) - CoinUtils
- **[Dual Bound Propagation](/algorithms/dual-bound-propagation/)** (1 impl) - CoinUtils
- **[Forcing Constraint Detection](/algorithms/forcing-constraint-detection/)** (1 impl) - CoinUtils
- **[LP Presolve (Preprocessing)](/algorithms/lp-presolve-preprocessing/)** (1 impl) - Clp
- **[LP Presolve - simplifies LP before solving via reversible transforms](/algorithms/lp-presolve-simplifies-lp-before-solving-via-rever/)** (1 impl) - CoinUtils
- **[Optimization-Based Bound Tightening](/algorithms/optimization-based-bound-tightening/)** (1 impl) - SHOT
- **[Singleton Column/Row Elimination](/algorithms/singleton-columnrow-elimination/)** (1 impl) - CoinUtils
- **[Slack Elimination (eliminateSlack)](/algorithms/slack-elimination-eliminateslack/)** (1 impl) - Cgl
- **[Tripleton Elimination](/algorithms/tripleton-elimination/)** (1 impl) - CoinUtils
- **[Variable Substitution (Non-Singleton)](/algorithms/variable-substitution-non-singleton/)** (1 impl) - CoinUtils

## Matrix Factorization

- **[ABC (Alternative Basis Code) LU Factorization](/algorithms/abc-alternative-basis-code-lu-factorization/)** (1 impl) - Clp
- **[Dense LU Factorization (LAPACK-style)](/algorithms/dense-lu-factorization-lapack-style/)** (1 impl) - CoinUtils
- **[LU Factorization with Forrest-Tomlin Updates](/algorithms/lu-factorization-with-forrest-tomlin-updates/)** (1 impl) - Clp
- **[LU factorization with Markowitz pivot selection](/algorithms/lu-factorization-with-markowitz-pivot-selection/)** (1 impl) - CoinUtils
- **[Left-looking LU with BTF preprocessing and partial pivoting](/algorithms/left-looking-lu-with-btf-preprocessing-and-partial/)** (1 impl) - SuiteSparse
- **[Multifrontal LU with threshold partial pivoting](/algorithms/multifrontal-lu-with-threshold-partial-pivoting/)** (1 impl) - SuiteSparse
- **[Sparse LDL' factorization (up-looking)](/algorithms/sparse-ldl-factorization-up-looking/)** (1 impl) - SuiteSparse
- **[Sparse LU with Markowitz Pivoting](/algorithms/sparse-lu-with-markowitz-pivoting/)** (1 impl) - CoinUtils

## Simplex Method

- **[Bron-Kerbosch with pivoting for weighted cliques](/algorithms/bron-kerbosch-with-pivoting-for-weighted-cliques/)** (1 impl) - CoinUtils
- **[Dual Simplex Method](/algorithms/dual-simplex-method/)** (1 impl) - Clp
- **[Primal Simplex Method](/algorithms/primal-simplex-method/)** (1 impl) - Clp
- **[Simplex Basis Warm Start](/algorithms/simplex-basis-warm-start/)** (1 impl) - CoinUtils
- **[Simplex Method for Linear Programming](/algorithms/simplex-method-for-linear-programming/)** (1 impl) - Clp
- **[Steepest Edge Dual Pivot Selection](/algorithms/steepest-edge-dual-pivot-selection/)** (1 impl) - Clp
- **[Steepest Edge and Devex Primal Pivot Selection](/algorithms/steepest-edge-and-devex-primal-pivot-selection/)** (1 impl) - Clp

## Interior Point Methods

- **[Direct interior point NLP solve](/algorithms/direct-interior-point-nlp-solve/)** (1 impl) - SHOT
- **[Interior Point Method (Barrier Method)](/algorithms/interior-point-method-barrier-method/)** (1 impl) - Clp
- **[Interior Point Method via Ipopt](/algorithms/interior-point-method-via-ipopt/)** (1 impl) - Gravity

## Branch and Bound

- **[Adaptive Hybrid Node Selection](/algorithms/adaptive-hybrid-node-selection/)** (1 impl) - Cbc
- **[Branch-and-Cut (B&C) for Mixed-Integer Programming](/algorithms/branch-and-cut-bc-for-mixed-integer-programming/)** (1 impl) - Cbc
- **[Branch-and-cut with lazy ESH constraints](/algorithms/branch-and-cut-with-lazy-esh-constraints/)** (1 impl) - SHOT
- **[Branching Variable Selection Strategies](/algorithms/branching-variable-selection-strategies/)** (1 impl) - Cbc
- **[Extended Cutting Plane (Westerlund-Pettersson)](/algorithms/extended-cutting-plane-westerlund-pettersson/)** (1 impl) - SHOT
- **[Hot-Start Optimization for Strong Branching](/algorithms/hot-start-optimization-for-strong-branching/)** (1 impl) - Clp
- **[Iterative cutting plane for convex minimax](/algorithms/iterative-cutting-plane-for-convex-minimax/)** (1 impl) - SHOT
- **[Lift-and-Project Cutting Planes](/algorithms/lift-and-project-cutting-planes/)** (1 impl) - Cgl
- **[Price-and-Cut Hybrid (generateVars + generateCuts)](/algorithms/price-and-cut-hybrid-generatevars-generatecuts/)** (1 impl) - Dip
- **[Root Node vs. Tree Strategy](/algorithms/root-node-vs-tree-strategy/)** (1 impl) - Cbc
- **[Search Tree Management with Priority Heap](/algorithms/search-tree-management-with-priority-heap/)** (1 impl) - Cbc
- **[Stern-Brocot tree / mediant search for best rational approximation](/algorithms/stern-brocot-tree-mediant-search-for-best-rational/)** (1 impl) - CoinUtils

## Primal Heuristics

- **[Feasibility Pump (FP)](/algorithms/feasibility-pump-fp/)** (1 impl) - Cbc
- **[Greedy Cover Heuristic (findGreedyCover)](/algorithms/greedy-cover-heuristic-findgreedycover/)** (1 impl) - Cgl
- **[MIP Primal Heuristics Framework](/algorithms/mip-primal-heuristics-framework/)** (1 impl) - Cbc

## Conflict Analysis

- **[Clique Storage](/algorithms/clique-storage/)** (1 impl) - CoinUtils
- **[Conflict Graph Construction](/algorithms/conflict-graph-construction/)** (1 impl) - CoinUtils
- **[Greedy Maximal Clique (greedy_maximal_clique)](/algorithms/greedy-maximal-clique-greedy_maximal_clique/)** (1 impl) - Cgl

## Data Structures

- **[Compressed Sparse Column/Row (CSC/CSR) format](/algorithms/compressed-sparse-columnrow-csccsr-format/)** (1 impl) - CoinUtils
- **[Dense Vector Storage](/algorithms/dense-vector-storage/)** (1 impl) - CoinUtils
- **[Hyper-sparse Computation](/algorithms/hyper-sparse-computation/)** (1 impl) - HiGHS
- **[Indexed sparse vector - hybrid sparse/dense storage](/algorithms/indexed-sparse-vector-hybrid-sparsedense-storage/)** (1 impl) - CoinUtils
- **[Merge-style sparse dot product](/algorithms/merge-style-sparse-dot-product/)** (1 impl) - CoinUtils
- **[Sparse Matrix Operations](/algorithms/sparse-matrix-operations/)** (1 impl) - SuiteSparse

## File I/O

- **[LP File Parsing](/algorithms/lp-file-parsing/)** (1 impl) - CoinUtils
- **[LP Method Selection (LPMethod enum)](/algorithms/lp-method-selection-lpmethod-enum/)** (1 impl) - Cbc
- **[MPS File Parsing](/algorithms/mps-file-parsing/)** (1 impl) - CoinUtils

## Other Algorithms

- **[Approximate Minimum Degree (AMD)](/algorithms/approximate-minimum-degree-amd/)** (1 impl) - SuiteSparse
- **[Convergence Properties](/algorithms/convergence-properties/)** (1 impl) - SHOT
- **[Data Layout Optimization](/algorithms/data-layout-optimization/)** (1 impl) - Clp
- **[Design Pattern: Abstract Factory + Strategy](/algorithms/design-pattern-abstract-factory-strategy/)** (1 impl) - Osi
- **[Duff's device - Tom Duff's loop unrolling technique that uses switch](/algorithms/duffs-device-tom-duffs-loop-unrolling-technique-th/)** (1 impl) - CoinUtils
- **[Duplicate Detection via Random Hashing](/algorithms/duplicate-detection-via-random-hashing/)** (1 impl) - CoinUtils
- **[Empty Row/Column Removal](/algorithms/empty-rowcolumn-removal/)** (1 impl) - CoinUtils
- **[Essential for Extended Supporting Hyperplane (ESH) method](/algorithms/essential-for-extended-supporting-hyperplane-esh-m/)** (1 impl) - SHOT
- **[Extended Supporting Hyperplane (ESH) method adds](/algorithms/extended-supporting-hyperplane-esh-method-adds/)** (1 impl) - SHOT
- **[Extended Supporting Hyperplane (Kronqvist 2016)](/algorithms/extended-supporting-hyperplane-kronqvist-2016/)** (1 impl) - SHOT
- **[Fixed Variable Removal](/algorithms/fixed-variable-removal/)** (1 impl) - CoinUtils
- **[Floating-Point Comparison](/algorithms/floating-point-comparison/)** (1 impl) - CoinUtils
- **[Forward mode computes derivatives in the direction of inputs.](/algorithms/forward-mode-computes-derivatives-in-the-direction/)** (1 impl) - CppAD
- **[Function Pointer Dispatch (scatterStruct)](/algorithms/function-pointer-dispatch-scatterstruct/)** (1 impl) - Clp
- **[Implied Free Variable Detection](/algorithms/implied-free-variable-detection/)** (1 impl) - CoinUtils
- **[Integrality Distance Threshold (away_)](/algorithms/integrality-distance-threshold-away_/)** (1 impl) - Cgl
- **[Linear Solver Selection (SymLinearSolverFactory)](/algorithms/linear-solver-selection-symlinearsolverfactory/)** (1 impl) - Ipopt
- **[MIP Solution Pool (getAllVariableSolutions)](/algorithms/mip-solution-pool-getallvariablesolutions/)** (1 impl) - SHOT
- **[MIP Solving](/algorithms/mip-solving/)** (1 impl) - HiGHS
- **[MIP Start (Warm Starting) (addMIPStart)](/algorithms/mip-start-warm-starting-addmipstart/)** (1 impl) - SHOT
- **[Message Handling System](/algorithms/message-handling-system/)** (1 impl) - CoinUtils
- **[Model Construction Interface](/algorithms/model-construction-interface/)** (1 impl) - CoinUtils
- **[Monotone Min-Heap](/algorithms/monotone-min-heap/)** (1 impl) - CoinUtils
- **[Objective Propagation](/algorithms/objective-propagation/)** (1 impl) - HiGHS
- **[Online Active Set Strategy](/algorithms/online-active-set-strategy/)** (1 impl) - qpOASES
- **[Online Active Set Strategy - works well for model](/algorithms/online-active-set-strategy-works-well-for-model/)** (1 impl) - qpOASES
- **[Operator overloading records a "tape" of operations.](/algorithms/operator-overloading-records-a-tape-of-operations/)** (1 impl) - CppAD
- **[PAMI - Parallel Minor Iterations (iterateMulti)](/algorithms/pami-parallel-minor-iterations-iteratemulti/)** (1 impl) - HiGHS
- **[Parallel Array Sorting](/algorithms/parallel-array-sorting/)** (1 impl) - CoinUtils
- **[Preprocessing Pipeline (IPPMode)](/algorithms/preprocessing-pipeline-ippmode/)** (1 impl) - Cbc
- **[Reverse mode automatic differentiation](/algorithms/reverse-mode-automatic-differentiation/)** (1 impl) - ADOL-C
- **[Row Classification (determineOneRowType)](/algorithms/row-classification-determineonerowtype/)** (1 impl) - Cgl
- **[SYMAMD (Symmetric AMD using COLAMD)](/algorithms/symamd-symmetric-amd-using-colamd/)** (1 impl) - SuiteSparse
- **[Solves KKT conditions directly when active set is known.](/algorithms/solves-kkt-conditions-directly-when-active-set-is-/)** (1 impl) - qpOASES
- **[Sparsification (sparsify)](/algorithms/sparsification-sparsify/)** (1 impl) - HiGHS
- **[Sparsity Pattern Extraction (getConstraintsJacobianSparsityPattern)](/algorithms/sparsity-pattern-extraction-getconstraintsjacobian/)** (1 impl) - SHOT
- **[Standard ESH outer approximation](/algorithms/standard-esh-outer-approximation/)** (1 impl) - SHOT
- **[Tarjan's Strongly Connected Components](/algorithms/tarjans-strongly-connected-components/)** (1 impl) - SuiteSparse
- **[Update/Downdate (rank-k modification)](/algorithms/updatedowndate-rank-k-modification/)** (1 impl) - SuiteSparse
- **[Warm Starting (setStartingPoint)](/algorithms/warm-starting-setstartingpoint/)** (1 impl) - SHOT
- **[Warm-Starting Protocol](/algorithms/warm-starting-protocol/)** (1 impl) - Clp
