/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsPathSeparator.h
 * @brief Path aggregation cuts from network structure
 *
 * Heuristically identifies network paths and generates flow-based cuts.
 *
 * **Network Path Detection:**
 * 1. Find rows with network structure (±1 coefficients)
 * 2. Aggregate rows to form source-sink paths
 * 3. Resulting aggregation gives flow conservation cuts
 *
 * **Separation Heuristic:**
 * - Start from fractional integer variables
 * - Follow flow through network-like constraints
 * - Randomized selection (HighsRandom) for diverse cuts
 *
 * **Cut Generation:**
 * - Aggregated row passed to MIR procedure
 * - Path structure often yields strong cuts
 * - Effective on transportation/assignment problems
 *
 * @see mip/HighsSeparator.h for base class interface
 * @see mip/HighsModkSeparator.h for related mod-k aggregation
 * @see util/HighsRandom.h for randomization
 */

#ifndef MIP_HIGHS_PATH_SEPARATOR_H_
#define MIP_HIGHS_PATH_SEPARATOR_H_

#include "mip/HighsMipSolver.h"
#include "mip/HighsSeparator.h"
#include "util/HighsRandom.h"

/// Helper class to compute single-row relaxations from the current LP
/// relaxation by substituting bounds and aggregating rows
class HighsPathSeparator : public HighsSeparator {
 private:
  HighsRandom randgen;

 public:
  void separateLpSolution(HighsLpRelaxation& lpRelaxation,
                          HighsLpAggregator& lpAggregator,
                          HighsTransformedLp& transLp,
                          HighsCutPool& cutpool) override;

  HighsPathSeparator(const HighsMipSolver& mipsolver)
      : HighsSeparator(mipsolver, kPathAggrSepaString) {
    randgen.initialise(mipsolver.options_mip_->random_seed);
  }
};

#endif
