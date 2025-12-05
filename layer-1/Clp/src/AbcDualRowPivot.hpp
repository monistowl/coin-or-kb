// Copyright (C) 2002, International Business Machines
// Corporation and others, Copyright (C) 2012, FasterCoin.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file AbcDualRowPivot.hpp
 * @brief Abstract base class for dual pivot row selection in ABC
 * @author John Forrest (FasterCoin, 2012)
 *
 * Defines the interface for choosing which row (basic variable) should
 * leave the basis in dual simplex iterations within the ABC framework.
 *
 * @algorithm Dual Simplex Row Selection Interface:
 * In dual simplex, we first choose the LEAVING variable (row), then
 * perform ratio test to find ENTERING variable (column).
 *
 * @algorithm Row Selection Strategies:
 *
 * 1. DANTZIG (AbcDualRowDantzig):
 *    i* = argmax_i |violation_i|
 *    O(k) where k = infeasible rows. Simple, no state to maintain.
 *
 * 2. STEEPEST EDGE (AbcDualRowSteepest):
 *    i* = argmax_i (violation_i)² / ||β_i||²
 *    where β_i = B⁻¹·eᵢ is the i-th row of B⁻¹.
 *    Normalizes by edge length for better geometric progress.
 *
 * @algorithm Weight Update Protocol:
 *   updateWeights1(): Compute tableau column, partial FT update
 *   updateWeightsOnly(): Just update norms (no FT)
 *   updateWeights2(): Finish weight updates after pivot
 *
 * This split allows pipelining with other operations.
 *
 * @algorithm ABC Optimizations:
 * - CoinIndexedVector references (not pointers) for cache locality
 * - Weights computed in chunks for vectorization
 * - FT update integrated with weight maintenance
 *
 * @see AbcDualRowDantzig for simple largest-infeasibility selection
 * @see AbcDualRowSteepest for steepest edge variant
 * @see ClpDualRowPivot for the standard (non-ABC) interface
 */

#ifndef AbcDualRowPivot_H
#define AbcDualRowPivot_H
#include "AbcCommon.hpp"

class AbcSimplex;
class CoinIndexedVector;

//#############################################################################

/** Dual Row Pivot Abstract Base Class
    
    Abstract Base Class for describing an interface to an algorithm
    to choose row pivot in dual simplex algorithm.  For some algorithms
    e.g. Dantzig choice then some functions may be null.
    
*/

class CLPLIB_EXPORT AbcDualRowPivot {

public:
  ///@name Algorithmic methods
  //@{

  /// Returns pivot row, -1 if none
  virtual int pivotRow() = 0;

  /** Does most of work for weights and returns pivot alpha.
      Also does FT update */
  virtual double updateWeights1(CoinIndexedVector &input, CoinIndexedVector &updateColumn) = 0;
  virtual void updateWeightsOnly(CoinIndexedVector &input) = 0;
  virtual double updateWeights(CoinIndexedVector &input, CoinIndexedVector &updateColumn) = 0;
  /// Actually updates weights
  virtual void updateWeights2(CoinIndexedVector &input, CoinIndexedVector &updateColumn) = 0;

  /** Updates primal solution (and maybe list of candidates)
      Uses input vector which it deletes
      Would be faster if we kept basic regions, but on other hand it
      means everything is always in sync
  */
  virtual void updatePrimalSolution(CoinIndexedVector &updateColumn,
    double theta)
    = 0;
  virtual void updatePrimalSolutionAndWeights(CoinIndexedVector &weightsVector,
    CoinIndexedVector &updateColumn,
    double theta);
  /** Saves any weights round factorization as pivot rows may change
      Will be empty unless steepest edge (will save model)
      May also recompute infeasibility stuff
      1) before factorization
      2) after good factorization (if weights empty may initialize)
      3) after something happened but no factorization
      (e.g. check for infeasible)
      4) as 2 but restore weights from previous snapshot
      5) for strong branching - initialize  , infeasibilities
  */
  virtual void saveWeights(AbcSimplex *model, int mode);
  /// Recompute infeasibilities
  virtual void recomputeInfeasibilities();
  /// checks accuracy and may re-initialize (may be empty)
  virtual void checkAccuracy();
  /// Gets rid of all arrays (may be empty)
  virtual void clearArrays();
  /// Returns true if would not find any row
  virtual bool looksOptimal() const
  {
    return false;
  }
  //@}

  ///@name Constructors and destructors
  //@{
  /// Default Constructor
  AbcDualRowPivot();

  /// Copy constructor
  AbcDualRowPivot(const AbcDualRowPivot &);

  /// Assignment operator
  AbcDualRowPivot &operator=(const AbcDualRowPivot &rhs);

  /// Destructor
  virtual ~AbcDualRowPivot();

  /// Clone
  virtual AbcDualRowPivot *clone(bool copyData = true) const = 0;

  //@}

  ///@name Other
  //@{
  /// Returns model
  inline AbcSimplex *model()
  {
    return model_;
  }

  /// Sets model (normally to NULL)
  inline void setModel(AbcSimplex *newmodel)
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
  AbcSimplex *model_;
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
