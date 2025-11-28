# Pass 2: Semantic Annotation

## Your Task

Enhance the structurally-annotated file with semantic documentation explaining **why** the code works and connecting it to mathematical/algorithmic theory.

## Instructions

1. **Review existing annotations** from Pass 1
2. **Resolve all `@todo PASS2:` markers** - replace with appropriate semantic tags
3. **Add `@algorithm`** where code implements a named technique
4. **Add `@math`** to explain mathematical foundations with formulas
5. **Add `@complexity`** with time/space analysis for algorithms
6. **Add `@ref`** to cite relevant literature
7. **Add `@note`** for non-obvious implementation details

## Tag Guidelines

### @algorithm
Use standard algorithm names. Examples:
- `@algorithm Revised simplex method`
- `@algorithm Markowitz pivot selection`
- `@algorithm Branch and bound with best-first search`

### @math
Include actual formulas using ASCII or LaTeX-style notation:
- `@math Reduced cost: c_j - c_B * B^{-1} * A_j`
- `@math KKT conditions: grad_f + sum(lambda_i * grad_g_i) = 0`

### @complexity
Include justification:
- `@complexity O(n^2) - nested loops over rows and columns`
- `@complexity O(nnz log n) - sparse matrix-vector multiply with sorted indices`

### @ref
Full citations:
- `@ref Dantzig, G. (1963). "Linear Programming and Extensions". Princeton.`
- `@ref Forrest, Tomlin (1972). "Updated triangular factors of the basis..."`

## Handling Uncertainty

If unsure about algorithm identity:
```
@note Appears to implement a variant of [technique]. Verify against [source].
```

If math is clear but source unknown:
```
@math [formula]
@note Standard formulation; see any LP textbook.
```

## What NOT to Do

- Do NOT leave any `@todo PASS2:` markers unresolved
- Do NOT guess at citations - mark uncertain with `@note`
- Do NOT change any functional code
- Do NOT add `@algorithm` to trivial code (simple getters, etc.)

## Output Format

Return the complete annotated file with all Pass 1 annotations preserved and Pass 2 annotations added.

## Context

**Library:** {{LIBRARY_NAME}}
**Layer:** {{LAYER}}
**File purpose:** {{FILE_PURPOSE}}
**Pass 1 notes:** {{PASS1_NOTES}}

{{LIBRARY_CONTEXT}}
