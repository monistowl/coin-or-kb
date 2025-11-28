/*
 *
 * Name:    exprExp.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of the exponential of a function
 *
 * (C) Carnegie-Mellon University, 2006-10.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprExp.hpp
 * @brief Exponential expression w = exp(x)
 *
 * Represents the exponential function e^x. This is a convex function
 * over all of R, so convexification uses secant cuts for overestimation
 * and tangent cuts for underestimation.
 *
 * **Convexification for w = exp(x) on [l,u]:**
 * - Underestimator (tangent): w >= exp(x0) + exp(x0)*(x - x0) at any x0 in [l,u]
 * - Overestimator (secant): w <= exp(l) + (exp(u) - exp(l))/(u - l) * (x - l)
 *
 * **Implied bounds:**
 * - Given w in [wl, wu] with wl > 0: x in [log(wl), log(wu)]
 * - Given x in [xl, xu]: w in [exp(xl), exp(xu)]
 *
 * **Bijective property:**
 * Exp is bijective with inverse log(), enabling tighter bound propagation.
 *
 * **Convexity:** Convex everywhere, simplifying global optimization.
 *
 * @see CouenneExprLog for the inverse function
 * @see CouenneExprUnary for base class
 */
#ifndef COUENNE_EXPREXP_HPP
#define COUENNE_EXPREXP_HPP

#include <math.h>

#include "CouenneExprUnary.hpp"

namespace Couenne {

/// class for the exponential, \f$ e^{f(x)} \f$

class COUENNELIB_EXPORT exprExp: public exprUnary {

 public:

  /// Constructor
  exprExp (expression *al):
    exprUnary (al) {} //< non-leaf expression, with argument list

  /// Cloning method
  expression *clone (Domain *d = NULL) const
    {return new exprExp (argument_ -> clone (d));}

  /// The operator's function
  inline unary_function F () {return exp;}

  /// Print operator
  std::string printOp () const
  {return "exp";}

  /// return l-2 norm of gradient at given point
  inline CouNumber gradientNorm (const double *x)
  {return (argument_ -> Index () < 0) ? 0. : exp (x [argument_ -> Index ()]);}

  /// Differentiation
  expression *differentiate (int index);

  /// Get lower and upper bound of an expression (if any)
  void getBounds (expression *&, expression *&);

  /// Get expression of lower and upper bound of an expression (if any)
  virtual void getBounds (CouNumber &lb, CouNumber&ub);

  /// Generate convexification cuts for this expression
  void generateCuts (expression *w, //const OsiSolverInterface &si,
		     OsiCuts &cs, const CouenneCutGenerator *cg,
		     t_chg_bounds * = NULL, int = -1,
		     CouNumber = -COUENNE_INFINITY,
		     CouNumber =  COUENNE_INFINITY);

  /// Code for comparisons
  virtual enum expr_type code () {return COU_EXPREXP;}

  /// Implied bound processing
  bool impliedBound (int, CouNumber *, CouNumber *, t_chg_bounds *, enum auxSign = expression::AUX_EQ);

  /// Set up branching object by evaluating many branching points for
  /// each expression's arguments
  virtual CouNumber selectBranch (const CouenneObject *obj,
				  const OsiBranchingInformation *info,
				  expression * &var,
				  double * &brpts,
 				  double * &brDist, // distance of current LP
					  	    // point to new convexifications
				  int &way);

  /// return true if bijective
  virtual bool isBijective() const {return true;}

  /// inverse of exponential
  virtual CouNumber inverse(expression *vardep) const
  {
    return log((*vardep)());
  }

  /// can this expression be further linearized or are we on its
  /// concave ("bad") side
  virtual bool isCuttable (CouenneProblem *problem, int index) const;

  /// either CONVEX, CONCAVE, AFFINE, or NONCONVEX
  //virtual enum convexity convexity ()
  //{return CONVEX;}
};

}

#endif
