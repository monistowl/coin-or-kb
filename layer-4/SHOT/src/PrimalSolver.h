/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file PrimalSolver.h
 * @brief NLP-based primal bound computation and solution repair
 *
 * Finds feasible solutions and improves the primal bound.
 *
 * **PrimalSolver Class:**
 * - primalSolutionCandidates: Points to check for feasibility
 * - fixedPrimalNLPCandidates: Integer-fixed NLP subproblems
 *
 * **Primal Solution Sources:**
 * - MIP solution pool points
 * - NLP local search from MIP solutions
 * - Rounding heuristics
 *
 * **Solution Validation:**
 * - addPrimalSolutionCandidate(): Submit candidate point
 * - checkPrimalSolutionCandidates(): Verify feasibility
 * - checkPrimalSolutionPoint(): Full constraint check
 *
 * **Fixed-Integer NLP:**
 * - addFixedNLPCandidate(): Queue NLP subproblem
 * - hasFixedNLPCandidateBeenTested(): Avoid re-solving
 *
 * @see DualSolver.h for dual bound computation
 * @see NLPSolver/ for backend NLP solvers (Ipopt)
 */
#pragma once
#include "Environment.h"
#include "Enums.h"
#include "Structs.h"

namespace SHOT
{

class PrimalSolver
{
public:
    PrimalSolver(EnvironmentPtr envPtr) { env = envPtr; }

    ~PrimalSolver()
    {
        primalSolutionCandidates.clear();
        fixedPrimalNLPCandidates.clear();
    }

    void addPrimalSolutionCandidate(VectorDouble pt, E_PrimalSolutionSource source, int iter);
    void addPrimalSolutionCandidates(std::vector<VectorDouble> pts, E_PrimalSolutionSource source, int iter);

    void addPrimalSolutionCandidate(SolutionPoint pt, E_PrimalSolutionSource source);
    void addPrimalSolutionCandidates(std::vector<SolutionPoint> pts, E_PrimalSolutionSource source);

    void checkPrimalSolutionCandidates();

    bool checkPrimalSolutionPoint(PrimalSolution primalSol);

    void addFixedNLPCandidate(
        VectorDouble pt, E_PrimalNLPSource source, double objVal, int iter, PairIndexValue maxConstrDev);

    bool hasFixedNLPCandidateBeenTested(double hash);

    std::vector<PrimalSolution> primalSolutionCandidates;
    std::vector<PrimalFixedNLPCandidate> fixedPrimalNLPCandidates;
    std::vector<PrimalFixedNLPCandidate> usedPrimalNLPCandidates;

private:
    EnvironmentPtr env;
};

} // namespace SHOT