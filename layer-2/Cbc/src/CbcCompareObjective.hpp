/**
 * @file CbcCompareObjective.hpp
 * @brief Best-bound (objective-based) node selection
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcCompareObjective: Implements best-first search.
 * Always explores node with best (lowest for min) LP bound.
 *
 * test(x,y) returns true if y has smaller objective than x.
 * Prioritizes most promising nodes for optimality proof.
 *
 * Advantages:
 * - Optimal search order for proving optimality
 * - Best global bound progression
 * - Minimizes total nodes for proof (in theory)
 *
 * Disadvantages:
 * - Can use exponential memory
 * - May take long to find first feasible solution
 * - Poor anytime behavior
 *
 * @see CbcCompareDepth for depth-first alternative
 * @see CbcCompareDefault for practical hybrid
 *
 * Edwin 11/25/09 carved out of CbcCompareActual
 */

#ifndef CbcCompareObjective_H
#define CbcCompareObjective_H

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

class CBCLIB_EXPORT CbcCompareObjective : public CbcCompareBase {
public:
  // Default Constructor
  CbcCompareObjective();

  virtual ~CbcCompareObjective();
  // Copy constructor
  CbcCompareObjective(const CbcCompareObjective &rhs);

  // Assignment operator
  CbcCompareObjective &operator=(const CbcCompareObjective &rhs);

  /// Clone
  virtual CbcCompareBase *clone() const;
  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /* This returns true if objective value of node y is less than
       objective value of node x */
  virtual bool test(CbcNode *x, CbcNode *y);
};

#endif //CbcCompareObjective_H

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
