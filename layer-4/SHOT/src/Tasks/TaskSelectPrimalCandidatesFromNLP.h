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
 * @algorithm Fixed-Integer NLP Primal Heuristic
 * @math Given MIP solution x̄ with integer values x̄_I:
 *       1. Fix: x_I = x̄_I (set bounds l_i = u_i = x̄_i)
 *       2. Solve NLP: min f(x) s.t. g(x) ≤ 0, x_I fixed
 *       3. If feasible: candidate x* may improve primal bound
 *       4. If infeasible: add integer cut Σ(1-y_i) + Σy_j ≥ 1
 *          to exclude this integer assignment
 *       Key primal bound improvement in BONMIN-style algorithms.
 * @complexity O(NLP solve time). Ipopt typically O(iterations × n³).
 * @ref Bonami et al. (2008). "An algorithmic framework for convex MINLP"
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