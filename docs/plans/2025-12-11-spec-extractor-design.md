# COIN-OR Spec Extractor MCP Tool

## Purpose

An MCP tool that extracts language-agnostic pseudocode specifications from COIN-OR classes, designed for porters and new solver authors.

**Primary users**:
- Porters writing drop-in replacements in Rust, Go, Julia, etc.
- New solver authors extending tools like minilp who want to learn from COIN-OR's battle-tested implementations

**Problem solved**: The knowledge base addresses discovery, comprehension, and context well. Specification extraction—turning dense C++ into portable algorithmic descriptions—remains manual work. This tool automates that.

## Interface

**Tool**: `extract_spec`

| Parameter | Type | Required | Description |
|-----------|------|----------|-------------|
| `class_name` | string | yes | Class to extract (e.g., `CoinSearchTree`) |
| `output_dir` | string | no | Where to write spec (default: `./specs/`) |

**Output**: Writes `{output_dir}/{class_name}.pseudo.md`

## Data Sources

The tool combines three inputs (in priority order):

1. **Source code** — The `.hpp` file from `layer-*/`
2. **Annotations** — `@algorithm`, `@math`, `@complexity` tags in the source
3. **API JSON** — Structured metadata from `site/static/api/<library>/<class>.json`

## Architecture

```
plugins/coin-or-spec/
├── plugin.json           # MCP manifest
├── mcp-server.py         # FastMCP server
└── prompts/
    └── extract-spec.md   # System prompt for extraction
```

**Resolution flow**:
1. Search `site/static/api/*/` for matching JSON file
2. From JSON, get source file path in `layer-*/`
3. Read the source `.hpp` file
4. Combine: source + JSON metadata + annotations
5. Pass to LLM with extraction prompt
6. Write result to `{output_dir}/{class_name}.pseudo.md`

## Output Format

```markdown
# {ClassName} Specification

## Purpose
One paragraph: what problem this class solves.

## Data Structures
Key state variables with types and invariants.

## Core Algorithm
Pseudocode for the main operation(s). Language-agnostic,
explicit about iteration order, early exits, edge cases.

## Invariants
What must be true before/after key operations.

## Numerical Considerations
Tolerances, potential overflow, degeneracy handling.

## Edge Cases
Empty inputs, boundary conditions, error states.

## Design Decisions
Why this approach? What alternatives exist?
```

## Prompt Principles

- Prefer explicit loops over "process all X"
- Name tolerances/epsilons explicitly (don't hide magic numbers)
- Flag C++-isms that won't port (RAII, templates, pointer arithmetic)
- Distinguish "must do" from "optimization"

## Usage Example

```
User: I'm porting CoinSearchTree to Rust. Extract the spec.

Claude: [calls extract_spec(class_name="CoinSearchTree")]

→ Writes specs/CoinSearchTree.pseudo.md

Claude: I've extracted the specification for CoinSearchTree.
Key points:
- Maintains a priority queue of nodes sorted by bound
- Core operations: push, pop, prune_by_bound
- Invariant: queue always sorted, no node with bound worse than incumbent
- Watch out for: floating-point comparison tolerance (1e-7 default)

The full spec is in specs/CoinSearchTree.pseudo.md
```

## Future Extensions

Once class-level extraction works well:
- **Algorithm focus**: Extract specs for concepts across multiple classes
- **Comparison mode**: Show how different libraries implement the same algorithm
- **Test generation**: Derive behavioral test cases from specs
