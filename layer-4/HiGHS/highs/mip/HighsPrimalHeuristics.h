/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsPrimalHeuristics.h
 * @brief Primal heuristics for finding MIP feasible solutions
 *
 * Collection of primal heuristics to discover incumbent solutions.
 *
 * **Sub-MIP Heuristics:**
 * - solveSubMip(): Solve restricted MIP with fixed/bounded variables
 * - RENS(): Relaxation Enforced Neighborhood Search (fix non-LP-integer vars)
 * - RINS(): Relaxation Induced Neighborhood Search (fix incumbent-matching vars)
 *
 * **Rounding Heuristics:**
 * - feasibilityPump(): Iterate between LP and MIP rounding until feasible
 * - centralRounding(): Round from analytic center
 * - randomizedRounding(): Probabilistic rounding based on fractionality
 * - ziRound(): Berthold's ZI-Round shifting
 * - tryRoundedPoint(): Simple rounding with constraint repair
 * - linesearchRounding(): Round along line between two points
 *
 * **Other Methods:**
 * - rootReducedCost(): Fix variables using reduced costs at root
 * - shifting(): Variable shifting to repair constraint violations
 *
 * **Adaptive Targeting:**
 * - determineTargetFixingRate(): Adjust fixing rate based on success history
 * - successObservations/infeasObservations: Track heuristic effectiveness
 *
 * @see mip/HighsMipSolverData.h for heuristic controller
 * @see mip/HighsLpRelaxation.h for LP solution access
 */
#ifndef HIGHS_PRIMAL_HEURISTICS_H_
#define HIGHS_PRIMAL_HEURISTICS_H_

#include <vector>

#include "lp_data/HStruct.h"
#include "lp_data/HighsLp.h"
#include "util/HighsRandom.h"

class HighsMipSolver;
class HighsLpRelaxation;

class HighsPrimalHeuristics {
 private:
  HighsMipSolver& mipsolver;
  size_t total_repair_lp;
  size_t total_repair_lp_feasible;
  size_t total_repair_lp_iterations;
  size_t lp_iterations;

  double successObservations;
  HighsInt numSuccessObservations;
  double infeasObservations;
  HighsInt numInfeasObservations;

  HighsRandom randgen;

  std::vector<HighsInt> intcols;

 public:
  HighsPrimalHeuristics(HighsMipSolver& mipsolver);

  void setupIntCols();

  bool solveSubMip(const HighsLp& lp, const HighsBasis& basis,
                   double fixingRate, std::vector<double> colLower,
                   std::vector<double> colUpper, HighsInt maxleaves,
                   HighsInt maxnodes, HighsInt stallnodes);

  double determineTargetFixingRate();

  void rootReducedCost();

  void RENS(const std::vector<double>& relaxationsol);

  void RINS(const std::vector<double>& relaxationsol);

  void feasibilityPump();

  void centralRounding();

  void flushStatistics();

  bool tryRoundedPoint(const std::vector<double>& point,
                       const int solution_source);

  bool linesearchRounding(const std::vector<double>& point1,
                          const std::vector<double>& point2,
                          const int solution_source);

  void randomizedRounding(const std::vector<double>& relaxationsol);

  void shifting(const std::vector<double>& relaxationsol);

  void ziRound(const std::vector<double>& relaxationsol);
};

#endif
