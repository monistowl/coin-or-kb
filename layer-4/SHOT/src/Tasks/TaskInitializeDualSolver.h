/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskInitializeDualSolver.h
 * @brief Configure and create MIP solver instance
 *
 * One-time setup for MIP solver before main loop.
 *
 * **TaskInitializeDualSolver Class:**
 * - useLazyStrategy: Single-tree (true) or multi-tree (false)
 * - run(): Create appropriate MIP solver type
 *
 * **Solver Selection:**
 * - CPLEX: MIPSolverCplex or MIPSolverCplexSingleTree
 * - Gurobi: MIPSolverGurobi or MIPSolverGurobiSingleTree
 * - CBC: MIPSolverCbc (multi-tree only)
 *
 * @see DualSolver.h for solver management
 * @see MIPSolver/ for solver implementations
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskInitializeDualSolver : public TaskBase
{
public:
    TaskInitializeDualSolver(EnvironmentPtr envPtr, bool useLazyStrategy);
    ~TaskInitializeDualSolver() override;

    void run() override;
    std::string getType() override;

private:
};
} // namespace SHOT