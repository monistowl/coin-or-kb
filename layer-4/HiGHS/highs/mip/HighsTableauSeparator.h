/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsTableauSeparator.h
 * @brief Gomory mixed-integer cuts from LP tableau
 *
 * Generates cuts by applying MIR procedure to simplex tableau rows.
 *
 * **Gomory Cut Generation:**
 * For each fractional basic integer variable:
 * 1. Extract tableau row: x_B[i] = f_0 - sum(a_j * x_N[j])
 * 2. Apply mixed-integer rounding (MIR)
 * 3. Produce cut: sum(floor(a_j) * x_j) ≤ floor(f_0) (simplified)
 *
 * **Separation Flow:**
 * 1. Get fractional integer variables from LP relaxation
 * 2. For each candidate, extract tableau row via BTRAN
 * 3. Transform using HighsTransformedLp (bound substitution)
 * 4. Apply MIR strengthening
 * 5. Add valid cuts to cut pool
 *
 * **Implementation:**
 * - numTries: Counter for separation attempts (controls effort)
 * - Uses kTableauSepaString identifier for statistics
 * - Inherits run() timing from HighsSeparator base class
 *
 * @see mip/HighsSeparator.h for base class interface
 * @see mip/HighsTransformedLp.h for bound substitution
 * @see mip/HighsSeparation.h for separator orchestration
 */

#ifndef MIP_HIGHS_TABLEAU_SEPARATOR_H_
#define MIP_HIGHS_TABLEAU_SEPARATOR_H_

#include "mip/HighsSeparator.h"

/// Helper class to compute single-row relaxations from the current LP
/// relaxation by substituting bounds and aggregating rows
class HighsTableauSeparator : public HighsSeparator {
 private:
  int64_t numTries;

 public:
  void separateLpSolution(HighsLpRelaxation& lpRelaxation,
                          HighsLpAggregator& lpAggregator,
                          HighsTransformedLp& transLp,
                          HighsCutPool& cutpool) override;

  HighsTableauSeparator(const HighsMipSolver& mipsolver)
      : HighsSeparator(mipsolver, kTableauSepaString), numTries(0) {}
};

#endif
