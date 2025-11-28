/*
 *
 * Name:    CouenneExprMultilin.hpp
 * Author:  Pietro Belotti
 * Purpose: Product of binary variables
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprBinProd.hpp
 * @brief Product of binary variables (specialized multilinear)
 *
 * Represents products of binary (0-1) variables: w = x₁ * x₂ * ... * xₙ
 * where each xᵢ ∈ {0, 1}. Inherits from exprMul but exploits the
 * binary domain for tighter cuts.
 *
 * **Key simplification:**
 * For binary variables, w = 1 iff all xᵢ = 1, otherwise w = 0.
 * This is equivalent to logical AND.
 *
 * **Linearization (standard form):**
 * For n binaries, the product can be linearized exactly with:
 * - w ≤ xᵢ for all i (w = 0 if any xᵢ = 0)
 * - w ≥ Σxᵢ - (n-1) (w = 1 if all xᵢ = 1)
 *
 * **Bounds:**
 * - Lower bound: 0 always (product of non-negative)
 * - Upper bound: 1 always (product of binaries ≤ 1)
 *
 * **isCuttable():**
 * Returns false - binary products are fully linearizable,
 * no convexification cuts beyond the standard form needed.
 *
 * @see exprMul which this specializes
 * @see CouenneExprMultiLin for general multilinear products
 */
#ifndef COUENNE_EXPRBINPROD_H
#define COUENNE_EXPRBINPROD_H

#include <vector>

#include "CouenneExprOp.hpp"

namespace Couenne {

  /// class for \f$ \prod_{i=1}^n f_i(x) \f$ with \f$ f_i(x) \f$ all binary

  class exprBinProd: public exprMul {

  public:

    /// Constructor
    exprBinProd (expression **, int);

    /// Constructor with two arguments
    exprBinProd (expression *, expression *);

    /// return l-2 norm of gradient at given point
    CouNumber gradientNorm (const double *x);

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
    void generateCuts (expression *w, //const OsiSolverInterface &si,
		       OsiCuts &cs, const CouenneCutGenerator *cg,
		       t_chg_bounds * = NULL, int = -1,
		       CouNumber = -COUENNE_INFINITY,
		       CouNumber =  COUENNE_INFINITY);

    /// code for comparison
    virtual enum expr_type code ()
    {return COU_EXPRMUL;}

    /// implied bound processing
    bool impliedBound (int, CouNumber *, CouNumber *, t_chg_bounds *, enum Couenne::expression::auxSign = Couenne::expression::AUX_EQ);

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

    /// balanced strategy for branching point selection in products
    CouNumber balancedMul (const OsiBranchingInformation *info, int index, int wind);

    /// can this expression be further linearized or are we on its
    /// concave ("bad") side
    virtual bool isCuttable (CouenneProblem *problem, int index) const
    {return false;} // concave on both sides, as for products
  };
}

#endif
