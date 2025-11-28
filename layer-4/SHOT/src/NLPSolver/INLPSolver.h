/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file NLPSolver/INLPSolver.h
 * @brief Abstract interface for NLP solver backends
 *
 * Pure virtual interface for primal bound NLP solvers.
 *
 * **Starting Point:**
 * - setStartingPoint(): Initialize solver from MIP solution
 * - clearStartingPoint(): Reset to default
 *
 * **Variable Fixing:**
 * - fixVariables(): Fix integer variables for NLP subproblem
 * - unfixVariables(): Restore full problem
 *
 * **Solution Methods:**
 * - solveProblem(): Execute NLP solver
 * - getSolution(): Retrieve primal point
 * - getObjectiveValue(): Primal objective value
 *
 * **Bound Management:**
 * - getVariableLowerBounds(), getVariableUpperBounds()
 * - updateVariableLowerBound(), updateVariableUpperBound()
 *
 * **Implementations:**
 * - NLPSolverIpoptBase: Ipopt interior point solver
 * - NLPSolverGAMS: GAMS NLP solvers
 * - NLPSolverSHOT: Recursive SHOT for NLP
 *
 * @see PrimalSolver.h for fixed-integer NLP subproblems
 * @see NLPSolverBase.h for implementation utilities
 */
#pragma once
#include "../Environment.h"
#include "../Enums.h"
#include "../Structs.h"

namespace SHOT
{
class INLPSolver
{
public:
    INLPSolver(EnvironmentPtr envPtr) : env(envPtr) {};

    virtual ~INLPSolver() = default;

    EnvironmentPtr env;

    virtual void setStartingPoint(VectorInteger variableIndexes, VectorDouble variableValues) = 0;
    virtual void clearStartingPoint() = 0;

    virtual E_NLPSolutionStatus solveProblem() = 0;
    virtual void fixVariables(VectorInteger variableIndexes, VectorDouble variableValues) = 0;

    virtual void unfixVariables() = 0;

    virtual void saveProblemToFile(std::string fileName) = 0;
    virtual void saveOptionsToFile(std::string fileName) = 0;

    virtual VectorDouble getSolution() = 0;
    virtual double getSolution(int i) = 0;
    virtual double getObjectiveValue() = 0;

    virtual VectorDouble getVariableLowerBounds() = 0;
    virtual VectorDouble getVariableUpperBounds() = 0;

    virtual void updateVariableLowerBound(int variableIndex, double bound) = 0;
    virtual void updateVariableUpperBound(int variableIndex, double bound) = 0;

    virtual std::string getSolverDescription() = 0;

protected:
    virtual E_NLPSolutionStatus solveProblemInstance() = 0;
};
} // namespace SHOT