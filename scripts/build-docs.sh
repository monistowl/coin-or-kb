#!/bin/bash
# Build script for COIN-OR Knowledge Base documentation
# Orchestrates: Doxygen → transform → Zola

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(dirname "$SCRIPT_DIR")"

cd "$PROJECT_ROOT"

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

log() { echo -e "${BLUE}[build]${NC} $1"; }
success() { echo -e "${GREEN}[build]${NC} $1"; }
error() { echo -e "${RED}[build]${NC} $1" >&2; }

# Parse arguments
SKIP_DOXYGEN=false
SKIP_TRANSFORM=false
SKIP_ZOLA=false
SERVE=false

while [[ $# -gt 0 ]]; do
    case $1 in
        --skip-doxygen) SKIP_DOXYGEN=true; shift ;;
        --skip-transform) SKIP_TRANSFORM=true; shift ;;
        --skip-zola) SKIP_ZOLA=true; shift ;;
        --serve) SERVE=true; shift ;;
        --help|-h)
            echo "Usage: $0 [options]"
            echo "Options:"
            echo "  --skip-doxygen    Skip Doxygen generation"
            echo "  --skip-transform  Skip XML→JSON+MD transform"
            echo "  --skip-zola       Skip Zola build"
            echo "  --serve           Start Zola dev server after build"
            exit 0
            ;;
        *) error "Unknown option: $1"; exit 1 ;;
    esac
done

# Step 1: Run Doxygen
if [ "$SKIP_DOXYGEN" = false ]; then
    log "Running Doxygen..."
    mkdir -p build/doxygen

    if ! command -v doxygen &> /dev/null; then
        error "doxygen not found. Please install: sudo apt install doxygen"
        exit 1
    fi

    doxygen Doxyfile
    success "Doxygen complete: build/doxygen/xml/"
else
    log "Skipping Doxygen (--skip-doxygen)"
fi

# Step 2: Transform XML to JSON + Markdown
if [ "$SKIP_TRANSFORM" = false ]; then
    log "Transforming Doxygen XML to JSON + Markdown..."

    if [ ! -d "build/doxygen/xml" ]; then
        error "Doxygen XML not found. Run without --skip-doxygen first."
        exit 1
    fi

    python3 scripts/transform-doxygen.py \
        build/doxygen/xml \
        site/content \
        site/static/api \
        --verbose

    success "Transform complete"
else
    log "Skipping transform (--skip-transform)"
fi

# Step 3: Build Zola site
if [ "$SKIP_ZOLA" = false ]; then
    log "Building Zola site..."

    if ! command -v zola &> /dev/null; then
        error "zola not found. Please install: cargo install zola"
        exit 1
    fi

    cd site
    zola build --output-dir ../build/site
    cd ..

    success "Zola build complete: build/site/"
else
    log "Skipping Zola build (--skip-zola)"
fi

# Summary
echo ""
success "=== Build Complete ==="
echo "  Doxygen HTML: build/doxygen/html/index.html"
echo "  JSON API:     site/static/api/"
echo "  Zola site:    build/site/"
echo ""

# Optionally serve
if [ "$SERVE" = true ]; then
    log "Starting Zola dev server..."
    cd site
    zola serve --port 1111
fi
