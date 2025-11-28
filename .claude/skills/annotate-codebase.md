---
name: annotate-codebase
description: Recursively annotate solver codebases with structured Doxygen-compatible documentation, capturing insights and self-improving over time. Use when annotating any file in layer-0 through layer-4.
---

# Annotate Codebase Skill

## Purpose

Systematically annotate C/C++ source files in the COIN-OR solver ecosystem with structured documentation that captures both code structure and mathematical principles.

## MANDATORY: Read Before Annotating

Before ANY annotation work, you MUST read:
1. `/home/tom/Code/vendor/AGENTS.md` - Master annotation guide
2. The relevant prompt template for your pass
3. Library-specific context if it exists

## The Two-Pass Annotation Process

### Pass 1: Structural (WHAT the code does)
- `@file`, `@brief` for every public symbol
- `@param` for all function parameters
- `@return` for non-void functions
- `@tparam` for template parameters
- `@see` for cross-references

**Prompt template:** `/home/tom/Code/vendor/prompts/pass1-structural.md`

### Pass 2: Semantic (WHY the code works)
- `@algorithm` with name and complexity
- `@math` for mathematical foundations
- `@complexity` for performance characteristics
- `@invariant` for class/loop invariants
- `@ref` for external citations

**Prompt template:** `/home/tom/Code/vendor/prompts/pass2-semantic.md`

## Tag Reference

For complete tag syntax, examples, and common patterns, see:
`.claude/skills/annotation-tags-reference.md`

## Workflow Checklist

### Before Starting a Library

- [ ] Check `.kb/status.json` for current library status
- [ ] Read library context file if exists: `/home/tom/Code/vendor/prompts/library-context/{library}.md`
- [ ] If no context file, create one from README and key headers
- [ ] Run baseline validation: `python3 scripts/validate.py layer-X/{Library}/src --summary`

### For Each File

- [ ] **Quick assessment** (~1 min skim):
  - Existing docs: none / partial / good?
  - Public API surface: how many classes/functions?
  - Depth needed: **Light** (good docs) or **Full** (sparse docs)?
- [ ] Read the ENTIRE file to understand structure
- [ ] Apply appropriate pass template
- [ ] Add annotations WITHOUT changing any code logic
- [ ] Validate: `python3 scripts/validate.py {file} --pass1`
- [ ] Fix any errors before moving on

**Light annotation:** `@file` header, `@see` cross-refs, format fixes only
**Full annotation:** Complete Pass 1 tags on all public API

### After Completing a Batch (5-10 files)

- [ ] Run coverage report: `python3 scripts/coverage-report.py layer-X/{Library}/src`
- [ ] Update status: `python3 scripts/update-status.py {library}`
- [ ] If any issues arose, document in retrospective (see Meta-Improvement)

### After Completing a Library

- [ ] Final validation: `python3 scripts/validate.py layer-X/{Library}/src --summary`
- [ ] Write retrospective to `.kb/log/retrospectives/{library}-retro.md`
- [ ] Update `.kb/status.json` with completion status
- [ ] Review insights and update this skill if needed

## Layer Processing Order

Process in dependency order to build understanding incrementally:

```
Layer 0 (foundations): CoinUtils, SuiteSparse
Layer 1 (LP/QP): Clp, Osi, qpOASES
Layer 2 (MIP): Cbc, Cgl, SYMPHONY
Layer 3 (NLP): Ipopt, Couenne, Bonmin
Layer 4 (applications): HiGHS, Gravity, SHOT
```

## Meta-Improvement: The Self-Improving Loop

This skill improves over time. Here's how:

### Capturing Insights

When you encounter ANY of these, document immediately:

1. **Validator limitations** - Regex doesn't parse X correctly
2. **Prompt gaps** - Instructions unclear for case Y
3. **Domain knowledge** - Mathematical insight Z would help
4. **Pattern discoveries** - Files of type W benefit from approach V

**Document to:** `.kb/log/retrospectives/{library}-{date}-insights.md`

### Snarl Spikes

