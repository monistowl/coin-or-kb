/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file NLPSolver/NLPSolverSHOT.h
 * @brief SHOT as NLP solver for convex subproblems
 *
 * Recursive use of SHOT to solve fixed-integer NLP.
 *
 * **NLPSolverSHOT Class:**
 * - Creates nested SHOT solver instance
 * - Solves convex NLP after fixing integer variables
 * - Useful when Ipopt is unavailable
 *
 * **Fixed-Integer NLP:**
 * - fixVariables(): Fix discrete variables to integer values
 * - solveProblemInstance(): Solve continuous subproblem
 * - getSolution(): Return primal solution
 *
 * **Nested Architecture:**
 * - Outer SHOT: Full MINLP (uses this as primal solver)
 * - Inner SHOT: Convex NLP (fixed integers)
 *
 * @note Self-referential design for solver-agnostic NLP solving
 */
#pragma once
#include "NLPSolverBase.h"

namespace SHOT
{
class Solver;

class NLPSolverSHOT : public NLPSolverBase
{
private:
    ProblemPtr sourceProblem;
    ProblemPtr relaxedProblem;

    VectorInteger fixedVariableIndexes;
    VectorDouble fixedVariableValues;

    bool problemInfoPrinted = false;

    void initializeMIPProblem();

public:
    NLPSolverSHOT(EnvironmentPtr envPtr, ProblemPtr source);

    ~NLPSolverSHOT() override;

    void setStartingPoint(VectorInteger variableIndexes, VectorDouble variableValues) override;
    void clearStartingPoint() override;

    void fixVariables(VectorInteger variableIndexes, VectorDouble variableValues) override;

    void unfixVariables() override;

    void saveOptionsToFile(std::string fileName) override;

    void saveProblemToFile(std::string fileName) override;

    VectorDouble getSolution() override;
    double getSolution(int i) override;

    double getObjectiveValue() override;

    void updateVariableLowerBound(int variableIndex, double bound) override;
    void updateVariableUpperBound(int variableIndex, double bound) override;

    std::string getSolverDescription() override;

    std::shared_ptr<Solver> solver;

protected:
    E_NLPSolutionStatus solveProblemInstance() override;

    VectorDouble getVariableLowerBounds() override;
    VectorDouble getVariableUpperBounds() override;
};
} // namespace SHOT