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
 * @algorithm Fixed-Integer NLP Candidate Selection
 * @math From MIP solution pool, select candidates for NLP refinement:
 *       1. Rank by constraint violation: prefer x̄ with small max_i g_i(x̄)
 *       2. Exclude already-tested integer assignments
 *       3. Limit to budget K candidates per iteration
 *       Diverse integer assignments improve primal bound exploration.
 *       Avoids wasting NLP solves on unpromising or repeated candidates.
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