# COIN-OR Annotated Knowledge Base

A deep, AI-parsable knowledge base that maps both the code structure and mathematical principles of optimization solver libraries from the COIN-OR ecosystem and related projects.

## Purpose

This repository contains optimization solver source code enriched with structured inline annotations. The goal is to create a comprehensive reference that enables AI agents to:

- Understand optimization algorithms and their implementations
- Navigate complex solver codebases efficiently
- Connect code to underlying mathematical theory
- Cross-reference related components across libraries

## Quick Start for AI Agents

### Option 1: Hosted API (No Setup)

Point any agent at the hosted JSON API:

```
https://monistowl.github.io/coin-or-kb/api/annotations.json
```

**Example prompt:**

> Fetch https://monistowl.github.io/coin-or-kb/api/annotations.json and help me understand how COIN-OR implements LU factorization for the simplex method.

**Hosted endpoints:**
- **Full API**: https://monistowl.github.io/coin-or-kb/api/annotations.json (2.1 MB)
- **Knowledge Graph**: https://monistowl.github.io/coin-or-kb/api/knowledge-graph/index.json
- **Learning Paths**: https://monistowl.github.io/coin-or-kb/learning-paths/
- **Source Browser**: https://monistowl.github.io/coin-or-kb/browser/
- **Derivations**: https://monistowl.github.io/coin-or-kb/derivations/

### Option 2: Local Clone (For Development)

```bash
git clone https://github.com/monistowl/coin-or-kb.git
cd coin-or-kb

# CLI queries
./scripts/kb-query.py algo "Markowitz"      # Search algorithms
./scripts/kb-query.py lib CoinUtils         # Get library overview
./scripts/kb-query.py stats                 # Show statistics

# Or load JSON directly
python3 -c "import json; kb = json.load(open('site/static/api/annotations.json')); print(kb['stats'])"
```

### Option 3: MCP Server (For Claude Desktop)

Add to `~/.config/Claude/claude_desktop_config.json`:

```json
{
  "mcpServers": {
    "coin-or-kb": {
      "command": "python",
      "args": ["/path/to/coin-or-kb/mcp-server/coin_or_kb_server.py"]
    }
  }
}
```

Then ask Claude: "Use the coin-or-kb tools to find simplex implementations."

---

## Repository Structure

```
coin-or-kb/
├── layer-0/          # Foundation libraries
│   ├── CoinUtils/    # COIN-OR utilities (sparse matrices, I/O, presolve)
│   └── SuiteSparse/  # Sparse linear algebra (AMD, CHOLMOD, UMFPACK, etc.)
│
├── layer-1/          # Core solver components
│   ├── Osi/          # Open Solver Interface (abstraction layer)
│   ├── Clp/          # COIN-OR LP Solver (simplex method)
│   ├── CppAD/        # Automatic differentiation
│   └── qpOASES/      # Active-set QP solver
│
├── layer-2/          # Advanced solvers
│   ├── Cgl/          # Cut Generator Library (MIR, Gomory, etc.)
│   ├── Cbc/          # COIN-OR Branch and Cut (MIP solver)
│   ├── Ipopt/        # Interior Point Optimizer (NLP solver)
│   └── ADOL-C/       # Automatic differentiation (tape-based)
│
├── layer-3/          # Specialized solvers
│   ├── Bonmin/       # MINLP solver (NLP-based B&B)
│   ├── Couenne/      # Global MINLP (spatial B&B)
│   ├── SYMPHONY/     # Parallel MIP (branch-cut-price)
│   ├── Bcp/          # Branch-Cut-Price framework
│   ├── CHiPPS-ALPS/  # Abstract parallel search
│   ├── CHiPPS-BLIS/  # MILP on ALPS framework
│   ├── Dip/          # Decomposition (Dantzig-Wolfe)
│   ├── DisCO/        # Conic optimization (MISOCP)
│   ├── Smi/          # Stochastic programming
│   └── oBB/          # Bound-constrained optimization
│
├── layer-4/          # High-level solvers (in progress)
│   ├── HiGHS/        # High-performance LP/MIP/QP
│   ├── Gravity/      # Nonlinear optimization modeling
│   ├── SHOT/         # Convex MINLP solver
│   ├── OS/           # Optimization Services
│   └── ...           # Additional libraries
│
├── .kb/              # Knowledge base metadata
│   └── status.json   # Annotation progress tracking
│
├── mcp-server/       # MCP server for AI agents
│   └── coin_or_kb_server.py
│
├── scripts/          # Tooling
│   ├── extract-annotations.py  # JSON API generator
│   ├── kb-query.py   # CLI query tool
│   └── validate.py   # Annotation validator
│
├── site/             # Zola static site
│   └── static/api/   # JSON API output
│
├── prompts/          # Context templates
└── docs/             # Design documents
```

