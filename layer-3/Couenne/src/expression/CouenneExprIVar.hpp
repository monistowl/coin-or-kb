/*
 *
 * Name:    exprIVar.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of the class exprIVar for integer variables
 *
 * (C) Carnegie-Mellon University, 2006-08.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprIVar.hpp
 * @brief Integer variable expression node
 *
 * Represents an integer-restricted decision variable in the
 * expression DAG. Inherits from exprVar with additional
 * integrality information.
 *
 * **Integer markers:**
 * - isInteger(): Always returns true (variable is integer-valued)
 * - isDefinedInteger(): Always returns true (defined as integer)
 *
 * **Printed notation:**
 * Prints as "y_i" where i is the variable index, distinguishing
 * from continuous variables which print as "x_i".
 *
 * **Usage:**
 * Integer variables require special handling in:
 * - Branch-and-bound (must branch to enforce integrality)
 * - Feasibility checking (must satisfy x ∈ ℤ)
 * - Solution rounding in heuristics
 *
 * @see exprVar base class for continuous variables
 * @see CouenneProblem::addVariable() for variable creation
 */
#ifndef COUENNE_EXPRIVAR_HPP
#define COUENNE_EXPRIVAR_HPP

#include <iostream>

#include "CouenneTypes.hpp"
#include "CouenneExpression.hpp"
#include "CouenneExprVar.hpp"

namespace Couenne {

/// variable-type operator. All variables of the expression must be
/// objects of this class

class COUENNELIB_EXPORT exprIVar: public exprVar {

 public:

  /// Constructor
  exprIVar (int varIndex, Domain *d = NULL):
    exprVar (varIndex, d) {}

  /// Copy constructor -- must go
  exprIVar (const exprIVar &e, Domain *d = NULL):
    exprVar (e, d) {}

  /// Cloning method
  virtual exprVar *clone (Domain *d = NULL) const
  {return new exprIVar (*this, d);}

  /// Print
  virtual void print (std::ostream &out = std::cout, bool = false) const
  {out << "y_" << varIndex_;}

  /// is this expression defined as an integer?
  virtual inline bool isDefinedInteger ()
  {return true;}

  /// Is this expression integer?
  virtual inline bool isInteger ()
  {return true;}
};

}

#endif
