/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskAddHyperplanes.h
 * @brief Add generated hyperplanes to MIP relaxation
 *
 * Transfers cuts from hyperplane pool to MIP solver.
 *
 * **TaskAddHyperplanes Class:**
 * - run(): Add pending hyperplanes to dual problem
 * - itersWithoutAddedHPs: Track stagnation
 *
 * **Cut Management:**
 * - Filters duplicate/dominated cuts
 * - Respects cut limit per iteration
 * - May trigger lazy vs pool constraint handling
 *
 * @algorithm Hyperplane Pool Management
 * @math Add linearizations π·x ≤ π₀ to MIP relaxation.
 *       Each cut derived from gradient: π = ∇g(x*), π₀ = ∇g(x*)·x* - g(x*).
 *       Filters dominated cuts and enforces per-iteration limits.
 * @complexity O(cuts × m) for dominance checking. Pool size bounded.
 * @see DualSolver.h for MIP constraint addition
 * @see TaskSelectHyperplanePointsESH.h for cut generation
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskAddHyperplanes : public TaskBase
{
public:
    TaskAddHyperplanes(EnvironmentPtr envPtr);
    ~TaskAddHyperplanes() override;

    void run() override;

    std::string getType() override;

private:
    int itersWithoutAddedHPs;
};
} // namespace SHOT