## Annotation Progress

| Layer | Status | Libraries | Files | Pass 2 |
|-------|--------|-----------|-------|--------|
| Layer 0 | **Pass 2 In Progress** | CoinUtils, SuiteSparse | 77 | 43 |
| Layer 1 | **Pass 2 In Progress** | Osi, Clp, CppAD, qpOASES | 207 | 87 |
| Layer 2 | **Pass 2 In Progress** | Cgl, Cbc, Ipopt, ADOL-C | 536 | 213 |
| Layer 3 | Pass 2 In Progress | 10 libraries | 572 | 254 |
| Layer 4 | Pass 1 Complete | HiGHS + 10 others | 510 | 82 |

**Total:** 1,902 annotated files, 679 with semantic (Pass 2) annotations across 28 libraries

## Knowledge Graph

The knowledge base includes a **concept graph** connecting algorithms, problem classes, and implementations:

- **41 concepts** (LP, MIP, NLP, simplex, interior point, branch-and-bound, etc.)
- **1,471 relationships** (requires, solves, implemented_in, etc.)
- **Algorithm guidance** for 13 key algorithms with when-to-use, gotchas, and references

**Endpoints:**
- `api/knowledge-graph/index.json` - Full graph with concepts and relationships
- `api/knowledge-graph/categories.json` - Concepts by category

## JSON API

The knowledge base is available as a machine-readable JSON API for AI agents and MCP servers:

```
site/static/api/annotations.json      # Full API (2.1 MB, pretty-printed)
site/static/api/knowledge-graph/      # Concept graph and relationships
```

**Structure:**
```json
{
  "version": "1.0",
  "layers": {
    "layer-0": {
      "CoinUtils": {
        "file_count": 68,
        "pass2_count": 33,
        "files": {
          "src/CoinFactorization.hpp": {
            "brief": "LU factorization for simplex basis",
            "algorithm": "LU factorization with Markowitz pivot selection",
            "math": "B = L·U where L lower triangular, U upper triangular",
            "complexity": "O(nnz) for sparse solves"
          }
        }
      }
    }
  }
}
```

The API is regenerated on every push via GitHub Actions (takes ~2 seconds).

## Annotation Schema

Annotations use Doxygen-compatible comment blocks:

### Pass 1 Tags (Structural)
- `@file` - File path and role
- `@brief` - One-line summary
- `@param` / `@return` - Function signatures
- `@see` - Cross-references to related code

### Pass 2 Tags (Semantic)
- `@algorithm` - Named algorithm being implemented
- `@math` - Mathematical formulas and theory
- `@complexity` - Time/space complexity
- `@ref` - Academic citations
- `@invariant` - Data structure invariants
- `@note` - Implementation details and gotchas

### Example Annotation

```cpp
/**
 * @file util/HFactor.h
 * @brief Basis matrix factorization, update and solves for HiGHS
 *
 * @algorithm LU factorization with Markowitz pivot selection
 * @math PBQ = LU where P,Q are permutation matrices minimizing fill-in
 *
 * **Key Operations:**
 * - build(): Form PBQ=LU factorization
 * - ftranCall(): Solve Bx=b (forward transformation)
 * - btranCall(): Solve B'x=b (backward transformation)
 * - update(): Rank-one update for basis change
 *
 * @complexity O(nnz) for sparse solves, O(n³) worst-case for dense
 * @ref Markowitz (1957). "The Elimination Form of the Inverse"
 *
 * @see simplex/HEkk.h for simplex algorithm using this factorization
 */
```

## Key Algorithms Documented

### Linear Programming
- Revised simplex method (primal/dual)
- Interior point methods (barrier, predictor-corrector)
- Presolve techniques (bound tightening, substitution)

### Mixed-Integer Programming
- Branch and bound / Branch and cut
- Cutting planes (Gomory, MIR, clique, cover)
- Branching strategies (strong, pseudo-cost, reliability)
- Primal heuristics (feasibility pump, RINS, diving)

### Nonlinear Programming
- Interior point for NLP (Ipopt)
- Sequential quadratic programming (qpOASES, SLSQP)
- Global optimization (Couenne spatial B&B)

