/*
 *
 * Name:    CouExpr.hpp
 * Author:  Pietro Belotti
 * Purpose: Container class for expressions
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouExpr.hpp
 * @brief Expression container with operator overloading for algebraic construction
 *
 * Provides a user-friendly wrapper around the expression DAG with
 * overloaded operators for building mathematical expressions in
 * natural algebraic notation.
 *
 * **CouExpr container:**
 * - Wraps an expression* with value semantics (cloning on copy)
 * - Allows algebraic expression construction: e1 + e2, sin(e), etc.
 *
 * **Supported operations:**
 * - Arithmetic: +, -, *, /, %, ^ (power)
 * - Trigonometric: sin, cos
 * - Other: log, exp
 *
 * **Operand types:**
 * - CouExpr & CouExpr → CouExpr
 * - CouNumber & CouExpr → CouExpr
 * - CouExpr & CouNumber → CouExpr
 *
 * **Example:**
 * ```cpp
 * CouExpr x(exprVar), y(exprVar);
 * CouExpr f = sin(x) + x*y + exp(y);
 * expression* e = f.Expression();
 * ```
 *
 * @see expression which is the underlying representation
 * @see CouenneProblem for high-level model construction
 */
#ifndef CouExpr_hpp
#define CouExpr_hpp

#include "CouenneExpression.hpp"

namespace Couenne {

class COUENNELIB_EXPORT CouExpr {

private:

  expression *expr_;

public:

  CouExpr (expression *e):
    expr_ (e) {}

  CouExpr (const CouExpr &e) {
    expr_ = e.expr_ -> clone ();
  }

  CouExpr &operator=(CouExpr &e) {
    expr_ = e.expr_ -> clone ();
    return *this;
  }

  expression *Expression () const
  {return expr_;}
};


COUENNELIB_EXPORT CouExpr operator+(CouExpr &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator/(CouExpr &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator%(CouExpr &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator-(CouExpr &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator*(CouExpr &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator^(CouExpr &e1, CouExpr &e2);

COUENNELIB_EXPORT CouExpr &sin(CouExpr &e);
COUENNELIB_EXPORT CouExpr &cos(CouExpr &e);
COUENNELIB_EXPORT CouExpr &log(CouExpr &e);
COUENNELIB_EXPORT CouExpr &exp(CouExpr &e);

COUENNELIB_EXPORT CouExpr &operator+(CouNumber &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator/(CouNumber &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator%(CouNumber &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator-(CouNumber &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator*(CouNumber &e1, CouExpr &e2);
COUENNELIB_EXPORT CouExpr &operator^(CouNumber &e1, CouExpr &e2);

COUENNELIB_EXPORT CouExpr &sin(CouNumber &e);
COUENNELIB_EXPORT CouExpr &cos(CouNumber &e);
COUENNELIB_EXPORT CouExpr &log(CouNumber &e);
COUENNELIB_EXPORT CouExpr &exp(CouNumber &e);

COUENNELIB_EXPORT CouExpr &operator+(CouExpr &e1, CouNumber &e2);
COUENNELIB_EXPORT CouExpr &operator/(CouExpr &e1, CouNumber &e2);
COUENNELIB_EXPORT CouExpr &operator%(CouExpr &e1, CouNumber &e2);
COUENNELIB_EXPORT CouExpr &operator-(CouExpr &e1, CouNumber &e2);
COUENNELIB_EXPORT CouExpr &operator*(CouExpr &e1, CouNumber &e2);
COUENNELIB_EXPORT CouExpr &operator^(CouExpr &e1, CouNumber &e2);

}

#endif
