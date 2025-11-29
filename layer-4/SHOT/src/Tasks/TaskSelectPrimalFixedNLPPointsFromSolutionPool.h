/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSelectPrimalFixedNLPPointsFromSolutionPool.h
 * @brief Select MIP solutions for fixed-integer NLP solving
 *
 * Chooses promising candidates for NLP refinement.
 *
 * **TaskSelectPrimalFixedNLPPointsFromSolutionPool Class:**
 * - run(): Select best candidates from solution pool
 *
 * **Selection Criteria:**
 * - Prioritize solutions close to feasibility
 * - Avoid already-tested integer assignments
 * - Respect NLP solve budget
 *
 * @see TaskSelectPrimalCandidatesFromNLP.h for NLP solving
 * @see DualSolver.h for solution pool access
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskSelectPrimalFixedNLPPointsFromSolutionPool : public TaskBase
{
public:
    TaskSelectPrimalFixedNLPPointsFromSolutionPool(EnvironmentPtr envPtr);
    ~TaskSelectPrimalFixedNLPPointsFromSolutionPool() override;

    void run() override;
    std::string getType() override;

private:
};
} // namespace SHOT