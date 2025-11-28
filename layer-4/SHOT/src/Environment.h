/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Environment.h
 * @brief Shared state container for SHOT solver components
 *
 * Central hub connecting all solver subsystems.
 *
 * **Environment Class Members:**
 * - problem: Original problem formulation
 * - reformulatedProblem: Convexified/linearized version
 * - modelingSystem: GAMS/AMPL/OSiL interface
 *
 * **Solver Components:**
 * - dualSolver: MIP solver for dual problem (CPLEX/Gurobi/CBC)
 * - primalSolver: NLP solver for primal bounds (Ipopt)
 * - rootsearchMethod: Line search for hyperplanes
 *
 * **Infrastructure:**
 * - settings: Solver configuration parameters
 * - results: Solution and statistics
 * - output: Logging via spdlog
 * - timing: Performance profiling
 * - events: Callback event handler
 * - tasks: Asynchronous task manager
 *
 * @see Solver.h for the main solver interface
 */
#pragma once

#include <memory>

#include "Structs.h"

namespace SHOT
{

class IRootsearchMethod;

class DllExport Environment
{
public:
    inline Environment() = default;
    inline ~Environment() = default;

    ResultsPtr results;
    SettingsPtr settings;
    ProblemPtr problem;
    ProblemPtr reformulatedProblem;
    ModelingSystemPtr modelingSystem;
    DualSolverPtr dualSolver;
    PrimalSolverPtr primalSolver;
    OutputPtr output;
    ReportPtr report;
    TaskHandlerPtr tasks;
    TimingPtr timing;
    EventHandlerPtr events;

    std::shared_ptr<IRootsearchMethod> rootsearchMethod;

    SolutionStatistics solutionStatistics;

private:
};

using EnvironmentPtr = std::shared_ptr<Environment>;
} // namespace SHOT
