#!/usr/bin/env python3
"""
Annotation Validator for Solver Knowledge Base

Validates C++ source files for annotation completeness according to
the schema defined in .kb/schemas/tags.json

Usage:
    python validate.py <file_or_directory> [--pass1|--pass2] [--json] [--verbose]
"""

import re
import sys
import json
import argparse
from pathlib import Path
from dataclasses import dataclass, field
from typing import Optional
from enum import Enum


class Severity(Enum):
    ERROR = "error"
    WARNING = "warning"
    INFO = "info"


@dataclass
class Tag:
    """Represents a parsed annotation tag."""
    name: str
    value: str
    line: int


@dataclass
class CommentBlock:
    """A Doxygen-style comment block."""
    content: str
    start_line: int
    end_line: int
    tags: list[Tag] = field(default_factory=list)

    def has_tag(self, name: str) -> bool:
        return any(t.name == name for t in self.tags)

    def get_tag(self, name: str) -> Optional[Tag]:
        for t in self.tags:
            if t.name == name:
                return t
        return None


@dataclass
class Symbol:
    """A C++ symbol (class, function, method)."""
    kind: str  # 'class', 'struct', 'function', 'method'
    name: str
    line: int
    is_public: bool
    params: list[str] = field(default_factory=list)
    return_type: str = ""
    comment: Optional[CommentBlock] = None


@dataclass
class Issue:
    """A validation issue."""
    severity: Severity
    rule: str
    message: str
    file: str
    line: int
    symbol: Optional[str] = None


class AnnotationParser:
    """Parse C++ files to extract comments and symbols."""

    # Regex patterns
    DOXYGEN_BLOCK = re.compile(
        r'/\*\*\s*(.*?)\*/',
        re.DOTALL
    )

    DOXYGEN_TAG = re.compile(
        r'@(\w+)\s+(.+?)(?=@\w+|\Z)',
        re.DOTALL
    )

    # Simplified patterns - not a full C++ parser but handles common cases
    CLASS_DECL = re.compile(
        r'^(?:template\s*<[^>]*>\s*)?'
        r'(class|struct)\s+'
        r'(?:[\w_]+\s+)?'  # optional export macro
        r'([\w_]+)',
        re.MULTILINE
    )

    FUNCTION_DECL = re.compile(
        r'^[ \t]*'
        r'(?:(?:static|virtual|inline|explicit|constexpr|COINUTILSLIB_EXPORT)\s+)*'
        r'([\w_:*&<>,\s]+?)\s+'  # return type
        r'([\w_]+)\s*'  # function name
        r'\(([^)]*)\)',  # parameters
        re.MULTILINE
    )

    def __init__(self, content: str, filename: str):
        self.content = content
        self.filename = filename
        self.lines = content.split('\n')

    def parse_comments(self) -> list[CommentBlock]:
        """Extract all Doxygen comment blocks."""
        comments = []

        for match in self.DOXYGEN_BLOCK.finditer(self.content):
            start_pos = match.start()
            end_pos = match.end()

            # Calculate line numbers
            start_line = self.content[:start_pos].count('\n') + 1
            end_line = self.content[:end_pos].count('\n') + 1

            # Parse content
            raw_content = match.group(1)
            # Clean up comment formatting
            cleaned = re.sub(r'^\s*\*\s?', '', raw_content, flags=re.MULTILINE)
            cleaned = cleaned.strip()

            # Extract tags
            tags = []
            for tag_match in self.DOXYGEN_TAG.finditer(cleaned):
                tag_name = tag_match.group(1)
                tag_value = tag_match.group(2).strip()
                # Clean multi-line values
                tag_value = re.sub(r'\s+', ' ', tag_value)
                tags.append(Tag(tag_name, tag_value, start_line))

            comments.append(CommentBlock(
                content=cleaned,
                start_line=start_line,
                end_line=end_line,
                tags=tags
            ))

        return comments

    def parse_symbols(self) -> list[Symbol]:
        """Extract public symbols that need annotation."""
        symbols = []

        # Track public/private scope
        in_public = True  # Assume file-level things are public
        brace_depth = 0

        # Find classes/structs
        for match in self.CLASS_DECL.finditer(self.content):
            kind = match.group(1)
            name = match.group(2)
            line = self.content[:match.start()].count('\n') + 1

            # Skip forward declarations
            rest_of_line = self.content[match.end():match.end()+100]
            if rest_of_line.strip().startswith(';'):
                continue

            symbols.append(Symbol(
                kind=kind,
                name=name,
                line=line,
                is_public=True  # Class declarations are public
            ))

        # Find functions/methods (simplified - won't catch everything)
        for match in self.FUNCTION_DECL.finditer(self.content):
            return_type = match.group(1).strip()
            name = match.group(2).strip()
            params_str = match.group(3).strip()
            line = self.content[:match.start()].count('\n') + 1

            # Skip if this looks like a control structure
            if name in ('if', 'while', 'for', 'switch', 'catch'):
                continue

            # Skip constructors/destructors in return type position
            if return_type in ('public', 'private', 'protected'):
                continue

            # Parse parameters (simplified)
            params = []
            if params_str and params_str != 'void':
                for p in params_str.split(','):
                    p = p.strip()
                    if p:
                        # Extract parameter name (last word)
                        parts = p.split()
                        if parts:
                            # Handle cases like "const int* foo"
                            param_name = parts[-1].lstrip('*&')
                            if param_name and not param_name.startswith('='):
                                params.append(param_name)

            # Determine return type for void check
            is_void = return_type.strip() in ('void', 'inline void', 'static void', 'virtual void')

            symbols.append(Symbol(
                kind='function',
                name=name,
                line=line,
                is_public=True,  # Simplified - assume public
                params=params,
                return_type=return_type
            ))

        return symbols

    def associate_comments(self, comments: list[CommentBlock], symbols: list[Symbol]):
        """Associate comment blocks with symbols they document."""
        for symbol in symbols:
            # Find comment immediately preceding the symbol
            for comment in comments:
                # Comment should end within a few lines before symbol
                if comment.end_line <= symbol.line <= comment.end_line + 3:
                    symbol.comment = comment
                    break


