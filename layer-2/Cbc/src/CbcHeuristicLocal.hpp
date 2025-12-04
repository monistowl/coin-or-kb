/**
 * @file CbcHeuristicLocal.hpp
 * @brief Local search and related improvement heuristics
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * Contains several improvement heuristics for MIP:
 *
 * @algorithm Local Search (2-opt) - CbcHeuristicLocal:
 *   solution() from incumbent x*:
 *   1. Try improving each variable: x_j → x_j ± 1, check feasibility.
 *   2. If infeasible, try 2-opt swaps: (x_i, x_j) → (x_i±1, x_j∓1).
 *   3. Accept any improving feasible move; repeat until no improvement.
 *   swap_=0 normal local search, swap_=1 embedded in B&C.
 *
 * @algorithm Proximity Search (Fischetti & Monaci 2014) - CbcHeuristicProximity:
 *   solution() minimizes distance to incumbent:
 *   1. Add proximity constraint: Σ|x_j - x*_j| ≤ δ (cutoff based).
 *   2. Optimize c^T x subject to proximity and original constraints.
 *   3. Progressively tighten δ; use Feasibility Pump infrastructure.
 *   Blends objective optimization with incumbent neighborhood.
 *
 * @algorithm Crossover/Path Relinking - CbcHeuristicCrossover:
 *   solution() combines multiple solutions:
 *   1. Fix variables where all useNumber_ solutions agree.
 *   2. Use random_ for tie-breaking diversification.
 *   3. Solve restricted MIP on free variables.
 *   Path relinking through solution pool agreement.
 *
 * CbcHeuristicNaive: Simple construction heuristic.
 * (a) Fix integers close to zero
 * (b) Fix integers with small costs to zero
 * (c) Tighten continuous bounds and optimize
 *
 * @see CbcHeuristicFPump for Feasibility Pump
 * @see CbcHeuristicRINS for neighborhood search
 * @see CbcHeuristic for base class
 */

#ifndef CbcHeuristicLocal_H
#define CbcHeuristicLocal_H

#include "CbcHeuristic.hpp"
/** LocalSearch class - 2-opt swap-based improvement
 */

class CBCLIB_EXPORT CbcHeuristicLocal : public CbcHeuristic {
public:
  // Default Constructor
  CbcHeuristicLocal();

  /* Constructor with model - assumed before cuts
       Initial version does not do Lps
    */
  CbcHeuristicLocal(CbcModel &model);

  // Copy constructor
  CbcHeuristicLocal(const CbcHeuristicLocal &);

  // Destructor
  ~CbcHeuristicLocal();

  /// Clone
  virtual CbcHeuristic *clone() const;

  /// Assignment operator
  CbcHeuristicLocal &operator=(const CbcHeuristicLocal &rhs);

  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /// Resets stuff if model changes
  virtual void resetModel(CbcModel *model);

  /// update model (This is needed if cliques update matrix etc)
  virtual void setModel(CbcModel *model);

  using CbcHeuristic::solution;
  /** returns 0 if no solution, 1 if valid solution.
        Sets solution values if good, sets objective value (only if good)
        This is called after cuts have been added - so can not add cuts
        First tries setting a variable to better value.  If feasible then
        tries setting others.  If not feasible then tries swaps

        ********

        This first version does not do LP's and does swaps of two integer
        variables.  Later versions could do Lps.
    */
  virtual int solution(double &objectiveValue,
    double *newSolution);
  /// This version fixes stuff and does IP
  int solutionFix(double &objectiveValue,
    double *newSolution,
    const int *keep);

  /// Sets type of search
  inline void setSearchType(int value)
  {
    swap_ = value;
  }
  /// Used array so we can set
  inline int *used() const
  {
    return used_;
  }

protected:
  // Data

  // Original matrix by column
  CoinPackedMatrix matrix_;

  // Number of solutions so we only do after new solution
  int numberSolutions_;
  // Type of search 0=normal, 1=BAB
  int swap_;
  /// Whether a variable has been in a solution (also when)
  int *used_;
};

/** Proximity Search class
 */
class CbcHeuristicFPump;
class CBCLIB_EXPORT CbcHeuristicProximity : public CbcHeuristic {
public:
  // Default Constructor
  CbcHeuristicProximity();

  /* Constructor with model - assumed before cuts
    */
  CbcHeuristicProximity(CbcModel &model);

