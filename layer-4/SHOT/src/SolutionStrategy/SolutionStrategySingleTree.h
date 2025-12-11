/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file SolutionStrategy/SolutionStrategySingleTree.h
 * @brief Lazy constraint callback strategy (single-tree)
 *
 * Callback-based outer approximation within single B&B tree.
 *
 * **Algorithm Pattern:**
 * 1. Solve MIP with lazy constraint callback
 * 2. Callback checks integer solutions for feasibility
 * 3. Generate hyperplanes for violated constraints
 * 4. Add as lazy constraints, solver continues
 *
 * **Task Flow (initializeStrategy):**
 * - CreateDualProblem → ConfigureCallback → SolveProblem
 * - (cuts added via callback during solve)
 *
 * **Advantages:**
 * - Single B&B tree exploration
 * - Potentially fewer node evaluations
 * - Better integration with MIP solver
 *
 * **Disadvantages:**
 * - Requires solver callback support
 * - Limited to CPLEX/Gurobi
 * - More complex debugging
 *
 * @algorithm Single-Tree Branch-and-Cut for Convex MINLP
 * @math Integrates ESH cut generation into MIP B&B via lazy constraints:
 *       1. Build initial MIP relaxation (linear + quadratic constraints)
 *       2. Register callback for integer solution events
 *       3. At each integer candidate x̄:
 *          - Check nonlinear g_i(x̄) ≤ 0 feasibility
 *          - Generate ESH cuts for violated constraints
 *          - Reject candidate and add cuts as lazy constraints
 *       4. Solver continues until gap closed or limit reached
 *       Avoids rebuilding B&B tree as in multi-tree approach.
 * @complexity Single MIP solve with O(nodes × callback cost) overhead.
 * @ref Kronqvist et al. (2016). "The extended supporting hyperplane algorithm"
 * @see MIPSolverCplexSingleTree, MIPSolverGurobiSingleTree
 */
#pragma once

#include "ISolutionStrategy.h"
#include "../Environment.h"

namespace SHOT
{
class SolutionStrategySingleTree : public ISolutionStrategy
{
public:
    SolutionStrategySingleTree(EnvironmentPtr envPtr);
    virtual ~SolutionStrategySingleTree();

    bool solveProblem() override;
    void initializeStrategy() override;

protected:
};
} // namespace SHOT