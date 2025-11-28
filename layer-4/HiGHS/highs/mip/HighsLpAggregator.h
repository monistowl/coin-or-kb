/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsLpAggregator.h
 * @brief Row aggregation for cut generation
 *
 * Combines LP rows with weights to create mixed-integer Gomory source rows.
 *
 * **Core Operations:**
 * - addRow(): Add weighted LP row to current aggregation
 * - getCurrentAggregation(): Extract combined row as sparse vector
 * - clear(): Reset for next aggregation
 *
 * **Aggregation Format:**
 * Result includes slack variables making it an equation with RHS = 0:
 *   sum(a_ij * x_j) + s_i = b_i  →  aggregated as equality
 *
 * **Implementation:**
 * - Uses HighsSparseVectorSum for efficient sparse combination
 * - Tracks nonzero indices incrementally
 * - negate parameter for sign flip (row sense conversion)
 *
 * **Cut Generation Context:**
 * 1. Start from LP tableau row (basis row)
 * 2. Aggregate additional rows to eliminate non-integer variables
 * 3. Pass to HighsTransformedLp for bound substitution
 * 4. Generate Gomory mixed-integer cuts
 *
 * @see mip/HighsTransformedLp.h for bound transformation
 * @see mip/HighsSeparation.h for cut orchestration
 * @see util/HighsSparseVectorSum.h for sparse vector arithmetic
 */

#ifndef MIP_HIGHS_LP_AGGREGATOR_H_
#define MIP_HIGHS_LP_AGGREGATOR_H_

#include <cstdint>
#include <vector>

#include "util/HighsSparseVectorSum.h"

class HighsLpRelaxation;

/// Helper class to compute single-row relaxations from the current LP
/// relaxation by substituting bounds and aggregating rows
class HighsLpAggregator {
 private:
  const HighsLpRelaxation& lprelaxation;

  HighsSparseVectorSum vectorsum;

 public:
  HighsLpAggregator(const HighsLpRelaxation& lprelaxation);

  /// add an LP row to the aggregation using the given weight
  void addRow(HighsInt row, double weight);

  /// returns the current aggregation of LP rows. The aggregation includes slack
  /// variables so that it is always an equation with right hand side 0.
  void getCurrentAggregation(std::vector<HighsInt>& inds,
                             std::vector<double>& vals, bool negate);

  /// clear the current aggregation
  void clear();

  /// checks whether the current aggregation is empty
  bool isEmpty() { return vectorsum.nonzeroinds.empty(); }
};

#endif
