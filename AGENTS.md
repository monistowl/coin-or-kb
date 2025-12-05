# Agent Instructions: Optimization Solver Knowledge Base

This document provides instructions for AI agents. There are two modes:
1. **Using the KB** — Query the knowledge base to understand optimization algorithms
2. **Contributing to the KB** — Add annotations to expand coverage

---

## Part 1: Using the Knowledge Base

### Hosted API (Fastest - No Setup)

Point any agent at the hosted JSON API:

```
https://monistowl.github.io/coin-or-kb/api/annotations.json
```

**Example prompt for any LLM:**
> Fetch https://monistowl.github.io/coin-or-kb/api/annotations.json and use it to answer questions about COIN-OR optimization libraries. This contains algorithm descriptions, mathematical formulations, and complexity analysis for 1,902 files across 28 libraries (679 with semantic annotations).

### Local Clone (For Development)

```bash
# Clone and explore
git clone https://github.com/monistowl/coin-or-kb.git
cd coin-or-kb

# What algorithms are documented?
./scripts/kb-query.py list

# Search for specific algorithms
./scripts/kb-query.py algo "simplex"
./scripts/kb-query.py algo "branch and bound"

# Search by math concept
./scripts/kb-query.py math "LU factorization"
./scripts/kb-query.py math "clique"

# Get library overview
./scripts/kb-query.py lib CoinUtils
./scripts/kb-query.py lib Cbc

# Get details on a specific file
./scripts/kb-query.py file CoinUtils CoinFactorization.hpp
```

### MCP Server Integration

For persistent access via Claude Desktop or other MCP clients:

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

**Available Tools:**
- `search_algorithms(query)` — Find algorithm implementations
- `search_math(query)` — Find mathematical concepts
- `get_library(name)` — Library overview with annotated files
- `get_file(library, file)` — Full annotations for a file
- `list_algorithms()` — All documented algorithms
- `query_concepts(query)` — Search the knowledge graph (41 concepts, 1,471 relationships)
- `get_algorithm_guidance(name)` — Detailed guidance for 13 key algorithms
- `get_stats()` — Knowledge base statistics

### JSON API

Load directly in Python:

```python
import json
with open('site/static/api/annotations.json') as f:
    kb = json.load(f)

# Structure: kb['layers'][layer]['libraries'][lib]['files'][path]
# Each file has: brief, algorithm, math, complexity, ref, see
```

### What You Can Learn

The KB documents 1,902 files across 28 libraries (679 with semantic annotations) covering:

- **Linear Programming**: Simplex method, interior point, presolve
- **Mixed-Integer Programming**: Branch-and-bound, cutting planes, heuristics
- **Nonlinear Programming**: Interior point (Ipopt), SQP
- **Sparse Linear Algebra**: LU factorization, Cholesky, AMD ordering
- **Automatic Differentiation**: Forward/reverse mode, tape-based

---

## Part 2: Contributing Annotations

**Goal:** Expand the knowledge base by adding structured annotations to source code.

**Constraints:**
- DO NOT change any functional behavior
- DO NOT refactor or restructure code
- DO NOT add features or "improve" code
- DO add comments, reformat for readability, remove provably dead code
- DO preserve all original functionality exactly

---

## Repository Structure

```
coin-or-kb/
├── layer-0/          # Foundation: CoinUtils, SuiteSparse
├── layer-1/          # Core: Osi, Clp, CppAD, qpOASES
├── layer-2/          # Advanced: Cgl, Cbc, Ipopt, ADOL-C
├── layer-3/          # Specialized: Bonmin, Couenne, SYMPHONY, etc.
├── layer-4/          # High-level: HiGHS, Gravity, SHOT, etc.
├── .kb/              # Knowledge base metadata
│   └── status.json   # Annotation progress tracking
├── mcp-server/       # MCP server for AI agents
│   └── coin_or_kb_server.py
├── scripts/          # Tooling
│   ├── extract-annotations.py  # JSON API generator
│   ├── kb-query.py   # CLI query tool
│   └── validate.py   # Annotation validator
├── site/             # Zola static site
│   └── static/api/   # JSON API output
└── prompts/          # Context templates
```

