/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskRepairInfeasibleDualProblem.h
 * @brief Recover from infeasible MIP relaxation
 *
 * Attempts to restore feasibility when cuts cause infeasibility.
 *
 * **TaskRepairInfeasibleDualProblem Class:**
 * - mainRepairTries, totRepairTries: Repair attempt counters
 * - run(): Attempt repair strategies
 *
 * **Repair Strategies:**
 * - Remove recently added cuts
 * - Relax cut coefficients
 * - Remove dominated cuts
 *
 * **When Called:**
 * - MIP solver returns infeasible
 * - May indicate numerical issues with cuts
 *
 * @algorithm MIP Relaxation Repair
 * @math When cuts render MIP infeasible (numerical issues):
 *       1. Identify recent cuts: {π_k·x ≤ π₀_k} from last iterations
 *       2. Remove or relax: try π_k·x ≤ π₀_k + ε for small ε
 *       3. Re-solve and verify feasibility restored
 * @complexity O(recent cuts × MIP solve). Limited repair attempts.
 * @see DualSolver.h for MIP status
 * @see TaskAddHyperplanes.h for cut management
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskRepairInfeasibleDualProblem : public TaskBase
{
public:
    TaskRepairInfeasibleDualProblem(EnvironmentPtr envPtr, std::string taskIDTrue, std::string taskIDFalse);
    ~TaskRepairInfeasibleDualProblem() override;

    void run() override;
    std::string getType() override;

private:
    std::string taskIDIfTrue;
    std::string taskIDIfFalse;
    int iterLastRepair = 0;
    int mainRepairTries = 0;
    int totRepairTries = 0;
};
} // namespace SHOT