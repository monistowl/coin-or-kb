/**
 * @file CbcHeuristicRandRound.hpp
 * @brief Randomized rounding heuristic
 * Copyright (C) 2008, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcHeuristicRandRound: Probabilistic rounding of LP solution.
 * Rounds fractional variables randomly with probabilities based on
 * their fractional values (e.g., x=0.7 rounds up with prob 0.7).
 *
 * Multiple trials with different random seeds can find diverse solutions.
 * Simple but can be surprisingly effective for certain problem structures.
 *
 * @see CbcHeuristic for base class
 * @see CbcHeuristicFPump for deterministic rounding approach
 */

#ifndef CbcHeuristicRandRound_H
#define CbcHeuristicRandRound_H

#include "CbcHeuristic.hpp"
/** Probabilistic rounding heuristic
 */

class CBCLIB_EXPORT CbcHeuristicRandRound : public CbcHeuristic {
public:
  // Default Constructor
  CbcHeuristicRandRound();

  /* Constructor with model - assumed before cuts
       Initial version does not do Lps
    */
  CbcHeuristicRandRound(CbcModel &model);

  // Copy constructor
  CbcHeuristicRandRound(const CbcHeuristicRandRound &);

  // Destructor
  ~CbcHeuristicRandRound();

  /// Clone
  virtual CbcHeuristic *clone() const;

  /// Assignment operator
  CbcHeuristicRandRound &operator=(const CbcHeuristicRandRound &rhs);

  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /// Resets stuff if model changes
  virtual void resetModel(CbcModel *model);

  /// update model (This is needed if cliques update matrix etc)
  virtual void setModel(CbcModel *model);

  using CbcHeuristic::solution;
  /** returns 0 if no solution, 1 if valid solution.
        Sets solution values if good, sets objective value (only if good)
        needs comments
    */
  virtual int solution(double &objectiveValue,
    double *newSolution);

protected:
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
