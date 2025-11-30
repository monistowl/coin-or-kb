+++
title = "COIN-OR Knowledge Base"
description = "Annotated documentation for optimization solver libraries"
template = "index.html"
+++

# COIN-OR Knowledge Base

A semantically annotated documentation project for the [COIN-OR](https://www.coin-or.org/) optimization solver stack. This knowledge base provides:

- **Algorithm Documentation** — Mathematical descriptions, complexity analysis, and academic references for each algorithm
- **Machine-Readable API** — JSON endpoints for AI agents and tooling
- **Cross-Reference Index** — Browse by algorithm type across all libraries

## Libraries

<div class="library-grid">
<div class="library-card">
<h3><a href="/libraries/coinutils/">CoinUtils</a></h3>
<span class="layer-badge">Layer 0</span>
<p>Foundation utilities: sparse matrices, LU factorization, I/O, presolve</p>
<span class="class-count">122 classes</span>
</div>
</div>

## Quick Links

**Key Classes:**
- [CoinFactorization](/libraries/coinutils/coinfactorization/) — Sparse LU with Markowitz pivoting, Forrest-Tomlin updates
- [CoinPackedMatrix](/libraries/coinutils/coinpackedmatrix/) — Column-major sparse matrix storage
- [CoinIndexedVector](/libraries/coinutils/coinindexedvector/) — Sparse vector with fast access patterns
- [CoinPresolveMatrix](/libraries/coinutils/coinpresolvematrix/) — Problem reduction and simplification

**For Developers:**
- [JSON API](/api/index.json) — Machine-readable class documentation
- [GitHub Repository](https://github.com/monistowl/coin-or-kb) — Source and annotations

## About This Project

This knowledge base extracts and enriches documentation from the COIN-OR C++ headers. Each class is annotated with:

| Tag | Purpose |
|-----|---------|
| `@algorithm` | Algorithm name and description |
| `@math` | Mathematical formulation |
| `@complexity` | Time/space complexity |
| `@ref` | Academic references |

The annotations flow through Doxygen to produce both human-readable HTML and machine-readable JSON, making the documentation accessible to both researchers and AI coding assistants.
