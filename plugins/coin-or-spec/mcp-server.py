#!/usr/bin/env python3
"""
COIN-OR Spec Extractor MCP Server

Extracts language-agnostic pseudocode specifications from COIN-OR classes
for porters and new solver authors.
"""

import json
import os
from pathlib import Path
from typing import Optional

from fastmcp import FastMCP

# Initialize FastMCP server
mcp = FastMCP("coin-or-spec")

# Base paths - adjust if needed
REPO_ROOT = Path(__file__).parent.parent.parent  # coin-or-kb/
API_DIR = REPO_ROOT / "site" / "static" / "api"
PROMPTS_DIR = Path(__file__).parent / "prompts"


def find_class_json(class_name: str) -> Optional[dict]:
    """Search all library API directories for a matching class JSON."""
    class_lower = class_name.lower()

    for lib_dir in API_DIR.iterdir():
        if not lib_dir.is_dir():
            continue

        # Try exact match first
        json_path = lib_dir / f"{class_lower}.json"
        if json_path.exists():
            with open(json_path) as f:
                return json.load(f)

        # Try case-insensitive search
        for json_file in lib_dir.glob("*.json"):
            if json_file.stem.lower() == class_lower:
                with open(json_file) as f:
                    return json.load(f)

    return None


def find_source_file(class_info: dict) -> Optional[Path]:
    """Locate the source file for a class."""
    # Try different field names used in the JSON
    header = class_info.get("header_file") or class_info.get("header")
    if not header:
        return None

    # Header might be relative to library or absolute from repo root
    layer = class_info.get("layer", "")
    library = class_info.get("library", "")

    # Try direct path first (layer-X/Library/...)
    if header.startswith("layer-"):
        source_path = REPO_ROOT / header
        if source_path.exists():
            return source_path

    # Try constructing path from library info
    if layer and library:
        layer_str = layer if isinstance(layer, str) else f"layer-{layer}"
        source_path = REPO_ROOT / layer_str / library / header
        if source_path.exists():
            return source_path

    # Search for the file
    for layer_dir in REPO_ROOT.glob("layer-*"):
        for hpp_file in layer_dir.rglob("*.hpp"):
            if hpp_file.name.lower() == Path(header).name.lower():
                return hpp_file

    return None


def load_extraction_prompt() -> str:
    """Load the extraction system prompt."""
    prompt_path = PROMPTS_DIR / "extract-spec.md"
    if prompt_path.exists():
        return prompt_path.read_text()

    # Fallback prompt if file doesn't exist
    return """Extract a language-agnostic pseudocode specification from this COIN-OR class.

Output format:
# {ClassName} Specification

## Purpose
One paragraph explaining what problem this class solves.

## Data Structures
Key state variables with types and invariants.

## Core Algorithm
Pseudocode for main operations. Be explicit about:
- Iteration order
- Early exits and edge cases
- Tolerances and numerical considerations

## Invariants
Pre/post conditions for key operations.

## Numerical Considerations
Tolerances, overflow risks, degeneracy handling.

## Edge Cases
Empty inputs, boundary conditions, error states.

## Design Decisions
Why this approach? What alternatives exist?

Guidelines:
- Use explicit loops, not "process all X"
- Name tolerances explicitly (e.g., epsilon = 1e-7)
- Flag C++-isms that won't port (RAII, templates, pointer tricks)
- Distinguish required behavior from optimizations
"""


