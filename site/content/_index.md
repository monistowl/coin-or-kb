+++
title = "COIN-OR Knowledge Base"
description = "Annotated documentation for optimization solver libraries"
template = "index.html"
+++

# COIN-OR Knowledge Base

Semantically annotated documentation for the [COIN-OR](https://www.coin-or.org/) open-source optimization stack. Find algorithm details, mathematical formulations, complexity analysis, and academic references — all extracted from annotated C++ headers.

<div class="quick-nav">
<a href="libraries/coinutils/" class="nav-card">
<strong>Browse CoinUtils</strong>
<span>122 foundation classes</span>
</a>
<a href="api/index.json" class="nav-card">
<strong>JSON API</strong>
<span>Machine-readable docs</span>
</a>
<a href="https://github.com/monistowl/coin-or-kb" class="nav-card">
<strong>Source Code</strong>
<span>Annotations on GitHub</span>
</a>
</div>

---

## Browse by Topic

### Matrix & Vector Operations
Core sparse data structures used throughout the solver stack.

| Class | Description |
|-------|-------------|
| [CoinPackedMatrix](@/libraries/coinutils/CoinPackedMatrix.md) | Column-major sparse matrix with efficient column operations |
| [CoinIndexedVector](@/libraries/coinutils/CoinIndexedVector.md) | Sparse vector with O(1) index lookup for basis operations |
| [CoinDenseVector](@/libraries/coinutils/CoinDenseVector.md) | Dense vector for small, frequently-accessed data |
| [CoinShallowPackedVector](@/libraries/coinutils/CoinShallowPackedVector.md) | Non-owning view into packed vector data |

### LU Factorization
Basis matrix factorization for the simplex method.

| Class | Description |
|-------|-------------|
| [CoinFactorization](@/libraries/coinutils/CoinFactorization.md) | **Sparse LU** with Markowitz pivoting, Forrest-Tomlin updates, FTRAN/BTRAN |
| [CoinDenseFactorization](@/libraries/coinutils/CoinDenseFactorization.md) | Dense factorization for small basis matrices |
| [CoinSimpFactorization](@/libraries/coinutils/CoinSimpFactorization.md) | Simplified factorization interface |
| [CoinOslFactorization](@/libraries/coinutils/CoinOslFactorization.md) | OSL-derived factorization routines |

### Presolve & Problem Reduction
Simplify problems before solving to improve performance.

| Class | Description |
|-------|-------------|
| [CoinPresolveMatrix](@/libraries/coinutils/CoinPresolveMatrix.md) | Matrix representation during presolve transformations |
| [CoinPostsolveMatrix](@/libraries/coinutils/CoinPostsolveMatrix.md) | Restore original solution after presolve |
| [CoinPresolveAction](@/libraries/coinutils/CoinPresolveAction.md) | Base class for all presolve operations |
| [doubleton_action](@/libraries/coinutils/doubleton_action.md) | Eliminate doubleton rows |
| [dupcol_action](@/libraries/coinutils/dupcol_action.md) | Remove duplicate columns |

### File I/O
Read and write optimization problem formats.

| Class | Description |
|-------|-------------|
| [CoinMpsIO](@/libraries/coinutils/CoinMpsIO.md) | MPS file format reader/writer (industry standard) |
| [CoinLpIO](@/libraries/coinutils/CoinLpIO.md) | LP file format reader/writer (CPLEX-style) |
| [CoinFileInput](@/libraries/coinutils/CoinFileInput.md) | Compressed file input (gzip support) |
| [CoinModel](@/libraries/coinutils/CoinModel.md) | In-memory problem builder |

### Warm Starting
Save and restore solver state for re-optimization.

| Class | Description |
|-------|-------------|
| [CoinWarmStart](@/libraries/coinutils/CoinWarmStart.md) | Base interface for warm start information |
| [CoinWarmStartBasis](@/libraries/coinutils/CoinWarmStartBasis.md) | Simplex basis status (structural + artificial) |
| [CoinWarmStartDual](@/libraries/coinutils/CoinWarmStartDual.md) | Dual variable values |
| [CoinWarmStartPrimalDual](@/libraries/coinutils/CoinWarmStartPrimalDual.md) | Combined primal and dual values |

### Graph Algorithms
Conflict graphs and clique detection for MIP.

| Class | Description |
|-------|-------------|
| [CoinConflictGraph](@/libraries/coinutils/CoinConflictGraph.md) | Variable conflict relationships |
| [CoinBronKerbosch](@/libraries/coinutils/CoinBronKerbosch.md) | Maximal clique enumeration |
| [CoinCliqueList](@/libraries/coinutils/CoinCliqueList.md) | Collection of cliques for cut generation |
| [CoinShortestPath](@/libraries/coinutils/CoinShortestPath.md) | Shortest path algorithms |

### Search Trees
Branch-and-bound tree management.

| Class | Description |
|-------|-------------|
| [CoinSearchTree](@/libraries/coinutils/CoinSearchTree.md) | Generic search tree container |
| [CoinSearchTreeCompareBest](@/libraries/coinutils/CoinSearchTreeCompareBest.md) | Best-first node selection |
| [CoinSearchTreeCompareDepth](@/libraries/coinutils/CoinSearchTreeCompareDepth.md) | Depth-first node selection |
| [CoinSearchTreeCompareBreadth](@/libraries/coinutils/CoinSearchTreeCompareBreadth.md) | Breadth-first node selection |

---

## Library Layers

COIN-OR is organized in dependency layers. Higher layers build on lower ones.

<div class="layer-diagram">
<div class="layer layer-4">
<strong>Layer 4: Applications</strong>
<span>SHOT, OS — Global optimization, web services</span>
</div>
<div class="layer layer-3">
<strong>Layer 3: MINLP</strong>
<span>Bonmin, Couenne — Mixed-integer nonlinear</span>
</div>
<div class="layer layer-2">
<strong>Layer 2: MIP & NLP</strong>
<span>Cbc, Ipopt — Branch-and-cut, interior point</span>
</div>
<div class="layer layer-1">
<strong>Layer 1: LP & Cuts</strong>
<span>Clp, Osi, Cgl — Simplex, interface, cut generators</span>
</div>
<div class="layer layer-0">
<strong>Layer 0: Foundation</strong>
<span>CoinUtils — Matrices, I/O, presolve (122 classes documented)</span>
</div>
</div>

---

## For AI Agents

This documentation is designed for both humans and machines. Every class has a JSON endpoint:

```
GET /api/coinutils/CoinFactorization.json
```

The JSON includes:
- Class name, brief, and detailed description
- `algorithms[]` — Named algorithms with math and complexity
- `methods[]` — All public methods with signatures and parameters
- `header_file`, `library`, `layer` — Source location metadata

**API Index:** [/api/index.json](api/index.json)

---

## Annotation Tags

Each class and method is annotated with semantic tags:

| Tag | Example |
|-----|---------|
| `@algorithm` | Sparse LU with Markowitz pivot selection |
| `@math` | Chooses pivot minimizing (r_i - 1)(c_j - 1) |
| `@complexity` | O(m²) worst case, typically O(m · nnz_avg) |
| `@ref` | Forrest & Tomlin, "Updating triangular factors" (1972) |

These annotations flow from C++ docblocks → Doxygen → JSON/HTML, making the mathematical content accessible to LLMs and search engines.
