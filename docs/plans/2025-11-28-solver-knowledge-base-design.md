# Annotated Optimization Solver Knowledge Base

**Date:** 2025-11-28
**Status:** Design complete, ready for implementation

## Overview & Goals

**Project:** Create a deep, agent-parsable knowledge base that maps both the code structure and mathematical principles of the COIN-OR optimization ecosystem and related solvers.

**Approach:** Fully fork ~35 solver libraries and add inline structured annotations directly to the source code. The annotated code becomes the source of truth; additional indexes (JSON graphs, embeddings) can be generated from it later.

**Two audiences (phased):**
1. **Phase 1 (now):** Agent consumption - structured tags enable extraction, querying, and skill-building
2. **Phase 2 (future):** Human students - same annotations, potentially expanded with more prose

**What we will do:**
- Add structured comment blocks explaining algorithms, math, complexity, references
- Reformat code for consistency and readability
- Remove provably dead code
- Build extraction tooling to generate knowledge base artifacts

**What we will NOT do:**
- Change any functional behavior
- Refactor code structure (even if "cleaner")
- Merge upstream changes (these are permanent forks)

**Success criteria:**
- An agent can answer "How does Clp's pricing strategy work?" by retrieving relevant annotated code
- An agent can trace "What calls `factorize()`?" through extracted call graphs
- Mathematical concepts link to their code implementations and literature references

---

## Repository Structure & Dependency Order

**Directory layout:**

```
/home/tom/Code/vendor/
├── .kb/                          # Knowledge base outputs (generated)
│   ├── indexes/                  # JSON graphs, search indexes
│   ├── extracts/                 # Markdown summaries per library
│   └── schemas/                  # Tag definitions, validation rules
├── layer-0/                      # Foundation libraries
│   ├── SuiteSparse/              # Sparse linear algebra
│   └── CoinUtils/                # COIN-OR utilities, CoinPackedMatrix
├── layer-1/                      # Core abstractions & solvers
│   ├── Osi/                      # Open Solver Interface
│   ├── Clp/                      # LP solver (simplex)
│   └── CppAD/                    # Automatic differentiation
├── layer-2/                      # Advanced solvers
│   ├── Cgl/                      # Cut generators
│   ├── Cbc/                      # MIP solver (branch & cut)
│   └── Ipopt/                    # NLP solver (interior point)
├── layer-3/                      # Specialized solvers
│   ├── Bonmin/                   # MINLP
│   ├── Couenne/                  # Global optimization
│   └── SYMPHONY/                 # Parallel MIP
├── layer-4/                      # High-level tools
│   ├── Gravity/                  # Modeling language
│   ├── HiGHS/                    # Modern LP/MIP (standalone)
│   └── ...
├── archive/                      # Original zips (reference)
├── scripts/                      # Tooling
└── prompts/                      # Agent prompt templates
```

**Processing order:** Strictly by layer. Complete Layer 0 annotations before starting Layer 1. This ensures:
- Foundational concepts (sparse matrices, solver interfaces) are documented first
- Cross-references point to already-annotated code
- Agent builds cumulative understanding

**Per-library structure:** Each extracted library keeps its original structure, with annotations added inline. A `.kb.json` manifest at the library root tracks annotation progress.

---

## Annotation Schema

**Tag format:** Doxygen-compatible with custom extensions. Parseable by standard tools and custom extractors.

```cpp
/**
 * @brief Select pivot element for basis update
 *
 * @algorithm Markowitz pivot selection
 * @math Chooses (i,j) minimizing (r_i - 1)(c_j - 1) where r_i = nonzeros in row i,
 *       c_j = nonzeros in column j. Balances sparsity preservation with numerical stability.
 * @complexity O(nnz) scan of active submatrix
 * @ref Markowitz, H. (1957). "The Elimination Form of the Inverse and Its
 *      Application to Linear Programming". Management Science 3(3):255-269.
 *
 * @param matrix Active submatrix of the basis
 * @param tolerance Minimum acceptable pivot magnitude for numerical stability
 * @return PivotResult containing row, column indices and pivot value
 *
 * @invariant Returned pivot satisfies |value| >= tolerance
 * @see updateBasis(), factorize()
 */
```

**Tag definitions:**

