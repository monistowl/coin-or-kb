/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsRedcostFixing.h
 * @brief Reduced cost fixing and lurking bounds for MIP
 *
 * Uses LP reduced costs to fix variable bounds based on cutoff.
 *
 * **Reduced Cost Fixing:**
 * If fixing variable j to its bound would increase objective beyond cutoff,
 * the opposite bound becomes valid. For minimization:
 * - If reduced_cost[j] > 0 and x[j] = lb: fixing to ub proves lb valid
 * - If reduced_cost[j] < 0 and x[j] = ub: fixing to lb proves ub valid
 *
 * **Lurking Bounds:**
 * Bounds that become valid at specific objective values:
 * - lurkingColUpper[col]: (objective_threshold, bound_value) pairs
 * - lurkingColLower[col]: Maps threshold to tighter bound
 * - getLurkingBounds(): Extract bounds valid at current cutoff
 *
 * **Propagation Methods:**
 * - propagateRootRedcost(): Apply fixings at root using stored costs
 * - propagateRedCost(): Apply fixings at any node using LP reduced costs
 * - addRootRedcost(): Store root LP reduced costs for later use
 *
 * **Integration:**
 * - Called when incumbent improves (new cutoff enables more fixings)
 * - Provides global domain tightening from LP dual information
 *
 * @see mip/HighsDomain.h for bound propagation
 * @see mip/HighsLpRelaxation.h for LP solution access
 */

#ifndef HIGHS_REDCOST_FIXING_H_
#define HIGHS_REDCOST_FIXING_H_

#include <map>
#include <vector>

#include "mip/HighsDomainChange.h"

class HighsDomain;
class HighsMipSolver;
class HighsLpRelaxation;

class HighsRedcostFixing {
  std::vector<std::multimap<double, HighsInt>> lurkingColUpper;
  std::vector<std::multimap<double, HighsInt>> lurkingColLower;

 public:
  std::vector<std::pair<double, HighsDomainChange>> getLurkingBounds(
      const HighsMipSolver& mipsolver) const;

  void propagateRootRedcost(const HighsMipSolver& mipsolver);

  static void propagateRedCost(const HighsMipSolver& mipsolver,
                               HighsDomain& localdomain,
                               const HighsLpRelaxation& lp);

  void addRootRedcost(const HighsMipSolver& mipsolver,
                      const std::vector<double>& lpredcost, double lpobjective);
};

#endif
