/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file lp_data/HighsAnalysis.h
 * @brief Timer clock aggregation for performance analysis
 *
 * Groups named timer clocks for measuring algorithm phases.
 *
 * **HighsTimerClock:**
 * - timer_pointer_: Reference to parent HighsTimer
 * - clock_[]: Vector of clock indices for this group
 *
 * **Usage:**
 * - Simplex phases (pricing, ratio test, update)
 * - IPM iterations
 * - MIP operations (cuts, branching, heuristics)
 *
 * @see util/HighsTimer.h for clock management
 */
#ifndef LP_DATA_HIGHS_ANALYSIS_H_
#define LP_DATA_HIGHS_ANALYSIS_H_

#include <vector>

#include "HConfig.h"
#include "util/HighsTimer.h"

struct HighsTimerClock {
  HighsTimer* timer_pointer_;
  std::vector<HighsInt> clock_;
};
#endif /* LP_DATA_HIGHS_ANALYSIS_H_ */
