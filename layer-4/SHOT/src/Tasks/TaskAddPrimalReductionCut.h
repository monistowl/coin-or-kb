/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskAddPrimalReductionCut.h
 * @brief Add objective cutoff based on incumbent
 *
 * Uses primal bound to tighten MIP relaxation.
 *
 * **TaskAddPrimalReductionCut Class:**
 * - currentLowerBoundForReductionCut: Current cutoff value
 * - run(): Update objective bound constraint
 *
 * **Cutoff Strategy:**
 * - Adds constraint: objective <= bestPrimal - epsilon
 * - Forces MIP to find improving solutions only
 * - Updated when primal bound improves
 *
 * @algorithm Primal Cutoff Constraint (Objective Reduction Cut)
 * @math When primal bound z̄ improves, add cutoff constraint to MIP:
 *       - Minimization: f(x) ≤ z̄ - ε (or t ≤ z̄ - ε for epigraph)
 *       - Prevents MIP from returning non-improving solutions
 *       - ε > 0 ensures strict improvement
 *       Updates dynamically as better incumbents are found.
 *       Reduces explored B&B nodes by tightening dual bound gap.
 * @see Results.h for primal bound tracking
 * @see TaskCheckMaxNumberOfPrimalReductionCuts.h for limit
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskAddPrimalReductionCut : public TaskBase
{
public:
    TaskAddPrimalReductionCut(EnvironmentPtr envPtr, std::string taskIDTrue, std::string taskIDFalse);
    ~TaskAddPrimalReductionCut() override;

    void run() override;

    std::string getType() override;

private:
    std::string taskIDIfTrue;
    std::string taskIDIfFalse;
    int totalReductionCutUpdates = 0;
    double currentLowerBoundForReductionCut = SHOT_DBL_INF;
};
} // namespace SHOT