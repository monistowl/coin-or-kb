# Pseudocode Specification Extraction

You are extracting a language-agnostic specification from a COIN-OR C++ class. The goal is to produce documentation that enables:
1. **Porters** to reimplement this class in Rust, Go, Julia, or other languages
2. **New solver authors** to understand the design decisions and trade-offs

## Output Format

Generate a markdown document with these sections:

```markdown
# {ClassName} Specification

## Purpose
One paragraph: what problem does this class solve? What role does it play in an optimization solver?

## Data Structures
List key state variables. For each:
- Name and semantic type (not C++ type)
- What it represents
- Invariants it must maintain

Example:
- `node_queue`: Priority queue of search nodes, ordered by bound (best-first)
  - Invariant: No node with bound worse than incumbent

## Core Algorithm

Pseudocode for the main operation(s). Use this style:

```
FUNCTION process_node(node):
    bound ← solve_lp_relaxation(node)

    IF bound ≤ incumbent THEN
        RETURN PRUNED

    IF solution_is_integer(node) THEN
        incumbent ← bound
        RETURN SOLUTION_FOUND

    (left, right) ← branch_on_variable(node)
    queue.push(left)
    queue.push(right)
    RETURN BRANCHED
```

Be explicit about:
- Iteration order (when it matters)
- Early exits and their conditions
- What triggers state changes

## Invariants

Pre/post conditions for key operations:

- **Before** `process_node`: node.bound > incumbent
- **After** `process_node`: incumbent may have improved, queue may have grown
- **Always**: queue contains only nodes with bound > incumbent

## Numerical Considerations

- **Tolerances**: Name them explicitly (e.g., `EPSILON = 1e-7` for bound comparisons)
- **Overflow risks**: Where might values exceed representable range?
- **Degeneracy**: How does the code handle ties, cycles, or numerically unstable cases?

## Edge Cases

What happens when:
- Input is empty?
- All variables are already integer?
- Problem is infeasible or unbounded?
- Numerical precision causes issues?

## Design Decisions

Answer these questions based on the code:
- Why this data structure? (What are the alternatives?)
- Why this algorithm variant? (What trade-offs does it make?)
- What's required vs. what's an optimization?
```

## Extraction Guidelines

### DO:
- Use explicit loops with clear termination conditions
- Name all tolerances and magic numbers
- Distinguish "must do" (correctness) from "should do" (performance)
- Explain C++ idioms in language-neutral terms
- Note when behavior depends on configuration/parameters

### DON'T:
- Include C++ implementation details (memory management, templates, pointers)
- Copy verbatim comments from source (rephrase for clarity)
- Assume reader knows COIN-OR conventions
- Include code that only matters for C++ (destructors, copy constructors)

### Translating C++ Idioms:

| C++ Pattern | Pseudocode Equivalent |
|-------------|----------------------|
| `std::vector<T>` | dynamic array |
| `std::map<K,V>` | dictionary/map |
| `iterator begin/end` | FOR EACH element IN collection |
| `nullptr` check | IF object EXISTS |
| RAII cleanup | (omit - note resources if relevant) |
| Template `<T>` | (omit - note if type matters) |
| `const &` parameter | (omit - just use parameter name) |

### Handling Missing Information:

If the source code doesn't reveal something important:
- Say "Implementation detail: [what's unclear]"
- Note what a porter would need to decide

If annotations mention something the code doesn't show:
- Trust the annotations for algorithm/math descriptions
- Note any discrepancies
