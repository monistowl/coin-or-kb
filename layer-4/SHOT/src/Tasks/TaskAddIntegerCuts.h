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
 * @algorithm No-Good Cuts (Integer Exclusion)
 * @math Given binary solution x̄, add cut:
 *       Σ_{j: x̄_j=1} (1-x_j) + Σ_{j: x̄_j=0} x_j ≥ 1
 *       Requires Hamming distance ≥ 1 from x̄. Excludes exactly this solution.
 * @complexity O(|binary variables|) per cut generation.
 * @ref Balas & Jeroslow (1972). "Canonical cuts on the unit hypercube".
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