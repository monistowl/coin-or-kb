/*
 *
 * Name:    CouenneComplObject.hpp
 * Authors: Pietro Belotti, Lehigh University
 * Purpose: Branching object for complementarity constraints
 *
 * (C) Carnegie-Mellon University, 2008-10.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneComplObject.hpp
 * @brief Branching object for complementarity constraints
 *
 * @algorithm Complementarity Object for MPEC Branching
 *
 * Handles branching on complementarity conditions x₁ · x₂ ≤ 0,
 * x₁ · x₂ ≥ 0, or x₁ · x₂ = 0. Common in equilibrium problems,
 * KKT conditions, and MPECs (Mathematical Programs with
 * Equilibrium Constraints).
 *
 * **Complementarity branching:**
 * For x₁ · x₂ = 0, branch on either:
 * - x₁ = 0 (one child node)
 * - x₂ = 0 (other child node)
 *
 * **Sign handling (sign_):**
 * - sign_ = 0: Classical x₁ · x₂ = 0
 * - sign_ = +1: x₁ · x₂ ≤ 0
 * - sign_ = -1: x₁ · x₂ ≥ 0
 *
 * **Infeasibility:**
 * Measures how much the complementarity is violated
 * to determine branching priority.
 *
 * @math inf(x₁,x₂) = max(0, sign_ × x₁ × x₂) for sign_ ∈ {-1,0,+1}
 * @complexity O(1) infeasibility check; creates CouenneComplBranchingObject
 *
 * @ref Ferris & Pang, "Engineering and Economic Applications of
 *      Complementarity Problems", SIAM Review, 1997
 *
 * @see CouenneObject base class
 * @see CouenneComplBranchingObject for the branching execution
 */
#ifndef COUENNECOMPLOBJECT_HPP
#define COUENNECOMPLOBJECT_HPP

#include "CouenneObject.hpp"

namespace Couenne {

/// OsiObject for complementarity constraints \f$ x_1 x_2 \ge,\le,= 0 \f$.
///
/// Associated with two variables \f$ x_1\f$ and \f$x_2\f$, branches with either \f$x_1=0\f$ or \f$x_2=0\f$

class COUENNELIB_EXPORT CouenneComplObject: public CouenneObject {

public:

  /// Constructor with information for branching point selection strategy
  CouenneComplObject (CouenneCutGenerator *c,
		      CouenneProblem *p,
		      exprVar *ref, Bonmin::BabSetupBase *base, JnlstPtr jnlst,
		      int sign);

  /// Constructor with lesser information, used for infeasibility only
  CouenneComplObject (exprVar *ref, Bonmin::BabSetupBase *base, JnlstPtr jnlst,
		      int sign);

  /// Destructor
  ~CouenneComplObject () {}

  /// Copy constructor
  CouenneComplObject (const CouenneComplObject &src);

  /// Cloning method
  virtual CouenneObject * clone () const
  {return new CouenneComplObject (*this);}

  /// compute infeasibility of this variable, |w - f(x)| (where w is
  /// the auxiliary variable defined as w = f(x)
  virtual double infeasibility (const OsiBranchingInformation *info, int &way) const;

  /// compute infeasibility of this variable, |w - f(x)|, where w is
  /// the auxiliary variable defined as w = f(x)
  virtual double checkInfeasibility (const OsiBranchingInformation * info) const;

  /// create CouenneBranchingObject or CouenneThreeWayBranchObj based
  /// on this object
  virtual OsiBranchingObject *createBranch (OsiSolverInterface*,
					    const OsiBranchingInformation*,
					    int way) const;
private:

  /// -1 if object is for xi * xj <= 0
  /// +1 if object is for xi * xj <= 0
  ///  0 if object is for xi * xj  = 0 (classical)
  int sign_;

};

}

#endif
