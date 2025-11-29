#!/usr/bin/env sh
#
# kb-tag-density.sh
#
# Count annotation tags (any `@` word) to see which tags dominate the KB.
# Uses ripgrep if available to keep performance high, falling back to grep.
#
# Usage:
#   ./scripts/kb-tag-density.sh
#   ./scripts/kb-tag-density.sh "@algorithm|@math" layer-4

set -eu

pattern='@[[:alpha:]]+'
if [ $# -gt 0 ]; then
  pattern="$1"
  shift
fi
paths="${@:-layer-*}"

run_rg() {
  rg -o --no-heading --color=never --no-filename "$pattern" $paths 2>/dev/null
}

if command -v rg >/dev/null 2>&1; then
  matches="$(run_rg)"
else
  matches="$(find $paths -type f \( -iname '*.h' -o -iname '*.hpp' -o -iname '*.c' -o -iname '*.cpp' \) -print0 |
    xargs -0 grep -h -o "$pattern" 2>/dev/null)"
fi

printf "%-20s %s\n" "Tag" "Count"
printf "%-20s %s\n" "----" "-----"

echo "$matches" | sort | uniq -c | sort -rn | awk '{printf "%-20s %s\n", $2, $1}'