**Processing order for Pass 1:** Work strictly by layer. Complete all Layer 0 libraries before starting Layer 1. Within a layer, order does not matter.

**Processing order for Pass 2:** Prioritize high-value algorithmic files across layers. Focus on core algorithm implementations (e.g., simplex pivot selection, IPM iteration, branch-and-bound) before utility classes.

---

## Annotation Schema

Use Doxygen-compatible comment blocks with the following tags:

### Required Tags

| Tag | When Required | Description |
|-----|---------------|-------------|
| `@brief` | All public classes, functions, methods | One-line summary of what it does (not how) |
| `@param` | All public functions with parameters | Describe each parameter |
| `@return` | All non-void public functions | Describe return value |

### Semantic Tags

| Tag | When to Use | Description |
|-----|-------------|-------------|
| `@algorithm` | Implementing a named algorithm | Standard name of the algorithm |
| `@math` | Code with mathematical basis | Formulas, theorems, mathematical relationships. Use Unicode math symbols (∇, ∈, ≤, Σ, etc.) for readability. |
| `@complexity` | Algorithms, hot paths | Time and space complexity with brief justification |
| `@ref` | Citing literature | Full citation: Author (Year). "Title". Journal/Book |
| `@invariant` | Data structures, stateful code | Conditions that must hold |
| `@see` | Related code | Cross-references to related functions/classes |
| `@note` | Non-obvious behavior | Implementation details, gotchas, edge cases |
| `@todo` | Needs further analysis | Mark for Pass 2 or human review |

### Tag Format Examples

**Minimal (simple utility):**
```cpp
/**
 * @brief Return the number of non-zero elements in the matrix
 * @return Count of structural non-zeros
 */
int getNumElements() const;
```

**Standard (public API):**
```cpp
/**
 * @brief Solve the linear system Ax = b using the current factorization
 *
 * @param rhs Right-hand side vector b (modified in place to contain solution)
 * @return 0 on success, non-zero error code on failure
 *
 * @see factorize(), updateFactorization()
 */
int solve(double* rhs);
```

**Full (algorithm implementation):**
```cpp
/**
 * @brief Select pivot element for basis update
 *
 * @algorithm Markowitz pivot selection
 * @math Chooses pivot (i,j) minimizing (r_i - 1)(c_j - 1) where:
 *       - r_i = number of non-zeros in row i of active submatrix
 *       - c_j = number of non-zeros in column j of active submatrix
 *       This heuristic minimizes expected fill-in during elimination.
 * @complexity O(nnz) where nnz = non-zeros in active submatrix
 * @ref Markowitz, H. (1957). "The Elimination Form of the Inverse and Its
 *      Application to Linear Programming". Management Science 3(3):255-269.
 *
 * @param matrix Pointer to active submatrix
 * @param tolerance Minimum acceptable |pivot| for numerical stability
 * @return PivotInfo struct containing row, column, and value
 *
 * @invariant Returned pivot satisfies |value| >= tolerance
 * @note Falls back to partial pivoting if no Markowitz-acceptable pivot found
 * @see updateBasis(), refactorize()
 */
PivotInfo selectPivot(const CoinPackedMatrix* matrix, double tolerance);
```

**Full with matrix notation (IPM example):**
```cpp
/**
 * @brief Solve KKT system for interior point method
 *
 * @algorithm Primal-Dual Interior Point Method
 * @math KKT system solved each iteration:
 * [W    A^T  -I ] [Δx]   [∇f - A^T y - z    ]
 * [A    0    0  ] [Δy] = [-c(x)             ]
 * [Z    0    X  ] [Δz]   [μe - XZe          ]
 * where W = ∇²L (Hessian), A = ∇c (constraint Jacobian).
 * Reduced to augmented system via block elimination.
 *
 * @complexity O(m²n + m³) per iteration: O(m²n) to form, O(m³) to factor.
 * @ref Wächter & Biegler (2006). "On the implementation of an interior-point
 *   filter line-search algorithm". Mathematical Programming 106(1):25-57.
 *
 * @see IpBacktrackingLineSearch for globalization
 */
```

---

## Two-Pass Annotation Process

### Pass 1: Structural Annotation

**Goal:** Document what the code does and how it's organized.

