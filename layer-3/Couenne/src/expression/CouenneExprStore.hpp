/*
 *
 * Name:    exprStore.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of a storage class for expressions
 *
 * (C) Carnegie-Mellon University, 2007.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprStore.hpp
 * @brief Expression that returns previously stored value
 *
 * Returns the Value() of the pointed-to expression rather than
 * re-evaluating it. Used for efficiency when an expression has
 * already been evaluated and the value cached.
 *
 * **Key difference from exprCopy/exprClone:**
 * - exprCopy: Calls (*copy_)() to evaluate
 * - exprClone: Calls (*copy_)() to evaluate
 * - exprStore: Calls copy_->Value() to get cached value
 *
 * **Usage pattern:**
 * When an expression tree is evaluated top-down, intermediate
 * results can be stored in value_ fields. exprStore allows
 * retrieval of these stored values without re-computation.
 *
 * **Destructor:**
 * Like exprClone, sets copy_ = NULL to prevent deletion.
 * Does NOT own the pointed-to expression.
 *
 * @see exprCopy which owns and evaluates
 * @see exprClone which references and evaluates
 */
#ifndef COUENNE_EXPRSTORE_HPP
#define COUENNE_EXPRSTORE_HPP

#include <iostream>

#include "CouenneTypes.hpp"
#include "CouenneExprCopy.hpp"

namespace Couenne {

/// storage class for previously evaluated expressions

class COUENNELIB_EXPORT exprStore: public exprCopy {

 protected:

  /// Value of the (previously evaluated) expression
  CouNumber value_;

 public:

  /// Constructor
  exprStore (expression *copy):
    exprCopy (copy) {}

  /// Store constructor -- Must go
  exprStore (const exprStore &e, Domain *d = NULL):
    exprCopy (e, d) {
    //copy_  = e.Original () -> clone ();
  }

  /// Destructor
  virtual ~exprStore ()
  {copy_ = NULL;}

  /// Printing
  virtual void print (std::ostream &out = std::cout,
		      bool descend      = false) const;

  /// Cloning method
  virtual inline expression *clone (Domain *d = NULL) const
  {return new exprStore (*this, d);}

  /// function for evaluating the expression -- returns value of
  /// exprCopy pointed to, which returns a value stored from a
  /// previous evaluation
  virtual inline CouNumber operator () ()
  {return (copy_ -> Value ());}
};

}

#endif
