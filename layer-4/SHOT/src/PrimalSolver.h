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
 * @algorithm Fixed-Integer NLP Subproblem:
 * Given integer solution y* from MIP, find best continuous x.
 *
 * FIXED NLP:
 *   min  f(x, y*)           (objective with fixed integers)
 *   s.t. g_i(x, y*) <= 0    (constraints with fixed integers)
 *        x in X             (linear constraints)
 *
 * The NLP subproblem is convex (if original constraints convex).
 * Solved by Ipopt or other NLP solver.
 *
 * OUTCOMES:
 *   1. Feasible: Update primal bound if f(x*, y*) < incumbent
 *   2. Infeasible: Add integer cut to exclude y*
 *   3. Unbounded: Problem formulation issue
 *
 * @algorithm Primal Heuristics:
 * Multiple strategies to find feasible solutions faster.
 *
 * SOLUTION SOURCES:
 *   1. MIP solution pool: Try multiple near-optimal MIP solutions
 *   2. Rounding: Round LP relaxation to nearest feasible integers
 *   3. Feasibility pump: Alternate rounding and projection
 *   4. Local search: Improve existing solution by neighborhood moves
 *
 * PRIORITY QUEUE:
 *   Solutions ranked by:
 *     - Source reliability (NLP > rounding > pool)
 *     - Constraint violation (less is better)
 *     - Objective value (lower is better for minimization)
 *
 * @algorithm Solution Validation:
 * Verify candidate satisfies all constraints to tolerance.
 *
 *   For each constraint g_i(x) <= 0:
 *     violation_i = max(0, g_i(x))
 *
 *   max_violation = max_i(violation_i)
 *
 *   Point is feasible if max_violation <= tolerance
 *
 * @math Primal bound update:
 *   If x is feasible and f(x) < z_P: z_P = f(x)
 *   Gap = (z_P - z_D) / |z_P|
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
 * @complexity
 * - Solution validation: O(m * nnz_constraint) per candidate
 * - Fixed NLP: depends on Ipopt (typically polynomial for convex)
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