@mcp.tool()
def extract_spec(class_name: str, output_dir: str = "./specs") -> str:
    """
    Extract a pseudocode specification for a COIN-OR class.

    Args:
        class_name: The class to extract (e.g., "ClpPresolve", "CoinSearchTree")
        output_dir: Directory to write the spec file (default: ./specs)

    Returns:
        Status message with path to generated spec or error details.
    """
    # Find class metadata
    class_info = find_class_json(class_name)
    if not class_info:
        return f"Error: Could not find class '{class_name}' in API data. Try checking site/static/api/ for available classes."

    # Find source file
    source_path = find_source_file(class_info)
    source_code = ""
    if source_path:
        try:
            source_code = source_path.read_text()
        except Exception as e:
            source_code = f"[Could not read source: {e}]"

    # Build context for extraction
    context = {
        "class_name": class_info.get("name", class_name),
        "library": class_info.get("library", "unknown"),
        "brief": class_info.get("brief", ""),
        "algorithms": class_info.get("algorithms", []),
        "methods": class_info.get("methods", []),
        "see_also": class_info.get("see", []),
        "source_file": str(source_path) if source_path else "not found",
        "source_code": source_code[:50000] if source_code else "[no source]",  # Limit size
    }

    # Format algorithms for display
    algo_text = ""
    for algo in context["algorithms"]:
        algo_text += f"\n### Algorithm: {algo.get('name', 'unnamed')}\n"
        if algo.get("math"):
            algo_text += f"Math: {algo['math']}\n"
        if algo.get("complexity"):
            algo_text += f"Complexity: {algo['complexity']}\n"

    # Prepare output
    output_path = Path(output_dir)
    output_path.mkdir(parents=True, exist_ok=True)
    spec_file = output_path / f"{class_name}.pseudo.md"

    # Build the extraction request
    extraction_prompt = load_extraction_prompt()

    # Return the gathered context - the LLM will use this to generate the spec
    result = f"""## Extracted Context for {class_name}

**Library**: {context['library']}
**Source**: {context['source_file']}
**Brief**: {context['brief']}

### Annotations
{algo_text if algo_text else 'No algorithm annotations found.'}

### See Also
{chr(10).join('- ' + s for s in context['see_also']) if context['see_also'] else 'None'}

### Source Code Preview
```cpp
{source_code[:8000] if source_code else '[no source available]'}
```

---

**Output will be written to**: `{spec_file}`

Use the extraction prompt guidelines to generate a complete pseudocode specification from the above context. After generating, write the result to the output file.
"""

    return result


@mcp.tool()
def list_classes(library: str = "") -> str:
    """
    List available classes in the COIN-OR knowledge base.

    Args:
        library: Filter by library name (e.g., "clp", "coinutils"). Empty for all.

    Returns:
        List of available class names.
    """
    classes = []

    for lib_dir in sorted(API_DIR.iterdir()):
        if not lib_dir.is_dir():
            continue

        lib_name = lib_dir.name
        if library and lib_name.lower() != library.lower():
            continue

        for json_file in sorted(lib_dir.glob("*.json")):
            if json_file.name in ("index.json",):
                continue
            classes.append(f"{lib_name}/{json_file.stem}")

    if not classes:
        return f"No classes found{' for library ' + library if library else ''}."

    return f"Found {len(classes)} classes:\n" + "\n".join(classes[:100])


@mcp.tool()
def search_classes(query: str) -> str:
    """
    Search for classes by name or description.

    Args:
        query: Search term (searches class names and briefs)

    Returns:
        Matching classes with their briefs.
    """
    query_lower = query.lower()
    matches = []

    for lib_dir in API_DIR.iterdir():
        if not lib_dir.is_dir():
            continue

        for json_file in lib_dir.glob("*.json"):
            if json_file.name == "index.json":
                continue

            try:
                with open(json_file) as f:
                    data = json.load(f)

                name = data.get("name", json_file.stem)
                brief = data.get("brief", "")

                if query_lower in name.lower() or query_lower in brief.lower():
                    matches.append({
                        "library": lib_dir.name,
                        "name": name,
                        "brief": brief[:100] + "..." if len(brief) > 100 else brief
                    })
            except:
                continue

    if not matches:
        return f"No classes matching '{query}' found."

    result = f"Found {len(matches)} matches:\n\n"
    for m in matches[:20]:
        result += f"**{m['library']}/{m['name']}**\n{m['brief']}\n\n"

    return result


if __name__ == "__main__":
    mcp.run()
