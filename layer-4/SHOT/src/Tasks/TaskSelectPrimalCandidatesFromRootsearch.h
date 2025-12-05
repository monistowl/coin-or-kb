/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSelectPrimalCandidatesFromRootsearch.h
 * @brief Extract primal candidates from ESH rootsearch
 *
 * Byproduct of boundary finding: feasible points near boundary.
 *
 * **TaskSelectPrimalCandidatesFromRootsearch Class:**
 * - run(): Check rootsearch intermediate points
 * - run(solPoints): Process specific solution points
 *
 * **Rootsearch Byproduct:**
 * - ESH rootsearch traverses from infeasible to interior
 * - Intermediate points may be feasible primal candidates
 * - Cheap way to discover feasible solutions
 *
 * @algorithm Primal Extraction from ESH Rootsearch
 * @math During rootsearch from interior x° to infeasible x̂:
 *       Check intermediate points x(λ) = λx° + (1-λ)x̂.
 *       Points with g(x(λ)) ≤ 0 and integer feasibility → primal candidates.
 * @complexity O(rootsearch iterations). No additional NLP solves required.
 * @see RootsearchMethod/ for boundary finding
 * @see TaskSelectHyperplanePointsESH.h for ESH main task
 */
#pragma once
#include "TaskBase.h"

#include "../Structs.h"

namespace SHOT
{
class TaskSelectPrimalCandidatesFromRootsearch : public TaskBase
{
public:
    TaskSelectPrimalCandidatesFromRootsearch(EnvironmentPtr envPtr);
    ~TaskSelectPrimalCandidatesFromRootsearch() override;
    void run() override;
    virtual void run(std::vector<SolutionPoint> solPoints);

    std::string getType() override;

private:
};
} // namespace SHOT