| Tag | Purpose | Required when |
|-----|---------|---------------|
| `@brief` | One-line summary (what, not how) | All public symbols |
| `@algorithm` | Named technique/method | Implementing known algorithm |
| `@math` | Formulas, theorems, mathematical basis | Any non-trivial math |
| `@complexity` | Time/space analysis | Algorithms, hot paths |
| `@ref` | Literature citation | Citing papers/books |
| `@param` | Parameter description | Public functions |
| `@return` | Return value description | Non-void public functions |
| `@invariant` | Conditions maintained/required | Stateful code, data structures |
| `@see` | Cross-references | Related functions/concepts |
| `@note` | Implementation details, gotchas | Non-obvious behavior |

**Validation:** A linter will check that required tags are present based on context.

---

## Two-Pass Annotation Process

### Pass 1: Structure + Shallow Semantics

*Goal:* Establish what the code does and how it's organized.

| Activity | Output |
|----------|--------|
| Parse file structure | `@brief` for all classes/functions |
| Document interfaces | `@param`, `@return` for public APIs |
| Identify data flow | `@see` cross-references |
| Extract invariants from asserts/docs | `@invariant` where obvious |
| Note unclear areas | `@todo` markers for Pass 2 |

*Agent prompt pattern:*
> "Annotate this file with structural tags. For each public symbol, write a `@brief`. Document parameters and returns. Add `@see` for obvious relationships. Mark anything requiring deeper analysis with `@todo`."

### Pass 2: Deep Semantics

*Goal:* Explain why the code works and connect to theory.

| Activity | Output |
|----------|--------|
| Identify algorithms | `@algorithm` with standard names |
| Document math | `@math` with formulas/theorems |
| Analyze complexity | `@complexity` with justification |
| Find literature | `@ref` citations |
| Resolve `@todo` markers | Replace with proper tags |

*Agent prompt pattern:*
> "This file implements [context from Pass 1]. For each `@todo` and each algorithm implementation, add `@algorithm`, `@math`, `@complexity`, and `@ref` tags. Cite specific papers where applicable."

**Review checkpoint:** Human reviews after each pass before proceeding. Feedback improves agent prompts for subsequent files.

---

## Knowledge Base Output Format

**Source of truth:** The annotated source code itself. Everything else is derived.

**Generated artifacts:**

```
.kb/
├── indexes/
│   ├── symbols.json          # All annotated symbols with tags
│   ├── algorithms.json       # @algorithm tags → code locations
│   ├── math-concepts.json    # @math tags → formulas, locations
│   ├── references.json       # @ref tags → bibliography
│   ├── call-graph.json       # Function → calls relationships
│   └── cross-refs.json       # @see links as graph edges
├── extracts/
│   ├── CoinUtils/
│   │   ├── overview.md       # Library summary
│   │   ├── sparse-matrix.md  # Concept deep-dive
│   │   └── api-reference.md  # Generated from @brief/@param
│   └── ...
├── log/
│   ├── progress.md           # Running log of what's done
│   ├── snarls/               # Issue spikes when we hit problems
│   └── retrospectives/       # Per-library lessons learned
└── schemas/
    ├── tags.json             # Tag definitions for validation
    └── library-manifest.json # Processing status per library
```

**Index schema example (algorithms.json):**

```json
{
  "markowitz-pivot": {
    "name": "Markowitz pivot selection",
    "locations": [
      {"file": "layer-1/Clp/src/ClpFactorization.cpp", "line": 342}
    ],
    "math": "Minimizes (r_i - 1)(c_j - 1) for fill-in reduction",
    "refs": ["markowitz1957"],
    "related": ["lu-factorization", "sparse-matrix"]
  }
}
```

**Query patterns supported:**
- "What implements Markowitz?" → `algorithms.json`
- "What calls `factorize()`?" → `call-graph.json`
- "Papers on interior point methods?" → `references.json` filtered by topic

---

## Tooling & Automation Pipeline

**Scripts:**

```
scripts/
├── extract-zips.sh       # Unzip to layer-N/ directories
├── annotate.py           # Agent orchestration for annotation
├── validate.py           # Lint annotations for completeness
├── generate-indexes.py   # Build .kb/ from annotated source
└── diff-report.py        # Show annotation coverage/progress
```

**Prompt templates:**

