// Copyright (C) 2003, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file CoinPresolveTripleton.hpp
 * @brief Tripleton row presolve: three-variable equation substitution
 *
 * @algorithm Tripleton Elimination:
 *   Given equality constraint ax + by + cz = d with three variables:
 *   1. Solve for y: y = (d - ax - cz) / b
 *   2. Substitute y into objective and all constraints containing y
 *   3. Eliminate the constraint row and variable y
 *   Only applied if substitution doesn't increase total nonzeros
 *
 * @math Original: ax + by + cz = d
 *   Substitution: y = (d - ax - cz) / b
 *   Objective: c_y·y = c_y·d/b - (c_y·a/b)x - (c_y·c/b)z
 *   Postsolve recovers y from optimal (x*, z*)
 *
 * @complexity Time: O(nnz(col_y) × avg_row_length) per tripleton
 *   Fill-in check prevents growth: only apply if beneficial
 *   Less common than doubleton but can still reduce problem size
 *
 * @see CoinPresolveDoubleton for two-variable case
 * @see CoinPresolveMatrix for the presolve framework
 */

#ifndef CoinPresolveTripleton_H
#define CoinPresolveTripleton_H
#define TRIPLETON 11
/** We are only going to do this if it does not increase number of elements?.
    It could be generalized to more than three but it seems unlikely it would
    help.

    As it is adapted from doubleton icoly is one dropped.
 */
class COINUTILSLIB_EXPORT tripleton_action : public CoinPresolveAction {
public:
  struct action {
    int icolx;
    int icolz;
    int row;

    int icoly;
    double cloy;
    double cupy;
    double costy;
    double clox;
    double cupx;
    double costx;

    double rlo;
    double rup;

    double coeffx;
    double coeffy;
    double coeffz;

    double *colel;

    int ncolx;
    int ncoly;
  };

  const int nactions_;
  const action *const actions_;

private:
  tripleton_action(int nactions,
    const action *actions,
    const CoinPresolveAction *next)
    : CoinPresolveAction(next)
    , nactions_(nactions)
    , actions_(actions)
  {
  }

public:
  const char *name() const { return ("tripleton_action"); }

  static const CoinPresolveAction *presolve(CoinPresolveMatrix *,
    const CoinPresolveAction *next);

  void postsolve(CoinPostsolveMatrix *prob) const;

  virtual ~tripleton_action();
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
