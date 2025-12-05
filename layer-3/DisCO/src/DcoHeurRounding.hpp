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
 * @file DcoHeurRounding.hpp
 * @brief Simple rounding heuristic for finding feasible solutions
 *
 * @algorithm Simple Rounding Heuristic for MICO
 * @math Given LP relaxation x*, round integer variables:
 *       x̃_j = round(x*_j) for all j ∈ I (integer set)
 *       x̃_j = x*_j for j ∉ I (continuous variables)
 *       Accept if x̃ is feasible: Ax̃ ≤ b, x̃ ∈ K (conic constraints)
 *
 * DcoHeurRounding implements a simple rounding heuristic based on
 * Achterberg's dissertation to find integer feasible solutions.
 *
 * **Algorithm (searchSolution):**
 * 1. Take fractional LP/conic solution
 * 2. Round each integer variable to nearest integer
 * 3. Check feasibility (constraints and cones)
 * 4. Return solution if feasible, NULL otherwise
 *
 * **Bound Fixing (bound_fix):**
 * Uses constraint structure to determine safe rounding directions:
 * - down_fix[i]: Variable i can be safely rounded down
 * - up_fix[i]: Variable i can be safely rounded up
 *
 * **searchSolution2():**
 * Alternative rounding strategy considering constraint types.
 *
 * @complexity O(n + m) for rounding and feasibility check
 * @ref Achterberg, T. (2007). "Constraint Integer Programming". PhD thesis, TU Berlin.
 *
 * @see DcoHeuristic.hpp for base class
 * @see DcoModel.hpp::feasibleSolution() for feasibility checking
 * @see DcoSolution.hpp for solution storage
 */

#ifndef DcoHeurRounding_hpp_
#define DcoHeurRounding_hpp_

// Disco headers
#include "DcoHeuristic.hpp"

/*!
  Implements simple rounding heuristic described in Achterberg's dissretation.

  # Ideas:
  When rounding solutions we can round integer leading variables up.

*/

/** Heuristic base class */
class DcoHeurRounding: virtual public DcoHeuristic {
  void bound_fix(int * down_fix, int * up_fix);
  void bound_fix2(char sense, int row_index, int * down_fix, int * up_fix);
public:
  ///@name Constructors and Destructor.
  //@{
  /// Useful constructor.
  DcoHeurRounding(DcoModel * model, char const * name,
                  DcoHeurStrategy strategy, int frequency);
  /// Destructor.
  virtual ~DcoHeurRounding() { }
  //@}

  ///@name Finding solutions.
  //@{
  /// returns a solution if found, NULL otherwise.
  virtual DcoSolution * searchSolution();
  virtual DcoSolution * searchSolution2();
  //@}

private:
  /// Disable default constructor.
  DcoHeurRounding();
  /// Disable copy constructor.
  DcoHeurRounding(const DcoHeurRounding & other);
  /// Disable copy assignment operator
  DcoHeurRounding & operator=(const DcoHeurRounding & rhs);
};

#endif
