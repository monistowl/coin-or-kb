/*===========================================================================*
 * This file is part of the Discrete Conic Optimization (DisCO) Solver.      *
 *                                                                           *
 * DisCO is distributed under the Eclipse Public License as part of the      *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *          Aykut Bulut, Lehigh University                                   *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Copyright (C) 2001-2018, Lehigh University, Aykut Bulut, Yan Xu, and      *
 *                          Ted Ralphs.                                      *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

/**
 * @file DcoBranchStrategyStrong.hpp
 * @brief Strong branching variable selection strategy
 *
 * Strong branching evaluates candidate variables by actually solving
 * the LP/conic relaxation for both branches before deciding.
 *
 * **Algorithm:**
 * 1. Select top N candidates (strongCandSize parameter)
 * 2. For each candidate, temporarily apply up/down bounds
 * 3. Solve relaxation and record objective change
 * 4. Score = product rule (down_change * up_change)
 * 5. Choose variable with best score
 *
 * **Scoring (updateScore):**
 * Uses product scoring: score = down_degradation * up_degradation
 * This favors variables where both branches improve the bound.
 *
 * **Trade-offs:**
 * - Pro: Best branching decisions, smaller trees
 * - Con: Expensive, many LP/conic solves per node
 *
 * @see DcoBranchStrategyPseudo.hpp for pseudocost (cheaper)
 * @see DcoBranchStrategyRel.hpp for reliability (hybrid)
 * @see DcoParams.hpp::strongCandSize for candidate count
 */

#ifndef DcoBranchStrategyStrong_h_
#define DcoBranchStrategyStrong_h_

#include <BcpsBranchObject.h>
#include <BcpsBranchStrategy.h>

#include "DcoModel.hpp"
#include "DcoBranchObject.hpp"

/*!
  Implements strong branching.
*/

class DcoBranchStrategyStrong : virtual public BcpsBranchStrategy {
  /// update score for the given branch object.
  void updateScore(BcpsBranchObject * bobject, double orig_lb,
                   double orig_ub, double orig_obj) const;
  // return integer infeasibility for the given value
  double infeas(double value) const;
 public:
  ///@name Constructor and Destructor.
  //@{
  /// Constructor.
  DcoBranchStrategyStrong(DcoModel * model);
  /// Destructor.
  virtual ~DcoBranchStrategyStrong() {}
  //@}

  ///@name Selecting and Creating branches.
  //@{
  /// Create a set of candidate branching objects from the given node.
  virtual int createCandBranchObjects(BcpsTreeNode * node);
  /// Compare current to other, return 1 if current is better, 0 otherwise
  virtual int betterBranchObject(BcpsBranchObject const * current,
                                 BcpsBranchObject const * other);
  //@}

 private:
  /// Disable default constructor.
  DcoBranchStrategyStrong();
  /// Disable copy constructor.
  DcoBranchStrategyStrong(DcoBranchStrategyStrong const & other);
  /// Disable copy assignment operator.
  DcoBranchStrategyStrong & operator=(DcoBranchStrategyStrong const & rhs);
};

#endif
