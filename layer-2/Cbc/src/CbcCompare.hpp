/**
 * @file CbcCompare.hpp
 * @brief Functor wrapper for node comparison
 *
 * @algorithm Node Priority Functor Wrapper
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcCompare: Thin wrapper making CbcCompareBase usable as functor.
 * Used by standard heap algorithms for node priority queue.
 *
 * Holds pointer to CbcCompareBase strategy object (test_).
 * operator() delegates to test_->test(x,y).
 *
 * @see CbcCompareBase for strategy interface
 * @see CbcTree for usage in node management
 */

#ifndef CbcCompare_H
#define CbcCompare_H

#include "CbcConfig.h"

class CbcCompareBase;

class CBCLIB_EXPORT CbcCompare {
public:
  CbcCompareBase *test_;
  // Default Constructor
  CbcCompare()
  {
    test_ = NULL;
  }

  virtual ~CbcCompare() {}

  bool operator()(CbcNode *x, CbcNode *y)
  {
    if (x == y) return false;
    return test_->test(x, y);
  }
  bool compareNodes(CbcNode *x, CbcNode *y)
  {
    return test_->test(x, y);
  }
  /// This is alternate test function
  inline bool alternateTest(CbcNode *x, CbcNode *y)
  {
    return test_->alternateTest(x, y);
  }

  /// return comparison object
  inline CbcCompareBase *comparisonObject() const
  {
    return test_;
  }
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
