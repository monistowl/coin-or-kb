/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/IMIPSolver.h
 * @brief Abstract interface for MIP solver backends
 *
 * Pure virtual interface for dual problem MIP solvers.
 *
 * **Problem Construction:**
 * - initializeProblem(), finalizeProblem(): Setup/teardown
 * - addVariable(): With type, bounds, and semi-bounds
 * - addLinearTermToObjective/Constraint(): Build incrementally
 * - addQuadraticTermToObjective/Constraint(): For MIQP/MIQCQP
 *
 * **Solution Methods:**
 * - solveProblem(): Execute MIP solver
 * - repairInfeasibility(): Attempt feasibility repair
 * - getObjectiveValue(), getDualObjectiveValue(): Bounds
 * - getVariableSolution(), getAllVariableSolutions(): Points
 *
 * **Hyperplane/Cut Management:**
 * - createHyperplane(): Add supporting hyperplane linearization
 * - createInteriorHyperplane(): Interior point cuts
 * - createIntegerCut(): No-good cuts for integer variables
 *
 * **Bound Management:**
 * - setCutOff(): Objective cutoff for pruning
 * - fixVariable(), unfixVariables(): For integer fixing
 * - presolveAndUpdateBounds(): Bound tightening
 *
 * **Implementations:**
 * - MIPSolverCplex, MIPSolverGurobi, MIPSolverCbc
 * - SingleTree variants for callback-based cut addition
 *
 * @see DualSolver.h for MIP solver orchestration
 * @see IRelaxationStrategy.h for LP relaxation handling
 *
 * @algorithm Multi-Tree vs Single-Tree Outer Approximation:
 *   Multi-Tree (this interface): Solve MIP from scratch each iteration
 *   @math Iteration k: solve MIP^k = {min cx : Ax <= b, linearizations_1...k}
 *   - Simpler implementation, uses MIP solver as black box
 *   - Can exploit MIP warm-starting between iterations
 *   - Used by default implementations (MIPSolverCbc, MIPSolverCplex)
 *   Single-Tree (callback-based): Add cuts during single B&B tree
 *   - More efficient: no tree re-exploration between iterations
 *   - Requires solver callback API (lazy constraint callbacks)
 *   @ref Kronqvist et al. (2016) - Extended Supporting Hyperplane Algorithm
 *
 * @algorithm Supporting Hyperplane Construction (createHyperplane):
 *   For convex constraint g(x) <= 0 at linearization point x̂:
 *   @math g(x̂) + ∇g(x̂)ᵀ(x - x̂) <= 0
 *        Rearranged: ∇g(x̂)ᵀx <= ∇g(x̂)ᵀx̂ - g(x̂)
 *   Returns as map<index, coef> and constant for efficient MIP construction.
 *   @ref Kelley (1960) - Cutting-plane method for convex programming
 *
 * @algorithm Cutoff Pruning (setCutOff):
 *   Prune B&B nodes where LP relaxation >= cutoff:
 *   - For minimization: cutoff = best primal bound - tolerance
 *   - Reduces MIP exploration significantly
 *   @math Prune node n if: LP(n) >= z* (current best solution)
 *   Can be set as hard cutoff or as objective constraint.
 *
 * @algorithm Infeasibility Repair (repairInfeasibility):
 *   When MIP relaxation becomes infeasible (over-approximation):
 *   - May indicate numerical issues or strong cutting
 *   - Attempts to find closest feasible point
 *   - Solver-specific: uses IIS analysis or feasibility pump
 *   @ref Achterberg et al. (2007) - Conflict analysis in MIP solving
 *
 * @algorithm MIP Start (Warm Starting) (addMIPStart):
 *   Provide known feasible solution to MIP solver:
 *   - From NLP subproblem solutions in outer approximation
 *   - Improves primal bound immediately
 *   - Guides B&B exploration toward good solutions
 *   @ref Achterberg (2007) - SCIP: Solving Constraint Integer Programs
 */
#pragma once
#include "../Environment.h"
#include "../Enums.h"
#include "../Structs.h"

#include <map>
#include <optional>
#include <string>
#include <vector>
#include <utility>

namespace SHOT
{

class IMIPSolver
{
public:
    virtual ~IMIPSolver() = default;

    virtual bool initializeProblem() = 0;
    virtual void checkParameters() = 0;

    virtual bool addVariable(std::string name, E_VariableType type, double lowerBound, double upperBound, double semiBound) = 0;

