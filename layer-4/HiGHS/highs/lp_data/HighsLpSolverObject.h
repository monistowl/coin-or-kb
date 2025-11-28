/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file lp_data/HighsLpSolverObject.h
 * @brief Aggregation of all objects needed for LP solving
 *
 * **HighsLpSolverObject:**
 * Bundles references to all components needed to solve an LP:
 * - lp_: The LP model data (HighsLp)
 * - basis_: Current simplex basis (HighsBasis)
 * - solution_: Primal/dual solution vectors (HighsSolution)
 * - highs_info_: Solver statistics and output (HighsInfo)
 * - ekk_instance_: Edinburgh simplex kernel (HEkk)
 * - callback_: User callback handler (HighsCallback)
 * - options_: Solver options (HighsOptions)
 * - timer_: Performance timer (HighsTimer)
 * - sub_solver_call_time_: Timing breakdown for sub-solvers
 * - model_status_: Current model status (kNotset, kOptimal, etc.)
 *
 * Used to pass solver context between functions without long parameter lists.
 *
 * @see simplex/HEkk.h for simplex implementation
 * @see lp_data/HighsLp.h for LP data structure
 */
#ifndef LP_DATA_HIGHS_LP_SOLVER_OBJECT_H_
#define LP_DATA_HIGHS_LP_SOLVER_OBJECT_H_

#include "lp_data/HighsInfo.h"
#include "lp_data/HighsOptions.h"
#include "simplex/HEkk.h"

class HighsLpSolverObject {
 public:
  HighsLpSolverObject(HighsLp& lp, HighsBasis& basis, HighsSolution& solution,
                      HighsInfo& highs_info, HEkk& ekk_instance,
                      HighsCallback& callback, HighsOptions& options,
                      HighsTimer& timer,
                      HighsSubSolverCallTime& sub_solver_call_time)
      : lp_(lp),
        basis_(basis),
        solution_(solution),
        highs_info_(highs_info),
        ekk_instance_(ekk_instance),
        callback_(callback),
        options_(options),
        timer_(timer),
        sub_solver_call_time_(sub_solver_call_time) {}

  HighsLp& lp_;
  HighsBasis& basis_;
  HighsSolution& solution_;
  HighsInfo& highs_info_;
  HEkk& ekk_instance_;
  HighsCallback& callback_;
  HighsOptions& options_;
  HighsTimer& timer_;
  HighsSubSolverCallTime& sub_solver_call_time_;
  HighsModelStatus model_status_ = HighsModelStatus::kNotset;
};

#endif  // LP_DATA_HIGHS_LP_SOLVER_OBJECT_H_
