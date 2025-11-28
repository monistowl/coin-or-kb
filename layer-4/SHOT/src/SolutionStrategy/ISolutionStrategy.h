/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file SolutionStrategy/ISolutionStrategy.h
 * @brief Abstract interface for solution strategies
 *
 * Base interface for algorithm selection.
 *
 * **Strategy Interface:**
 * - initializeStrategy(): Configure tasks and solvers
 * - solveProblem(): Execute the solution algorithm
 *
 * **Strategy Implementations:**
 * - SolutionStrategyMultiTree: Iterative outer approximation
 *   - Solve MIP, add cuts, repeat
 * - SolutionStrategySingleTree: Lazy constraint callback
 *   - Single MIP with callback cut injection
 * - SolutionStrategyNLP: Pure NLP (no integer variables)
 * - SolutionStrategyMIQP/MIQCQP: Direct quadratic solving
 *
 * **Selection Logic:**
 * - Problem classification determines best strategy
 * - Convex MINLP → ESH (multi-tree or single-tree)
 * - QP/QCQP → Direct solver if supported
 * - NLP → Interior point only
 *
 * @see TaskHandler.h for task execution flow
 * @see Solver.h for strategy selection
 */
#pragma once

#include "../Environment.h"

namespace SHOT
{
class ISolutionStrategy
{
public:
    virtual ~ISolutionStrategy() = default;

    virtual void initializeStrategy() = 0;
    virtual bool solveProblem() = 0;

protected:
    EnvironmentPtr env;
};
} // namespace SHOT
