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
 * @algorithm RINS (Relaxation Induced Neighborhood Search):
 * Fix variables where LP solution matches incumbent.
 *
 *   For each integer variable x_j:
 *     if LP_sol[j] == incumbent[j] (both integral):
 *       Fix x_j = incumbent[j]
 *
 *   Solve resulting sub-MIP (much smaller than original)
 *   If finds better solution: update incumbent
 *
 * INTUITION: Variables that agree likely have correct values.
 *            Focus search on disagreeing (uncertain) variables.
 *
 * @algorithm RENS (Relaxation Enforced Neighborhood Search):
 * Fix variables that are already integral in LP relaxation.
 *
 *   For each integer variable x_j:
 *     if LP_sol[j] is integral (within tolerance):
 *       Fix x_j = round(LP_sol[j])
 *
 *   Solve sub-MIP to determine fractional variable values
 *
 * INTUITION: LP relaxation provides good guidance.
 *            Only "repair" the fractional parts.
 *
 * @algorithm Feasibility Pump:
 * Iterates between LP and rounding until feasible.
 *
 *   x_tilde = round(LP_solution)  // Initial MIP point
 *   while (not_converged):
 *     // LP phase: find LP point closest to MIP point
 *     Solve: min sum_j |x_j - x_tilde_j|
 *            s.t. Ax <= b
 *     x_LP = LP_solution
 *
 *     // MIP phase: round LP point
 *     x_tilde = round(x_LP)
 *
 *     if (x_tilde is feasible): return x_tilde
 *     if (cycle detected): perturb x_tilde randomly
 *
 * @algorithm ZI-Round (Zero-One Rounding):
 * Shifts variables one at a time to improve integrality.
 *
 *   For each fractional integer variable x_j:
 *     Test shifting up: x_j -> ceil(x_j)
 *     Test shifting down: x_j -> floor(x_j)
 *     Choose shift that maintains feasibility
 *     Update constraint slacks incrementally
 *
 * @ref Danna, Rothberg & Le Pape (2005). "Exploring Relaxation Induced
 *   Neighborhoods to Improve MIP Solutions". Math. Programming 102(1):71-90.
 * @ref Berthold (2014). "RENS: The Optimal Rounding". Math. Programming Comp.
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
 * @complexity
 * - RINS/RENS: O(sub-MIP size) - typically much smaller than original
 * - Feasibility pump: O(iterations * LP_solve)
 * - ZI-Round: O(n * m) for n variables, m constraints
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
