#!/usr/bin/env python3
"""
kb-layer-report.py

Print a TSV summary of layer/library status from .kb metadata.
Pipe-friendly output supports further filtering or feeding into tools like
`column -t` or `fzf`.

Usage:
    python scripts/kb-layer-report.py
    python scripts/kb-layer-report.py --layer layer-4 --fields layer,library,status
"""

from __future__ import annotations

import argparse
import json
from pathlib import Path
from typing import Iterable, Sequence


def load_json(path: Path) -> dict:
    try:
        return json.loads(path.read_text())
    except FileNotFoundError:
        raise SystemExit(f"Missing {path}")
    except json.JSONDecodeError as exc:
        raise SystemExit(f"Bad JSON {path}: {exc}")


def iter_layers(status: dict, mapping: dict, layer_filter: str | None = None) -> Iterable[dict]:
    for layer in sorted(mapping.keys()):
        if not layer.startswith("layer-"):
            continue
        if layer_filter and layer != layer_filter:
            continue
        layer_status = status.get("layers", {}).get(layer, {})
        libs = mapping.get(layer, {}).get("libraries", {})
        for lib, meta in libs.items():
            entry = layer_status.get("libraries", {}).get(lib, {})
            yield {
                "layer": layer,
                "library": lib,
                "status": entry.get("status", ""),
                "pass1": entry.get("pass1_complete", False),
                "pass2": entry.get("pass2_complete", False),
                "files_total": entry.get("files_total", ""),
                "files_pass1": entry.get("files_pass1", ""),
                "files_pass2": entry.get("files_pass2", ""),
                "notes": entry.get("notes", ""),
                "purpose": meta.get("purpose", ""),
            }


def format_bool(val: bool) -> str:
    return "yes" if val else "no"


def main() -> None:
    parser = argparse.ArgumentParser(description="Summarize KB progress per layer/library.")
    parser.add_argument("--layer", help="Limit to one layer (e.g., layer-3)")
    parser.add_argument(
        "--fields",
        default="layer\tlibrary\tstatus\tpass1\tpass2\tfiles_pass1\tfiles_total\tpurpose",
        help="Tab-separated fields (default: layer\\tlibrary\\tstatus\\tpass1\\tpass2\\tfiles_pass1\\tfiles_total\\tpurpose)",
    )
    args = parser.parse_args()

    root = Path(__file__).resolve().parents[1]
    status = load_json(root / ".kb" / "status.json")
    mapping = load_json(root / ".kb" / "library-mapping.json")

    fields = args.fields.split("\t")
    print("\t".join(fields))
    for entry in iter_layers(status, mapping, layer_filter=args.layer):
        row = []
        for field in fields:
            value = entry.get(field, "")
            if field in ("pass1", "pass2"):
                value = format_bool(value)
            row.append(str(value))
        print("\t".join(row))


if __name__ == "__main__":
    main()
