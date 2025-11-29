/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/MIPSolverCbc.h
 * @brief COIN-OR Cbc implementation of IMIPSolver interface
 *
 * Provides open-source MIP solving using Cbc branch-and-cut solver.
 *
 * **MIPSolverCbc Class:**
 * - Implements IMIPSolver interface
 * - Uses OsiClpSolverInterface for LP subproblems
 * - CbcModel for branch-and-cut
 * - CoinModel for problem construction
 *
 * **Key Data Structures:**
 * - osiInterface: OSI LP solver (Clp)
 * - cbcModel: MIP solver model
 * - coinModel: Problem builder
 * - objectiveLinearExpression: CoinPackedVector
 *
 * **CbcMessageHandler:**
 * - Custom message handler for SHOT logging
 * - Routes Cbc output through SHOT's Output system
 *
 * **Limitations:**
 * - supportsQuadraticObjective(): No
 * - supportsQuadraticConstraints(): No
 * - LP/MIP only (no MIQP/QCQP)
 *
 * @note Default open-source MIP solver, no license required
 * @see Cbc branch-and-cut library
 *
 * @algorithm SHOT Outer Approximation via MIP (solveProblem):
 *   SHOT solves MINLP by iterating between:
 *   1. Solve MIP relaxation (linearized problem) → dual bound
 *   2. Evaluate NLP at integer solution → primal bound (if feasible)
 *   3. Add hyperplane cuts to improve approximation
 *   This class provides step 1 using CBC branch-and-cut.
 *   @math For convex MINLP: MIP relaxation provides valid dual bound
 *         since hyperplanes underestimate convex functions.
 *   @complexity Each MIP solve is NP-hard; CBC uses B&C with CGL cuts
 *   @ref Duran & Grossmann (1986) - Outer Approximation for MINLP
 *   @ref Kronqvist et al. (2019) - SHOT solver description
 *
 * @algorithm Hyperplane (Supporting Hyperplane) Addition (createHyperplane):
 *   For nonlinear constraint g(x) <= 0 at point x̂:
 *   @math Linearization: g(x̂) + ∇g(x̂)ᵀ(x - x̂) <= 0
 *   For convex g, this is a valid outer approximation cut.
 *   Added as linear constraints via addLinearConstraint().
 *   @ref Kelley's cutting-plane method (1960)
 *
 * @algorithm Integer Cut (No-Good Cut) Generation (createIntegerCut):
 *   Excludes previously found integer solutions:
 *   @math For binary x with solution x̂ ∈ {0,1}ⁿ:
 *         ∑(x_j : x̂_j=1) - ∑(x_j : x̂_j=0) <= |{j: x̂_j=1}| - 1
 *   Prevents cycling when NLP subproblem fails or solution is infeasible.
 *
 * @algorithm Dual Bound Computation (getDualObjectiveValue):
 *   The optimal value of the MIP relaxation provides a dual bound:
 *   - For minimization: MIP optimum <= true MINLP optimum
 *   - Quality improves as more hyperplanes are added
 *   - Convergence guaranteed for convex MINLP (finite # of linearizations)
 *
 * @algorithm MIP Solution Pool (getAllVariableSolutions):
 *   CBC can return multiple feasible integer solutions.
 *   SHOT uses these as candidate points for NLP evaluation:
 *   - More solutions = more chances to find primal feasible point
 *   - Controlled by setSolutionLimit()
 *   @ref Solution pool heuristics in MIP solvers
 */
#pragma once
#include "MIPSolverBase.h"

#include <optional>

#include "CoinPackedVector.hpp"
#include "CoinMessageHandler.hpp"

class OsiClpSolverInterface;
class CbcModel;
class CoinModel;
class CbcObject;

namespace SHOT
{

class CbcMessageHandler : public CoinMessageHandler
{
private:
    EnvironmentPtr env;

public:
    CbcMessageHandler(EnvironmentPtr envPtr) : CoinMessageHandler() { env = envPtr; }

    CbcMessageHandler(const CbcMessageHandler& r) : CoinMessageHandler(r), env(r.env) { }

    CbcMessageHandler& operator=(const CbcMessageHandler& r)
    {
        CoinMessageHandler::operator=(r);
        env = r.env;
        return *this;
    }

    virtual CoinMessageHandler* clone() const { return new CbcMessageHandler(*this); }

    virtual int print();
};

class MIPSolverCbc : public IMIPSolver, MIPSolverBase
{
public:
    MIPSolverCbc(EnvironmentPtr envPtr);
    ~MIPSolverCbc() override;

    bool initializeProblem() override;

    void checkParameters() override;

    bool addVariable(
        std::string name, E_VariableType type, double lowerBound, double upperBound, double semiBound) override;

    bool initializeObjective() override;
    bool addLinearTermToObjective(double coefficient, int variableIndex) override;
    bool addQuadraticTermToObjective(double coefficient, int firstVariableIndex, int secondVariableIndex) override;
    bool finalizeObjective(bool isMinimize, double constant = 0.0) override;

    bool initializeConstraint() override;
    bool addLinearTermToConstraint(double coefficient, int variableIndex) override;
    bool addQuadraticTermToConstraint(double coefficient, int firstVariableIndex, int secondVariableIndex) override;
    bool finalizeConstraint(std::string name, double valueLHS, double valueRHS, double constant = 0.0) override;

    bool finalizeProblem() override;

    void initializeSolverSettings() override;

    void writeProblemToFile(std::string filename) override;
    void writePresolvedToFile(std::string filename) override;

    int addLinearConstraint(std::map<int, double>& elements, double constant, std::string name) override
    {
        return (addLinearConstraint(elements, constant, name, false, true));
    }

    int addLinearConstraint(
        const std::map<int, double>& elements, double constant, std::string name, bool isGreaterThan) override
    {
        return (addLinearConstraint(elements, constant, name, isGreaterThan, true));
    }

    int addLinearConstraint(const std::map<int, double>& elements, double constant, std::string name,
        bool isGreaterThan, bool allowRepair) override;

    bool addSpecialOrderedSet(
        E_SOSType type, VectorInteger variableIndexes, VectorDouble variableWeights = {}) override;

    bool createHyperplane(Hyperplane hyperplane) override { return (MIPSolverBase::createHyperplane(hyperplane)); }

    bool createIntegerCut(IntegerCut& integerCut) override;

    bool createInteriorHyperplane(Hyperplane hyperplane) override
    {
        return (MIPSolverBase::createInteriorHyperplane(hyperplane));
    }

    std::optional<std::pair<std::map<int, double>, double>> createHyperplaneTerms(Hyperplane hyperplane) override
    {
        return (MIPSolverBase::createHyperplaneTerms(hyperplane));
    }

    void fixVariable(int varIndex, double value) override;

    void fixVariables(VectorInteger variableIndexes, VectorDouble variableValues) override
    {
        MIPSolverBase::fixVariables(variableIndexes, variableValues);
    }

    void unfixVariables() override { MIPSolverBase::unfixVariables(); }

    void updateVariableBound(int varIndex, double lowerBound, double upperBound) override;
    void updateVariableLowerBound(int varIndex, double lowerBound) override;
    void updateVariableUpperBound(int varIndex, double upperBound) override;

    PairDouble getCurrentVariableBounds(int varIndex) override;

    void presolveAndUpdateBounds() override { return (MIPSolverBase::presolveAndUpdateBounds()); }

    std::pair<VectorDouble, VectorDouble> presolveAndGetNewBounds() override;

    void activateDiscreteVariables(bool activate) override;
    bool getDiscreteVariableStatus() override { return (MIPSolverBase::getDiscreteVariableStatus()); }

    E_DualProblemClass getProblemClass() override { return (MIPSolverBase::getProblemClass()); }

    void executeRelaxationStrategy() override { MIPSolverBase::executeRelaxationStrategy(); }

    E_ProblemSolutionStatus solveProblem() override;
    bool repairInfeasibility() override;

    E_ProblemSolutionStatus getSolutionStatus() override;
    int getNumberOfSolutions() override;
    VectorDouble getVariableSolution(int solIdx) override;
    std::vector<SolutionPoint> getAllVariableSolutions() override { return (MIPSolverBase::getAllVariableSolutions()); }
    double getDualObjectiveValue() override;
    double getObjectiveValue(int solIdx) override;
    double getObjectiveValue() override { return (MIPSolverBase::getObjectiveValue()); }

    int increaseSolutionLimit(int increment) override;
    void setSolutionLimit(long limit) override;
    int getSolutionLimit() override;

    void setTimeLimit(double seconds) override;

    void setCutOff(double cutOff) override;
    void setCutOffAsConstraint(double cutOff) override;
    void addMIPStart(VectorDouble point) override;
    void deleteMIPStarts() override;

    bool supportsQuadraticObjective() override;
    bool supportsQuadraticConstraints() override;

    double getUnboundedVariableBoundValue() override;

    int getNumberOfExploredNodes() override;

    int getNumberOfOpenNodes() override { return (MIPSolverBase::getNumberOfOpenNodes()); }

    int getNumberOfVariables() override { return (MIPSolverBase::getNumberOfVariables()); }

    bool hasDualAuxiliaryObjectiveVariable() override { return (MIPSolverBase::hasDualAuxiliaryObjectiveVariable()); }

    int getDualAuxiliaryObjectiveVariableIndex() override
    {
        return (MIPSolverBase::getDualAuxiliaryObjectiveVariableIndex());
    }

    void setDualAuxiliaryObjectiveVariableIndex(int index) override
    {
        MIPSolverBase::setDualAuxiliaryObjectiveVariableIndex(index);
    }

    std::string getConstraintIdentifier(E_HyperplaneSource source) override
    {
        return (MIPSolverBase::getConstraintIdentifier(source));
    };

    std::string getSolverVersion() override;

private:
    std::unique_ptr<OsiClpSolverInterface> osiInterface;
    std::unique_ptr<CbcModel> cbcModel;
    std::unique_ptr<CoinModel> coinModel;
    std::unique_ptr<CbcMessageHandler> messageHandler;

    CoinPackedVector objectiveLinearExpression;

    long int solLimit;
    double timeLimit = 1e100;
    double cutOff;
    int numberOfThreads = 1;
    double objectiveConstant = 0.0;

    std::vector<std::pair<std::string, double>> MIPStart;

    std::vector<E_VariableType> variableTypes;
    std::vector<std::pair<int, std::array<double, 4>>> lotsizes;
};

} // namespace SHOT