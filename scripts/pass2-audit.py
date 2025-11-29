#!/usr/bin/env python3
"""
Pass 2 Audit Tool

Analyzes annotated files to:
1. Count Pass 2 tags (@algorithm, @math, @complexity, @ref)
2. Identify files likely needing Pass 2 annotation
3. Find unresolved @todo PASS2: markers
4. Generate priority list for Pass 2 work

Usage:
    python pass2-audit.py <directory> [--json] [--priority]
"""

import re
import sys
import json
import argparse
from pathlib import Path
from dataclasses import dataclass, field
from typing import List, Dict, Set


@dataclass
class FileAudit:
    """Audit results for a single file."""
    path: str

    # Pass 1 tag counts
    file_tags: int = 0
    brief_tags: int = 0
    param_tags: int = 0
    return_tags: int = 0
    see_tags: int = 0

    # Pass 2 tag counts
    algorithm_tags: int = 0
    math_tags: int = 0
    complexity_tags: int = 0
    ref_tags: int = 0
    invariant_tags: int = 0
    note_tags: int = 0

    # Issues
    todo_pass2: List[str] = field(default_factory=list)

    # Hints suggesting Pass 2 needed
    algo_function_names: List[str] = field(default_factory=list)

    @property
    def pass1_total(self) -> int:
        return self.file_tags + self.brief_tags + self.param_tags + self.return_tags + self.see_tags

    @property
    def pass2_total(self) -> int:
        return self.algorithm_tags + self.math_tags + self.complexity_tags + self.ref_tags

    @property
    def priority_score(self) -> int:
        """Higher score = higher priority for Pass 2 work."""
        score = 0
        score += len(self.todo_pass2) * 10  # Explicit markers
        score += len(self.algo_function_names) * 5  # Algorithmic function names
        score -= self.pass2_total * 3  # Already has Pass 2 annotations
        return max(0, score)

    @property
    def tier(self) -> str:
        """Classify file into priority tier."""
        if len(self.todo_pass2) > 0:
            return "A"  # Explicit markers = definitely needs work
        if len(self.algo_function_names) > 3:
            return "A"  # Many algorithmic functions
        if len(self.algo_function_names) > 0 and self.pass2_total == 0:
            return "B"  # Some algorithmic functions, no Pass 2 annotations yet
        if self.pass2_total > 0:
            return "C"  # Already has some Pass 2 annotations
        return "D"  # Probably doesn't need Pass 2 work


# Patterns for algorithmic function names
ALGO_HINTS = [
    'solve', 'factor', 'pivot', 'branch', 'cut', 'search',
    'optimize', 'iterate', 'update', 'compute', 'calculate',
    'decompose', 'eliminate', 'substitute', 'reduce',
    'presolve', 'postsolve', 'transform', 'scale',
    'project', 'separate', 'generate', 'heuristic',
    'bound', 'relax', 'propagate', 'infer'
]

ALGO_PATTERN = re.compile(
    r'(?:^|\s)(?:void|int|bool|double|[\w:]+)\s+(' +
    '|'.join(f'\\w*{hint}\\w*' for hint in ALGO_HINTS) +
    r')\s*\(',
    re.IGNORECASE | re.MULTILINE
)


def audit_file(filepath: Path) -> FileAudit:
    """Audit a single file for Pass 2 readiness."""
    content = filepath.read_text(errors='replace')
    audit = FileAudit(path=str(filepath))

    # Count tags
    audit.file_tags = len(re.findall(r'@file\b', content))
    audit.brief_tags = len(re.findall(r'@brief\b', content))
    audit.param_tags = len(re.findall(r'@param\b', content))
    audit.return_tags = len(re.findall(r'@return\b', content))
    audit.see_tags = len(re.findall(r'@see\b', content))

    audit.algorithm_tags = len(re.findall(r'@algorithm\b', content))
    audit.math_tags = len(re.findall(r'@math\b', content))
    audit.complexity_tags = len(re.findall(r'@complexity\b', content))
    audit.ref_tags = len(re.findall(r'@ref\b', content))
    audit.invariant_tags = len(re.findall(r'@invariant\b', content))
    audit.note_tags = len(re.findall(r'@note\b', content))

    # Find @todo PASS2: markers
    for match in re.finditer(r'@todo\s+PASS2[:\s]+([^\n]+)', content, re.IGNORECASE):
        audit.todo_pass2.append(match.group(1).strip())

    # Find algorithmic function names
    for match in ALGO_PATTERN.finditer(content):
        func_name = match.group(1)
        if func_name not in audit.algo_function_names:
            audit.algo_function_names.append(func_name)

    return audit


def audit_directory(dirpath: Path) -> List[FileAudit]:
    """Audit all C++ files in a directory."""
    audits = []

    for pattern in ['**/*.hpp', '**/*.h', '**/*.cpp']:
        for filepath in dirpath.glob(pattern):
            try:
                audit = audit_file(filepath)
                audits.append(audit)
            except Exception as e:
                print(f"Error processing {filepath}: {e}", file=sys.stderr)

    return audits


