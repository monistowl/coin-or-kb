---
description: Annotate source files using the two-pass documentation process
arguments:
  - name: target
    description: File path, directory, or library name to annotate
    required: true
  - name: pass
    description: Which pass to run (1 or 2, default 1)
    required: false
---

# Annotate Command

You are annotating: `$ARGUMENTS`

## Before You Start

1. Load the annotate-codebase skill: Use `Skill` tool with `annotate-codebase`
2. Read AGENTS.md for full context
3. Check current status in `.kb/status.json`

## Determine What to Annotate

Parse the target argument:
- If it's a file path → annotate that single file
- If it's a directory → annotate all `.hpp` and `.h` files in it
- If it's a library name (e.g., "CoinUtils", "Clp") → find it in the layer structure

## Execute the Workflow

Follow the annotate-codebase skill checklist exactly:

1. Read library context if available
2. For each file:
   - Read entire file first
   - Apply Pass 1 or Pass 2 annotations
   - Validate after
3. Update status when complete
4. Write retrospective if insights emerged

## After Completion

Report:
- Files annotated
- Tags added
- Coverage improvement
- Any issues encountered
