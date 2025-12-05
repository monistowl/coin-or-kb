/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Solver.h
 * @brief Main solver interface for convex MINLP problems
 *
 * Primary entry point for the SHOT optimizer.
 *
 * @algorithm SHOT (Supporting Hyperplane Optimization Toolkit):
 * Global optimization for convex MINLP via outer approximation.
 *
 * PROBLEM CLASS:
 *   min  f(x,y)
 *   s.t. g_i(x,y) <= 0     (convex constraints)
 *        x in X            (linear constraints)
 *        y in {0,1}^p      (binary variables)
 *
 * OUTER APPROXIMATION PRINCIPLE:
 *   Replace convex constraints g(x) <= 0 with linear approximations:
 *     g(x_k) + nabla g(x_k)'(x - x_k) <= 0
 *
 *   The linearization is a supporting hyperplane at x_k.
 *   For convex g: g(x) >= g(x_k) + nabla g(x_k)'(x - x_k)
 *   So the linear approx is a valid relaxation.
 *
 * DUAL BOUND (lower bound):
 *   Solve MIP with accumulated linear cuts.
 *   Solution may violate nonlinear constraints.
 *
 * PRIMAL BOUND (upper bound):
 *   Fix integers from MIP solution, solve NLP.
 *   If feasible: valid upper bound on optimal value.
 *
 * CONVERGENCE:
 *   For convex MINLP: dual bound -> optimal as cuts accumulate.
 *   Gap = (primal - dual) / |primal| -> 0
 *
 * @algorithm Solution Strategies:
 * MULTI-TREE (traditional):
 *   - Solve MIP to optimality
 *   - Add cuts at solution
 *   - Re-solve MIP
 *   - Iterate until gap closed
 *
 * SINGLE-TREE (lazy constraints):
 *   - One MIP solve with callback
 *   - At integer nodes: add lazy cuts
 *   - More efficient for large problems
 *
 * ECP (Extended Cutting Plane):
 *   - Add cuts at LP solutions too
 *   - Faster convergence but more cuts
 *
 * ESH (Extended Supporting Hyperplane):
 *   - Add cuts at interior points
 *   - Better approximation quality
 *
 * @complexity
 * - Each iteration: O(MIP) + O(NLP) for primal heuristic
 * - Convergence: finite for convex MINLP, exponential worst case
 * - Practice: often fast due to warm starts and cut reuse
 *
 * @ref Kronqvist, Lundell & Westerlund (2016). "The Extended Supporting
 *   Hyperplane Algorithm for Convex Mixed-Integer Nonlinear Programming".
 *   J. Global Optimization 64(2):249-272.
 *
 * **Solver Class:**
 * - setProblem(): Load GAMS/AMPL/OSiL problem file
 * - solveProblem(): Execute the selected solution strategy
 * - getPrimalSolution(): Retrieve best incumbent solution
 *
 * **Solution Workflow:**
 * 1. Initialize settings (setOptionsFromFile/String)
 * 2. Load problem (setProblem)
 * 3. Solve (solveProblem)
 * 4. Retrieve results (getResultsOSrL, getPrimalSolution)
 *
 * **Callbacks:**
 * - registerCallback(): Monitor NewPrimalSolution, UserTerminationCheck
 *
 * **Results Access:**
 * - getCurrentDualBound(): Best lower bound
 * - getPrimalBound(): Best upper bound (incumbent)
 * - getAbsoluteObjectiveGap(): |primal - dual|
 * - getRelativeObjectiveGap(): |primal - dual| / |primal|
 *
 * @see Environment.h for shared state container
 * @see SolutionStrategy/ISolutionStrategy.h for algorithm implementations
 */
#pragma once

#include <memory>
#include <string>

#include "Environment.h"
#include "Enums.h"
#include "EventHandler.h"
#include "Structs.h"

#include "ModelingSystem/IModelingSystem.h"
#include "SolutionStrategy/ISolutionStrategy.h"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace SHOT
{
class DllExport Solver
{
private:
    std::unique_ptr<ISolutionStrategy> solutionStrategy;

    void initializeSettings();
    void verifySettings();

    void setConvexityBasedSettingsPreReformulation();
    void setConvexityBasedSettings();

    void initializeDebugMode();

    bool selectStrategy();

    bool isProblemInitialized = false;
    bool isProblemSolved = false;

    EnvironmentPtr env;

public:
    Solver();
    Solver(std::shared_ptr<spdlog::sinks::sink> consoleSink);
    Solver(EnvironmentPtr environment);
    ~Solver();

    EnvironmentPtr getEnvironment();

    bool setOptionsFromFile(std::string fileName);
    bool setOptionsFromString(std::string options);
    bool setOptionsFromOSoL(std::string options);

    bool setLogFile(std::string filename);

    bool setProblem(std::string fileName);
    bool setProblem(ProblemPtr problem, ProblemPtr reformulatedProblem, ModelingSystemPtr modelingSystem = nullptr);
    bool setProblem(ProblemPtr problem, ModelingSystemPtr modelingSystem = nullptr)
    {
        return setProblem(problem, nullptr, modelingSystem);
    };

    ProblemPtr getOriginalProblem() { return (env->problem); };
    ProblemPtr getReformulatedProblem() { return (env->reformulatedProblem); };

    bool solveProblem();

    void finalizeSolution();

    template <typename Callback> inline void registerCallback(const E_EventType& event, Callback&& callback)
    {
        env->events->registerCallback(event, callback);
    }

    std::string getOptionsOSoL();
    std::string getOptions();

    std::string getResultsOSrL();
    std::string getResultsTrace();
    std::string getResultsSol();

    void updateSetting(std::string name, std::string category, int value);
    void updateSetting(std::string name, std::string category, std::string value);
    void updateSetting(std::string name, std::string category, double value);
    void updateSetting(std::string name, std::string category, bool value);

    VectorString getSettingIdentifiers(E_SettingType type);

    double getCurrentDualBound();
    double getPrimalBound();
    double getAbsoluteObjectiveGap();
    double getRelativeObjectiveGap();

    bool hasPrimalSolution();
    PrimalSolution getPrimalSolution();
    std::vector<PrimalSolution> getPrimalSolutions();

    E_TerminationReason getTerminationReason();
    E_ModelReturnStatus getModelReturnStatus();
};
} // namespace SHOT