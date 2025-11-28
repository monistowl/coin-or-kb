/*
 *
 * Name:    exprClone.hpp
 * Author:  Pietro Belotti
 * Purpose: definition of the clone class (different from exprCopy in
 *          that evaluation is propagated)
 *
 * (C) Carnegie-Mellon University, 2006.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprClone.hpp
 * @brief Non-owning reference to another expression
 *
 * Points to another expression but does NOT own it - the destructor
 * sets copy_ = NULL to prevent exprCopy's destructor from deleting it.
 *
 * **Key difference from exprCopy:**
 * - exprCopy: Owns copy_, deletes it in destructor
 * - exprClone: Does NOT own copy_, just references it
 *
 * **Usage:**
 * Use exprClone when you need multiple references to the same
 * expression without duplicating memory or ownership.
 *
 * **getOriginal():**
 * Used in constructor to skip through chains of clones/copies
 * to find the actual underlying expression.
 *
 * **Evaluation:**
 * operator() calls (*copy_)() which evaluates the pointed-to
 * expression and returns its result.
 *
 * @see exprCopy which owns its referenced expression
 * @see exprStore for storing computed values
 */
#ifndef COUENNE_EXPRCLONE_HPP
#define COUENNE_EXPRCLONE_HPP

#include <iostream>

#include "CouenneTypes.hpp"
#include "CouenneExprCopy.hpp"

namespace Couenne {

/// expression clone (points to another expression)

class COUENNELIB_EXPORT exprClone: public exprCopy {

 public:

  /// Constructor
  exprClone  (expression *copy):
    exprCopy (getOriginal (copy)) {}

  /// copy constructor
  exprClone (const exprClone &e, Domain *d = NULL):
  //{copy_ = e.copy_;}// d = e.domain_;}
  exprCopy (e, d) {}

  /// cloning method
  expression *clone (Domain *d = NULL) const
  {return new exprClone (*this, d);}
  /*{
    if (copy_ != Original ()) return copy_ -> clone (d);
    else                      return new exprClone (*this, d);
    }*/
  //{return copy_ -> Original () -> clone (d);}

  /// Destructor
  virtual ~exprClone () {
    //if (copy_ != Original ())
    //delete copy_;
    copy_ = NULL; // unlink pointer so that ~exprCopy does nothing
  }

  /// Printing
  virtual void print (std::ostream &out = std::cout,
		      bool descend      = false) const;

  /// value
  inline CouNumber Value () const
  {return copy_ -> Value ();}

  /// null function for evaluating the expression
  inline CouNumber operator () ()
  {return ((*copy_) ());}
};

}

#endif
