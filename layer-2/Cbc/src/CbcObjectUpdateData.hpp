/**
 * @file CbcObjectUpdateData.hpp
 * @brief Data carrier for updating branching objects after branching
 *
 * @algorithm Feedback Carrier for Dynamic Pseudocost Learning
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcObjectUpdateData: Encapsulates information about a completed branch
 * to update the originating CbcObject. Used primarily for learning
 * dynamic pseudocosts from actual branching outcomes.
 *
 * Captured data:
 * - change_: Actual objective change from this branch
 * - status_: LP outcome (0=optimal, 1=infeasible, 2=unknown)
 * - intDecrease_: Reduction in integer infeasibilities
 * - way_: Branch direction taken (-1 down, +1 up)
 *
 * Flow: After solving a child node, CbcNode creates this object
 * and calls object_->updateInformation() to feed back the results.
 *
 * @see CbcSimpleIntegerDynamicPseudoCost for main consumer
 * @see CbcObject::createUpdateInformation() for creation
 * @see CbcObject::updateInformation() for consumption
 *
 * Edwin 11/12/2009 carved from CbcBranchBase
 */

#ifndef CbcObjectUpdateData_H
#define CbcObjectUpdateData_H

#include "CbcObject.hpp"
/*  This stores data so an object can be updated
 */
class CBCLIB_EXPORT CbcObjectUpdateData {

public:
  /// Default Constructor
  CbcObjectUpdateData();

  /// Useful constructor
  CbcObjectUpdateData(CbcObject *object,
    int way,
    double change,
    int status,
    int intDecrease_,
    double branchingValue);

  /// Copy constructor
  CbcObjectUpdateData(const CbcObjectUpdateData &);

  /// Assignment operator
  CbcObjectUpdateData &operator=(const CbcObjectUpdateData &rhs);

  /// Destructor
  virtual ~CbcObjectUpdateData();

public:
  /// data

  /// Object
  CbcObject *object_;
  /// Branch as defined by instance of CbcObject
  int way_;
  /// Object number
  int objectNumber_;
  /// Change in objective
  double change_;
  /// Status 0 Optimal, 1 infeasible, 2 unknown
  int status_;
  /// Decrease in number unsatisfied
  int intDecrease_;
  /// Branching value
  double branchingValue_;
  /// Objective value before branching
  double originalObjective_;
  /// Current cutoff
  double cutoff_;
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
