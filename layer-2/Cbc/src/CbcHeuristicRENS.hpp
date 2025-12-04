/**
 * @file CbcHeuristicRENS.hpp
 * @brief RENS - Relaxation Enforced Neighborhood Search
 * Copyright (C) 2006, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicRENS: Fixes variables based on LP relaxation solution.
 * Unlike RINS (which needs an incumbent), RENS works from LP alone.
 *
 * @algorithm RENS - Relaxation Enforced Neighborhood Search:
 *   solution() from LP solution x̄ (no incumbent required):
 *   1. For integer variable j: If x̄_j at bound, fix x_j = round(x̄_j).
 *   2. Fixing strategy controlled by rensType_ (bounds, dj, priorities).
 *   3. Solve restricted MIP on free variables.
 *   4. Return solution if found, else continue B&C.
 *   No incumbent needed - works early in search tree.
 *
 * @math Reduced cost fixing in RENS:
 *   rensType_=1: Fix x_j if d̄_j > threshold (reduced cost high).
 *   rensType_=3: Fix if d̄_j > 0.01 × avg(d̄).
 *   Variables with high reduced cost unlikely to change in optimal.
 *
 * rensType_ controls fixing strategy:
 * - 0: Fix at lower bound only
 * - 1: Fix based on reduced costs
 * - 2: Fix at upper bound as well
 * - 3: Fix based on 0.01*average reduced cost
 * - +16: Allow two tries
 * - +32: Use existing solution to keep more variables
 * - +64: Honor high priority variables
 * - +128: Honor low priority variables
 *
 * @see CbcHeuristicRINS for incumbent-based neighborhood
 * @see CbcHeuristic for base class
 *
 * Edwin 12/5/09 carved out of CbcHeuristicRINS
 */

#ifndef CbcHeuristicRENS_H
#define CbcHeuristicRENS_H

#include "CbcHeuristic.hpp"

/** LocalSearch class
 */

class CBCLIB_EXPORT CbcHeuristicRENS : public CbcHeuristic {
public:
  // Default Constructor
  CbcHeuristicRENS();

  /* Constructor with model - assumed before cuts
       Initial version does not do Lps
    */
  CbcHeuristicRENS(CbcModel &model);

  // Copy constructor
  CbcHeuristicRENS(const CbcHeuristicRENS &);

  // Destructor
  ~CbcHeuristicRENS();

  /// Clone
  virtual CbcHeuristic *clone() const;

  /// Assignment operator
  CbcHeuristicRENS &operator=(const CbcHeuristicRENS &rhs);

  /// Resets stuff if model changes
  virtual void resetModel(CbcModel *model);

  /// update model (This is needed if cliques update matrix etc)
  virtual void setModel(CbcModel *model);

  using CbcHeuristic::solution;
  /** returns 0 if no solution, 1 if valid solution.
        Sets solution values if good, sets objective value (only if good)
        This does Relaxation Extension Neighborhood Search
        Does not run if when_<2 and a solution exists
    */
  virtual int solution(double &objectiveValue,
    double *newSolution);

  /// Set type
  inline void setRensType(int value)
  {
    rensType_ = value;
  }

protected:
  // Data
  /// Number of tries
  int numberTries_;
  /** Type
        0 - fix at LB
        1 - fix on dj
        2 - fix at UB as well
	3 - fix on 0.01*average dj
	add 16 to allow two tries
	32 - if solution exists use to keep more variables
	64 - if priorities keep high priority
	128 - if priorities keep low priority
    */
  int rensType_;
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
