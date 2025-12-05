// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.

/**
 * @file ClpPEDualRowDantzig.hpp
 * @brief Positive Edge enhanced Dantzig pricing for dual simplex
 * @author Jeremy Omer
 *
 * Combines classic dual Dantzig pricing (most infeasible row) with
 * Positive Edge compatibility checking. Prioritizes compatible rows
 * that can make real progress on degenerate problems.
 *
 * @algorithm Positive Edge Dual Row Selection:
 * Dual analog of PE primal pricing - prefers rows that make progress.
 *
 * @math DUAL DEGENERACY:
 * Occurs when nonbasic variables have c̄_j = 0 (multiple optimal bases).
 * Ratio test may give θ = 0 → basis change but no dual improvement.
 *
 * @algorithm Dual Compatibility:
 * Row i is compatible if leaving basic variable x_Bi would
 * allow some dual variable to improve:
 *   Compatible_i = ∃j : (c̄_j = 0) ∧ (can become nonzero after pivot)
 *
 * @algorithm Bi-Dimensional Dual Pricing:
 * Score(i) = |violation_i|^(1-ψ) × Compat(i)^ψ
 *
 * Where violation_i = max(l_i - x_Bi, x_Bi - u_i, 0) measures
 * how far basic variable i is from feasibility.
 *
 * ψ parameter (default 0.5):
 *   ψ = 0: Pure Dantzig (most infeasible)
 *   ψ = 1: Pure compatibility
 *   ψ = 0.5: Balanced
 *
 * @complexity O(m) per selection like standard Dantzig.
 * Compatibility updates amortized over multiple iterations.
 *
 * @ref Towhidi, Desrosiers, Soumis (2014): "The positive edge criterion"
 *
 * @see ClpPESimplex for the compatibility framework
 * @see ClpDualRowDantzig for the base pricing rule
 * @see ClpPEDualRowSteepest for steepest edge variant
 */

#ifndef ClpPEDualRowDantzig_H
#define ClpPEDualRowDantzig_H

#include "ClpDualRowPivot.hpp"
#include "ClpDualRowDantzig.hpp"
#include "ClpSimplex.hpp"
#include "CoinIndexedVector.hpp"
#include "ClpFactorization.hpp"
#include "ClpNonLinearCost.hpp"
#include "ClpSimplexDual.hpp"
#include "ClpPackedMatrix.hpp"
#include "ClpPESimplex.hpp"

class CLPLIB_EXPORT ClpPEDualRowDantzig : public ClpDualRowDantzig {

public:
  /// Default Constructor
  ClpPEDualRowDantzig(double psi = 0.5);

  /// Copy constructor
  ClpPEDualRowDantzig(const ClpPEDualRowDantzig &);

  /// Assignment operator
  ClpPEDualRowDantzig &operator=(const ClpPEDualRowDantzig &rhs);

  /// Destructor
  virtual ~ClpPEDualRowDantzig();

  /// Clone
  virtual ClpDualRowPivot *clone(bool copyData = true) const;

public:
  ///@name Algorithmic methods
  //@{

  /// Returns pivot row, -1 if none
  virtual int pivotRow();

  /// Update the compatible variables and
  /// call the base class method to update weights
  virtual double updateWeights(CoinIndexedVector *input,
    CoinIndexedVector *spare,
    CoinIndexedVector *spare2,
    CoinIndexedVector *updatedColumn);

  /** Save weights - this may initialize weights as well
	 This is as parent but may initialize ClpPESimplex
     */
  virtual void saveWeights(ClpSimplex *model, int mode);
  //@}

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
  bool updateCompatibles_;
  int coDegenCompatibles_, coConsecutiveCompatibles_;
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
