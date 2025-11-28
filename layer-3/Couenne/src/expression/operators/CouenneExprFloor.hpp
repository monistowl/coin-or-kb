/*
 *
 * Name:    exprFloor.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of floor
 *
 * (C) Pietro Belotti, 2011.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprFloor.hpp
 * @brief Floor function w = floor(x)
 *
 * Returns the largest integer not exceeding x. Piecewise constant
 * function with jump discontinuities at each integer.
 *
 * **Convexification challenge:**
 * floor(x) is neither convex nor concave nor continuous. The function
 * is constant on intervals [n, n+1) with value n.
 *
 * **Bound propagation:**
 * - lb(w) = floor(lb(x))
 * - ub(w) = floor(ub(x))
 *
 * **Integrality:**
 * Result is always integer-valued, even when argument is continuous.
 * This can introduce implicit integrality constraints.
 *
 * **Not cuttable:**
 * No convex relaxation exists for piecewise constant functions.
 * Must rely on branching to handle.
 *
 * @see exprCeil for the complementary ceiling function
 */
#ifndef COUENNE_EXPRFLOOR_HPP
#define COUENNE_EXPRFLOOR_HPP

#include "CouenneExpression.hpp"

namespace Couenne {

/// class floor, \f$ \lfloor f(x) \rfloor \f$

class exprFloor: public exprUnary {

 public:

  /// constructor, destructor
  exprFloor (expression *arg):
    exprUnary (arg) {}

  /// cloning method
  expression *clone (Domain *d = NULL) const
  {return new exprFloor (argument_ -> clone (d));}

  //// the operator's function
  inline unary_function F ()
  {return floor;}

  /// print operator
  std::string printOp () const
  {return "floor";}

  /// return l-2 norm of gradient at given point
  inline CouNumber gradientNorm (const double *x) {
    return (argument_ -> Index () < 0) ?
      0. : fabs (x [argument_ -> Index ()]);
  }

  /// obtain derivative of expression
  expression *differentiate (int index);

  /// Get lower and upper bound of an expression (if any)
  void getBounds (expression *&, expression *&);

  /// Get value of lower and upper bound of an expression
  void getBounds (CouNumber &lb, CouNumber &ub);

  /// generate equality between *this and *w
  void generateCuts (expression *w, //const OsiSolverInterface &si,
		     OsiCuts &cs, const CouenneCutGenerator *cg,
		     t_chg_bounds * = NULL, int = -1,
		     CouNumber = -COUENNE_INFINITY,
		     CouNumber =  COUENNE_INFINITY);

  /// code for comparisons
  virtual enum expr_type code ()
  {return COU_EXPRFLOOR;}

  /// implied bound processing
  bool impliedBound (int index, CouNumber *l, CouNumber *u, t_chg_bounds *chg, enum auxSign = expression::AUX_EQ) {

    bool impl = true;
    return impl;
  }

  /// Set up branching object by evaluating many branching points for
  /// each expression's arguments
  virtual CouNumber selectBranch (const CouenneObject *obj,
				  const OsiBranchingInformation *info,
				  expression * &var,
				  double * &brpts,
 				  double * &brDist, // distance of current LP
					  	    // point to new convexifications
				  int &way)
  {return 0.;}

  /// closest feasible points in function in both directions
  virtual void closestFeasible (expression *varind, expression *vardep,
				CouNumber& left, CouNumber& right) const;

  /// can this expression be further linearized or are we on its
  /// concave ("bad") side?
  virtual bool isCuttable (CouenneProblem *problem, int index) const
  {return false;}

  /// either CONVEX, CONCAVE, AFFINE, or NONCONVEX
  //virtual enum convexity convexity () const;
};

}

#endif
