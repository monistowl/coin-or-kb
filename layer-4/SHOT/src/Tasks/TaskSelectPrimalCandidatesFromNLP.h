/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSelectPrimalCandidatesFromNLP.h
 * @brief Solve fixed-integer NLP for primal candidates
 *
 * Uses NLP solver (Ipopt) with fixed integer variables.
 *
 * **TaskSelectPrimalCandidatesFromNLP Class:**
 * - solveFixedNLP(): Fix integers, solve continuous NLP
 * - createInfeasibilityCut(): Handle infeasible NLP
 * - createIntegerCut(): Exclude tested integer assignment
 *
 * **Fixed-Integer NLP:**
 * - Take MIP solution's integer values
 * - Solve continuous relaxation with fixed integers
 * - Provides locally optimal primal candidates
 *
 * **Usage:**
 * - Triggered by primal stagnation
 * - May improve primal bound significantly
 *
 * @see NLPSolver/ for Ipopt interface
 * @see TaskCheckPrimalStagnation.h for trigger
 */
#pragma once
#include "TaskBase.h"

#include <memory>
#include <string>
#include <vector>

#include "../Structs.h"

namespace SHOT
{
class INLPSolver;

class TaskSelectPrimalCandidatesFromNLP : public TaskBase
{
public:
    TaskSelectPrimalCandidatesFromNLP(EnvironmentPtr envPtr, bool useReformulatedProblem);
    ~TaskSelectPrimalCandidatesFromNLP() override;
    void run() override;
    std::string getType() override;

private:
    virtual bool solveFixedNLP();

    void createInfeasibilityCut(const VectorDouble point);
    void createIntegerCut(VectorDouble point);

    std::shared_ptr<INLPSolver> NLPSolver;

    VectorInteger discreteVariableIndexes;
    std::vector<VectorDouble> testedPoints;
    VectorDouble fixPoint;

    double originalNLPTime;
    double originalNLPIter;

    VectorDouble originalLBs;
    VectorDouble originalUBs;

    VectorString variableNames;

    std::shared_ptr<TaskBase> taskSelectHPPts;

    int originalIterFrequency;
    double originalTimeFrequency;

    ProblemPtr sourceProblem;
    bool sourceIsReformulatedProblem = false;
};
} // namespace SHOT