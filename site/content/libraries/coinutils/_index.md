+++
title = "CoinUtils"
description = "Layer 0 - Foundation utilities for COIN-OR solvers"
template = "library.html"
sort_by = "title"

[extra]
layer = 0
+++

# CoinUtils — Foundation Utilities

CoinUtils provides the fundamental building blocks used by all COIN-OR optimization libraries. Every solver in the stack depends on these core utilities for sparse linear algebra, file I/O, and numerical infrastructure.

**Layer 0** | 122 files | 18 with algorithm annotations

---

## Why CoinUtils Matters

Optimization solvers spend most of their time doing linear algebra:
- **Simplex**: Factor basis, compute $B^{-1}A$, update after pivots
- **Interior Point**: Solve normal equations $(ADA^T)\Delta y = r$
- **Branch-and-Bound**: Re-solve LPs after bound changes

CoinUtils provides the efficient sparse data structures and algorithms that make this tractable for problems with millions of variables.

---

## Core Components

### Sparse Matrix Classes

Large optimization problems are **sparse** — most entries are zero. CoinUtils provides column-major storage that exploits this:

| Class | Purpose |
|-------|---------|
| [CoinPackedMatrix](@/libraries/coinutils/CoinPackedMatrix.md) | Column-major sparse matrix |
| [CoinPackedVector](@/libraries/coinutils/CoinPackedVector.md) | Sparse vector with indices |
| [CoinIndexedVector](@/libraries/coinutils/CoinIndexedVector.md) | Sparse vector with O(1) index lookup |
| [CoinShallowPackedVector](@/libraries/coinutils/CoinShallowPackedVector.md) | Non-owning view into packed data |

**Why column-major?** LP constraints $Ax \leq b$ are naturally column-oriented: each column is a variable's coefficients in all constraints. Column access is $O(1)$, critical for pricing in simplex.

### LU Factorization

The basis matrix $B$ changes by one column per simplex iteration. Rather than refactoring from scratch, CoinUtils supports efficient **updates**:

| Class | Purpose |
|-------|---------|
| [CoinFactorization](@/libraries/coinutils/CoinFactorization.md) | Sparse LU with Markowitz pivoting |
| [CoinOslFactorization](@/libraries/coinutils/CoinOslFactorization.md) | OSL-derived factorization |
| [CoinDenseFactorization](@/libraries/coinutils/CoinDenseFactorization.md) | Dense fallback for small bases |

**Key algorithms**:
- **Markowitz pivoting**: Minimize fill-in during factorization
- **Forrest-Tomlin updates**: Update $L$ and $U$ after basis change
- **FTRAN/BTRAN**: Forward and backward triangular solves

### File I/O

Read and write standard optimization file formats:

| Class | Format |
|-------|--------|
| [CoinMpsIO](@/libraries/coinutils/CoinMpsIO.md) | MPS (industry standard) |
| [CoinLpIO](@/libraries/coinutils/CoinLpIO.md) | LP (CPLEX-style) |
| [CoinFileInput](@/libraries/coinutils/CoinFileInput.md) | Compressed files (gzip) |
| [CoinModel](@/libraries/coinutils/CoinModel.md) | In-memory problem builder |

### Presolve

Simplify problems before solving to reduce size and improve numerics:

| Class | Operation |
|-------|-----------|
| [CoinPresolveMatrix](@/libraries/coinutils/CoinPresolveMatrix.md) | Presolve state management |
| [CoinPostsolveMatrix](@/libraries/coinutils/CoinPostsolveMatrix.md) | Restore original solution |
| [doubleton_action](@/libraries/coinutils/doubleton_action.md) | Eliminate doubleton rows |
| [dupcol_action](@/libraries/coinutils/dupcol_action.md) | Remove duplicate columns |

**Common reductions**:
- Remove fixed variables
- Eliminate singleton rows/columns
- Detect infeasibility or unboundedness early
- Tighten bounds via constraint propagation

