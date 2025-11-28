/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file lp_data/HighsRanging.h
 * @brief Sensitivity analysis (ranging) for LP optimal solutions
 *
 * Computes allowable ranges for objective coefficients and bounds.
 *
 * **HighsRangingRecord:**
 * - value_[]: New coefficient/bound value at range limit
 * - objective_[]: Objective value at range limit
 * - in_var_[]: Variable entering basis at limit
 * - ou_var_[]: Variable leaving basis at limit
 *
 * **HighsRanging Structure:**
 * - col_cost_up/dn: Objective coefficient increase/decrease
 * - col_bound_up/dn: Variable bound increase/decrease
 * - row_bound_up/dn: Constraint RHS increase/decrease
 *
 * **Sensitivity Analysis:**
 * - For costs: Range where current basis remains optimal
 * - For bounds: Range where current basis remains primal feasible
 * - Shadow prices from dual variables
 *
 * @see lp_data/HighsLpSolverObject.h for solver state
 */
#ifndef LP_DATA_HIGHS_RANGING_H_
#define LP_DATA_HIGHS_RANGING_H_

#include <vector>

#include "lp_data/HighsLpSolverObject.h"

struct HighsRangingRecord {
  std::vector<double> value_;
  std::vector<double> objective_;
  std::vector<HighsInt> in_var_;
  std::vector<HighsInt> ou_var_;
};

struct HighsRanging {
  bool valid = false;
  HighsRangingRecord col_cost_up;
  HighsRangingRecord col_cost_dn;
  HighsRangingRecord col_bound_up;
  HighsRangingRecord col_bound_dn;
  HighsRangingRecord row_bound_up;
  HighsRangingRecord row_bound_dn;
  void invalidate();
  void clear();
};

HighsStatus getRangingData(HighsRanging& ranging,
                           HighsLpSolverObject& solver_object);
void writeRangingFile(FILE* file, const HighsLp& lp,
                      const double objective_function_value,
                      const HighsBasis& basis, const HighsSolution& solution,
                      const HighsRanging& ranging, const HighsInt style);
#endif
