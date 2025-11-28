/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/RelaxationStrategyBase.h
 * @brief Shared helper methods for relaxation strategies
 *
 * Common termination checks for LP/MIP relaxation control.
 *
 * **RelaxationStrategyBase Class:**
 * - isRelaxedSolutionInterior(): Check if LP solution is interior
 * - isConstraintToleranceReached(): Feasibility achieved
 * - isGapReached(): Optimality gap tolerance met
 *
 * **Use Case:**
 * - Determines when to stop LP phase and switch to MIP
 * - Checks convergence criteria during relaxation
 *
 * @see RelaxationStrategyStandard.h for concrete implementation
 */
#pragma once
#include "IRelaxationStrategy.h"
#include "IMIPSolver.h"

namespace SHOT
{
class RelaxationStrategyBase
{
public:
protected:
    bool isRelaxedSolutionInterior();
    bool isConstraintToleranceReached();
    bool isGapReached();

    EnvironmentPtr env;
};

} // namespace SHOT