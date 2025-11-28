/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/MIPSolverGurobiSingleTree.h
 * @brief Gurobi with lazy constraint callback for single-tree ESH
 *
 * Extends MIPSolverGurobi with callback-based cut generation.
 *
 * **GurobiCallbackSingleTree Class:**
 * - Inherits GRBCallback + MIPSolverCallbackBase
 * - callback(): Called at candidate solution points
 * - createHyperplane()/createIntegerCut(): Add lazy constraints
 * - addLazyConstraint(): Generate ESH cuts from solution
 *
 * **MIPSolverGurobiSingleTree Class:**
 * - solveProblem(): Single MIP solve with callbacks enabled
 * - isCallbackInitialized: Track callback registration
 *
 * **Node Information:**
 * - lastExploredNodes/lastOpenNodes: B&B tree progress
 * - Used for iteration reporting within callback
 *
 * @see SolutionStrategySingleTree.h for algorithm context
 */
#pragma once
#include "MIPSolverBase.h"
#include "MIPSolverGurobi.h"
#include "MIPSolverCallbackBase.h"

namespace SHOT
{

class GurobiCallbackSingleTree : public GRBCallback, public MIPSolverCallbackBase
{
public:
    GRBVar* vars;
    GurobiCallbackSingleTree(GRBVar* xvars, EnvironmentPtr envPtr);
    ~GurobiCallbackSingleTree();

protected:
    void callback() override;

private:
    int lastExploredNodes = 0;
    int lastOpenNodes = 0;
    bool showOutput = false;

    bool createHyperplane(Hyperplane hyperplane);

    virtual bool createIntegerCut(IntegerCut& integerCut);

    void addLazyConstraint(std::vector<SolutionPoint> candidatePoints);
};

class MIPSolverGurobiSingleTree : public MIPSolverGurobi
{
public:
    MIPSolverGurobiSingleTree(EnvironmentPtr envPtr);
    ~MIPSolverGurobiSingleTree() override;

    void checkParameters() override;

    void initializeSolverSettings() override;

    int increaseSolutionLimit(int increment) override;
    void setSolutionLimit(long limit) override;
    int getSolutionLimit() override;

    E_ProblemSolutionStatus solveProblem() override;

private:
    bool isCallbackInitialized = false;
    std::unique_ptr<GurobiCallbackSingleTree> gurobiCallback;
};
} // namespace SHOT