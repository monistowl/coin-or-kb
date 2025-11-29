/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/MIPSolutionLimitStrategyUnlimited.h
 * @brief No limit on MIP solution pool size
 *
 * Allows solver to collect all feasible solutions.
 *
 * **MIPSolutionLimitStrategyUnlimited Class:**
 * - getInitialLimit(): Returns maximum integer
 * - updateLimit(): No-op (always unlimited)
 *
 * **Use Case:**
 * - Thorough exploration of solution space
 * - May slow down iterations
 *
 * @see IMIPSolutionLimitStrategy.h for interface
 * @see MIPSolutionLimitStrategyIncrease.h for gradual increase
 */
#pragma once
#include "IMIPSolutionLimitStrategy.h"

namespace SHOT
{
class MIPSolutionLimitStrategyUnlimited : public IMIPSolutionLimitStrategy
{
public:
    MIPSolutionLimitStrategyUnlimited(EnvironmentPtr envPtr);
    ~MIPSolutionLimitStrategyUnlimited() override = default;

    bool updateLimit() override;
    int getNewLimit() override;
    int getInitialLimit() override;
};
} // namespace SHOT