class Validator:
    """Validate annotations against schema rules."""

    PASS1_TAGS = {'brief', 'param', 'return', 'see', 'invariant', 'file', 'todo'}
    PASS2_TAGS = {'algorithm', 'math', 'complexity', 'ref', 'note'}

    def __init__(self, validation_pass: int = 2):
        self.validation_pass = validation_pass
        self.issues: list[Issue] = []

    def validate_file(self, filepath: Path) -> list[Issue]:
        """Validate a single file."""
        self.issues = []

        content = filepath.read_text(errors='replace')
        parser = AnnotationParser(content, str(filepath))

        comments = parser.parse_comments()
        symbols = parser.parse_symbols()
        parser.associate_comments(comments, symbols)

        # Validate each symbol
        for symbol in symbols:
            self._validate_symbol(symbol, filepath)

        # Check for unresolved @todo in pass 2
        if self.validation_pass >= 2:
            for comment in comments:
                for tag in comment.tags:
                    if tag.name == 'todo':
                        self.issues.append(Issue(
                            severity=Severity.ERROR,
                            rule="no_unresolved_todos",
                            message=f"Unresolved @todo: {tag.value[:50]}...",
                            file=str(filepath),
                            line=tag.line
                        ))

        return self.issues

    def _validate_symbol(self, symbol: Symbol, filepath: Path):
        """Validate a single symbol's annotations."""

        if not symbol.is_public:
            return

        if symbol.comment is None:
            self.issues.append(Issue(
                severity=Severity.ERROR,
                rule="public_symbols_need_docs",
                message=f"Public {symbol.kind} '{symbol.name}' has no documentation",
                file=str(filepath),
                line=symbol.line,
                symbol=symbol.name
            ))
            return

        comment = symbol.comment

        # Check @brief
        if not comment.has_tag('brief'):
            # Check for implicit brief (first line without @)
            first_line = comment.content.split('\n')[0].strip()
            if not first_line or first_line.startswith('@'):
                self.issues.append(Issue(
                    severity=Severity.ERROR,
                    rule="public_symbols_need_brief",
                    message=f"{symbol.kind} '{symbol.name}' missing @brief",
                    file=str(filepath),
                    line=symbol.line,
                    symbol=symbol.name
                ))

        # Check @param for functions
        if symbol.kind in ('function', 'method') and symbol.params:
            documented_params = {t.value.split()[0] for t in comment.tags if t.name == 'param'}
            for param in symbol.params:
                if param not in documented_params:
                    self.issues.append(Issue(
                        severity=Severity.ERROR,
                        rule="params_documented",
                        message=f"Parameter '{param}' not documented in '{symbol.name}'",
                        file=str(filepath),
                        line=symbol.line,
                        symbol=symbol.name
                    ))

        # Check @return for non-void functions
        if symbol.kind in ('function', 'method'):
            is_void = 'void' in symbol.return_type and '*' not in symbol.return_type
            is_constructor = symbol.name == symbol.return_type or symbol.name.startswith('~')

            if not is_void and not is_constructor and not comment.has_tag('return'):
                self.issues.append(Issue(
                    severity=Severity.WARNING,
                    rule="return_documented",
                    message=f"Non-void function '{symbol.name}' missing @return",
                    file=str(filepath),
                    line=symbol.line,
                    symbol=symbol.name
                ))

        # Pass 2 checks
        if self.validation_pass >= 2:
            # Check for @algorithm on functions with algorithmic names
            algo_hints = ['solve', 'factor', 'pivot', 'branch', 'cut', 'search',
                         'optimize', 'iterate', 'update', 'compute']
            name_lower = symbol.name.lower()

            if any(hint in name_lower for hint in algo_hints):
                if not comment.has_tag('algorithm') and not comment.has_tag('note'):
                    self.issues.append(Issue(
                        severity=Severity.WARNING,
                        rule="algorithms_identified",
                        message=f"'{symbol.name}' may implement algorithm - consider @algorithm or @note",
                        file=str(filepath),
                        line=symbol.line,
                        symbol=symbol.name
                    ))


