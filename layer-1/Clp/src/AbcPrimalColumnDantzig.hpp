// Copyright (C) 2002, International Business Machines
// Corporation and others, Copyright (C) 2012, FasterCoin.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file AbcPrimalColumnDantzig.hpp
 * @brief Dantzig's rule for ABC primal simplex pivot selection
 * @author John Forrest (FasterCoin, 2012)
 *
 * Implements the simplest pivot selection: choose the nonbasic variable
 * with most negative reduced cost. This is Dantzig's original 1947 rule
 * adapted for the ABC optimized simplex framework.
 *
 * @algorithm Dantzig's Original Pivot Rule (1947):
 * Select entering variable j* = argmin_{j} { c̄_j : c̄_j < 0 }
 *
 * @math REDUCED COST:
 * c̄_j = c_j - π'A_j  where π = c_B'·B⁻¹ are dual variables
 *
 * c̄_j < 0 means increasing x_j will decrease objective.
 * Choose most negative = steepest descent in reduced cost space.
 *
 * @algorithm FULL PRICING:
 * Must examine all n-m nonbasic variables to find minimum.
 * "Lumbers over all columns" - no sophisticated screening.
 *
 * @complexity O(n) per pricing iteration.
 * Simple but can be slow on large problems.
 *
 * WHEN TO USE:
 * - Debugging: Simplest rule, easiest to verify
 * - Small problems: Overhead of steepest edge not worth it
 * - Dense problems: Steepest edge weight updates expensive
 *
 * WHEN TO AVOID:
 * - Large sparse problems: Use partial pricing or steepest edge
 * - Degenerate problems: Dantzig can cycle; steepest edge more stable
 *
 * ABC optimization: Uses CoinPartitionedVector for cache-friendly
 * scanning of reduced costs.
 *
 * @see AbcPrimalColumnPivot for the base interface
 * @see AbcPrimalColumnSteepest for recommended steepest edge variant
 * @see ClpPrimalColumnDantzig for the standard (non-ABC) implementation
 */

#ifndef AbcPrimalColumnDantzig_H
#define AbcPrimalColumnDantzig_H

#include "AbcPrimalColumnPivot.hpp"

//#############################################################################

/** Primal Column Pivot Dantzig Algorithm Class

This is simplest choice - choose largest infeasibility

*/

class AbcPrimalColumnDantzig : public AbcPrimalColumnPivot {

public:
  ///@name Algorithmic methods
  //@{

  /** Returns pivot column, -1 if none.
         Lumbers over all columns - slow
         The Packed CoinIndexedVector updates has cost updates - for normal LP
         that is just +-weight where a feasibility changed.  It also has
         reduced cost from last iteration in pivot row
         Can just do full price if you really want to be slow
     */
  virtual int pivotColumn(CoinPartitionedVector *updates,
    CoinPartitionedVector *spareRow2,
    CoinPartitionedVector *spareColumn1);

  /// Just sets model
  virtual void saveWeights(AbcSimplex *model, int)
  {
    model_ = model;
  }
  //@}

  ///@name Constructors and destructors
  //@{
  /// Default Constructor
  AbcPrimalColumnDantzig();

  /// Copy constructor
  AbcPrimalColumnDantzig(const AbcPrimalColumnDantzig &);

  /// Assignment operator
  AbcPrimalColumnDantzig &operator=(const AbcPrimalColumnDantzig &rhs);

  /// Destructor
  virtual ~AbcPrimalColumnDantzig();

  /// Clone
  virtual AbcPrimalColumnPivot *clone(bool copyData = true) const;

  //@}

  //---------------------------------------------------------------------------

private:
  ///@name Private member data
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
