/*
 *
 * Name:    CouennePSDcon.hpp
 * Author:  Pietro Belotti
 * Purpose: define the class of positive semidefinite constraints
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouennePSDcon.hpp
 * @brief Positive semidefinite constraint X ⪰ 0
 *
 * Represents a constraint that a matrix of expressions must be
 * positive semidefinite (all eigenvalues non-negative).
 *
 * **Mathematical meaning:**
 * X ⪰ 0 is equivalent to:
 * - All eigenvalues of X are non-negative
 * - v'Xv >= 0 for all vectors v
 * - X can be written as X = A'A for some matrix A
 *
 * **Common usage:**
 * - Product matrices: X_ij = x_i * x_j must be PSD
 * - Covariance matrices in statistics
 * - Second-order cone constraints (via PSD embedding)
 *
 * **Handling in Couenne:**
 * PSD constraints are not directly enforceable in MILP/NLP.
 * Instead, they are enforced via:
 * 1. SDP cuts (see CouenneSdpCuts)
 * 2. Eigenvalue constraints (expensive)
 * 3. Principal minor constraints
 *
 * @see CouenneSdpCuts for cut generation from PSD constraints
 * @see CouenneExprMatrix for matrix representation
 */
#ifndef CouennePSDcon_hpp
#define CouennePSDcon_hpp

#include "CouenneConfig.h"
#include "CouenneProblemElem.hpp"
#include <iostream>

namespace Couenne {

  class CouenneExprMatrix;
  class CouenneProblem;
  class Domain;

  /// Class to represent positive semidefinite constraints //////////////////

  class COUENNELIB_EXPORT CouennePSDcon: public CouenneConstraint {

  protected:

    CouenneExprMatrix *X_; ///< contains indices of matrix X \succeq 0

  public:

    /// Constructor
    CouennePSDcon  (CouenneExprMatrix *X):
      CouenneConstraint (),
      X_                (X) {}

    /// Destructor
    ~CouennePSDcon ();

    /// Copy constructor
    CouennePSDcon (const CouennePSDcon &c, Domain *d = NULL);

    /// Assignment operator
    CouennePSDcon &operator= (const CouennePSDcon &c);

    /// Cloning method
    inline CouenneConstraint *clone (Domain *d = NULL) const
    {return new CouennePSDcon (*this, d);}

    /// return X
    CouenneExprMatrix *getX () const {return X_;}

    /// Decompose body of constraint through auxiliary variables
    exprAux *standardize (CouenneProblem *);

    /// Print constraint
    void print (std::ostream & = std::cout);
  };
}

#endif
