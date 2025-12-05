/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file DualSolver.h
 * @brief MIP-based dual bound computation via supporting hyperplanes
 *
 * Manages the linearization-based dual problem.
 *
 * @algorithm Supporting Hyperplane Generation:
 * Creates linear approximations of convex constraint set.
 *
 * LINEARIZATION AT POINT x_k:
 *   For constraint g(x) <= 0 (convex):
 *     Cut: g(x_k) + nabla g(x_k)'(x - x_k) <= 0
 *
 *   Rearranged: nabla g(x_k)' x <= nabla g(x_k)' x_k - g(x_k)
 *
 * CUT GENERATION POINTS:
 *   1. MIP solutions (infeasible for NLP)
 *   2. LP relaxation solutions
 *   3. Interior points (for ESH)
 *   4. Root relaxation solutions
 *
 * @algorithm Extended Supporting Hyperplane (ESH):
 * Adds cuts at interior points for tighter approximation.
 *
 * INTERIOR POINT PROJECTION:
 *   Given interior point x_int (g(x_int) < 0):
 *   - Draw line from x_int to infeasible point x_inf
 *   - Find boundary point x_bnd where g(x_bnd) = 0
 *   - Add hyperplane at x_bnd
 *
 *   This creates cuts that better approximate the boundary
 *   than cuts at infeasible points alone.
 *
 * @algorithm Integer Cuts (No-Good Cuts):
 * Exclude previously found integer solutions.
 *
 *   For integer solution y*:
 *     sum_{j: y*_j=1} (1-y_j) + sum_{j: y*_j=0} y_j >= 1
 *
 *   Forces at least one integer variable to change.
 *   Used when NLP subproblem is infeasible.
 *
 * @math Dual bound at iteration k:
 *   z_D^k = optimal value of MIP with k hyperplanes
 *   z_D^k <= z_D^(k+1) <= z* (monotone non-decreasing)
 *
 * **DualSolver Class:**
 * - MIPSolver: Backend MIP solver (CPLEX/Gurobi/CBC/HiGHS)
 * - generatedHyperplanes: All cutting planes added
 * - hyperplaneWaitingList: Pending cuts to add
 *
 * **Hyperplane Management:**
 * - addHyperplane(): Add supporting hyperplane cut
 * - addGeneratedHyperplane(): Record a hyperplane
 * - hasHyperplaneBeenAdded(): Avoid duplicate cuts
 *
 * **Integer Cuts:**
 * - addIntegerCut(): Add no-good cuts for MINLP
 * - generatedIntegerCuts: All integer cuts
 *
 * **Interior Points:**
 * - interiorPointCandidates: Candidate interior points
 * - interiorPts: Verified interior points for ESH
 *
 * @complexity
 * - Hyperplane addition: O(n) per cut (n = variables)
 * - Duplicate check: O(1) via hash
 * - MIP solve: depends on backend solver
 *
 * @see PrimalSolver.h for primal bound computation
 * @see MIPSolver/ for backend implementations
 */
#pragma once
#include "Environment.h"
#include "Structs.h"

namespace SHOT
{
class DualSolver
{
public:
    DualSolver(EnvironmentPtr envPtr);

    ~DualSolver() { dualSolutionCandidates.clear(); }

    MIPSolverPtr MIPSolver;
    std::vector<DualSolution> dualSolutionCandidates;

    void addDualSolutionCandidate(DualSolution solution);
    void checkDualSolutionCandidates();

    void addHyperplane(Hyperplane& hyperplane);
    void addGeneratedHyperplane(const Hyperplane& hyperplane);
    bool hasHyperplaneBeenAdded(double hash, int constraintIndex);

    void addIntegerCut(IntegerCut integerCut);
    void addGeneratedIntegerCut(IntegerCut integerCut);
    bool hasIntegerCutBeenAdded(double hash);

    std::vector<GeneratedHyperplane> generatedHyperplanes;
    std::vector<Hyperplane> hyperplaneWaitingList;

    std::vector<IntegerCut> generatedIntegerCuts;
    std::vector<IntegerCut> integerCutWaitingList;

    std::vector<std::shared_ptr<InteriorPoint>> interiorPointCandidates;
    std::vector<std::shared_ptr<InteriorPoint>> interiorPts;

    double cutOffToUse = SHOT_DBL_INF;
    bool useCutOff = false;
    bool isSingleTree = false;

private:
    EnvironmentPtr env;
};

} // namespace SHOT