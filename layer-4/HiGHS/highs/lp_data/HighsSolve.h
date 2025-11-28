/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file lp_data/HighsSolve.h
 * @brief Top-level LP solve dispatch and special case handling
 *
 * Entry points for solving LPs with solver selection and preprocessing.
 *
 * **Main Solve Functions:**
 * - solveLp(): Primary entry point dispatching to simplex/IPM
 * - solveUnconstrainedLp(): Handle LPs with no constraints
 *
 * **Solver Selection:**
 * - useIpm(): Check if IPM should be used based on options
 * - useHipo(): Check if parallel HIPO IPM is appropriate
 *   - Considers problem size, structure, and options
 *
 * **Preprocessing:**
 * - assessExcessiveObjectiveBoundScaling(): Detect numerical issues
 *   - Warns if objective/bound ratio is extreme
 *   - Populates user_scale_data for remediation
 *
 * **Dispatch Logic:**
 * 1. Check for special cases (unconstrained, trivially infeasible)
 * 2. Select solver (simplex vs IPM vs HIPO)
 * 3. Call appropriate solver with prepared solver object
 *
 * @see lp_data/HighsLpSolverObject.h for solver state container
 * @see simplex/HEkk.h for simplex implementation
 * @see ipm/IpxWrapper.h for IPM implementation
 */
#ifndef LP_DATA_HIGHSSOLVE_H_
#define LP_DATA_HIGHSSOLVE_H_

#include "lp_data/HighsModelUtils.h"
HighsStatus solveLp(HighsLpSolverObject& solver_object, const string message);
HighsStatus solveUnconstrainedLp(HighsLpSolverObject& solver_object);
HighsStatus solveUnconstrainedLp(const HighsOptions& options, const HighsLp& lp,
                                 HighsModelStatus& model_status,
                                 HighsInfo& highs_info, HighsSolution& solution,
                                 HighsBasis& basis);
void assessExcessiveObjectiveBoundScaling(const HighsLogOptions log_options,
                                          const HighsModel& model,
                                          HighsUserScaleData& user_scale_data);
bool useIpm(const std::string& solver);
bool useHipo(const HighsOptions& options,
             const std::string& specific_solver_option, const HighsLp& lp,
             const bool logging = false);
#endif  // LP_DATA_HIGHSSOLVE_H_
