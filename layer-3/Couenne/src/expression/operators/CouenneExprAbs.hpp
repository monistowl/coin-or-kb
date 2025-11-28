/*
 *
 * Name:    exprAbs.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of the absolute value of a function
 *
 * (C) Carnegie-Mellon University, 2006-10.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprAbs.hpp
 * @brief Absolute value expression w = |x|
 *
 * Represents the absolute value function. This is a convex function
 * with a non-differentiable point at x = 0.
 *
 * **Convexification for w = |x| on [l,u]:**
 * - If l >= 0: w = x (identity)
 * - If u <= 0: w = -x (negation)
 * - If l < 0 < u: convex envelope is
 *   - w >= x (right branch)
 *   - w >= -x (left branch)
 *   - w <= ((u+l)*x + u*(-l) - l*u) / (u - l) (secant from (l,-l) to (u,u))
 *
 * **Implied bounds:**
 * - w >= 0 always
 * - Given w in [0, wu]: x in [-wu, wu] ∩ [l, u]
 * - Given x in [l, u]: w in [min(|l|,|u|)?, max(|l|,|u|)]
 *
 * **Integer preservation:**
 * If argument is integer, |x| is also integer.
 *
 * @see CouenneExprUnary for base class
 */
#ifndef COUENNE_EXPRABS_HPP
#define COUENNE_EXPRABS_HPP

#include <math.h>

#include "CouenneExprUnary.hpp"
#include "CouenneExprConst.hpp"

namespace Couenne {

/// class for \f$ |f(x)| \f$

class COUENNELIB_EXPORT exprAbs: public exprUnary {

 public:

  /// Constructor
  exprAbs  (expression *al):
    exprUnary (al) {} //< non-leaf expression, with argument list

  /// The operator's function
  inline unary_function F () {return fabs;}

  /// cloning method
  expression *clone (Domain *d = NULL) const
    {return new exprAbs (argument_ -> clone (d));}

  /// output
  std::string printOp () const
    {return "abs";}

  /// return l_2 norm of gradient at given point
  inline CouNumber gradientNorm (const double *x)
  {return ((argument_ -> Index () < 0) ? 0. : 1.);}

  /// differentiation
  expression *differentiate (int index);

  /// Get lower and upper bound of an expression (if any)
  virtual void getBounds (expression *&, expression *&);

  /// Get value of lower and upper bound of an expression (if any)
  virtual void getBounds (CouNumber &lb, CouNumber &ub);

  /// generate equality between *this and *w
  void generateCuts (expression *w, //const OsiSolverInterface &si,
		     OsiCuts &cs, const CouenneCutGenerator *cg,
		     t_chg_bounds * = NULL, int = -1,
		     CouNumber = -COUENNE_INFINITY,
		     CouNumber =  COUENNE_INFINITY);

  /// code for comparisons
  enum expr_type code () {return COU_EXPRABS;}

  /// is this expression integer?
  inline bool isInteger ()
  {return argument_ -> isInteger ();}

  /// implied bound processing
  bool impliedBound (int, CouNumber *, CouNumber *, t_chg_bounds *, enum auxSign = expression::AUX_EQ);

  /// set up branching object by evaluating many branching points for
  /// each expression's arguments
  virtual CouNumber selectBranch (const CouenneObject *obj,
				  const OsiBranchingInformation *info,
				  expression * &var,
				  double * &brpts,
 				  double * &brDist, // distance of current LP
					  	    // point to new convexifications
				  int &way);

  /// closest feasible points in function in both directions
  virtual void closestFeasible (expression *varind, expression *vardep,
				CouNumber& left, CouNumber& right) const;

  /// can this expression be further linearized or are we on its
  /// concave ("bad") side
  virtual bool isCuttable (CouenneProblem *problem, int index) const;

  /// either CONVEX, CONCAVE, AFFINE, or NONCONVEX
  //virtual enum convexity convexity () const;
};

}

#endif
