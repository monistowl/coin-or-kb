/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskInitializeRootsearch.h
 * @brief Setup rootsearch method for ESH
 *
 * One-time initialization of boundary finding algorithm.
 *
 * **TaskInitializeRootsearch Class:**
 * - run(): Create and configure rootsearch method
 *
 * **Rootsearch Setup:**
 * - Select algorithm (TOMS 748, bisection)
 * - Configure tolerances and iteration limits
 * - Required for ESH hyperplane generation
 *
 * @algorithm Rootsearch Initialization for ESH
 * @math ESH requires finding boundary point x* on line from interior x° to
 *       infeasible x̂. Rootsearch finds λ* where g(x° + λ*(x̂-x°)) = 0.
 *       Algorithm selection:
 *       - TOMS 748: 4th-order optimal bracketing (faster convergence)
 *       - Bisection: Simple halving (guaranteed but slower)
 *       Tolerances: lambdaTol (line parameter), constrTol (constraint value).
 * @ref Alefeld, Potra, Shi (1995). "TOMS 748"
 * @see RootsearchMethod/ for algorithm implementations
 * @see TaskSelectHyperplanePointsESH.h for usage
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskInitializeRootsearch : public TaskBase
{
public:
    TaskInitializeRootsearch(EnvironmentPtr envPtr);
    ~TaskInitializeRootsearch() override;

    void run() override;

    std::string getType() override;
};
} // namespace SHOT