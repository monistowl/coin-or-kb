/**
 * @file CbcHeuristicDivePseudoCost.hpp
 * @brief Dive heuristic using pseudocost estimates
 * Copyright (C) 2008, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicDivePseudoCost: Most informed diving strategy.
 * Uses pseudocosts to estimate objective change from fixing.
 *
 * @algorithm Pseudocost-Guided Variable Selection:
 *   selectVariableToBranch() for fractional integer x_j:
 *   1. Compute f_j = x̄_j - ⌊x̄_j⌋ (fractional part).
 *   2. Down estimate: D_j = f_j × ψ_j^- (from downArray_).
 *   3. Up estimate: U_j = (1-f_j) × ψ_j^+ (from upArray_).
 *   4. Score_j = product or weighted combination of D_j, U_j.
 *   5. Select j* = argmax{Score_j}; round toward smaller estimate.
 *
 * @math Pseudocost scoring for diving:
 *   ψ_j^- ≈ (Δobj/Δx̄_j) for down branches on x_j.
 *   ψ_j^+ ≈ (Δobj/Δx̄_j) for up branches on x_j.
 *   Score typically: (1-f)·ψ^- + f·ψ^+ or product-based.
 *   fixOtherVariables() exploits reduced costs: fix if |r̄_j| > gap.
 *
 * initializeData() prepares pseudocost arrays (downArray_, upArray_).
 * fixOtherVariables() uses reduced costs for additional fixing.
 *
 * Generally most effective but requires pseudocost information.
 *
 * @see CbcHeuristicDive for base class and diving algorithm
 * @see CbcSimpleIntegerDynamicPseudoCost for pseudocost learning
 */

#ifndef CbcHeuristicDivePseudoCost_H
#define CbcHeuristicDivePseudoCost_H

#include "CbcHeuristicDive.hpp"

/** Dive using pseudocost estimates
 */

class CBCLIB_EXPORT CbcHeuristicDivePseudoCost : public CbcHeuristicDive {
public:
  // Default Constructor
  CbcHeuristicDivePseudoCost();

  // Constructor with model - assumed before cuts
  CbcHeuristicDivePseudoCost(CbcModel &model);

  // Copy constructor
  CbcHeuristicDivePseudoCost(const CbcHeuristicDivePseudoCost &);

  // Destructor
  ~CbcHeuristicDivePseudoCost();

  /// Clone
  virtual CbcHeuristicDivePseudoCost *clone() const;

  /// Assignment operator
  CbcHeuristicDivePseudoCost &operator=(const CbcHeuristicDivePseudoCost &rhs);

  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /// Selects the next variable to branch on
  /** Returns true if all the fractional variables can be trivially
        rounded. Returns false, if there is at least one fractional variable
        that is not trivially roundable. In this case, the bestColumn
        returned will not be trivially roundable.
    */
  virtual bool selectVariableToBranch(OsiSolverInterface *solver,
    const double *newSolution,
    int &bestColumn,
    int &bestRound);
  /** Initializes any data which is going to be used repeatedly
        in selectVariableToBranch */
  virtual void initializeData();
  /// Fix other variables at bounds
  virtual int fixOtherVariables(OsiSolverInterface *solver,
    const double *solution,
    PseudoReducedCost *candidate,
    const double *random);
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
