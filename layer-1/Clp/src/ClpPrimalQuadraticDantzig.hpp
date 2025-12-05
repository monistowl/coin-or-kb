// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpPrimalQuadraticDantzig.hpp
 * @brief Dantzig-style pricing for quadratic programming
 *
 * Extends ClpPrimalColumnPivot for QP problems where the reduced cost
 * depends on the current solution (due to the quadratic objective).
 *
 * @algorithm Dantzig Pricing for Quadratic Programs:
 * Simple but robust variable selection for QP simplex.
 *
 * @math REDUCED COST FOR QP:
 * For LP: c̄_j = c_j - π'A_j (constant during iteration)
 * For QP: c̄_j = c_j + (Qx)_j - π'A_j (changes with x!)
 *
 * @algorithm Selection Rule:
 * Choose entering variable j* = argmax |c̄_j| among:
 *   - Variables at lower bound with c̄_j < 0 (can increase)
 *   - Variables at upper bound with c̄_j > 0 (can decrease)
 *
 * @complexity O(n) per pricing: examines all nonbasic variables.
 * No sophisticated structures like steepest edge or Devex.
 *
 * WHY REDUCED COST CHANGES IN QP:
 *   ∇f(x) = c + Qx
 *   When basic variables change → x changes → Qx changes → c̄ changes
 *   Must recompute all reduced costs each iteration (expensive!)
 *
 * quadraticInfo_ stores:
 *   - Current Qx product
 *   - Solution state for gradient updates
 *
 * Use when: Starting out with QP, need robust method.
 * Avoid when: Large problems (use steepest edge variants).
 *
 * @see ClpPrimalColumnPivot for the abstract pivot interface
 * @see ClpQuadraticObjective for the QP objective representation
 * @see ClpSimplexPrimalQuadratic for the QP simplex solver
 */

#ifndef ClpPrimalQuadraticDantzig_H
#define ClpPrimalQuadraticDantzig_H

#include "ClpPrimalColumnPivot.hpp"
class ClpSimplexPrimalQuadratic;
class ClpQuadraticInfo;
//#############################################################################

/** Primal Column Pivot Dantzig Algorithm Class

This is simplest choice - choose largest infeasibility

*/

class ClpPrimalQuadraticDantzig : public ClpPrimalColumnPivot {

public:
  ///@name Algorithmic methods
  //@{

  /** Returns pivot column, -1 if none.
         Lumbers over all columns - slow
         updateArray has cost updates (also use pivotRow_ from last iteration)
         Can just do full price if you really want to be slow
     */
  virtual int pivotColumn(CoinIndexedVector *updates,
    CoinIndexedVector *spareRow1,
    CoinIndexedVector *spareRow2,
    CoinIndexedVector *spareColumn1,
    CoinIndexedVector *spareColumn2);

  /// Just sets model
  virtual void saveWeights(ClpSimplex *model, int mode)
  {
    model_ = model;
  }
  //@}

  ///@name Constructors and destructors
  //@{
  /// Default Constructor
  ClpPrimalQuadraticDantzig();

  /// Copy constructor
  ClpPrimalQuadraticDantzig(const ClpPrimalQuadraticDantzig &);

  /// Constructor from model
  ClpPrimalQuadraticDantzig(ClpSimplexPrimalQuadratic *model,
    ClpQuadraticInfo *info);

  /// Assignment operator
  ClpPrimalQuadraticDantzig &operator=(const ClpPrimalQuadraticDantzig &rhs);

  /// Destructor
  virtual ~ClpPrimalQuadraticDantzig();

  /// Clone
  virtual ClpPrimalColumnPivot *clone(bool copyData = true) const;

  //@}

  //---------------------------------------------------------------------------

private:
  ///@name Private member data
  /// Pointer to info
  ClpQuadraticInfo *quadraticInfo_;
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
