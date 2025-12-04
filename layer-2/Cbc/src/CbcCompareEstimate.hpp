/**
 * @file CbcCompareEstimate.hpp
 * @brief Estimate-based node selection strategy
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcCompareEstimate: Node selection using solution estimates.
 * Used during rounding phases where estimated objective matters.
 *
 * @algorithm Estimate-Based Node Selection:
 *   test(x, y) comparison for heap ordering:
 *   Returns true if estimate(y) < estimate(x).
 *   estimate = guessedObjectiveValue() from pseudocost extrapolation.
 *   Effect: Explores nodes most likely to yield good solutions first.
 *   Used during diving/rounding phases when LP bound is less informative.
 *
 * @math Pseudocost-based estimation:
 *   estimate(node) = LP_bound + Σ ψ_j × distance_to_integer(x_j).
 *   Approximates objective of integer-feasible descendant.
 *   More predictive than LP bound when many variables fractional.
 *   Particularly useful early in search before strong bounds available.
 *
 * test(x,y) compares node estimates (guessedObjectiveValue).
 * Estimates typically come from pseudocost extrapolation or
 * other predictive methods.
 *
 * Useful when LP relaxation bound is weak but estimates
 * from branching information are more informative.
 *
 * @see CbcCompareObjective for LP bound comparison
 * @see CbcCompareDefault for adaptive strategy
 * @see CbcNode::guessedObjectiveValue() for estimate source
 *
 * Edwin 11/25/09 carved out of CbcCompareActual
 */

#ifndef CbcCompareEstimate_H
#define CbcCompareEstimate_H

//#############################################################################
/*  These are alternative strategies for node traversal.
    They can take data etc for fine tuning

    At present the node list is stored as a heap and the "test"
    comparison function returns true if node y is better than node x.

*/
#include "CbcNode.hpp"
#include "CbcCompareBase.hpp"
#include "CbcCompare.hpp"
class CbcModel;

/* This is when rounding is being done
*/
class CBCLIB_EXPORT CbcCompareEstimate : public CbcCompareBase {
public:
  // Default Constructor
  CbcCompareEstimate();
  ~CbcCompareEstimate();
  // Copy constructor
  CbcCompareEstimate(const CbcCompareEstimate &rhs);

  // Assignment operator
  CbcCompareEstimate &operator=(const CbcCompareEstimate &rhs);

  /// Clone
  virtual CbcCompareBase *clone() const;
  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  virtual bool test(CbcNode *x, CbcNode *y);
};

#endif //CbcCompareEstimate_H

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
