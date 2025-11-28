/*
 *
 * Name:    lqelems.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of elemental elements of linear and bilinear expressions
 *
 * (C) Carnegie-Mellon University, 2007.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneLQelems.hpp
 * @brief Linear and quadratic term storage for standardization
 *
 * Data structures for collecting linear and quadratic terms during
 * expression standardization (conversion to auxiliary variable form).
 *
 * **quadElem:**
 * Single quadratic term c·xᵢ·xⱼ:
 * - varI_, varJ_: Variable pointers
 * - coeff_: Coefficient c
 *
 * **LinMap:**
 * Sparse map of linear terms: index → coefficient
 * - insert(index, coe): Add/accumulate coefficient
 * - Auto-removes zero entries
 *
 * **QuadMap:**
 * Sparse map of quadratic terms: (i,j) → coefficient
 * - insert(indI, indJ, coe): Add/accumulate coefficient
 * - Auto-removes zero entries
 *
 * **Usage:**
 * During standardization, expressions like x² + 2xy + 3x + 4
 * are decomposed into LinMap (3x + 4 constant) and QuadMap
 * (x² + 2xy). These are then converted to auxiliary form.
 *
 * @see CouenneProblem::standardize() which uses these structures
 */
#ifndef COUENNE_LQELEMS_H
#define COUENNE_LQELEMS_H

#include <map>

#include "CouenneConfig.h"
#include "CouenneTypes.hpp"

namespace Couenne {

class COUENNELIB_EXPORT quadElem {

private:
  exprVar   *varI_;
  exprVar   *varJ_;
  CouNumber  coeff_;

public:

  quadElem (exprVar *i, exprVar *j, CouNumber c):
    varI_ (i),
    varJ_ (j),
    coeff_ (c) {}

  quadElem (const quadElem &src):
    varI_ (src.varI_),
    varJ_ (src.varJ_),
    coeff_ (src.coeff_) {}

  quadElem *clone ()
  {return new quadElem (*this);}

  inline exprVar   *varI  () {return varI_;}
  inline exprVar   *varJ  () {return varJ_;}
  inline CouNumber  coeff () {return coeff_;}
};


class COUENNELIB_EXPORT LinMap {

private:
  std::map <int, CouNumber> lmap_;

public:

  /// public access
  std::map <int, CouNumber> &Map ()
  {return lmap_;}

  /// insert a pair <int,CouNumber> into a map for linear terms
  void insert (int index, CouNumber coe) {

    std::map <int, CouNumber>::iterator i = lmap_.find (index);

    if (i != lmap_.end()) {
      if (fabs (i -> second += coe) < COUENNE_EPS)
	lmap_.erase (i);
    } else {
      std::pair <int, CouNumber> npair (index, coe);
      lmap_.insert (npair);
    }
  }
};


class COUENNELIB_EXPORT QuadMap {

private:
  std::map <std::pair <int, int>, CouNumber> qmap_;

public:

  /// public access
  std::map <std::pair <int, int>, CouNumber> &Map ()
  {return qmap_;}

  /// insert a pair <<int,int>,CouNumber> into a map for quadratic terms
  void insert (int indI, int indJ, CouNumber coe) {

    std::pair <int, int> nind (indI, indJ);
    std::map  <std::pair <int, int>, CouNumber>::iterator i = qmap_.find (nind);

    if (i != qmap_.end()) {
      if (fabs (i -> second += coe) < COUENNE_EPS)
	qmap_.erase (i);
    } else {
      std::pair <std::pair <int, int>, CouNumber> npair (nind, coe);
      qmap_.insert (npair);
    }
  }
};

}

#endif