```
prompts/
├── pass1-structural.md   # Agent prompt template for Pass 1
├── pass2-semantic.md     # Agent prompt template for Pass 2
└── library-context/      # Per-library context snippets
    ├── coinutils.md
    ├── clp.md
    └── ...
```

**Annotation workflow:**

```
Raw source → Pass 1 (agent) → Review (human) → Pass 2 (agent) → Review (human) → Generate indexes
```

**Progress tracking:** `.kb/status.json` tracks per-file state: `raw` → `pass1` → `reviewed1` → `pass2` → `reviewed2` → `complete`

---

## Quality & Review Process

**Review criteria by pass:**

| Pass 1 Review | Pass 2 Review |
|---------------|---------------|
| `@brief` accurate and useful? | `@algorithm` names correct? |
| `@param`/`@return` complete? | `@math` formulas accurate? |
| Cross-refs (`@see`) sensible? | `@complexity` analysis sound? |
| No functional code changes? | `@ref` citations verifiable? |
| Formatting consistent? | Math-code mapping clear? |

**Feedback loop:**

```
Review file → Note issues → Categorize:
├── Agent fixable    → Update prompt, re-run on this file
├── Prompt problem   → Improve prompt template for future files
├── Schema problem   → Adjust tag definitions
└── Human-only       → Fix manually, document why
```

**Quality signals to track:**
- **Coverage:** % of public symbols with `@brief`
- **Depth:** % of algorithm implementations with `@algorithm` + `@math`
- **Accuracy:** Sampled spot-checks against literature
- **Consistency:** Lint pass rate, style uniformity

**Iteration cadence:**
1. Annotate 3-5 files in a module
2. Human reviews batch
3. Refine prompts based on patterns
4. Continue with improved prompts
5. After completing a library, retrospective: what worked, what to change?

**Acceptance criteria for "complete" library:**
- All public APIs have `@brief`, `@param`, `@return`
- All algorithm implementations have `@algorithm`, `@math`
- Validation linter passes with no errors
- Human spot-check of 10% of annotations confirms accuracy

---

## Progress Log & Meta-Improvement

**Progress log format:**

```markdown
## 2024-01-15
- Completed: CoinUtils/src/CoinPackedMatrix.cpp (Pass 1 + 2)
- Issue: Agent confused Markowitz pivot with Markowitz portfolio theory
- Fix: Added disambiguation to library-context/coinutils.md
- Next: CoinPackedVector.cpp
```

**Snarl spike format:**

```markdown
# Snarl: Template Metaprogramming in CppAD

## Problem
Agent struggles to annotate expression template code - the "algorithm"
is compile-time, not runtime.

## Options considered
1. Skip template machinery, annotate only public API
2. Create new tags: @meta-algorithm, @compile-time
3. Annotate with prose @note explaining the pattern

## Decision
Option 3 - prose explanation, defer specialized tags

## Follow-up
Revisit if we hit this pattern frequently
```

---

## Future: Student Adaptation (Phase 2)

**Goal:** Transform agent-parsable annotations into educational materials.

**What changes:**

| Agent-focused (Phase 1) | Student-focused (Phase 2) |
|------------------------|---------------------------|
| `@math` terse formulas | Expanded derivations, intuition |
| `@algorithm` names only | Step-by-step explanations |
| `@ref` citations | Links to accessible resources |
| Assumes math background | Defines prerequisites |

**Layered annotation approach:**

```cpp
/**
 * @brief Select pivot element for basis update
 * @algorithm Markowitz pivot selection
 * @math Minimizes (r_i - 1)(c_j - 1)
 *
 * @student-explanation
 * When we eliminate variables in Gaussian elimination, each step can create
 * new non-zeros ("fill-in"). Markowitz's insight: choose pivots that minimize
 * fill-in by picking elements where the row and column are already sparse.
 *
 * @prereq Linear algebra (matrix factorization), basic complexity analysis
 * @exercise Try modifying the tolerance parameter - what happens to
 *           numerical stability vs. sparsity?
 */
```

**Not designed now, but preserved:** The structured tags from Phase 1 make Phase 2 tractable.

---

## Next Steps

1. Set up directory structure and extract zips to layer directories
2. Create initial prompt templates for Pass 1
3. Start with CoinUtils (smallest Layer 0 library)
4. Annotate 3-5 files, review, refine prompts
5. Complete CoinUtils, write retrospective
6. Proceed to SuiteSparse, then Layer 1
