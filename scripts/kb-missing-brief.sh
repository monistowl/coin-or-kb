#!/usr/bin/env sh
#
# kb-missing-brief.sh
#
# Show header/source files that do not contain a specific annotation tag.
# Defaults to `@brief` so agents can find files lacking structural docs.
#
# Usage:
#   ./scripts/kb-missing-brief.sh
#   ./scripts/kb-missing-brief.sh @todo layer-4/HiGHS

set -eu

tag="${1:-@brief}"
shift 1 || true
paths="${@:-layer-*}"

printf "Searching for files without %s:\n" "$tag"

for path in $paths; do
  [ -d "$path" ] || continue
  find "$path" -type f \( -iname '*.h' -o -iname '*.hpp' -o -iname '*.c' -o -iname '*.cpp' \) | \
    while IFS= read -r file; do
      if ! grep -q "$tag" "$file"; then
        printf "%s\n" "$file"
      fi
    done
done
