+++
title = "COIN-OR Knowledge Base"
description = "Annotated documentation for optimization solver libraries"
template = "index.html"
+++

# COIN-OR Knowledge Base

Semantically annotated documentation for the [COIN-OR](https://www.coin-or.org/) open-source optimization stack. Find algorithm details, mathematical formulations, complexity analysis, and academic references — all extracted from annotated C++ headers.

<div class="quick-nav">
<a href="learning-paths/" class="nav-card featured">
<strong>Start Learning</strong>
<span>Guided paths for students</span>
</a>
<a href="derivations/" class="nav-card">
<strong>Derivations</strong>
<span>Step-by-step proofs</span>
</a>
<a href="libraries/coinutils/" class="nav-card">
<strong>Browse CoinUtils</strong>
<span>122 foundation classes</span>
</a>
<a href="api/index.json" class="nav-card">
<strong>JSON API</strong>
<span>Machine-readable docs</span>
</a>
</div>

---

## For Students: Getting Started

New to optimization solvers? Here's what you need to dive in.

<div class="prereq-grid">

<div class="prereq-card">
<h4>Prerequisites</h4>
<ul>
<li><strong>Linear Algebra</strong> — Matrices, solving $Ax = b$, rank, null space</li>
<li><strong>Calculus</strong> — Derivatives, gradients (for nonlinear optimization)</li>
<li><strong>Programming</strong> — Ability to read C++ (not write it)</li>
</ul>
</div>

<div class="prereq-card">
<h4>Recommended Path</h4>
<ol>
<li><a href="learning-paths/lp-fundamentals/">LP Fundamentals</a> — Sparse matrices → LU → Simplex</li>
<li><a href="learning-paths/mip-journey/">MIP Journey</a> — Branch-and-bound, cuts, heuristics</li>
<li><a href="browser/">Source Browser</a> — Explore real implementations</li>
</ol>
</div>

</div>

<div class="try-interactive">
<strong>Try it now:</strong> <a href="learning-paths/simplex-example/">Interactive Simplex Example</a> — Step through a complete solve with visualization
</div>

---

## Browse by Topic

### Matrix & Vector Operations
Core sparse data structures used throughout the solver stack.

| Class | Description |
|-------|-------------|
| [CoinPackedMatrix](@/libraries/coinutils/CoinPackedMatrix.md) | Column-major sparse matrix with efficient column operations |
| [CoinIndexedVector](@/libraries/coinutils/CoinIndexedVector.md) | Sparse vector with $O(1)$ index lookup for basis operations |
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

<div class="diagram-container">
<img src="diagrams/coin-or-layers.svg" alt="COIN-OR library architecture" class="architecture-diagram">
</div>

<details>
<summary>Text version of layer diagram</summary>

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
</details>

---

## Mathematical Formulations

The knowledge base captures mathematical formulations from the solver documentation. For example, the standard form LP:

$$\min_{x} \quad c^T x \quad \text{subject to} \quad Ax = b, \quad x \geq 0$$

And the Markowitz pivot selection criterion minimizes fill-in during LU factorization:

$$\text{score}(a_{ij}) = (r_i - 1)(c_j - 1)$$

where $r_i$ is the row count and $c_j$ is the column count for element $a_{ij}$.

---

## For AI Agents

This knowledge base is built for machine consumption. Point your agent at it and instantly gain expertise on 28 optimization libraries.

### Hosted API (No Setup Required)

Fetch the JSON API directly — works with any agent that can read URLs:

```
https://monistowl.github.io/coin-or-kb/api/annotations.json
```

**Example prompt for Claude, GPT, or any LLM:**

> Fetch https://monistowl.github.io/coin-or-kb/api/annotations.json and use it to answer questions about COIN-OR optimization libraries. This contains algorithm descriptions, mathematical formulations, and complexity analysis for 1,902 files across 28 libraries (688 with semantic annotations).

**API Endpoints:**

| Endpoint | Description |
|----------|-------------|
| [`/api/annotations.json`](api/annotations.json) | Full knowledge base with semantic annotations (2.1 MB) |
| [`/api/knowledge-graph/`](api/knowledge-graph/) | Concept graph with 41 concepts, 1,471 relationships |
| [`/algorithms/`](algorithms/) | Human-readable algorithm cross-reference |

---

### Local MCP Server (For Claude Desktop)

Add to your Claude Desktop `claude_desktop_config.json`:

```json
{
  "mcpServers": {
    "coin-or-kb": {
      "command": "python",
      "args": ["/path/to/mcp-server/coin_or_kb_server.py"]
    }
  }
}
```

**Available MCP Tools:**

| Tool | Description |
|------|-------------|
| `search_algorithms` | Find implementations by algorithm name ("LU factorization", "simplex") |
| `search_math` | Find files by mathematical concept ("clique", "Ax=b", "dual") |
| `get_library` | Overview of a library with all annotated files |
| `get_file` | Full annotations for a specific file |
| `list_algorithms` | List all documented algorithms |
| `query_concepts` | Search the knowledge graph (41 concepts, 1,471 relationships) |
| `get_algorithm_guidance` | Detailed guidance for 13 key algorithms |
| `get_stats` | Knowledge base statistics |

### CLI Query Tool

For quick lookups without MCP:

```bash
# Search by algorithm
./scripts/kb-query.py algo "Markowitz"          # LU factorization pivot selection
./scripts/kb-query.py algo "branch and bound"   # MIP tree search

# Search by math concept
./scripts/kb-query.py math "clique"             # Conflict graph algorithms
./scripts/kb-query.py math "reduced cost"       # Simplex pricing

# Get library overview
./scripts/kb-query.py lib CoinUtils             # Foundation library
./scripts/kb-query.py lib Ipopt                 # NLP solver

# Get specific file details
./scripts/kb-query.py file CoinUtils CoinFactorization.hpp

# List all documented algorithms
./scripts/kb-query.py list
```

### JSON API

Load the entire knowledge base directly:

```python
import json
with open('site/static/api/annotations.json') as f:
    kb = json.load(f)

# Find all simplex-related algorithms
for layer in kb['layers'].values():
    for lib in layer['libraries'].values():
        for path, file in lib['files'].items():
            algo = file.get('algorithm', '')
            if 'simplex' in algo.lower():
                print(f"{lib['name']}/{path}")
                print(f"  {algo[:100]}...")
```

**API Endpoints:**
- [`/api/annotations.json`](api/annotations.json) — Full knowledge base (2.1 MB)
- [`/api/knowledge-graph/`](api/knowledge-graph/) — Concept graph and relationships

### What's in the Annotations?

Each annotated file can include:

| Tag | Example |
|-----|---------|
| `@algorithm` | Sparse LU with Markowitz pivot selection |
| `@math` | Chooses pivot minimizing $(r_i - 1)(c_j - 1)$ |
| `@complexity` | $O(m^2)$ worst case, typically $O(m \cdot \text{nnz})$ |
| `@ref` | Forrest & Tomlin, "Updating triangular factors" (1972) |
| `@brief` | One-line summary of the file's purpose |
| `@see` | Cross-references to related code |

**Coverage:** 1,902 annotated files across 28 libraries. 688 files have deep semantic annotations (`@algorithm`, `@math`, `@complexity`).
