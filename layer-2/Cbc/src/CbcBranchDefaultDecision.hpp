/**
 * @file CbcBranchDefaultDecision.hpp
 * @brief Default branching variable selection
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcBranchDefaultDecision: Simple selection algorithm without pseudocosts.
 *
 * @algorithm Default Branching Selection (betterBranch):
 *   Two-phase decision rule:
 *   Phase 1 (before solution): Select variable minimizing infeasibility count.
 *     Score = numInfUp + numInfDn (prefer variables that eliminate more)
 *   Phase 2 (after solution): Select variable maximizing objective degradation.
 *     Score = changeUp + changeDn (prefer variables that bound objective)
 *
 * @math Direction selection within variable:
 *   Prefer up branch (+1) if numInfUp < numInfDn or changeUp > changeDn.
 *   Prefer down branch (-1) otherwise.
 *   Ties broken by direction that constrains solution space more.
 *
 * @complexity O(1) per comparison - just evaluates score function.
 *   No pseudocost tracking or update cost.
 *
 * Returns +1 for up branch preferred, -1 for down branch.
 * Remembers best candidate for comparison chain.
 *
 * @see CbcBranchDecision for base class
 * @see CbcBranchDynamicDecision for pseudocost-based selection
 * @see CbcBranchingObject for what gets compared
 *
 * Edwin 11/10/2009 carved out of CbcBranchActual
 */

#ifndef CbcBranchDefaultDecision_H
#define CbcBranchDefaultDecision_H

#include "CbcBranchBase.hpp"
/** Branching decision default class

  This class implements a simple default algorithm
  (betterBranch()) for choosing a branching variable.
*/

class CBCLIB_EXPORT CbcBranchDefaultDecision : public CbcBranchDecision {
public:
  // Default Constructor
  CbcBranchDefaultDecision();

  // Copy constructor
  CbcBranchDefaultDecision(const CbcBranchDefaultDecision &);

  virtual ~CbcBranchDefaultDecision();

  /// Clone
  virtual CbcBranchDecision *clone() const;

  /// Initialize, <i>e.g.</i> before the start of branch selection at a node
  virtual void initialize(CbcModel *model);

  /** \brief Compare two branching objects. Return nonzero if \p thisOne is
           better than \p bestSoFar.

      The routine compares branches using the values supplied in \p numInfUp and
      \p numInfDn until a solution is found by search, after which it uses the
      values supplied in \p changeUp and \p changeDn. The best branching object
      seen so far and the associated parameter values are remembered in the
      \c CbcBranchDefaultDecision object. The nonzero return value is +1 if the
      up branch is preferred, -1 if the down branch is preferred.

      As the names imply, the assumption is that the values supplied for
      \p numInfUp and \p numInfDn will be the number of infeasibilities reported
      by the branching object, and \p changeUp and \p changeDn will be the
      estimated change in objective. Other measures can be used if desired.

      Because an \c CbcBranchDefaultDecision object remembers the current best
      branching candidate (#bestObject_) as well as the values used in the
      comparison, the parameter \p bestSoFar is redundant, hence unused.
    */
  virtual int betterBranch(CbcBranchingObject *thisOne,
    CbcBranchingObject *bestSoFar,
    double changeUp, int numInfUp,
    double changeDn, int numInfDn);
  /** Sets or gets best criterion so far */
  virtual void setBestCriterion(double value);
  virtual double getBestCriterion() const;

  /** \brief Compare N branching objects. Return index of best
        and sets way of branching in chosen object.

      This routine is used only after strong branching.
    */

  virtual int
  bestBranch(CbcBranchingObject **objects, int numberObjects, int numberUnsatisfied,
    double *changeUp, int *numberInfeasibilitiesUp,
    double *changeDown, int *numberInfeasibilitiesDown,
    double objectiveValue);

private:
  /// Illegal Assignment operator
  CbcBranchDefaultDecision &operator=(const CbcBranchDefaultDecision &rhs);

  /// data

  /// "best" so far
  double bestCriterion_;

  /// Change up for best
  double bestChangeUp_;

  /// Number of infeasibilities for up
  int bestNumberUp_;

  /// Change down for best
  double bestChangeDown_;

  /// Pointer to best branching object
  CbcBranchingObject *bestObject_;

  /// Number of infeasibilities for down
  int bestNumberDown_;
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
