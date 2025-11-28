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
 * Dantzig's rule: Choose the variable with largest reduced cost violation.
 * For QP, the reduced cost c̄_j = c_j + (Qx)_j - π'A_j changes as x changes.
 *
 * This is the simplest QP pricing rule - it examines all non-basic variables
 * to find the most attractive one. Slow but robust.
 *
 * quadraticInfo_: Holds current quadratic gradient Qx and related state.
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
