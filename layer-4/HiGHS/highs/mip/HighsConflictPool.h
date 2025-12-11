/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file mip/HighsConflictPool.h
 * @brief Storage for learned conflict constraints
 *
 * Manages nogood constraints derived from infeasible subproblems.
 *
 * **Conflict Storage:**
 * - conflictEntries_[]: Domain changes forming each conflict
 * - conflictRanges_[]: {start, end} pairs indexing entries
 * - Each conflict: set of HighsDomainChange that together are infeasible
 *
 * **Aging System:**
 * - ages_[]: Tracks how long since conflict was active
 * - ageDistribution_[]: Count of conflicts at each age
 * - performAging(): Increment ages, remove old conflicts
 * - resetAge(): Reset age when conflict becomes active
 * - agelim_: Maximum age before deletion
 *
 * **Memory Management:**
 * - freeSpaces_: Ordered set of reusable entry ranges
 * - deletedConflicts_: Reusable conflict indices
 * - softlimit_: Target maximum conflicts
 *
 * **Key Methods:**
 * - addConflictCut(): Store conflict from infeasibility analysis
 * - addReconvergenceCut(): Store conflict with reconvergence point
 * - removeConflict(): Delete conflict and free space
 *
 * **Propagation Integration:**
 * - propagationDomains[]: Domains using conflicts for propagation
 * - modification_[]: Version counter for conflict updates
 *
 * @algorithm Conflict-Driven Clause Learning (CDCL):
 *   When LP infeasibility detected, derive nogood from branching decisions:
 *   @math If decisions D₁ ∧ D₂ ∧ ... ∧ Dₖ lead to infeasibility,
 *         then ¬D₁ ∨ ¬D₂ ∨ ... ∨ ¬Dₖ is a valid constraint.
 *   Stored as set of HighsDomainChange that cannot all be active.
 *   @ref Achterberg, T. (2007). "Conflict analysis in mixed integer
 *        programming". Discrete Optimization 4(1):4-20.
 *
 * @algorithm Reconvergence Cuts:
 *   Strengthen conflicts using reconvergence analysis:
 *   @math If conflict C holds at node N, and bound change b
 *         is implied on all paths from root to N,
 *         then C ∪ {b} is also valid.
 *   Enables learning more general conflicts from specific failures.
 *   @see mip/HighsDomain.h for ConflictSet::computeReconvergenceFrontier()
 *
 * @algorithm Conflict Propagation:
 *   Use conflicts for bound tightening at B&B nodes:
 *   @math If conflict is {x₁ ≥ a₁, x₂ ≤ b₂, ...} and all but one
 *         condition holds, the remaining condition must be false.
 *   propagationDomains[] tracks which domains use conflicts.
 *   @complexity O(conflict_size) per propagation check
 *
 * @algorithm Conflict Aging:
 *   Same aging scheme as cut pool:
 *   @math age_i += 1 when conflict not used, reset to 0 when active
 *   Removes old conflicts to bound memory: O(softlimit_) conflicts.
 *
 * @see mip/HighsDomain.h for conflict derivation
 * @see mip/HighsSearch.h for conflict generation during search
 */
#ifndef HIGHS_CONFLICTPOOL_H_
#define HIGHS_CONFLICTPOOL_H_

#include <set>
#include <vector>

#include "mip/HighsDomain.h"
#include "util/HighsInt.h"

class HighsConflictPool {
 private:
  HighsInt agelim_;
  HighsInt softlimit_;
  std::vector<HighsInt> ageDistribution_;
  std::vector<int16_t> ages_;
  std::vector<unsigned> modification_;

  std::vector<HighsDomainChange> conflictEntries_;
  std::vector<std::pair<HighsInt, HighsInt>> conflictRanges_;

  /// keep an ordered set of free spaces in the row arrays so that they can be
  /// reused efficiently
  std::set<std::pair<HighsInt, HighsInt>> freeSpaces_;

  /// vector of deleted conflicts so that their indices can be reused
  std::vector<HighsInt> deletedConflicts_;

  std::vector<HighsDomain::ConflictPoolPropagation*> propagationDomains;

 public:
  HighsConflictPool(HighsInt agelim, HighsInt softlimit)
      : agelim_(agelim),
        softlimit_(softlimit),
        ageDistribution_(),
        ages_(),
        modification_(),
        conflictEntries_(),
        conflictRanges_(),
        freeSpaces_(),
        deletedConflicts_(),
        propagationDomains() {
    ageDistribution_.resize(agelim_ + 1);
  }

  void addConflictCut(const HighsDomain& domain,
                      const std::set<HighsDomain::ConflictSet::LocalDomChg>&
                          reasonSideFrontier);

  void addReconvergenceCut(
      const HighsDomain& domain,
      const std::set<HighsDomain::ConflictSet::LocalDomChg>&
          reconvergenceFrontier,
      const HighsDomainChange& reconvergenceDomchg);

  void removeConflict(HighsInt conflict);

  void performAging();

  void resetAge(HighsInt conflict) {
    if (ages_[conflict] > 0) {
      ageDistribution_[ages_[conflict]] -= 1;
      ageDistribution_[0] += 1;
      ages_[conflict] = 0;
    }
  }

  void setAgeLimit(HighsInt agelim) {
    agelim_ = agelim;
    ageDistribution_.resize(agelim_ + 1);
  }

  unsigned getModificationCount(HighsInt cut) const {
    return modification_[cut];
  }

  void addPropagationDomain(HighsDomain::ConflictPoolPropagation* domain) {
    propagationDomains.push_back(domain);
  }

  void removePropagationDomain(HighsDomain::ConflictPoolPropagation* domain) {
    for (HighsInt k = propagationDomains.size() - 1; k >= 0; --k) {
      if (propagationDomains[k] == domain) {
        propagationDomains.erase(propagationDomains.begin() + k);
        return;
      }
    }
  }

  const std::vector<HighsDomainChange>& getConflictEntryVector() const {
    return conflictEntries_;
  }

  const std::vector<std::pair<HighsInt, HighsInt>>& getConflictRanges() const {
    return conflictRanges_;
  }

  HighsInt getNumConflicts() const {
    return conflictRanges_.size() - deletedConflicts_.size();
  }
};

#endif
