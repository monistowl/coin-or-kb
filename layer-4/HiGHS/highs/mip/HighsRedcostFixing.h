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
 * @algorithm Reduced Cost Fixing:
 *   Derive variable bounds from LP reduced costs and cutoff:
 *   @math For minimization with cutoff z̄:
 *         If d_j > 0 and x_j at lower bound l_j:
 *           x_j ≤ l_j + (z̄ - z_LP) / d_j
 *         If d_j < 0 and x_j at upper bound u_j:
 *           x_j ≥ u_j + (z̄ - z_LP) / d_j
 *   When gap = z̄ - z_LP is small, bounds become tight.
 *   @complexity O(n) per LP solution
 *   @ref Nemhauser, G. and Wolsey, L. (1988). "Integer and Combinatorial
 *        Optimization". Wiley, Section II.1.
 *
 * @algorithm Lurking Bounds:
 *   Precompute bounds that activate at specific objective thresholds:
 *   @math lurking_bound_j(z̄) = l_j + (z̄ - z_root) / d_j^{root}
 *   Stored as multimap: objective_threshold → bound_value
 *   When incumbent improves, extract all bounds with threshold ≥ new_cutoff.
 *   @complexity O(log n) per lookup via std::multimap
 *   @note More effective than repeated propagation on incumbent updates
 *
 * @algorithm Root Reduced Cost Caching:
 *   Store root LP reduced costs for global bound tightening:
 *   - Root LP typically tightest bounds (no branching)
 *   - Reduced costs stable across B&B tree
 *   - propagateRootRedcost() applies cached costs with current cutoff
 *   @complexity O(n) storage, O(n) per propagation
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
