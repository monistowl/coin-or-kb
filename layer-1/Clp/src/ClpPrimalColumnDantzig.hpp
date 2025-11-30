// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpPrimalColumnDantzig.hpp
 * @brief Dantzig's rule for primal simplex pivot selection
 *
 * Implements the simplest pivot column selection: choose the nonbasic variable
 * with the most negative reduced cost (for minimization). This is Dantzig's
 * original 1947 rule.
 *
 * Simple and fast per iteration, but typically requires more iterations than
 * steepest edge methods on degenerate or difficult problems. Use
 * ClpPrimalColumnSteepest for better performance on most problems.
 *
 * @algorithm Dantzig's Rule (Primal Simplex Entering Variable Selection):
 * Scans all nonbasic variables and selects the one with most negative reduced
 * cost. This greedy choice maximizes rate of improvement per unit movement.
 * No weight storage needed - stateless selection based purely on current
 * reduced costs. Fast per iteration but may cycle on degenerate problems
 * without anti-cycling rules (handled elsewhere in ClpSimplexPrimal).
 *
 * @math For minimization, select entering column j* = argmin{d_j | d_j < 0}
 * where d_j = c_j - c_B^T B^{-1} A_j is the reduced cost of nonbasic column j.
 * If d_j >= 0 for all j, current solution is optimal.
 * The most negative d_j gives steepest descent in objective space,
 * though not necessarily fewest iterations to optimality.
 *
 * @complexity O(n) per iteration to scan all nonbasic reduced costs.
 * Total work depends heavily on problem structure - may require
 * O(2^n) iterations worst case (Klee-Minty), but polynomial expected
 * for random problems. Steepest edge typically 2-3x fewer iterations.
 *
 * @ref Dantzig, G.B. (1947). "Maximization of a linear function of variables
 *   subject to linear inequalities". Activity Analysis of Production and
 *   Allocation. [Original simplex paper]
 * @ref Klee, V. & Minty, G.J. (1972). "How good is the simplex algorithm?".
 *   Inequalities III. [Worst-case exponential example]
 *
 * @see ClpPrimalColumnPivot for the base interface
 * @see ClpPrimalColumnSteepest for recommended steepest edge variant
 * @see ClpSimplexPrimal for the primal simplex algorithm
 */

#ifndef ClpPrimalColumnDantzig_H
#define ClpPrimalColumnDantzig_H

#include "ClpPrimalColumnPivot.hpp"

//#############################################################################

/** Primal Column Pivot Dantzig Algorithm Class

This is simplest choice - choose largest infeasibility

*/

class CLPLIB_EXPORT ClpPrimalColumnDantzig : public ClpPrimalColumnPivot {

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
  virtual int pivotColumn(CoinIndexedVector *updates,
    CoinIndexedVector *spareRow1,
    CoinIndexedVector *spareRow2,
    CoinIndexedVector *spareColumn1,
    CoinIndexedVector *spareColumn2);

  /// Just sets model
  virtual void saveWeights(ClpSimplex *model, int)
  {
    model_ = model;
  }
  //@}

  ///@name Constructors and destructors
  //@{
  /// Default Constructor
  ClpPrimalColumnDantzig();

  /// Copy constructor
  ClpPrimalColumnDantzig(const ClpPrimalColumnDantzig &);

  /// Assignment operator
  ClpPrimalColumnDantzig &operator=(const ClpPrimalColumnDantzig &rhs);

  /// Destructor
  virtual ~ClpPrimalColumnDantzig();

  /// Clone
  virtual ClpPrimalColumnPivot *clone(bool copyData = true) const;

  //@}

  //---------------------------------------------------------------------------

private:
  ///@name Private member data
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
