#!/usr/bin/env python3
"""
Fix absolute markdown links to use Zola's @/ internal link syntax.

Patterns to fix:
1. [text](/libraries/lib/) -> [text](@/libraries/lib/_index.md)
2. [text](/libraries/lib/Class/) -> [text](@/libraries/lib/Class.md)
3. [text](/algorithms/algo-name/) -> [text](@/algorithms/algo-name.md)
4. [text](/learning-paths/path/) -> [text](@/learning-paths/path.md) or _index.md
5. [text](/browser/) -> [text](@/browser.md)
6. [text](/browser/?query) -> {{ link(path="/browser/?query", text="text") }}
"""

import re
import os
from pathlib import Path

CONTENT_DIR = Path("/home/tom/Code/coin-or-kb/site/content")

# Check which files exist to determine correct path
def find_file_case_insensitive(dir_path, filename):
    """Find actual filename with correct case."""
    if not dir_path.exists():
        return None
    for f in dir_path.iterdir():
        if f.name.lower() == filename.lower():
            return f.name
    return None

def get_correct_path(url_path):
    """Convert URL path to correct @/ internal link path.
    Returns None if no matching file exists (will use shortcode instead).
    """
    # Remove leading/trailing slashes
    path = url_path.strip('/')

    # Handle query parameters - these need shortcode
    if '?' in path:
        return None  # Signal to use shortcode

    # Split into directory and file parts
    parts = path.split('/')

    # Check if it's a section (has _index.md) or a page (.md)
    content_path = CONTENT_DIR / path

    # Check if it's a section with _index.md
    index_path = content_path / "_index.md"
    if index_path.exists():
        return f"@/{path}/_index.md"

    # Try to find the file with correct case
    if len(parts) >= 2:
        dir_path = CONTENT_DIR / '/'.join(parts[:-1])
        filename = parts[-1]

        # Try as .md file
        actual_name = find_file_case_insensitive(dir_path, f"{filename}.md")
        if actual_name:
            correct_path = '/'.join(parts[:-1]) + '/' + actual_name
            return f"@/{correct_path}"

        # Try as _index.md in subdirectory
        actual_dir = find_file_case_insensitive(dir_path, filename)
        if actual_dir:
            index_check = dir_path / actual_dir / "_index.md"
            if index_check.exists():
                correct_path = '/'.join(parts[:-1]) + '/' + actual_dir + '/_index.md'
                return f"@/{correct_path}"

    # First check if it's a direct .md file with exact case
    md_path = CONTENT_DIR / f"{path}.md"
    if md_path.exists():
        return f"@/{path}.md"

    # Check if path already ends with .md pattern in content
    if content_path.with_suffix('.md').exists():
        return f"@/{path}.md"

    # File doesn't exist - use shortcode to preserve link (will be broken but build won't fail)
    return None

def fix_markdown_links(content, filepath):
    """Fix absolute links in markdown content."""

    # Pattern for markdown links: [text](/path/) or [text](/path)
    link_pattern = r'\[([^\]]+)\]\((/(?:libraries|algorithms|learning-paths|browser)[^)]*)\)'

    def replace_link(match):
        text = match.group(1)
        url = match.group(2)

        # Handle browser links with query params - convert to shortcode
        if '?' in url:
            # Convert [text](/browser/?library=X) to {{ link(path="/browser/?library=X", text="text") }}
            return f'{{{{ link(path="{url}", text="{text}") }}}}'

        # Get the correct internal link path
        new_path = get_correct_path(url)
        if new_path:
            return f'[{text}]({new_path})'
        else:
            # Fallback to shortcode
            return f'{{{{ link(path="{url}", text="{text}") }}}}'

    return re.sub(link_pattern, replace_link, content)

def process_file(filepath):
    """Process a single markdown file."""
    with open(filepath, 'r') as f:
        content = f.read()

    # Check if file has any absolute links to fix
    if not re.search(r'\]\(/(?:libraries|algorithms|learning-paths|browser)', content):
        return False

    new_content = fix_markdown_links(content, filepath)

    if new_content != content:
        with open(filepath, 'w') as f:
            f.write(new_content)
        return True
    return False

def main():
    """Process all markdown files in content directory."""
    fixed_count = 0

    for md_file in CONTENT_DIR.rglob("*.md"):
        if process_file(md_file):
            print(f"Fixed: {md_file.relative_to(CONTENT_DIR)}")
            fixed_count += 1

    print(f"\nTotal files fixed: {fixed_count}")

if __name__ == "__main__":
    main()