### Graph Algorithms

For MIP cut generation, CoinUtils includes conflict graph structures:

| Class | Purpose |
|-------|---------|
| [CoinConflictGraph](@/libraries/coinutils/CoinConflictGraph.md) | Variable conflict relationships |
| [CoinBronKerbosch](@/libraries/coinutils/CoinBronKerbosch.md) | Maximal clique enumeration |
| [CoinCliqueList](@/libraries/coinutils/CoinCliqueList.md) | Clique storage for cuts |
| [CoinShortestPath](@/libraries/coinutils/CoinShortestPath.md) | Shortest path algorithms |

### Search Trees

For branch-and-bound tree management:

| Class | Purpose |
|-------|---------|
| [CoinSearchTree](@/libraries/coinutils/CoinSearchTree.md) | Generic search tree |
| [CoinSearchTreeCompareBest](@/libraries/coinutils/CoinSearchTreeCompareBest.md) | Best-first selection |
| [CoinSearchTreeCompareDepth](@/libraries/coinutils/CoinSearchTreeCompareDepth.md) | Depth-first selection |

---

## Architecture

CoinUtils has no external dependencies — it's pure C++ designed for portability:

```
CoinPackedMatrix / CoinIndexedVector  <- Sparse storage
        |
CoinFactorization                      <- LU factorization
        |
CoinMpsIO / CoinLpIO                   <- File I/O
        |
CoinPresolve*                          <- Problem reduction
```

Higher-level solvers (Clp, Cbc) build on these primitives.

---

## Usage Example

```cpp
#include "CoinPackedMatrix.hpp"
#include "CoinMpsIO.hpp"

// Read an MPS file
CoinMpsIO reader;
reader.readMps("problem.mps");

// Access the constraint matrix
const CoinPackedMatrix* matrix = reader.getMatrixByCol();

// Get problem dimensions
int numRows = reader.getNumRows();
int numCols = reader.getNumCols();

// Access column data
for (int j = 0; j < numCols; j++) {
    const CoinBigIndex start = matrix->getVectorFirst(j);
    const CoinBigIndex end = matrix->getVectorLast(j);
    const int* indices = matrix->getIndices() + start;
    const double* elements = matrix->getElements() + start;
    // Process column j...
}
```

---

## Key Algorithms

### Markowitz Pivoting

When factoring $PA = LU$, choose pivots to minimize fill-in:

$$\text{score}(a_{ij}) = (r_i - 1)(c_j - 1)$$

where $r_i$ = row count, $c_j$ = column count. Lower score = less fill-in.

See [CoinFactorization](@/libraries/coinutils/CoinFactorization.md) for implementation.

### Forrest-Tomlin Update

After a basis change (column swap), update $L$ and $U$ without full refactorization:
1. Form spike from new column
2. Push spike through $L$ and $U$
3. Restore triangularity with row/column operations

This makes each simplex iteration $O(m)$ instead of $O(m^3)$.

### Compressed Sparse Storage (CSC)

Store sparse matrix $A$ as:
- `elements[]`: Non-zero values
- `indices[]`: Row indices of non-zeros
- `starts[]`: Start position of each column

Memory: $O(\text{nnz} + n)$ instead of $O(mn)$ for dense.

---

## Performance Tips

1. **Pre-allocate**: Use `reserve()` before building matrices
2. **Column access**: Prefer column-major operations
3. **Update vs. refactor**: Balance stability vs. speed
4. **Indexed vectors**: Use for hyper-sparse operations

---

## Related Resources

- [LP Fundamentals Learning Path](@/learning-paths/lp-fundamentals.md) — Start here
- [LU Factorization Algorithm](@/algorithms/lu-factorization-with-markowitz-pivot-selection.md) — Detailed algorithm
- [Sparse Matrix Operations](@/algorithms/sparse-matrix-operations.md) — CSC format
- [Simplex Convergence Derivation](/derivations/simplex-convergence/) — Why simplex works
