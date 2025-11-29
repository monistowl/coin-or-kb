/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskAddIntegerCuts.h
 * @brief Add integer cuts to exclude visited solutions
 *
 * Prevents revisiting same integer assignment.
 *
 * **TaskAddIntegerCuts Class:**
 * - run(): Generate cut excluding current integer solution
 *
 * **Integer Cut Types:**
 * - No-good cuts: Exclude exact binary assignment
 * - Local branching: Limit Hamming distance
 *
 * **Usage:**
 * - Multi-tree strategy uses these extensively
 * - Prevents cycling through same MIP solutions
 *
 * @see DualSolver.h for cut addition
 * @see SolutionStrategy/ for multi-tree workflow
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskAddIntegerCuts : public TaskBase
{
public:
    TaskAddIntegerCuts(EnvironmentPtr envPtr);
    ~TaskAddIntegerCuts() override;

    void run() override;
    std::string getType() override;

private:
};
} // namespace SHOT