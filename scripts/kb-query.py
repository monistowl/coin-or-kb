#!/usr/bin/env python3
"""
Quick query tool for COIN-OR Knowledge Base.

Usage:
  kb-query.py algo <query>     - Search algorithms
  kb-query.py math <query>     - Search mathematical concepts
  kb-query.py lib <name>       - Get library overview
  kb-query.py file <lib> <f>   - Get file annotations
  kb-query.py list             - List all algorithms
  kb-query.py stats            - Show statistics

Examples:
  kb-query.py algo "LU factorization"
  kb-query.py math "clique"
  kb-query.py lib CoinUtils
  kb-query.py file CoinUtils CoinFactorization.hpp
"""

import json
import sys
from pathlib import Path


def load_kb():
    """Load knowledge base JSON."""
    for p in [
        Path(__file__).parent.parent / 'site/static/api/annotations.json',
        Path('site/static/api/annotations.json'),
    ]:
        if p.exists():
            with open(p) as f:
                return json.load(f)
    print("Error: annotations.json not found", file=sys.stderr)
    sys.exit(1)


def search_algorithms(kb, query):
    """Search for algorithms."""
    query_lower = query.lower()
    results = []

    for layer_name, layer in kb.get('layers', {}).items():
        for lib_name, lib in layer.get('libraries', {}).items():
            for file_path, data in lib.get('files', {}).items():
                algo = data.get('algorithm', '')
                if query_lower in algo.lower():
                    print(f"\n=== {lib_name}/{file_path} ===")
                    print(f"Brief: {data.get('brief', 'N/A')}")
                    print(f"\nAlgorithm:\n{algo[:800]}")
                    if data.get('complexity'):
                        print(f"\nComplexity: {data['complexity'][:200]}")
                    results.append(file_path)

    print(f"\n--- Found {len(results)} files ---")


def search_math(kb, query):
    """Search for math concepts."""
    query_lower = query.lower()
    results = []

    for layer_name, layer in kb.get('layers', {}).items():
        for lib_name, lib in layer.get('libraries', {}).items():
            for file_path, data in lib.get('files', {}).items():
                math = data.get('math', '')
                if query_lower in math.lower():
                    print(f"\n=== {lib_name}/{file_path} ===")
                    print(f"Brief: {data.get('brief', 'N/A')}")
                    print(f"\nMath:\n{math[:600]}")
                    results.append(file_path)

    print(f"\n--- Found {len(results)} files ---")


def get_library(kb, name):
    """Get library overview."""
    name_lower = name.lower()

    for layer_name, layer in kb.get('layers', {}).items():
        for lib_name, lib in layer.get('libraries', {}).items():
            if lib_name.lower() == name_lower:
                print(f"=== {lib_name} ({layer_name}) ===")
                print(f"Files: {lib.get('file_count', 0)}")
                print(f"Pass 2 (semantic): {lib.get('pass2_count', 0)}")

                print("\nFiles with semantic annotations:")
                for f, data in lib.get('files', {}).items():
                    if data.get('has_pass2'):
                        algo = data.get('algorithm', '')
                        algo_short = algo.split('\n')[0][:60] if algo else ''
                        print(f"  {f}")
                        print(f"    {data.get('brief', '')[:70]}")
                        if algo_short:
                            print(f"    @algorithm: {algo_short}...")
                return

    print(f"Library '{name}' not found")


def get_file(kb, library, file_query):
    """Get file annotations."""
    lib_lower = library.lower()
    file_lower = file_query.lower()

    for layer_name, layer in kb.get('layers', {}).items():
        for lib_name, lib in layer.get('libraries', {}).items():
            if lib_name.lower() == lib_lower:
                for f, data in lib.get('files', {}).items():
                    if file_lower in f.lower():
                        print(f"=== {lib_name}/{f} ===\n")
                        for key in ['brief', 'algorithm', 'math', 'complexity', 'ref', 'see']:
                            if data.get(key):
                                val = data[key]
                                if isinstance(val, list):
                                    val = '\n  '.join(val)
                                print(f"@{key}:\n  {val}\n")
                        return

    print(f"File '{file_query}' not found in {library}")


def list_algorithms(kb):
    """List all documented algorithms."""
    algos = []

    for layer_name, layer in kb.get('layers', {}).items():
        for lib_name, lib in layer.get('libraries', {}).items():
            for file_path, data in lib.get('files', {}).items():
                if data.get('algorithm'):
                    name = data['algorithm'].split('\n')[0].split(':')[0].strip()
                    algos.append((lib_name, file_path, name))

    print(f"Documented algorithms ({len(algos)}):\n")
    for lib, f, name in sorted(algos, key=lambda x: x[0]):
        print(f"  {lib:20} {name[:50]}")
        print(f"                       → {f}")


def show_stats(kb):
    """Show knowledge base statistics."""
    stats = kb.get('stats', {})
    print("=== COIN-OR Knowledge Base Statistics ===\n")
    print(f"Layers: {stats.get('total_layers', 0)}")
    print(f"Libraries: {stats.get('total_libraries', 0)}")
    print(f"Annotated files: {stats.get('total_files', 0)}")
    print(f"Files with Pass 2 (semantic): {stats.get('total_pass2_files', 0)}")

    print("\nBy layer:")
    for layer_name, layer in kb.get('layers', {}).items():
        files = sum(lib.get('file_count', 0) for lib in layer.get('libraries', {}).values())
        pass2 = sum(lib.get('pass2_count', 0) for lib in layer.get('libraries', {}).values())
        print(f"  {layer_name}: {files} files, {pass2} with semantic annotations")


def main():
    if len(sys.argv) < 2:
        print(__doc__)
        sys.exit(1)

    kb = load_kb()
    cmd = sys.argv[1].lower()

    if cmd == 'algo' and len(sys.argv) > 2:
        search_algorithms(kb, ' '.join(sys.argv[2:]))
    elif cmd == 'math' and len(sys.argv) > 2:
        search_math(kb, ' '.join(sys.argv[2:]))
    elif cmd == 'lib' and len(sys.argv) > 2:
        get_library(kb, sys.argv[2])
    elif cmd == 'file' and len(sys.argv) > 3:
        get_file(kb, sys.argv[2], sys.argv[3])
    elif cmd == 'list':
        list_algorithms(kb)
    elif cmd == 'stats':
        show_stats(kb)
    else:
        print(__doc__)
        sys.exit(1)


if __name__ == '__main__':
    main()
