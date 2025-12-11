/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file SolutionStrategy/SolutionStrategyMultiTree.h
 * @brief Iterative outer approximation strategy (multi-tree)
 *
 * Classic outer approximation loop for convex MINLP.
 *
 * **Algorithm Pattern:**
 * 1. Solve MIP relaxation to get candidate point
 * 2. Generate supporting hyperplanes at violated points
 * 3. Add cuts to MIP and resolve
 * 4. Repeat until convergence or termination
 *
 * **Task Flow (initializeStrategy):**
 * - CreateDualProblem → SolveIteration → SelectHyperplanes
 * - AddHyperplanes → CheckTermination → loop
 *
 * **Advantages:**
 * - No callback complexity
 * - Can use any MIP solver
 * - Easier debugging/logging
 *
 * **Disadvantages:**
 * - Multiple MIP solves
 * - May regenerate same B&B tree work
 *
 * @algorithm Multi-Tree Outer Approximation for Convex MINLP
 * @math Iterative refinement of polyhedral approximation:
 *       repeat {
 *         x̄ ← solve MIP relaxation (linear outer approx)
 *         if g(x̄) ≤ 0: x̄ is MINLP-feasible, update primal bound
 *         else: for violated g_i(x̄) > 0:
 *           x* ← ESH rootsearch boundary point
 *           Add cut: ∇g_i(x*)·(x - x*) ≤ 0
 *       } until gap ≤ ε or iteration limit
 *       Each MIP solve explores fresh B&B tree with accumulated cuts.
 * @complexity O(iterations × MIP_solve_time + cuts × rootsearch_cost).
 * @ref Duran & Grossmann (1986). "An outer-approximation algorithm for
 *      a class of mixed-integer nonlinear programs". Math. Programming.
 * @see SolutionStrategySingleTree for callback-based variant
 */
#pragma once

#include "ISolutionStrategy.h"
#include "../Environment.h"

namespace SHOT
{
class SolutionStrategyMultiTree : public ISolutionStrategy
{
public:
    SolutionStrategyMultiTree(EnvironmentPtr envPtr);
    virtual ~SolutionStrategyMultiTree();

    bool solveProblem() override;
    void initializeStrategy() override;

protected:
};
} // namespace SHOT