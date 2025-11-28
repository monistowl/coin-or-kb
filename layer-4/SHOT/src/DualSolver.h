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
 * @algorithm Extended Supporting Hyperplane (ESH) method adds
 *            linearizations at boundary and interior points
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