/**
 * @file ClpPEPrimalColumnDantzig.hpp
 * @brief Positive Edge enhanced Dantzig pricing for primal simplex
 * @author Jeremy Omer, Mehdi Towhidi
 *
 * Combines classic Dantzig pricing (most negative reduced cost) with
 * Positive Edge compatibility checking. Prioritizes compatible columns
 * that can make real progress on degenerate problems.
 *
 * @algorithm Positive Edge Primal Pricing:
 * Addresses degeneracy by preferring "compatible" entering variables.
 *
 * @math DEGENERACY PROBLEM:
 * When basic variables are at bounds, ratio test gives θ = 0.
 * Pivot changes basis but x, z unchanged → no progress.
 * Degenerate pivots can cycle or stall for many iterations.
 *
 * @algorithm Compatibility Definition:
 * Column j is compatible if entering it would DECREASE some infeasibility:
 *   Compatible_j = ∃i : (x_Bi at bound) ∧ (α_ij ≠ 0) ∧ (sign gives progress)
 *
 * Intuition: Compatible columns can "unlock" degenerate basic variables.
 *
 * @algorithm Bi-Dimensional Pricing:
 * Score(j) = |c̄_j|^(1-ψ) × Compat(j)^ψ
 *
 * Where ψ ∈ [0,1] controls priority (default 0.5):
 *   ψ = 0: Pure Dantzig (ignore compatibility)
 *   ψ = 1: Pure compatibility (ignore reduced cost)
 *   ψ = 0.5: Balanced - good default
 *
 * @complexity O(n) per pricing like Dantzig, but with compatibility
 * check overhead. Compatibility set updated periodically, not every iter.
 *
 * @ref Towhidi, Desrosiers, Soumis (2014): "The positive edge criterion
 *      within COIN-OR's CLP"
 *
 * @see ClpPESimplex for the compatibility framework
 * @see ClpPrimalColumnDantzig for the base pricing rule
 * @see ClpPEPrimalColumnSteepest for steepest edge variant
 */

#ifndef ClpPEPrimalColumnDantzig_H
#define ClpPEPrimalColumnDantzig_H

#include "ClpPrimalColumnDantzig.hpp"
#include "ClpPrimalColumnPivot.hpp"
#include "ClpSimplex.hpp"
#include "CoinIndexedVector.hpp"
#include "ClpFactorization.hpp"
#include "ClpNonLinearCost.hpp"
#include "ClpSimplexPrimal.hpp"
#include "ClpPackedMatrix.hpp"
#include "ClpPESimplex.hpp"

class CLPLIB_EXPORT ClpPEPrimalColumnDantzig : public ClpPrimalColumnDantzig {

public:
  /** constructors */
  ClpPEPrimalColumnDantzig(double psi = 0.5);
  ClpPEPrimalColumnDantzig(const ClpPEPrimalColumnDantzig &); //copy constructor

  /** destructor */
  ~ClpPEPrimalColumnDantzig();

  /** assignment operator */
  ClpPEPrimalColumnDantzig &operator=(const ClpPEPrimalColumnDantzig &rhs);

  /** clone */
  ClpPrimalColumnPivot *clone(bool copyData = true) const;

  virtual int pivotColumn(CoinIndexedVector *updates,
    CoinIndexedVector *spareRow1,
    CoinIndexedVector *spareRow2,
    CoinIndexedVector *spareColumn1,
    CoinIndexedVector *spareColumn2);

  //@}
  /** Save weights - this may initialize weights as well
	 This is as parent but may initialize ClpPESimplex
     */
  virtual void saveWeights(ClpSimplex *model, int mode);
  //---------------------------------------------------------------------------
private:
  /* this PESimplex object is used to identify the compatible variables */
  ClpPESimplex *modelPE_;

  /* psi is the factor used in the bi-dimensional pricing, it is < 1 and
       1/psi grows with the priority given to compatible variables */
  double psi_;

  /* useful counters for the update of the set of compatible variables */
  int iCurrent_;
  int iInterval_;

  /* record if previous iterations concluded that compatibles should not be checked */
  int coDegenCompatibles_;
  int coConsecutiveCompatibles_;
  bool updateCompatibles_;
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