  // Copy constructor
  CbcHeuristicProximity(const CbcHeuristicProximity &);

  // Destructor
  ~CbcHeuristicProximity();

  /// Clone
  virtual CbcHeuristic *clone() const;

  /// Assignment operator
  CbcHeuristicProximity &operator=(const CbcHeuristicProximity &rhs);

  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /// Resets stuff if model changes
  virtual void resetModel(CbcModel *model);

  /// update model (This is needed if cliques update matrix etc)
  virtual void setModel(CbcModel *model);

  using CbcHeuristic::solution;
  /** returns 0 if no solution, 1 if valid solution.
        Sets solution values if good, sets objective value (only if good)
    */
  virtual int solution(double &objectiveValue,
    double *newSolution);
  /// Set extra increment
  inline void setIncrement(double value)
  {
    increment_ = value;
  }
  /// Used array so we can set
  inline int *used() const
  {
    return used_;
  }

protected:
  // Data
  /// Increment to use if no change
  double increment_;
  /// Copy of Feasibility pump
  CbcHeuristicFPump *feasibilityPump_;
  /// Number of solutions so we only do after new solution
  int numberSolutions_;
  /// Whether a variable has been in a solution (also when)
  int *used_;
};

/** Naive class
    a) Fix all ints as close to zero as possible
    b) Fix all ints with nonzero costs and < large to zero
    c) Put bounds round continuous and UIs and maximize
 */

class CBCLIB_EXPORT CbcHeuristicNaive : public CbcHeuristic {
public:
  // Default Constructor
  CbcHeuristicNaive();

  /* Constructor with model - assumed before cuts
       Initial version does not do Lps
    */
  CbcHeuristicNaive(CbcModel &model);

  // Copy constructor
  CbcHeuristicNaive(const CbcHeuristicNaive &);

  // Destructor
  ~CbcHeuristicNaive();

  /// Clone
  virtual CbcHeuristic *clone() const;

  /// Assignment operator
  CbcHeuristicNaive &operator=(const CbcHeuristicNaive &rhs);

  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /// Resets stuff if model changes
  virtual void resetModel(CbcModel *model);

  /// update model (This is needed if cliques update matrix etc)
  virtual void setModel(CbcModel *model);

  using CbcHeuristic::solution;
  /** returns 0 if no solution, 1 if valid solution.
        Sets solution values if good, sets objective value (only if good)
    */
  virtual int solution(double &objectiveValue,
    double *newSolution);

  /// Sets large cost value
  inline void setLargeValue(double value)
  {
    large_ = value;
  }
  /// Gets large cost value
  inline double largeValue() const
  {
    return large_;
  }

protected:
  /// Data
  /// Large value
  double large_;
};

/** Crossover Search class
 */

class CBCLIB_EXPORT CbcHeuristicCrossover : public CbcHeuristic {
public:
  // Default Constructor
  CbcHeuristicCrossover();

  /* Constructor with model - assumed before cuts
       Initial version does not do Lps
    */
  CbcHeuristicCrossover(CbcModel &model);

  // Copy constructor
  CbcHeuristicCrossover(const CbcHeuristicCrossover &);

  // Destructor
  ~CbcHeuristicCrossover();

  /// Clone
  virtual CbcHeuristic *clone() const;

  /// Assignment operator
  CbcHeuristicCrossover &operator=(const CbcHeuristicCrossover &rhs);

  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  /// Resets stuff if model changes
  virtual void resetModel(CbcModel *model);

  /// update model (This is needed if cliques update matrix etc)
  virtual void setModel(CbcModel *model);

  using CbcHeuristic::solution;
  /** returns 0 if no solution, 1 if valid solution.
        Fix variables if agree in useNumber_ solutions
        when_ 0 off, 1 only at new solutions, 2 also every now and then
        add 10 to make only if agree at lower bound
    */
  virtual int solution(double &objectiveValue,
    double *newSolution);

  /// Sets number of solutions to use
  inline void setNumberSolutions(int value)
  {
    if (value > 0 && value <= 10)
      useNumber_ = value;
  }

protected:
  // Data
  /// Attempts
  std::vector< double > attempts_;
  /// Random numbers to stop same search happening
  double random_[10];
  /// Number of solutions so we only do after new solution
  int numberSolutions_;
  /// Number of solutions to use
  int useNumber_;
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
