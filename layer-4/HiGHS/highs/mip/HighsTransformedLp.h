/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsTransformedLp.h
 * @brief LP bound transformations for cutting plane separation
 *
 * Transforms LP rows into single-row relaxations suitable for cut generation
 * by substituting bounds and handling complementation.
 *
 * **Bound Substitution Types (BoundType enum):**
 * - kSimpleLb/kSimpleUb: Direct variable bounds (x ≥ lb, x ≤ ub)
 * - kVariableLb/kVariableUb: VLB/VUB from implications (x ≥ a*y + b)
 *
 * **Bound Selection:**
 * - bestVlb/bestVub[]: Tightest variable bound for each column
 * - simpleLbDist/simpleUbDist[]: Distance of LP value from simple bounds
 * - lbDist/ubDist[]: Distance considering all bound types
 * - boundDist[]: Minimum distance (used for coefficient strengthening)
 *
 * **Transform Operations:**
 * - transform(): Convert row to standard form for cut generation
 *   - Substitutes bounds to get non-negative variables
 *   - Tracks which bound type used per variable
 *   - Returns integralPositive flag for MIR applicability
 * - untransform(): Reverse transformation to original space
 *
 * **Cut Generation Flow:**
 * 1. Aggregate LP rows (via HighsLpAggregator)
 * 2. Transform to standard form (substitute bounds)
 * 3. Apply cut procedure (Gomory, MIR, etc.)
 * 4. Untransform back to original variables
 *
 * @see mip/HighsLpAggregator.h for row aggregation
 * @see mip/HighsImplications.h for VUB/VLB structures
 * @see mip/HighsSeparation.h for cut orchestration
 */

#ifndef MIP_HIGHS_TRANSFORMED_LP_H_
#define MIP_HIGHS_TRANSFORMED_LP_H_

#include <vector>

#include "lp_data/HConst.h"
#include "mip/HighsImplications.h"
#include "util/HighsCDouble.h"
#include "util/HighsInt.h"
#include "util/HighsSparseVectorSum.h"

class HighsLpRelaxation;

/// Helper class to compute single-row relaxations from the current LP
/// relaxation by substituting bounds and aggregating rows
class HighsTransformedLp {
 private:
  const HighsLpRelaxation& lprelaxation;

  std::vector<std::pair<HighsInt, HighsImplications::VarBound>> bestVub;
  std::vector<std::pair<HighsInt, HighsImplications::VarBound>> bestVlb;
  std::vector<double> simpleLbDist;
  std::vector<double> simpleUbDist;
  std::vector<double> lbDist;
  std::vector<double> ubDist;
  std::vector<double> boundDist;
  enum class BoundType : uint8_t {
    kSimpleUb,
    kSimpleLb,
    kVariableUb,
    kVariableLb,
  };
  std::vector<BoundType> boundTypes;
  HighsSparseVectorSum vectorsum;

 public:
  HighsTransformedLp(const HighsLpRelaxation& lprelaxation,
                     HighsImplications& implications);

  double boundDistance(HighsInt col) const { return boundDist[col]; }

  bool transform(std::vector<double>& vals, std::vector<double>& upper,
                 std::vector<double>& solval, std::vector<HighsInt>& inds,
                 double& rhs, bool& integralPositive, bool preferVbds = false);

  bool untransform(std::vector<double>& vals, std::vector<HighsInt>& inds,
                   double& rhs, bool integral = false);
};

#endif
