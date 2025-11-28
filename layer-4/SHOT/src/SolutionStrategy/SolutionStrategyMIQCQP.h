/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file SolutionStrategy/SolutionStrategyMIQCQP.h
 * @brief Direct MIQCQP solver for convex quadratic problems
 *
 * Bypasses ESH for problems solvable by CPLEX/Gurobi MIQCQP.
 *
 * **SolutionStrategyMIQCQP Class:**
 * - initializeStrategy(): Configure for direct MIQCQP solve
 * - solveProblem(): Single solver call, no outer approximation
 *
 * **Use Case:**
 * - Convex MIQCQP (quadratic constraints, convex)
 * - CPLEX and Gurobi support convex QCQP natively
 * - Faster than iterative linearization for small problems
 *
 * **Problem Classification:**
 * - All constraints must be convex quadratic
 * - Solver must support QCQP (supportsQuadraticConstraints)
 *
 * @algorithm Direct MIQCQP branch-and-bound
 * @see SolutionStrategyMultiTree.h for general MINLP
 */
#pragma once

#include "ISolutionStrategy.h"
#include "../Environment.h"

namespace SHOT
{
class SolutionStrategyMIQCQP : public ISolutionStrategy
{
public:
    SolutionStrategyMIQCQP(EnvironmentPtr envPtr);
    virtual ~SolutionStrategyMIQCQP();

    bool solveProblem() override;
    void initializeStrategy() override;

protected:
};
} // namespace SHOT