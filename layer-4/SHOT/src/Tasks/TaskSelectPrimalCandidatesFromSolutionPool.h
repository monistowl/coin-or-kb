/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSelectPrimalCandidatesFromSolutionPool.h
 * @brief Check MIP solution pool for feasible MINLP solutions
 *
 * Extracts primal candidates from MIP solver's solution pool.
 *
 * **TaskSelectPrimalCandidatesFromSolutionPool Class:**
 * - run(): Iterate through MIP solution pool
 * - Check each solution for original constraint feasibility
 *
 * **Primal Candidate Processing:**
 * - MIP solution may violate nonlinear constraints
 * - Feasible solutions update primal bound
 * - Infeasible solutions generate hyperplanes
 *
 * @see DualSolver.h for solution pool access
 * @see PrimalSolver.h for feasibility checking
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskSelectPrimalCandidatesFromSolutionPool : public TaskBase
{
public:
    TaskSelectPrimalCandidatesFromSolutionPool(EnvironmentPtr envPtr);
    ~TaskSelectPrimalCandidatesFromSolutionPool() override;

    void run() override;
    std::string getType() override;

private:
};
} // namespace SHOT