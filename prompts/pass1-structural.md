# Pass 1: Structural Annotation

## Your Task

Annotate the provided source file with structural documentation. Focus on **what** the code does, not **why** it works.

## Instructions

1. **Read the entire file first** to understand its structure
2. **Add `@brief`** to every public class, struct, function, and method
3. **Add `@param`** for each parameter of public functions
4. **Add `@return`** for non-void public functions
5. **Add `@see`** for obvious relationships (overloads, related functions, base classes)
6. **Add `@invariant`** where clear from assertions or existing comments
7. **Add `@todo PASS2:`** to mark anything needing deeper algorithm/math analysis

## What NOT to Do

- Do NOT add `@algorithm`, `@math`, `@complexity`, or `@ref` tags (those are Pass 2)
- Do NOT deeply analyze algorithm internals
- Do NOT change any functional code
- Do NOT add comments to private implementation details unless they help understand public API

## Quality Standards

- Every `@brief` must be meaningful, not just restating the function name
  - BAD: `@brief Get the number of rows`
  - GOOD: `@brief Return the row count of the constraint matrix`
- Parameters should explain what the parameter represents, not just its type
- Cross-references (`@see`) should point to genuinely related code

## Output Format

Return the complete annotated file. Preserve all original code exactly - only add/modify comments.

## Context

**Library:** {{LIBRARY_NAME}}
**Layer:** {{LAYER}}
**File purpose:** {{FILE_PURPOSE}}

{{LIBRARY_CONTEXT}}