### Sparse Linear Algebra
- LU factorization with Markowitz ordering
- Cholesky factorization (CHOLMOD)
- Approximate minimum degree (AMD/COLAMD)
- Multifrontal methods (UMFPACK, MUMPS)

### Automatic Differentiation
- Forward mode (seed vectors)
- Reverse mode (adjoints)
- Tape-based tracing (CppAD, ADOL-C)

## Usage for AI Agents

### MCP Server

The knowledge base includes an MCP (Model Context Protocol) server for AI agent integration:

```bash
# Run the MCP server
python mcp-server/coin_or_kb_server.py
```

**Available Tools:**
- `search_algorithms` - Find implementations of algorithms (e.g., "LU factorization", "simplex")
- `search_math` - Find files with mathematical concepts (e.g., "clique", "Ax=b")
- `get_library` - Get overview of a library with annotated files
- `get_file` - Get all annotations for a specific file
- `list_algorithms` - List all documented algorithms (87+)
- `get_stats` - Get knowledge base statistics

**Claude Desktop Configuration:**
```json
{
  "mcpServers": {
    "coin-or-kb": {
      "command": "python",
      "args": ["/path/to/coin-or-kb/mcp-server/coin_or_kb_server.py"]
    }
  }
}
```

### CLI Query Tool

For quick lookups without MCP:

```bash
# Search algorithms
./scripts/kb-query.py algo "Markowitz"
./scripts/kb-query.py algo "branch and bound"

# Search mathematical concepts
./scripts/kb-query.py math "clique"
./scripts/kb-query.py math "dual"

# Get library overview
./scripts/kb-query.py lib CoinUtils
./scripts/kb-query.py lib HiGHS

# Get file details
./scripts/kb-query.py file CoinUtils CoinFactorization.hpp

# List all algorithms
./scripts/kb-query.py list

# Show statistics
./scripts/kb-query.py stats
```

### JSON API (Direct Access)

Load the knowledge base directly:

```python
import json
with open('site/static/api/annotations.json') as f:
    kb = json.load(f)

# Find all LU factorization implementations
for layer in kb['layers'].values():
    for lib in layer['libraries'].values():
        for path, file in lib['files'].items():
            if 'algorithm' in file and 'LU' in file.get('algorithm', ''):
                print(f"{lib['name']}/{path}: {file['algorithm']}")
```

### Direct Source Search
```bash
# Search for algorithm implementations
grep -r "@algorithm.*Markowitz" layer-*/

# Find cross-references to a component
grep -r "@see.*HighsDomain" layer-4/HiGHS/
```

### Understanding a Subsystem
1. Query the MCP server or JSON API for the library/file
2. Check `@brief` for purpose, `@algorithm` for technique
3. Follow `@see` references to related components
4. Check `@math` for underlying theory, `@complexity` for performance

### Contribution Guidelines
See [AGENTS.md](AGENTS.md) for detailed instructions on:
- Annotation format and quality standards
- Two-pass annotation process
- Domain knowledge requirements
- What NOT to do (no code changes!)

## Libraries Covered

### COIN-OR Ecosystem
- **CoinUtils** - Sparse matrices, I/O, presolve utilities
- **Osi** - Open Solver Interface abstraction
- **Clp** - Simplex LP solver
- **Cgl** - Cut generators for MIP
- **Cbc** - Branch and cut MIP solver
- **Ipopt** - Interior point NLP solver
- **Bonmin** - Basic Open-source MINLP solver
- **Couenne** - Convex Over/Under ENvelopes (global MINLP)
- **SYMPHONY** - Parallel branch-cut-price MIP
- **Bcp** - Branch-Cut-Price framework
- **CHiPPS** - Parallel tree search (ALPS + BLIS)
- **Dip** - Decomposition for Integer Programming
- **DisCO** - Discrete Conic Optimization

### External Libraries
- **SuiteSparse** - Sparse direct solvers (Davis et al.)
- **HiGHS** - High-performance LP/MIP solver
- **qpOASES** - Online active-set QP solver
- **CppAD/ADOL-C** - Automatic differentiation
- **Gravity** - Nonlinear optimization modeling

## License

The annotations in this repository are provided for educational and research purposes. The underlying source code retains its original licenses (primarily EPL-2.0 for COIN-OR, MIT for HiGHS, LGPL/BSD for SuiteSparse).

## Acknowledgments

This knowledge base builds on decades of work by the optimization research community, including:
- COIN-OR Foundation and contributors
- SuiteSparse developers (Tim Davis et al.)
- HiGHS team (Edinburgh)
- Ipopt developers (Waechter, Biegler)
- And many others in the mathematical optimization community
