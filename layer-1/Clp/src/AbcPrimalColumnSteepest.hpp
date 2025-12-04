// Copyright (C) 2002, International Business Machines
// Corporation and others, Copyright (C) 2012, FasterCoin.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file AbcPrimalColumnSteepest.hpp
 * @brief Steepest edge and Devex for ABC primal simplex
 * @author John Forrest (FasterCoin, 2012)
 *
 * Implements advanced pivot column selection for ABC primal simplex:
 * - Steepest Edge: Normalizes reduced costs by column norms
 * - Devex: Approximate steepest edge with cheaper updates
 *
 * @algorithm Steepest Edge for Primal Simplex Column Selection:
 *   Choose entering column s that maximizes |d_s|/||B⁻¹·a_s||:
 *   1. Maintain weights w_j = ||B⁻¹·a_j||² for each nonbasic column
 *   2. Select s = argmax_j (d_j²/w_j) where d_j is reduced cost
 *   3. Update weights using new FTRAN result when basis changes
 *   Equivalent to moving along steepest descent in transformed space.
 *
 * @algorithm Devex (Approximate Steepest Edge):
 *   Cheaper alternative maintaining reference framework weights:
 *   1. Initialize w_j = 1 for all nonbasic columns
 *   2. After pivot, update only: w_s' = ||B⁻¹·a_s||², w_j' = max(w_j, w_j_hat²)
 *      where w_j_hat is contribution from pivot column
 *   3. Reset all weights to 1 periodically (every ~factorization)
 *   Typically 80-90% as effective as full steepest edge at lower cost.
 *
 * @math Steepest edge weight update (Harris, 1973):
 *   Let α = B⁻¹·a_s (pivot column). After pivot where row r leaves:
 *   w_j' = w_j - 2·α_j·(a_j^T·τ) + α_j²·w_s where τ = (B⁻ᵀ·e_r)/α_r
 *   Incoming column: w_s' = 1/α_r² (becomes basic, new row weight)
 *
 * @complexity Steepest edge: O(m) per pivot for weight update.
 *   Devex: O(nnz(pivot_column)) per pivot, much sparser.
 *   Both reduce iteration count significantly vs Dantzig.
 *
 * @ref Harris (1973). "Pivot selection methods of the Devex LP code".
 *      Mathematical Programming 5:1-28.
 *
 * Modes (controlled by constructor parameter):
 * - 0: Exact Devex
 * - 1: Full steepest edge
 * - 2: Partial exact Devex (scan subset of nonbasics)
 * - 3: Switches between 0/2 based on factorization (default)
 * - 4: Starts as partial Dantzig/Devex, may switch
 * - 5: Always partial Dantzig
 * - >=10: Mini-sprint mode
 *
 * Key optimizations over ClpPrimalColumnSteepest:
 * - Uses CoinPartitionedVector for parallel column blocks
 * - Vectorized weight updates in djsAndDevex()
 * - Efficient partial pricing with partialPricing()
 *
 * @see AbcPrimalColumnPivot for the base interface
 * @see AbcPrimalColumnDantzig for simpler alternative
 * @see ClpPrimalColumnSteepest for the standard (non-ABC) implementation
 */

#ifndef AbcPrimalColumnSteepest_H
#define AbcPrimalColumnSteepest_H

#include "AbcPrimalColumnPivot.hpp"
#include <bitset>

//#############################################################################
class CoinIndexedVector;

/** Primal Column Pivot Steepest Edge Algorithm Class

See Forrest-Goldfarb paper for algorithm

*/

class AbcPrimalColumnSteepest : public AbcPrimalColumnPivot {

public:
  ///@name Algorithmic methods
  //@{

  /** Returns pivot column, -1 if none.
         The Packed CoinIndexedVector updates has cost updates - for normal LP
         that is just +-weight where a feasibility changed.  It also has
         reduced cost from last iteration in pivot row
         Parts of operation split out into separate functions for
         profiling and speed
     */
  virtual int pivotColumn(CoinPartitionedVector *updates,
    CoinPartitionedVector *spareRow2,
    CoinPartitionedVector *spareColumn1);
  /// Just update djs
  void justDjs(CoinIndexedVector *updates,
    CoinIndexedVector *spareColumn1);
  /// Update djs doing partial pricing (dantzig)
  int partialPricing(CoinIndexedVector *updates,
    int numberWanted,
    int numberLook);
  /// Update djs, weights for Devex using djs
  void djsAndDevex(CoinIndexedVector *updates,
    CoinIndexedVector *spareRow2,
    CoinIndexedVector *spareColumn1);
  /// Update djs, weights for Devex using pivot row
  void djsAndDevex2(CoinIndexedVector *updates,
    CoinIndexedVector *spareColumn1);
  /// Update weights for Devex
  void justDevex(CoinIndexedVector *updates,
    CoinIndexedVector *spareColumn1);
  /** Does steepest work
      type - 
      0 - just djs
      1 - just steepest
      2 - both using scaleFactor
      3 - both using extra array
   */
  int doSteepestWork(CoinPartitionedVector *updates,
    CoinPartitionedVector *spareRow2,
    CoinPartitionedVector *spareColumn1,
    int type);