When annotation gets stuck or confusing, create a snarl spike:

```markdown
# Snarl Spike: {Brief Description}

**File:** {path}
**Symptom:** {what went wrong}
**Root cause:** {why it happened}
**Resolution:** {how you fixed it}
**Prevention:** {how to avoid in future}
```

**Save to:** `.kb/log/snarls/{date}-{brief-slug}.md`

### Incorporating Improvements

After each retrospective, ask:

1. Should AGENTS.md be updated? → Update it
2. Should prompt templates change? → Update them
3. Should this skill change? → Update it
4. Should validation tooling improve? → Create issue or fix

**The skill definition itself should evolve.** Edit this file when you learn something that would help future annotation work.

## Quality Gates

### Pass 1 Minimum Requirements
- Every public class/struct has `@brief`
- Every public function has `@brief`
- Every parameter has `@param`
- Every non-void return has `@return`
- Every template param has `@tparam`

### Pass 2 Minimum Requirements
- Non-trivial algorithms have `@algorithm`
- Mathematical operations have `@math` or references
- Complex operations have `@complexity`
- Key invariants are documented

### Coverage Targets
- Pass 1: 95%+ of public symbols documented
- Pass 2: All algorithms and mathematical operations explained

## Handling Uncertainty

When you're unsure about something:

1. **Algorithm name unknown:** Use `@todo PASS2: Identify algorithm`
2. **Math unclear:** Add `@note Implementation details need expert review`
3. **Historical context missing:** Check git blame, add what you find
4. **Complexity uncertain:** Add `@complexity` with your best estimate and `@todo verify`

Never leave symbols undocumented because you're uncertain. Document what you know, flag what you don't.

## Example Annotation Block

```cpp
/**
 * @file CoinPackedVector.hpp
 * @brief Sparse vector implementation using index-value pairs
 *
 * Provides efficient storage for vectors with many zero elements,
 * common in LP constraint matrices. Supports sorted and unsorted modes
 * for different access patterns.
 *
 * @see CoinPackedMatrix for 2D sparse storage
 */

/**
 * @brief Add a single element to the sparse vector
 *
 * @param index Position in the conceptual dense vector
 * @param element Value to store at that position
 *
 * @algorithm Linear insertion, maintains sort order if vector is sorted
 * @complexity O(n) worst case if sorted, O(1) amortized if unsorted
 *
 * @note Duplicate indices are allowed; semantics depend on usage
 */
void insert(int index, double element);
```

## Validation Commands

```bash
# Check single file (Pass 1)
python3 scripts/validate.py path/to/file.hpp --pass1

# Check single file (Pass 2)
python3 scripts/validate.py path/to/file.hpp --pass2

# Coverage summary for library
python3 scripts/coverage-report.py layer-X/Library/src

# Update status tracking
python3 scripts/update-status.py library-name
```

## Recovery from Mistakes

If you realize you've made annotation errors:

1. Don't panic - annotations don't change code behavior
2. Re-read the file with fresh eyes
3. Fix incorrect annotations in place
4. Run validation to confirm fixes
5. Document what went wrong in a snarl spike

## Session Continuity

If a session is interrupted:

1. Check `.kb/status.json` for last known state
2. Run validation on the last library worked on
3. Pick up from the last incomplete file
4. Re-read library context before continuing

---

## Changelog

Track improvements to this skill here:

### 2025-11-28 (Initial)
- Created from pilot annotation of 5 CoinUtils files
- Incorporated lessons from `coinutils-pilot-retro.md`:
  - Validator has `@param[out]` parsing limitation
  - Member initializers cause false positive function detections
  - `@todo PASS2:` pattern works well for flagging semantic gaps

### 2025-11-28 (Session 2)
- Added "Quick Assessment" step to For Each File checklist
- Defined Light vs Full annotation depth
- Added cross-reference to annotation-tags-reference.md
- Lessons from session 2 retrospective:
  - Files with existing Doxygen docs need light touch only
  - Tag counts are more reliable progress metric than validator coverage %