    virtual bool initializeObjective() = 0;
    virtual bool addLinearTermToObjective(double coefficient, int variableIndex) = 0;
    virtual bool addQuadraticTermToObjective(double coefficient, int firstVariableIndex, int secondVariableIndex) = 0;
    virtual bool finalizeObjective(bool isMinimize, double constant = 0.0) = 0;

    virtual bool initializeConstraint() = 0;
    virtual bool addLinearTermToConstraint(double coefficient, int variableIndex) = 0;
    virtual bool addQuadraticTermToConstraint(double coefficient, int firstVariableIndex, int secondVariableIndex) = 0;
    virtual bool finalizeConstraint(std::string name, double valueLHS, double valueRHS, double constant = 0.0) = 0;

    virtual bool finalizeProblem() = 0;

    virtual void initializeSolverSettings() = 0;

    virtual VectorDouble getVariableSolution(int solIdx) = 0;
    virtual int getNumberOfSolutions() = 0;

    virtual E_DualProblemClass getProblemClass() = 0;

    virtual void activateDiscreteVariables(bool activate) = 0;
    virtual bool getDiscreteVariableStatus() = 0;

    virtual void executeRelaxationStrategy() = 0;

    virtual E_ProblemSolutionStatus solveProblem() = 0;
    virtual bool repairInfeasibility() = 0;

    virtual E_ProblemSolutionStatus getSolutionStatus() = 0;
    virtual double getObjectiveValue() = 0;

    virtual double getDualObjectiveValue() = 0;

    virtual double getObjectiveValue(int solIdx) = 0;

    virtual int increaseSolutionLimit(int increment) = 0;
    virtual void setSolutionLimit(long limit) = 0;
    virtual int getSolutionLimit() = 0;

    virtual void writeProblemToFile(std::string filename) = 0;
    virtual void writePresolvedToFile(std::string filename) = 0;

    virtual std::vector<SolutionPoint> getAllVariableSolutions() = 0;
    virtual int addLinearConstraint(std::map<int, double>& elements, double constant, std::string name) = 0;
    virtual int addLinearConstraint(
        const std::map<int, double>& elements, double constant, std::string name, bool isGreaterThan)
        = 0;
    virtual int addLinearConstraint(
        const std::map<int, double>& elements, double constant, std::string name, bool isGreaterThan, bool allowRepair)
        = 0;

    virtual bool addSpecialOrderedSet(E_SOSType type, VectorInteger variableIndexes, VectorDouble variableWeights = {})
        = 0;

    virtual void setTimeLimit(double seconds) = 0;

    virtual void setCutOff(double cutOff) = 0;
    virtual void setCutOffAsConstraint(double cutOff) = 0;

    virtual void addMIPStart(VectorDouble point) = 0;
    virtual void deleteMIPStarts() = 0;

    virtual void fixVariable(int varIndex, double value) = 0;
    virtual void fixVariables(VectorInteger variableIndexes, VectorDouble variableValues) = 0;
    virtual void unfixVariables() = 0;

    virtual void updateVariableBound(int varIndex, double lowerBound, double upperBound) = 0;
    virtual void updateVariableLowerBound(int varIndex, double lowerBound) = 0;
    virtual void updateVariableUpperBound(int varIndex, double upperBound) = 0;

    virtual PairDouble getCurrentVariableBounds(int varIndex) = 0;

    virtual void presolveAndUpdateBounds() = 0;
    virtual std::pair<VectorDouble, VectorDouble> presolveAndGetNewBounds() = 0;

    virtual bool createHyperplane(Hyperplane hyperplane) = 0;
    virtual bool createInteriorHyperplane(Hyperplane hyperplane) = 0;
    virtual bool createIntegerCut(IntegerCut& integerCut) = 0;

    virtual std::optional<std::pair<std::map<int, double>, double>> createHyperplaneTerms(Hyperplane hyperplane) = 0;

    virtual bool supportsQuadraticObjective() = 0;
    virtual bool supportsQuadraticConstraints() = 0;

    virtual double getUnboundedVariableBoundValue() = 0;

    virtual int getNumberOfExploredNodes() = 0;
    virtual int getNumberOfOpenNodes() = 0;

    virtual int getNumberOfVariables() = 0;

    virtual bool hasDualAuxiliaryObjectiveVariable() = 0;
    virtual int getDualAuxiliaryObjectiveVariableIndex() = 0;
    virtual void setDualAuxiliaryObjectiveVariableIndex(int index) = 0;

    virtual std::string getConstraintIdentifier(E_HyperplaneSource source) = 0;

    virtual std::string getSolverVersion() = 0;

protected:
};
} // namespace SHOT