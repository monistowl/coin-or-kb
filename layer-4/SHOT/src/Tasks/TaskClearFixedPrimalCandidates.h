/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskClearFixedPrimalCandidates.h
 * @brief Clear pending fixed-integer NLP candidates
 *
 * Resets candidate queue between iterations.
 *
 * **TaskClearFixedPrimalCandidates Class:**
 * - run(): Empty the fixed-NLP candidate list
 *
 * **Usage:**
 * - Called at start of each iteration
 * - Ensures fresh candidate selection each cycle
 *
 * @see TaskSelectPrimalFixedNLPPointsFromSolutionPool.h for selection
 * @see TaskSelectPrimalCandidatesFromNLP.h for NLP solving
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskClearFixedPrimalCandidates : public TaskBase
{
public:
    TaskClearFixedPrimalCandidates(EnvironmentPtr envPtr);
    ~TaskClearFixedPrimalCandidates() override;

    void run() override;

    std::string getType() override;

private:
};
} // namespace SHOT