  /// Updates weights - part 1 - also checks accuracy
  virtual void updateWeights(CoinIndexedVector *input);

  /// Checks accuracy - just for debug
  void checkAccuracy(int sequence, double relativeTolerance,
    CoinIndexedVector *rowArray1);

  /// Initialize weights
  void initializeWeights();

  /** Save weights - this may initialize weights as well
         mode is -
         1) before factorization
         2) after factorization
         3) just redo infeasibilities
         4) restore weights
         5) at end of values pass (so need initialization)
     */
  virtual void saveWeights(AbcSimplex *model, int mode);
  /// Gets rid of last update
  virtual void unrollWeights();
  /// Gets rid of all arrays
  virtual void clearArrays();
  /// Returns true if would not find any column
  virtual bool looksOptimal() const;
  /// Called when maximum pivots changes
  virtual void maximumPivotsChanged();
  //@}

  /**@name gets and sets */
  //@{
  /// Mode
  inline int mode() const
  {
    return mode_;
  }
  //@}

  /** enums for persistence
     */
  enum Persistence {
    normal = 0x00, // create (if necessary) and destroy
    keep = 0x01 // create (if necessary) and leave
  };

  ///@name Constructors and destructors
  //@{
  /** Default Constructor
         0 is exact devex, 1 full steepest, 2 is partial exact devex
         3 switches between 0 and 2 depending on factorization
         4 starts as partial dantzig/devex but then may switch between 0 and 2.
         By partial exact devex is meant that the weights are updated as normal
         but only part of the nonbasic variables are scanned.
         This can be faster on very easy problems.
     */
  AbcPrimalColumnSteepest(int mode = 3);

  /// Copy constructor
  AbcPrimalColumnSteepest(const AbcPrimalColumnSteepest &rhs);

  /// Assignment operator
  AbcPrimalColumnSteepest &operator=(const AbcPrimalColumnSteepest &rhs);

  /// Destructor
  virtual ~AbcPrimalColumnSteepest();

  /// Clone
  virtual AbcPrimalColumnPivot *clone(bool copyData = true) const;

  //@}

  ///@name Private functions to deal with devex
  /** reference would be faster using AbcSimplex's status_,
         but I prefer to keep modularity.
     */
  inline bool reference(int i) const
  {
    return ((reference_[i >> 5] >> (i & 31)) & 1) != 0;
  }
  inline void setReference(int i, bool trueFalse)
  {
    unsigned int &value = reference_[i >> 5];
    int bit = i & 31;
    if (trueFalse)
      value |= (1 << bit);
    else
      value &= ~(1 << bit);
  }
  /// Set/ get persistence
  inline void setPersistence(Persistence life)
  {
    persistence_ = life;
  }
  inline Persistence persistence() const
  {
    return persistence_;
  }

  //@}
  //---------------------------------------------------------------------------

private:
  ///@name Private member data
  // Update weight
  double devex_;
  /// weight array
  double *weights_;
  /// square of infeasibility array (just for infeasible columns)
  CoinIndexedVector *infeasible_;
  /// alternate weight array (so we can unroll)
  CoinIndexedVector *alternateWeights_;
  /// save weight array (so we can use checkpoint)
  double *savedWeights_;
  // Array for exact devex to say what is in reference framework
  unsigned int *reference_;
  /** Status
         0) Normal
         -1) Needs initialization
         1) Weights are stored by sequence number
     */
  int state_;
  /**
         0 is exact devex, 1 full steepest, 2 is partial exact devex
         3 switches between 0 and 2 depending on factorization
         4 starts as partial dantzig/devex but then may switch between 0 and 2.
         5 is always partial dantzig
         By partial exact devex is meant that the weights are updated as normal
         but only part of the nonbasic variables are scanned.
         This can be faster on very easy problems.

         New dubious option is >=10 which does mini-sprint

     */
  int mode_;
  /// Life of weights
  Persistence persistence_;
  /// Number of times switched from partial dantzig to 0/2
  int numberSwitched_;
  // This is pivot row (or pivot sequence round re-factorization)
  int pivotSequence_;
  // This is saved pivot sequence
  int savedPivotSequence_;
  // This is saved outgoing variable
  int savedSequenceOut_;
  // Iteration when last rectified
  int lastRectified_;
  // Size of factorization at invert (used to decide algorithm)
  int sizeFactorization_;
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