**Tasks:**
1. Add `@brief` to every public class, struct, function, method
2. Add `@param` and `@return` to public functions
3. Add `@see` for obvious relationships (overloads, related functions, base classes)
4. Add `@invariant` where clear from assertions, comments, or documentation
5. Add `@todo` to mark anything needing deeper analysis

**Do not in Pass 1:**
- Research algorithms or mathematical background
- Add `@algorithm`, `@math`, `@complexity`, or `@ref` tags
- Spend time on private/internal implementation details

**Quality bar:**
- Every public symbol has `@brief`
- Every public function has `@param`/`@return` (if applicable)
- `@brief` is accurate and useful (not just restating the name)

### Pass 2: Semantic Annotation

**Goal:** Explain why the code works and connect to theory.

**Tasks:**
1. Resolve all `@todo` markers from Pass 1
2. Identify named algorithms and add `@algorithm` tag
3. Document mathematical foundations with `@math`
4. Analyze and document complexity with `@complexity`
5. Find and cite relevant literature with `@ref`
6. Add `@note` for non-obvious implementation details

**Research expectations:**
- Use your knowledge of optimization algorithms, linear algebra, numerical methods
- Cite specific papers when the code implements a published technique
- If uncertain about algorithm identity, note the uncertainty in `@note`

**Quality bar:**
- All algorithm implementations have `@algorithm`
- Mathematical code has `@math` explaining the theory
- No unresolved `@todo` markers remain

---

## Domain Knowledge: Optimization Solvers

### Key Concepts You Should Know

**Linear Programming (LP):**
- Simplex method (primal, dual, revised)
- Interior point methods (barrier, predictor-corrector)
- Presolve techniques (variable fixing, row reduction)
- Duality theory

**Mixed Integer Programming (MIP):**
- Branch and bound
- Cutting planes (Gomory, MIR, clique, cover)
- Branching strategies (most infeasible, strong branching)
- Node selection (best-first, depth-first)

**Nonlinear Programming (NLP):**
- Interior point for nonlinear (IPOPT)
- Sequential quadratic programming
- KKT conditions, constraint qualification

**Sparse Linear Algebra:**
- Sparse matrix formats (CSC, CSR, triplet)
- LU factorization with pivoting
- Fill-in minimization
- Numerical stability vs. sparsity tradeoffs

### Common Patterns in COIN-OR Code

**Class naming:**
- `Coin*` - CoinUtils base classes (CoinPackedMatrix, CoinMessageHandler)
- `Clp*` - Clp solver classes
- `Cbc*` - Cbc MIP solver classes
- `Osi*` - Open Solver Interface abstractions

**Method naming:**
- `get*/set*` - Accessors
- `*Row*/*Column*` - Operations on rows/columns
- `primal*/dual*` - Simplex-related
- `branch*/cut*` - MIP-related

**Data structures:**
- `CoinPackedMatrix` - Sparse matrix (CSC format typically)
- `CoinPackedVector` - Sparse vector
- `CoinIndexedVector` - Sparse vector with dense backing

---

## What NOT to Do

### Code Changes

**NEVER:**
- Change function signatures
- Change algorithm logic
- Change data structure layouts
- Add error handling that wasn't there
- "Fix" bugs (report them in `@note` or `@todo` instead)
- Optimize code
- Refactor for "clarity"

**Exception:** Remove provably dead code. Code is "provably dead" if:
- It's `#if 0` blocked out
- It's commented out with clear intent
- Static analysis proves it unreachable
- **When in doubt, leave it**

### Annotation Mistakes

**NEVER:**
- Write `@brief` that just restates the function name
  - Bad: `@brief Get the number of rows`
  - Good: `@brief Return row count of the constraint matrix`
- Use vague `@math` descriptions
  - Bad: `@math Uses linear algebra`
  - Good: `@math Solves Ax=b via LU factorization with partial pivoting`
- Cite papers you haven't verified implement this algorithm
- Guess at complexity without analysis
- Leave `@todo` markers in Pass 2 output (resolve or escalate)

### Scope Creep

**NEVER:**
- Document private implementation details in Pass 1
- Deep-dive into one file while neglecting others
- Annotate test files or examples (unless specifically requested)
- Generate supplementary documentation files
- Create indexes or summaries (that's tooling's job)

