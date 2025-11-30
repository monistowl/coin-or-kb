// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpDualRowPivot.hpp
 * @brief Abstract base class for dual simplex pivot row selection
 *
 * In dual simplex, the pivot row (leaving variable) is chosen based on
 * primal infeasibility. This class defines the interface for different
 * selection strategies. Derived classes implement specific rules.
 *
 * Key methods:
 * - pivotRow(): Select which row (basic variable) leaves the basis
 * - updateWeights(): Maintain pricing information after pivots
 * - updatePrimalSolution(): Update solution after basis change
 *
 * @algorithm Dual Simplex Pivot Row Selection (Strategy Pattern):
 * Chooses which basic variable leaves the basis in dual simplex iteration.
 * The leaving variable is primal infeasible (violating bounds).
 * Common strategies:
 * - Dantzig: Choose most infeasible variable (simple, fast per iteration)
 * - Steepest edge: Minimize ||B^{-1}e_i|| weighted infeasibility (fewer iterations)
 * - Partial pricing: Only scan subset of rows (for large problems)
 *
 * @math In dual simplex, we maintain dual feasibility (reduced costs correct signs)
 * and iterate toward primal feasibility. Leaving variable selection:
 * - Find i where x_B[i] < l_i or x_B[i] > u_i (primal infeasibility)
 * - Dantzig: max{|x_B[i] - bound_i|}
 * - Steepest: max{|x_B[i] - bound_i| / ||B^{-1}e_i||}
 * The ||B^{-1}e_i|| weights are maintained incrementally across iterations.
 *
 * @complexity Dantzig: O(m) scan of basic variables per iteration.
 * Steepest edge: O(m) scan + O(nnz) weight updates per iteration.
 * Steepest edge typically reduces total iteration count by 2-3x,
 * outweighing higher per-iteration cost for most problems.
 *
 * @ref Goldfarb, D. & Reid, J.K. (1977). "A practicable steepest-edge simplex
 *   algorithm". Mathematical Programming 12:361-371.
 * @ref Forrest, J.J. & Goldfarb, D. (1992). "Steepest-edge simplex algorithms
 *   for linear programming". Mathematical Programming 57:341-374.
 *
 * @see ClpDualRowDantzig for simple most-infeasible selection
 * @see ClpDualRowSteepest for steepest edge pricing (recommended)
 * @see ClpSimplexDual for the dual simplex algorithm
 * @see ClpPrimalColumnPivot for the primal simplex equivalent
 */

#ifndef ClpDualRowPivot_H
#define ClpDualRowPivot_H

#include "ClpConfig.h"

class ClpSimplex;
class CoinIndexedVector;

//#############################################################################

/** Dual Row Pivot Abstract Base Class

Abstract Base Class for describing an interface to an algorithm
to choose row pivot in dual simplex algorithm.  For some algorithms
e.g. Dantzig choice then some functions may be null.

*/

class CLPLIB_EXPORT ClpDualRowPivot {

public:
  ///@name Algorithmic methods
  //@{

  /// Returns pivot row, -1 if none
  virtual int pivotRow() = 0;

  /** Updates weights and returns pivot alpha.
         Also does FT update */
  virtual double updateWeights(CoinIndexedVector *input,
    CoinIndexedVector *spare,
    CoinIndexedVector *spare2,
    CoinIndexedVector *updatedColumn)
    = 0;

  /** Updates primal solution (and maybe list of candidates)
         Uses input vector which it deletes
         Computes change in objective function
         Would be faster if we kept basic regions, but on other hand it
         means everything is always in sync
     */
  /* FIXME: this was pure virtul (=0). Why? */
  virtual void updatePrimalSolution(CoinIndexedVector *input,
    double theta,
    double &changeInObjective)
    = 0;
  /** Saves any weights round factorization as pivot rows may change
         Will be empty unless steepest edge (will save model)
         May also recompute infeasibility stuff
         1) before factorization
         2) after good factorization (if weights empty may initialize)
         3) after something happened but no factorization
            (e.g. check for infeasible)
         4) as 2 but restore weights from previous snapshot
         5) for strong branching - initialize to 1 , infeasibilities
	 6) scale back
         7) for strong branching - initialize full weights , infeasibilities
     */
  virtual void saveWeights(ClpSimplex *model, int mode);
  /// checks accuracy and may re-initialize (may be empty)
  virtual void checkAccuracy();
  /// Gets rid of last update (may be empty)
  virtual void unrollWeights();
  /// Gets rid of all arrays (may be empty)
  virtual void clearArrays();
  /// Returns true if would not find any row
  virtual bool looksOptimal() const
  {
    return false;
  }
  /// Called when maximum pivots changes
  virtual void maximumPivotsChanged() {}
  //@}

  ///@name Constructors and destructors
  //@{
  /// Default Constructor
  ClpDualRowPivot();

  /// Copy constructor
  ClpDualRowPivot(const ClpDualRowPivot &);

  /// Assignment operator
  ClpDualRowPivot &operator=(const ClpDualRowPivot &rhs);

  /// Destructor
  virtual ~ClpDualRowPivot();

  /// Clone
  virtual ClpDualRowPivot *clone(bool copyData = true) const = 0;

  //@}

  ///@name Other
  //@{
  /// Returns model
  inline ClpSimplex *model()
  {
    return model_;
  }

  /// Sets model (normally to NULL)
  inline void setModel(ClpSimplex *newmodel)
  {
    model_ = newmodel;
  }

  /// Returns type (above 63 is extra information)
  inline int type()
  {
    return type_;
  }

  //@}

  //---------------------------------------------------------------------------

protected:
  ///@name Protected member data
  //@{
  /// Pointer to model
  ClpSimplex *model_;
  /// Type of row pivot algorithm
  int type_;
  //@}
};
#ifndef CLP_DUAL_COLUMN_MULTIPLIER
//#define CLP_DUAL_COLUMN_MULTIPLIER 0.99999
#endif
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
