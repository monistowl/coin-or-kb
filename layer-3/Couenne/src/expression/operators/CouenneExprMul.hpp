/*
 *
 * Name:    exprMul.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of multiplications
 *
 * (C) Carnegie-Mellon University, 2006-10.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprMul.hpp
 * @brief N-ary multiplication expression with McCormick convexification
 *
 * Represents products of the form w = x1 * x2 * ... * xn.
 * During standardization, n-ary products are decomposed into
 * binary products: w1 = x1*x2, w2 = w1*x3, etc.
 *
 * @algorithm McCormick Envelope for Bilinear Terms:
 * Convex relaxation of w = x·y over [xL,xU] × [yL,yU]:
 * 1. Lower envelope (concave underestimator):
 *    w ≥ xL·y + x·yL - xL·yL  (tangent at (xL, yL))
 *    w ≥ xU·y + x·yU - xU·yU  (tangent at (xU, yU))
 * 2. Upper envelope (convex overestimator):
 *    w ≤ xL·y + x·yU - xL·yU  (tangent at (xL, yU))
 *    w ≤ xU·y + x·yL - xU·yL  (tangent at (xU, yL))
 * 3. These 4 planes form the convex envelope of x·y over the box.
 *
 * n-ary standardization:
 *   x₁·x₂·x₃ → w₁ = x₁·x₂, w₂ = w₁·x₃
 * introduces O(n-1) auxiliary variables.
 *
 * @math McCormick derivation:
 * For w = x·y, we have:
 *   (x-xL)(y-yL) ≥ 0 ⟹ xy ≥ xL·y + x·yL - xL·yL
 * Similarly for other corners.
 * Envelope is tight at all 4 corners of the box.
 *
 * @complexity O(1) to generate 4 cuts. Bound tightening improves
 * relaxation quality: gap ∝ (xU-xL)·(yU-yL).
 *
 * @ref McCormick (1976). "Computability of global solutions to factorable
 *   nonconvex programs". Mathematical Programming 10(1):147-175.
 *
 * @see CouenneExprDiv for division (uses same convexification)
 * @see CouenneExprBinProd for binary product specialization
 */
#ifndef COUENNE_EXPRMUL_H
#define COUENNE_EXPRMUL_H

#include <vector>

#include "CouenneExprOp.hpp"

namespace Couenne {

class CouenneCutGenerator;

/// class for multiplications, \f$ \prod_{i=1}^n f_i(x) \f$

class COUENNELIB_EXPORT exprMul: public exprOp {

 public:

  /// Constructor
  exprMul (expression **, int);

  /// Constructor with two arguments
  exprMul (expression *, expression *);

  /// Cloning method
  virtual expression *clone (Domain *d = NULL) const
  {return new exprMul (clonearglist (d), nargs_);}

  /// Print operator
  std::string printOp () const
  {return "*";}

  /// Method to evaluate the expression
  inline CouNumber operator () ();

  /// return l-2 norm of gradient at given point
  virtual CouNumber gradientNorm (const double *x);

  /// differentiation
  expression *differentiate (int index);

  /// simplification
  expression *simplify ();

  /// get a measure of "how linear" the expression is:
  virtual int Linearity ();

  /// Get lower and upper bound of an expression (if any)
  virtual void getBounds (expression *&, expression *&);

  /// Get value of lower and upper bound of an expression (if any)
  virtual void getBounds (CouNumber &lb, CouNumber &ub);

  /// reduce expression in standard form, creating additional aux
  /// variables (and constraints)
  virtual exprAux *standardize (CouenneProblem *p, bool addAux = true);

  /// generate equality between *this and *w
  virtual void generateCuts (expression *w, //const OsiSolverInterface &si,
			     OsiCuts &cs, const CouenneCutGenerator *cg,
			     t_chg_bounds * = NULL, int = -1,
			     CouNumber = -COUENNE_INFINITY,
			     CouNumber =  COUENNE_INFINITY);

  /// code for comparison
  virtual enum expr_type code ()
  {return COU_EXPRMUL;}

  /// implied bound processing
  virtual bool impliedBound (int, CouNumber *, CouNumber *, t_chg_bounds *,
			     enum Couenne::expression::auxSign = Couenne::expression::AUX_EQ);

  /// set up branching object by evaluating many branching points for
  /// each expression's arguments
  virtual CouNumber selectBranch (const CouenneObject *obj,
				  const OsiBranchingInformation *info,
				  expression * &var,
				  double * &brpts,
 				  double * &brDist, // distance of current LP
					  	    // point to new convexifications
				  int &way);

  /// compute \f$y^{lv}\f$ and \f$y^{uv}\f$ for Violation Transfer algorithm
  virtual void closestFeasible (expression *varind,
				expression *vardep,
				CouNumber &left,
				CouNumber &right) const;
protected:

  /// inferring bounds on factors of a product
  int impliedBoundMul (CouNumber wl,
		       CouNumber wu,
		       std::vector <CouNumber> &xl,
		       std::vector <CouNumber> &xu,
		       std::vector <std::pair <int, CouNumber> > &nl,
		       std::vector <std::pair <int, CouNumber> > &nu);

  /// balanced strategy for branching point selection in products
  CouNumber balancedMul (const OsiBranchingInformation *info, int index, int wind);

  /// can this expression be further linearized or are we on its
  /// concave ("bad") side
  virtual bool isCuttable (CouenneProblem *problem, int index) const
  {return false;} // concave on both sides, as for products
};


/// compute multiplication
inline CouNumber exprMul:: operator () () {

  CouNumber ret = 1.;
  expression **al = arglist_;

  for (int n = nargs_; n--;)
    ret *= (**al++) ();

  return ret;
}


/// unified convexification of products and divisions
COUENNELIB_EXPORT
void unifiedProdCuts (const CouenneCutGenerator *, OsiCuts &,
		      int, CouNumber, CouNumber, CouNumber,
		      int, CouNumber, CouNumber, CouNumber,
		      int, CouNumber, CouNumber, CouNumber,
		      t_chg_bounds *, enum expression::auxSign);


/// better cuts than those from unifiedProdCuts
COUENNELIB_EXPORT
void upperEnvHull (const CouenneCutGenerator *cg, OsiCuts &cs,
		   int xi, CouNumber x0, CouNumber xl, CouNumber xu,
		   int yi, CouNumber y0, CouNumber yl, CouNumber yu,
		   int wi, CouNumber w0, CouNumber wl, CouNumber wu);


/// compute distance from future convexifications in set \f$\{(x,y,w):
/// w = xy\}\f$ with x,y,w bounded. Unified with exprDiv
COUENNELIB_EXPORT
double *computeMulBrDist (const OsiBranchingInformation *info,
			  int xi, int yi, int wi, int brind, double *brpt, int nPts = 1);

}

#endif
