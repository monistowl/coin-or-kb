/**
 * @file CbcFeasibilityBase.hpp
 * @brief User-defined feasibility checking
 *
 * @algorithm User-Defined Feasibility Override Interface
 * Copyright (C) 2005, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcFeasibilityBase: Allows user to override default feasibility tests.
 * Called after LP solve to let user examine solution and declare status.
 *
 * feasible() return values:
 * - 0: Use default determination
 * - 1: Pretend solution is integer feasible
 * - -1: Pretend problem is infeasible
 *
 * mode parameter:
 * - 0: Called after solve, before cuts
 * - -1: Called after strong branching
 *
 * Use cases:
 * - Accept near-integer solutions as integer
 * - Reject solutions violating problem-specific constraints
 * - Implement custom tolerances
 *
 * @see CbcModel::setFeasibilityTest()
 */

#ifndef CbcFeasibilityBase_H
#define CbcFeasibilityBase_H

#include "CbcConfig.h"

//#############################################################################
/*  There are cases where the user wants to control how CBC sees the problems feasibility.
    The user may want to examine the problem and say :
    a) The default looks OK
    b) Pretend this problem is Integer feasible
    c) Pretend this problem is infeasible even though it looks feasible

    This simple class allows user to do that.

*/

class CbcModel;
class CBCLIB_EXPORT CbcFeasibilityBase {
public:
  // Default Constructor
  CbcFeasibilityBase() {}

  /**
       On input mode:
       0 - called after a solve but before any cuts
       -1 - called after strong branching
       Returns :
       0 - no opinion
       -1 pretend infeasible
       1 pretend integer solution
    */
  virtual int feasible(CbcModel *, int)
  {
    return 0;
  }

  virtual ~CbcFeasibilityBase() {}

  // Copy constructor
  CbcFeasibilityBase(const CbcFeasibilityBase &) {}

  // Assignment operator
  CbcFeasibilityBase &operator=(const CbcFeasibilityBase &)
  {
    return *this;
  }

  /// Clone
  virtual CbcFeasibilityBase *clone() const
  {
    return new CbcFeasibilityBase(*this);
  }
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
