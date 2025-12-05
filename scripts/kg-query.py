#!/usr/bin/env python3
"""
CLI tool for querying the COIN-OR Mathematical Concept Knowledge Graph.

Usage:
  kg-query.py explore <concept>        Show concept with relationships
  kg-query.py path <from> <to>         Find path between concepts
  kg-query.py prereqs <concept>        Show prerequisites tree
  kg-query.py impl <concept>           Find implementations
  kg-query.py search <query>           Search concepts
  kg-query.py list [category]          List concepts
  kg-query.py categories               Show all categories

Examples:
  kg-query.py explore interior_point_method
  kg-query.py path simplex_method KKT_conditions
  kg-query.py prereqs spatial_branch_and_bound
  kg-query.py impl "LU factorization"
  kg-query.py search convex
  kg-query.py list algorithm
"""

import sys
import json
from pathlib import Path

# Add mcp-server to path for knowledge_graph module
sys.path.insert(0, str(Path(__file__).parent.parent / 'mcp-server'))
from knowledge_graph import KnowledgeGraph


def format_concept(concept: dict, indent: int = 0) -> str:
    """Format a concept for display."""
    prefix = "  " * indent
    lines = []

    lines.append(f"{prefix}╭─ {concept.get('name', concept.get('id', '?'))}")

    if concept.get('aliases'):
        lines.append(f"{prefix}│  aliases: {', '.join(concept['aliases'])}")

    lines.append(f"{prefix}│  category: {concept.get('category', '?')}")

    if concept.get('definition'):
        defn = concept['definition'][:200]
        if len(concept['definition']) > 200:
            defn += "..."
        lines.append(f"{prefix}│  {defn}")

    if concept.get('intuition'):
        lines.append(f"{prefix}│")
        intuition = concept['intuition'][:200]
        if len(concept['intuition']) > 200:
            intuition += "..."
        lines.append(f"{prefix}│  💡 {intuition}")

    if concept.get('key_equations'):
        lines.append(f"{prefix}│")
        lines.append(f"{prefix}│  equations:")
        for eq in concept['key_equations'][:3]:
            lines.append(f"{prefix}│    • {eq}")

    # Relationships
    rels = concept.get('relationships', {})
    if rels:
        lines.append(f"{prefix}│")
        for rel_type, targets in rels.items():
            if targets:
                lines.append(f"{prefix}│  {rel_type}:")
                for t in targets[:5]:
                    tid = t['id'] if isinstance(t, dict) else t
                    lines.append(f"{prefix}│    → {tid}")
                if len(targets) > 5:
                    lines.append(f"{prefix}│    ... and {len(targets) - 5} more")

    if concept.get('used_by'):
        lines.append(f"{prefix}│")
        lines.append(f"{prefix}│  used_by:")
        for u in concept['used_by'][:5]:
            lines.append(f"{prefix}│    ← {u.get('name', u.get('id', '?'))}")

    lines.append(f"{prefix}╰───")
    return "\n".join(lines)


def format_path(result: dict) -> str:
    """Format a path result."""
    if not result.get('found'):
        return f"❌ {result.get('message', 'No path found')}"

    lines = [f"✓ Path found ({result['length']} hops):"]
    lines.append("")

    for i, step in enumerate(result['path']):
        if i == 0:
            lines.append(f"  {step['from_name']}")
        lines.append(f"    │")
        lines.append(f"    ╰─({step['relationship']})─→ {step['to_name']}")

    return "\n".join(lines)


def format_prereqs(result: dict, indent: int = 0) -> str:
    """Format prerequisites tree."""
    lines = []
    prefix = "  " * indent

    if indent == 0:
        lines.append(f"Prerequisites for: {result.get('name', result.get('concept', '?'))}")
        lines.append("")

    for prereq in result.get('requires', []):
        cat = prereq.get('category', '?')
        lines.append(f"{prefix}├─ {prereq['name']} [{cat}]")

        if prereq.get('requires'):
            sub_lines = format_prereqs(prereq, indent + 1)
            lines.append(sub_lines)

    return "\n".join(lines)


def format_implementations(result: dict) -> str:
    """Format implementations list."""
    if result.get('error'):
        return f"❌ {result['error']}"

    lines = [f"Implementations of: {result.get('name', result.get('concept', '?'))}"]
    lines.append(f"Found: {result['implementation_count']} files")
    lines.append("")

    for impl in result.get('implementations', []):
        ref = impl.get('reference', '?')
        brief = impl.get('brief', '')
        lines.append(f"  • {ref}")
        if brief:
            lines.append(f"    {brief[:80]}...")

    return "\n".join(lines)


def format_search(results: list) -> str:
    """Format search results."""
    if not results:
        return "No concepts found."

    lines = [f"Found {len(results)} concepts:"]
    lines.append("")

    for r in results[:10]:
        score = r.get('score', 0)
        cat = r.get('category', '?')
        lines.append(f"  [{score}] {r['name']} ({cat})")
        if r.get('definition'):
            lines.append(f"       {r['definition'][:60]}...")

    if len(results) > 10:
        lines.append(f"  ... and {len(results) - 10} more")

    return "\n".join(lines)


def format_list(results: list) -> str:
    """Format concept list."""
    if not results:
        return "No concepts found."

    # Group by category
    by_cat = {}
    for r in results:
        cat = r.get('category', 'unknown')
        if cat not in by_cat:
            by_cat[cat] = []
        by_cat[cat].append(r)

    lines = []
    for cat, concepts in sorted(by_cat.items()):
        lines.append(f"\n{cat.upper()} ({len(concepts)})")
        lines.append("─" * 40)
        for c in concepts:
            aliases = f" ({', '.join(c['aliases'])})" if c.get('aliases') else ""
            lines.append(f"  • {c['name']}{aliases}")

    return "\n".join(lines)


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)

    kg = KnowledgeGraph()
    cmd = sys.argv[1]

    if cmd == "explore" and len(sys.argv) >= 3:
        concept_id = " ".join(sys.argv[2:])
        result = kg.explore_concept(concept_id)
        if result.get('error'):
            print(f"❌ {result['error']}")
        else:
            print(format_concept(result))

    elif cmd == "path" and len(sys.argv) >= 4:
        from_c = sys.argv[2]
        to_c = sys.argv[3]
        result = kg.find_path(from_c, to_c)
        print(format_path(result))

    elif cmd == "prereqs" and len(sys.argv) >= 3:
        concept_id = " ".join(sys.argv[2:])
        result = kg.prerequisites_for(concept_id)
        if result.get('error'):
            print(f"❌ {result['error']}")
        else:
            print(format_prereqs(result))

    elif cmd == "impl" and len(sys.argv) >= 3:
        concept_id = " ".join(sys.argv[2:])
        result = kg.implementations_of(concept_id)
        print(format_implementations(result))

    elif cmd == "search" and len(sys.argv) >= 3:
        query = " ".join(sys.argv[2:])
        results = kg.search_concepts(query)
        print(format_search(results))

    elif cmd == "list":
        category = sys.argv[2] if len(sys.argv) >= 3 else None
        results = kg.list_concepts(category)
        print(format_list(results))

    elif cmd == "categories":
        cats = kg.get_categories()
        print("Categories:")
        for cat, desc in cats.get('category_descriptions', {}).items():
            count = len(cats.get('categories', {}).get(cat, []))
            print(f"  • {cat} ({count}): {desc}")

    else:
        print(__doc__)
        sys.exit(1)


if __name__ == '__main__':
    main()
