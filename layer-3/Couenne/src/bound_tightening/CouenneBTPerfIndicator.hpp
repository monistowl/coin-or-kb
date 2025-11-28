/*
 *
 * Name:    CouenneBTPerfIndicator.hpp
 * Author:  Pietro Belotti
 * Purpose: Measures performance of BT in terms of shrunken bounds
 *
 * (C) Pietro Belotti, 2011.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneBTPerfIndicator.hpp
 * @brief Performance metrics for bound tightening
 *
 * Tracks effectiveness of bound tightening methods (FBBT, OBBT, etc.)
 * by measuring how much bounds are reduced and how many variables are fixed.
 *
 * **Metrics tracked:**
 * - nFixed_: Number of variables fixed (lb == ub)
 * - boundRatio_: Average bound width shrinkage ratio
 * - shrunkInf_: Bounds that became finite from infinite
 * - shrunkDoubleInf_: [-inf,inf] that became [a,inf] or [-inf,b]
 * - nProvedInfeas_: Number of infeasibility proofs
 *
 * **Usage:**
 * 1. Call setOldBounds() before bound tightening
 * 2. Run bound tightening
 * 3. Call update() with new bounds
 * 4. Metrics accumulated for end-of-run summary
 *
 * **Timing:**
 * - totalTime_: CPU time spent in this bound tightener
 * - nRuns_: Number of invocations
 *
 * @see CouenneFixPoint which uses this for FBBT stats
 * @see CouenneAggrProbing which uses this for OBBT stats
 */
#ifndef COUENNEBTPERFINDICATOR_HPP
#define COUENNEBTPERFINDICATOR_HPP

#include "CoinHelperFunctions.hpp"
#include <string.h>

#include "CouenneConfig.h"
#include "CouenneTypes.hpp"

namespace Couenne {

  class CouenneProblem;

  class COUENNELIB_EXPORT CouenneBTPerfIndicator {

  protected:

    std::string name_;                /// Whose performance is this?

    mutable double nFixed_;           /// number of fixed variables
    mutable double boundRatio_;       /// average bound width shrinkage
    mutable double shrunkInf_;        /// average # bounds that went from infinite to finite (counts twice if [-inf,inf] to [a,b]
    mutable double shrunkDoubleInf_;  /// average # bounds that went from doubly infinite to infinite
    mutable double nProvedInfeas_;    /// average # proofs of infeasibility

    mutable double weightSum_;        /// total weight (used to give an average indicator at the end of Couenne)

    mutable double *oldLB_;           /// old lower bounds (initial, i.e. before BT)
    mutable double *oldUB_;           /// old upper bounds

    mutable double totalTime_;        /// CPU time spent on this

    mutable int    nRuns_;            /// number of runs

    CouenneProblem *problem_;         /// Couenne problem info

    bool stats_;                      /// Should stats be printed at the end? Copied from problem_ -> Jnlst () -> ProduceOutput (ERROR, BOUNDTIGHTENING)

  public:


    ///
    CouenneBTPerfIndicator (CouenneProblem *p, const std::string &name);

    ///
    ~CouenneBTPerfIndicator ();

    ///
    CouenneBTPerfIndicator (const CouenneBTPerfIndicator &rhs);

    ///
    CouenneBTPerfIndicator &operator= (const CouenneBTPerfIndicator &rhs);

    ///
    void setOldBounds (const CouNumber *lb, const CouNumber *ub) const;

    /// add to timer
    void addToTimer (double time) const;

    ///
    void update (const CouNumber *lb, const CouNumber *ub, int depth) const;
  };
}

#endif
