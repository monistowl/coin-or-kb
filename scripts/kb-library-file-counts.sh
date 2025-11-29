#!/usr/bin/env sh
#
# kb-library-file-counts.sh
#
# List each layer/library pair plus the number of C/C++ source and header files.
# Uses only POSIX utilities so it can run in minimal shell environments.
#
# Usage:
#   ./scripts/kb-library-file-counts.sh
#   ./scripts/kb-library-file-counts.sh layer-4

set -eu

root="$(cd "$(dirname "$0")/.." && pwd)"
layers="${1:-$root/layer-*}"

printf "%-12s %-25s %6s\n" "Layer" "Library" "Files"
printf "%-12s %-25s %6s\n" "-----" "-------" "-----"

{
  for layer in $layers; do
    [ -d "$layer" ] || continue
    layer_name="$(basename "$layer")"
    for lib in "$layer"/*; do
      [ -d "$lib" ] || continue
      lib_name="$(basename "$lib")"
      count="$(find "$lib" -type f \( -iname '*.h' -o -iname '*.hpp' -o -iname '*.c' -o -iname '*.cpp' \) | wc -l | tr -d '[:space:]')"
      printf "%-12s %-25s %6s\n" "$layer_name" "$lib_name" "$count"
    done
  done
} | sort -k1,1 -k2,2
