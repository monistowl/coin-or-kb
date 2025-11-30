# Zola Documentation Site Design

**Date:** 2024-11-30
**Status:** Approved

## Overview

Static documentation site exposing the COIN-OR knowledge base annotations for both AI agents (primary) and human readers (secondary).

## Architecture

```
C++ Headers → Doxygen → XML → Python Transform → JSON + Markdown → Zola → Static Site
```

### Components

1. **Doxygen config** (`Doxyfile`) - Generate XML for all layers
2. **Transform script** (`scripts/build-docs.py`) - Parse Doxygen XML, emit JSON + Markdown
3. **Zola site** (`site/`) - Templates, config, static assets
4. **Build script** (`scripts/build-site.sh`) - Orchestrates the full pipeline

### Output Structure

```
site/
├── config.toml           # Zola config
├── content/
│   ├── _index.md         # Homepage
│   ├── libraries/        # Per-library pages
│   │   ├── coinutils/
│   │   ├── clp/
│   │   └── ...
│   └── algorithms/       # Cross-cutting algorithm index
├── static/
│   └── api/              # JSON files for AI consumption
│       ├── index.json    # Master index
│       └── libraries/    # Per-library JSON
└── templates/            # Zola templates
```

## JSON Schema (AI-First)

### Master Index (`/api/index.json`)

```json
{
  "version": "1.0",
  "generated": "2024-11-30T...",
  "libraries": [
    {"id": "coinutils", "name": "CoinUtils", "layer": 0, "path": "/api/libraries/coinutils.json"},
    {"id": "clp", "name": "Clp", "layer": 1, "path": "/api/libraries/clp.json"}
  ],
  "algorithms": [
    {"id": "simplex", "name": "Simplex Method", "libraries": ["clp", "highs"]},
    {"id": "interior-point", "name": "Interior Point", "libraries": ["clp", "ipopt"]}
  ],
  "stats": {"total_algorithms": 152, "total_files": 500}
}
```

### Per-Library (`/api/libraries/clp.json`)

```json
{
  "id": "clp",
  "name": "Clp",
  "description": "COIN-OR Linear Programming solver",
  "files": [{
    "path": "src/ClpSimplex.hpp",
    "classes": [{
      "name": "ClpSimplex",
      "brief": "Main simplex solver class",
      "algorithms": [{
        "name": "Dual Simplex",
        "math": "...",
        "complexity": "O(2^n) worst, polynomial average",
        "refs": ["Dantzig (1963)"]
      }],
      "methods": [{
        "name": "dual",
        "signature": "int dual(int ifValuesPass)",
        "brief": "Dual simplex algorithm",
        "params": [{"name": "ifValuesPass", "desc": "..."}],
        "source": "// code snippet..."
      }]
    }]
  }]
}
```

## Markdown Pages & Zola Templates

### Library Page Frontmatter

```yaml
+++
title = "Clp - COIN-OR LP Solver"
description = "Simplex-based linear programming solver"
[taxonomies]
algorithms = ["simplex", "dual-simplex", "interior-point"]
layer = ["layer-1"]
[extra]
json_path = "/api/libraries/clp.json"
+++
```

### Templates

- `templates/index.html` - Homepage with library grid, stats
- `templates/library.html` - Library overview, file list, algorithm summary
- `templates/file.html` - Single file with classes, methods, code
- `templates/algorithm.html` - Cross-cutting: shows all implementations

### Features

- Syntax-highlighted code blocks (Zola built-in)
- KaTeX for rendering `@math` formulas
- Collapsible sections for large method lists
- Search via Pagefind
- Dark/light theme toggle

## Build Process

### Build Script (`scripts/build-site.sh`)

```bash
#!/bin/bash
set -e

# 1. Generate Doxygen XML
doxygen Doxyfile

# 2. Transform to JSON + Markdown
python3 scripts/build-docs.py

# 3. Build Zola site
cd site && zola build
```

### Doxygen Config Highlights

```
GENERATE_XML = YES
XML_OUTPUT = .kb/doxygen-xml
EXTRACT_ALL = YES
INPUT = layer-0 layer-1 layer-2 layer-3 layer-4
FILE_PATTERNS = *.h *.hpp
```

## Implementation Order

1. Minimal Zola scaffold with placeholder content
2. Doxygen config that successfully parses the codebase
3. Python transform script (XML → JSON + Markdown)
4. Zola templates to render the generated content
5. Algorithm cross-index generation
6. Polish: search, math rendering, styling

## Hosting

Static output in `public/` - deployable to GitHub Pages, Netlify, or any static host.
