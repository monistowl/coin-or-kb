/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskFindInteriorPoint.h
 * @brief Find strictly feasible interior point for ESH
 *
 * Critical for ESH: rootsearch needs interior point endpoint.
 *
 * **TaskFindInteriorPoint Class:**
 * - NLPSolvers: Solvers for finding interior
 * - run(): Attempt to find strictly feasible point
 *
 * **Interior Point Methods:**
 * - Solve feasibility problem with slack maximization
 * - Use NLP solver (Ipopt) with modified objective
 * - Required for ESH rootsearch to work
 *
 * @algorithm Interior Point Finding via Slack Maximization
 * @math Solve: max s subject to g_i(x) ≤ -s for all constraints i.
 *       If s* > 0, point x* is strictly interior (all constraints slack).
 *       Required for ESH rootsearch: interpolates interior → exterior.
 * @complexity O(NLP solve). Uses Ipopt or minimax cutting-plane.
 * @see TaskUpdateInteriorPoint.h for runtime updates
 * @see RootsearchMethod/ for interior point usage
 */
#pragma once
#include "TaskBase.h"

#include <memory>
#include <vector>

namespace SHOT
{

class INLPSolver;

class TaskFindInteriorPoint : public TaskBase
{
public:
    TaskFindInteriorPoint(EnvironmentPtr envPtr);
    ~TaskFindInteriorPoint() override;

    void run() override;
    std::string getType() override;

private:
    std::vector<std::unique_ptr<INLPSolver>> NLPSolvers;

    VectorString variableNames;
};
} // namespace SHOT