def print_summary(audits: List[FileAudit]):
    """Print summary statistics."""
    total_files = len(audits)

    # Aggregate counts
    total_pass1 = sum(a.pass1_total for a in audits)
    total_pass2 = sum(a.pass2_total for a in audits)
    total_todos = sum(len(a.todo_pass2) for a in audits)
    total_algo_hints = sum(len(a.algo_function_names) for a in audits)

    # Tier breakdown
    tiers = {'A': 0, 'B': 0, 'C': 0, 'D': 0}
    for a in audits:
        tiers[a.tier] += 1

    print(f"\n{'='*60}")
    print("PASS 2 AUDIT SUMMARY")
    print(f"{'='*60}")
    print(f"Files analyzed:          {total_files}")
    print(f"\nPass 1 Tags:")
    print(f"  @file:                 {sum(a.file_tags for a in audits)}")
    print(f"  @brief:                {sum(a.brief_tags for a in audits)}")
    print(f"  @param:                {sum(a.param_tags for a in audits)}")
    print(f"  @return:               {sum(a.return_tags for a in audits)}")
    print(f"  @see:                  {sum(a.see_tags for a in audits)}")
    print(f"  Total:                 {total_pass1}")
    print(f"\nPass 2 Tags:")
    print(f"  @algorithm:            {sum(a.algorithm_tags for a in audits)}")
    print(f"  @math:                 {sum(a.math_tags for a in audits)}")
    print(f"  @complexity:           {sum(a.complexity_tags for a in audits)}")
    print(f"  @ref:                  {sum(a.ref_tags for a in audits)}")
    print(f"  Total:                 {total_pass2}")
    print(f"\nPass 2 Work Indicators:")
    print(f"  @todo PASS2 markers:   {total_todos}")
    print(f"  Algorithmic functions: {total_algo_hints}")
    print(f"\nPriority Tiers:")
    print(f"  A (Definitely needs):  {tiers['A']} files")
    print(f"  B (Probably needs):    {tiers['B']} files")
    print(f"  C (Partially done):    {tiers['C']} files")
    print(f"  D (Skip):              {tiers['D']} files")
    print(f"{'='*60}")


def print_priority_list(audits: List[FileAudit], limit: int = 20):
    """Print files prioritized for Pass 2 work."""
    # Sort by priority score descending
    sorted_audits = sorted(audits, key=lambda a: a.priority_score, reverse=True)

    print(f"\n{'='*60}")
    print(f"TOP {limit} FILES FOR PASS 2 ANNOTATION")
    print(f"{'='*60}")

    for i, audit in enumerate(sorted_audits[:limit], 1):
        if audit.priority_score == 0:
            break
        print(f"\n{i}. [{audit.tier}] {audit.path}")
        print(f"   Score: {audit.priority_score}")
        if audit.todo_pass2:
            print(f"   @todo PASS2: {len(audit.todo_pass2)} markers")
            for todo in audit.todo_pass2[:3]:
                print(f"     - {todo[:60]}...")
        if audit.algo_function_names:
            print(f"   Algorithmic functions: {', '.join(audit.algo_function_names[:5])}")
        if audit.pass2_total > 0:
            print(f"   Existing Pass 2 tags: {audit.pass2_total}")


def main():
    parser = argparse.ArgumentParser(description='Audit files for Pass 2 readiness')
    parser.add_argument('path', type=Path, help='Directory to audit')
    parser.add_argument('--json', action='store_true', help='Output as JSON')
    parser.add_argument('--priority', action='store_true', help='Show priority list')
    parser.add_argument('--limit', type=int, default=20, help='Number of files in priority list')

    args = parser.parse_args()

    if not args.path.is_dir():
        print(f"Error: {args.path} is not a directory", file=sys.stderr)
        sys.exit(1)

    audits = audit_directory(args.path)

    if args.json:
        data = {
            'summary': {
                'files': len(audits),
                'pass1_tags': sum(a.pass1_total for a in audits),
                'pass2_tags': sum(a.pass2_total for a in audits),
                'todo_pass2_markers': sum(len(a.todo_pass2) for a in audits),
            },
            'files': [
                {
                    'path': a.path,
                    'tier': a.tier,
                    'priority_score': a.priority_score,
                    'pass1_tags': a.pass1_total,
                    'pass2_tags': a.pass2_total,
                    'todo_pass2': a.todo_pass2,
                    'algo_functions': a.algo_function_names,
                }
                for a in sorted(audits, key=lambda a: a.priority_score, reverse=True)
            ]
        }
        print(json.dumps(data, indent=2))
    else:
        print_summary(audits)
        if args.priority:
            print_priority_list(audits, args.limit)


if __name__ == '__main__':
    main()
