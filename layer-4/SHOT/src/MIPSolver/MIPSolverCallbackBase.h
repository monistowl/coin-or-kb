/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file MIPSolver/MIPSolverCallbackBase.h
 * @brief Shared logic for single-tree callback handlers
 *
 * Base class for CPLEX and Gurobi callback implementations.
 *
 * **MIPSolverCallbackBase Class:**
 * - addLazyConstraint(): Generate and add ESH cuts
 * - checkFixedNLPStrategy(): Decide if NLP should be called
 * - checkIterationLimit()/checkUserTermination(): Termination checks
 * - printIterationReport(): Console output in callback
 *
 * **Task Objects:**
 * - taskSelectPrimNLPOriginal/Reformulated: Fixed-integer NLP
 * - taskSelectHPPts: ESH/ECP hyperplane selection
 * - taskSelectPrimalSolutionFromRootsearch: Rootsearch primal
 * - tUpdateInteriorPoint: Interior point maintenance
 *
 * @see MIPSolverCplexSingleTree.h, MIPSolverGurobiSingleTree.h
 */
#pragma once

#include "../Environment.h"

#include "../Tasks/TaskSelectHyperplanePointsObjectiveFunction.h"
#include "../Tasks/TaskSelectPrimalCandidatesFromRootsearch.h"
#include "../Tasks/TaskSelectPrimalCandidatesFromNLP.h"
#include "../Tasks/TaskSelectHyperplanePointsESH.h"
#include "../Tasks/TaskSelectHyperplanePointsECP.h"
#include "../Tasks/TaskUpdateInteriorPoint.h"

#include <memory>
#include <string>
#include <vector>

namespace SHOT
{
class MIPSolverCallbackBase
{
public:
    virtual ~MIPSolverCallbackBase() = default;

private:
protected:
    bool isMinimization = true;
    int lastNumAddedHyperplanes = 0;
    double lastUpdatedPrimal;

    int lastSummaryIter = 0;
    double lastSummaryTimeStamp = 0.0;
    int lastHeaderIter = 0;

    bool warningMessageShownLargeRHS = false;

    std::shared_ptr<TaskSelectPrimalCandidatesFromNLP> taskSelectPrimNLPOriginal;
    std::shared_ptr<TaskSelectPrimalCandidatesFromNLP> taskSelectPrimNLPReformulated;
    std::shared_ptr<TaskBase> taskSelectHPPts;
    std::shared_ptr<TaskSelectHyperplanePointsObjectiveFunction> taskSelectHPPtsByObjectiveRootsearch;
    std::shared_ptr<TaskSelectPrimalCandidatesFromRootsearch> taskSelectPrimalSolutionFromRootsearch;
    std::shared_ptr<TaskUpdateInteriorPoint> tUpdateInteriorPoint;

    bool checkFixedNLPStrategy(SolutionPoint point);

    bool checkIterationLimit();

    bool checkUserTermination();

    void addLazyConstraint(std::vector<SolutionPoint> candidatePoints);

    void printIterationReport(SolutionPoint solution, std::string threadId);

    EnvironmentPtr env;
};
} // namespace SHOT