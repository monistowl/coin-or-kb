#!/usr/bin/env python3
"""
kb-status.py

Compact status dashboard combining .kb/status.json and library-mapping.json.
Shows per-layer library progress (pass1/pass2) plus notes. Designed for quick
terminal use by agents.

Usage:
    python scripts/kb-status.py [--layer layer-N] [--show-notes]
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Dict, Any


def load_json(path: Path) -> Dict[str, Any]:
    """Load JSON file with basic error handling."""
    try:
        return json.loads(path.read_text())
    except FileNotFoundError:
        raise SystemExit(f"Missing file: {path}")
    except json.JSONDecodeError as exc:
        raise SystemExit(f"Invalid JSON in {path}: {exc}")


def format_status(lib_entry: Dict[str, Any]) -> str:
    """Render a concise status string."""
    p1 = "pass1_complete" if lib_entry.get("pass1_complete") else ""
    p2 = "pass2_complete" if lib_entry.get("pass2_complete") else ""
    status = lib_entry.get("status", "")
    flags = ", ".join(filter(None, [status, p1, p2]))
    return flags or "unknown"


def print_layer(layer: str, status: Dict[str, Any], mapping: Dict[str, Any], show_notes: bool) -> None:
    """Print a single layer block."""
    layer_meta = status.get("layers", {}).get(layer, {})
    layer_desc = mapping.get(layer, {}).get("description", "")
    libraries = mapping.get(layer, {}).get("libraries", {})

    print(f"\n{layer}: {layer_desc}")
    print("-" * (len(layer) + len(layer_desc) + 2))

    for lib, meta in libraries.items():
        lib_status = layer_meta.get("libraries", {}).get(lib, {})
        flags = format_status(lib_status)
        files_total = lib_status.get("files_total", "?")
        files_done = lib_status.get("files_pass1", lib_status.get("files_total", "?"))
        notes = lib_status.get("notes", "")
        print(f"{lib:<18} {flags:<20} files:{files_done}/{files_total}  purpose: {meta.get('purpose','')}")
        if show_notes and notes:
            print(f"  notes: {notes}")


def main() -> None:
    parser = argparse.ArgumentParser(description="Quick status dashboard for coin-or-kb.")
    parser.add_argument("--layer", help="Limit output to a specific layer (e.g., layer-3)")
    parser.add_argument("--show-notes", action="store_true", help="Include notes for each library")
    args = parser.parse_args()

    root = Path(__file__).resolve().parents[1]
    status = load_json(root / ".kb" / "status.json")
    mapping = load_json(root / ".kb" / "library-mapping.json")

    layers = [args.layer] if args.layer else [k for k in mapping.keys() if k.startswith("layer-")]
    for layer in sorted(layers):
        if layer in mapping:
            print_layer(layer, status, mapping, args.show_notes)


if __name__ == "__main__":
    main()