---

## Handling Uncertainty

### Algorithm Identification

If you're unsure whether code implements a named algorithm:

```cpp
/**
 * @brief Select entering variable for simplex iteration
 *
 * @note Appears to implement a variant of Dantzig's rule with
 *       partial pricing. Verify against Dantzig (1963) or
 *       Maros (2003) Ch. 9 for precise classification.
 */
```

### Mathematical Formulas

If the math is clear but you're uncertain of the source:

```cpp
/**
 * @math Computes reduced cost: c_j - c_B * B^{-1} * A_j
 * @note Standard reduced cost formula; see any LP textbook
 */
```

### Incomplete Understanding

If you cannot determine what code does after reasonable effort:

```cpp
/**
 * @brief [Purpose unclear - needs human review]
 * @todo This function appears to modify the basis representation but
 *       the relationship between ftranU and btranU is unclear.
 *       May relate to Forrest-Tomlin update. Needs expert review.
 */
```

---

## File-by-File Process

When annotating a file:

1. **Read the entire file first** - understand structure before annotating
2. **Check for existing documentation** - preserve and enhance, don't duplicate
3. **Identify public API** - classes, functions, methods visible outside this file
4. **Annotate top-down** - file header, classes, then methods
5. **Cross-reference within file** - use `@see` to link related pieces
6. **Check your work** - re-read annotations for accuracy

### File Header Template

```cpp
/**
 * @file CoinPackedMatrix.cpp
 * @brief Implementation of sparse matrix operations in CSC format
 *
 * This file implements the CoinPackedMatrix class, providing:
 * - Construction from various formats (dense, triplet, CSR)
 * - Matrix-vector multiplication
 * - Submatrix extraction
 * - Modification operations (append, delete rows/columns)
 *
 * @see CoinPackedMatrix.hpp for class declaration
 * @see CoinPackedVector.cpp for sparse vector operations
 */
```

---

## Quality Checklist

Before considering a file complete, verify:

### Pass 1
- [ ] Every public class has `@brief`
- [ ] Every public method has `@brief`
- [ ] Every public function has `@param` for each parameter
- [ ] Every non-void public function has `@return`
- [ ] `@brief` descriptions are meaningful (not name-restating)
- [ ] Obvious cross-references have `@see`
- [ ] Complex/unclear code has `@todo` for Pass 2

### Pass 2
- [ ] All `@todo` markers resolved or escalated
- [ ] Algorithm implementations have `@algorithm`
- [ ] Mathematical code has `@math`
- [ ] Non-trivial algorithms have `@complexity`
- [ ] Published techniques have `@ref`
- [ ] Non-obvious behavior documented in `@note`

---

## Library-Specific Context

When annotating a specific library, additional context files may be available at:
`prompts/library-context/<library-name>.md`

These provide:
- Library purpose and scope
- Key classes and their relationships
- Common patterns in that codebase
- Known gotchas or confusing areas
- References to primary literature for that library's algorithms

**Always check for library-specific context before starting annotation.**

---

## Reporting Issues

When you encounter something that needs human attention:

### In-Code Reporting

Use `@todo` with clear description:
```cpp
/**
 * @todo HUMAN_REVIEW: This appears to be a numerical stability hack.
 *       The magic constant 1e-12 is unexplained. May need domain expert.
 */
```

### Snarl Documentation

For systematic issues affecting multiple files, create a snarl spike in your output:

```markdown
## Snarl: [Short Title]

**Files affected:** List specific files
**Problem:** Describe the issue clearly
**Options considered:** What approaches you thought of
**Recommendation:** What you think should be done
**Questions for human:** Specific decisions needed
```

---

## Summary

1. **Your job:** Add structured annotations that explain what code does and why
2. **Not your job:** Change code, fix bugs, refactor, or optimize
3. **Pass 1:** Structure - `@brief`, `@param`, `@return`, `@see`
4. **Pass 2:** Semantics - `@algorithm`, `@math`, `@complexity`, `@ref`
5. **When uncertain:** Document the uncertainty, don't guess
6. **Quality matters:** A wrong annotation is worse than no annotation

The goal is a knowledge base that lets future agents (and humans) understand these solver codebases deeply. Every annotation should add genuine insight.