@dataclass
class ValidationReport:
    """Summary of validation results."""
    files_checked: int = 0
    symbols_found: int = 0
    symbols_documented: int = 0
    errors: int = 0
    warnings: int = 0
    issues: list[Issue] = field(default_factory=list)

    @property
    def coverage(self) -> float:
        if self.symbols_found == 0:
            return 0.0
        return self.symbols_documented / self.symbols_found * 100

    def to_dict(self) -> dict:
        return {
            'files_checked': self.files_checked,
            'symbols_found': self.symbols_found,
            'symbols_documented': self.symbols_documented,
            'coverage_percent': round(self.coverage, 1),
            'errors': self.errors,
            'warnings': self.warnings,
            'issues': [
                {
                    'severity': i.severity.value,
                    'rule': i.rule,
                    'message': i.message,
                    'file': i.file,
                    'line': i.line,
                    'symbol': i.symbol
                }
                for i in self.issues
            ]
        }


def validate_path(path: Path, validation_pass: int, verbose: bool = False) -> ValidationReport:
    """Validate a file or directory."""
    report = ValidationReport()
    validator = Validator(validation_pass)

    # Collect files
    if path.is_file():
        files = [path]
    else:
        files = list(path.rglob('*.hpp')) + list(path.rglob('*.h')) + list(path.rglob('*.cpp'))

    for filepath in files:
        if verbose:
            print(f"Checking {filepath}...", file=sys.stderr)

        try:
            issues = validator.validate_file(filepath)
            report.files_checked += 1
            report.issues.extend(issues)

            # Count symbols (re-parse for stats)
            content = filepath.read_text(errors='replace')
            parser = AnnotationParser(content, str(filepath))
            comments = parser.parse_comments()
            symbols = parser.parse_symbols()
            parser.associate_comments(comments, symbols)

            public_symbols = [s for s in symbols if s.is_public]
            documented = [s for s in public_symbols if s.comment is not None]

            report.symbols_found += len(public_symbols)
            report.symbols_documented += len(documented)

        except Exception as e:
            if verbose:
                print(f"Error processing {filepath}: {e}", file=sys.stderr)

    # Count severities
    report.errors = sum(1 for i in report.issues if i.severity == Severity.ERROR)
    report.warnings = sum(1 for i in report.issues if i.severity == Severity.WARNING)

    return report


def main():
    parser = argparse.ArgumentParser(description='Validate annotation coverage')
    parser.add_argument('path', type=Path, help='File or directory to validate')
    parser.add_argument('--pass1', action='store_true', help='Validate Pass 1 only')
    parser.add_argument('--pass2', action='store_true', help='Validate Pass 1 + Pass 2 (default)')
    parser.add_argument('--json', action='store_true', help='Output as JSON')
    parser.add_argument('--verbose', '-v', action='store_true', help='Verbose output')

    args = parser.parse_args()

    validation_pass = 1 if args.pass1 else 2

    report = validate_path(args.path, validation_pass, args.verbose)

    if args.json:
        print(json.dumps(report.to_dict(), indent=2))
    else:
        # Human-readable output
        print(f"\n{'='*60}")
        print(f"ANNOTATION VALIDATION REPORT (Pass {validation_pass})")
        print(f"{'='*60}")
        print(f"Files checked:      {report.files_checked}")
        print(f"Symbols found:      {report.symbols_found}")
        print(f"Symbols documented: {report.symbols_documented}")
        print(f"Coverage:           {report.coverage:.1f}%")
        print(f"Errors:             {report.errors}")
        print(f"Warnings:           {report.warnings}")

        if report.issues:
            print(f"\n{'─'*60}")
            print("ISSUES:")
            print(f"{'─'*60}")

            # Group by file
            by_file: dict[str, list[Issue]] = {}
            for issue in report.issues:
                by_file.setdefault(issue.file, []).append(issue)

            for filepath, issues in sorted(by_file.items()):
                print(f"\n{filepath}:")
                for issue in sorted(issues, key=lambda i: i.line):
                    icon = "❌" if issue.severity == Severity.ERROR else "⚠️"
                    print(f"  {icon} L{issue.line}: {issue.message}")

        print(f"\n{'='*60}")

        # Exit code
        sys.exit(1 if report.errors > 0 else 0)


if __name__ == '__main__':
    main()
