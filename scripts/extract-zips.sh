#!/bin/bash
# Extract zip archives into their designated layer directories
# Based on .kb/library-mapping.json

set -e
VENDOR_DIR="/home/tom/Code/vendor"
ARCHIVE_DIR="$VENDOR_DIR/archive"

echo "=== Extracting Layer 0 (Foundation) ==="
unzip -q "$ARCHIVE_DIR/CoinUtils-master.zip" -d "$VENDOR_DIR/layer-0/"
mv "$VENDOR_DIR/layer-0/CoinUtils-master" "$VENDOR_DIR/layer-0/CoinUtils"

unzip -q "$ARCHIVE_DIR/SuiteSparse-dev.zip" -d "$VENDOR_DIR/layer-0/"
mv "$VENDOR_DIR/layer-0/SuiteSparse-dev" "$VENDOR_DIR/layer-0/SuiteSparse"

echo "=== Extracting Layer 1 (Core) ==="
unzip -q "$ARCHIVE_DIR/Osi-master.zip" -d "$VENDOR_DIR/layer-1/"
mv "$VENDOR_DIR/layer-1/Osi-master" "$VENDOR_DIR/layer-1/Osi"

unzip -q "$ARCHIVE_DIR/Clp-master.zip" -d "$VENDOR_DIR/layer-1/"
mv "$VENDOR_DIR/layer-1/Clp-master" "$VENDOR_DIR/layer-1/Clp"

unzip -q "$ARCHIVE_DIR/CppAD-master.zip" -d "$VENDOR_DIR/layer-1/"
mv "$VENDOR_DIR/layer-1/CppAD-master" "$VENDOR_DIR/layer-1/CppAD"

unzip -q "$ARCHIVE_DIR/qpOASES-master.zip" -d "$VENDOR_DIR/layer-1/"
mv "$VENDOR_DIR/layer-1/qpOASES-master" "$VENDOR_DIR/layer-1/qpOASES"

echo "=== Extracting Layer 2 (Advanced) ==="
unzip -q "$ARCHIVE_DIR/Cgl-master.zip" -d "$VENDOR_DIR/layer-2/"
mv "$VENDOR_DIR/layer-2/Cgl-master" "$VENDOR_DIR/layer-2/Cgl"

unzip -q "$ARCHIVE_DIR/Cbc-master.zip" -d "$VENDOR_DIR/layer-2/"
mv "$VENDOR_DIR/layer-2/Cbc-master" "$VENDOR_DIR/layer-2/Cbc"

unzip -q "$ARCHIVE_DIR/Ipopt-stable-3.14.zip" -d "$VENDOR_DIR/layer-2/"
mv "$VENDOR_DIR/layer-2/Ipopt-stable-3.14" "$VENDOR_DIR/layer-2/Ipopt"

unzip -q "$ARCHIVE_DIR/ADOL-C-master.zip" -d "$VENDOR_DIR/layer-2/"
mv "$VENDOR_DIR/layer-2/ADOL-C-master" "$VENDOR_DIR/layer-2/ADOL-C"

echo "=== Extracting Layer 3 (Specialized) ==="
unzip -q "$ARCHIVE_DIR/Bonmin-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/Bonmin-master" "$VENDOR_DIR/layer-3/Bonmin"

unzip -q "$ARCHIVE_DIR/Couenne-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/Couenne-master" "$VENDOR_DIR/layer-3/Couenne"

unzip -q "$ARCHIVE_DIR/SYMPHONY-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/SYMPHONY-master" "$VENDOR_DIR/layer-3/SYMPHONY"

unzip -q "$ARCHIVE_DIR/Bcp-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/Bcp-master" "$VENDOR_DIR/layer-3/Bcp"

unzip -q "$ARCHIVE_DIR/CHiPPS-ALPS-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/CHiPPS-ALPS-master" "$VENDOR_DIR/layer-3/CHiPPS-ALPS"

unzip -q "$ARCHIVE_DIR/CHiPPS-BLIS-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/CHiPPS-BLIS-master" "$VENDOR_DIR/layer-3/CHiPPS-BLIS"

unzip -q "$ARCHIVE_DIR/Dip-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/Dip-master" "$VENDOR_DIR/layer-3/Dip"

unzip -q "$ARCHIVE_DIR/DisCO-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/DisCO-master" "$VENDOR_DIR/layer-3/DisCO"

unzip -q "$ARCHIVE_DIR/Smi-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/Smi-master" "$VENDOR_DIR/layer-3/Smi"

unzip -q "$ARCHIVE_DIR/oBB-master.zip" -d "$VENDOR_DIR/layer-3/"
mv "$VENDOR_DIR/layer-3/oBB-master" "$VENDOR_DIR/layer-3/oBB"

echo "=== Extracting Layer 4 (High-level) ==="
unzip -q "$ARCHIVE_DIR/HiGHS-master.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/HiGHS-master" "$VENDOR_DIR/layer-4/HiGHS"

unzip -q "$ARCHIVE_DIR/Gravity-master.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/Gravity-master" "$VENDOR_DIR/layer-4/Gravity"

unzip -q "$ARCHIVE_DIR/SHOT-master.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/SHOT-master" "$VENDOR_DIR/layer-4/SHOT"

unzip -q "$ARCHIVE_DIR/OS-master.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/OS-master" "$VENDOR_DIR/layer-4/OS"

unzip -q "$ARCHIVE_DIR/Cmpl-master.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/Cmpl-master" "$VENDOR_DIR/layer-4/Cmpl"

unzip -q "$ARCHIVE_DIR/Creme-master.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/Creme-master" "$VENDOR_DIR/layer-4/Creme"

unzip -q "$ARCHIVE_DIR/GAMSlinks-master.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/GAMSlinks-master" "$VENDOR_DIR/layer-4/GAMSlinks"

unzip -q "$ARCHIVE_DIR/Sonnet-master.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/Sonnet-master" "$VENDOR_DIR/layer-4/Sonnet"

unzip -q "$ARCHIVE_DIR/clp-spreadsheet-solver-main.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/clp-spreadsheet-solver-main" "$VENDOR_DIR/layer-4/clp-spreadsheet-solver"

unzip -q "$ARCHIVE_DIR/cuopt-main.zip" -d "$VENDOR_DIR/layer-4/"
mv "$VENDOR_DIR/layer-4/cuopt-main" "$VENDOR_DIR/layer-4/cuopt"

echo "=== Extraction complete ==="
echo "Layer 0: $(ls $VENDOR_DIR/layer-0 | wc -l) libraries"
echo "Layer 1: $(ls $VENDOR_DIR/layer-1 | wc -l) libraries"
echo "Layer 2: $(ls $VENDOR_DIR/layer-2 | wc -l) libraries"
echo "Layer 3: $(ls $VENDOR_DIR/layer-3 | wc -l) libraries"
echo "Layer 4: $(ls $VENDOR_DIR/layer-4 | wc -l) libraries"
