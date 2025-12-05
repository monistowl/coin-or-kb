/*
 *
 * Name:    CouenneComplBranchingObject.hpp
 * Authors: Pietro Belotti, Lehigh University
 * Purpose: Branching object for complementarity constraints
 *
 * (C) Carnegie-Mellon University, 2008-09.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneComplBranchingObject.hpp
 * @brief Branching object for complementarity constraints
 *
 * @algorithm Complementarity Branching for MPEC
 *
 * Handles branching on complementarity conditions x₁·x₂ = 0
 * (or ≤ 0, ≥ 0 variants) arising in MPEC problems.
 *
 * **Branching strategy:**
 * For x₁·x₂ = 0, creates two children:
 * - Left child: x₁ = 0 (fix first variable)
 * - Right child: x₂ = 0 (fix second variable)
 *
 * **Sign variants:**
 * - sign_ = 0: Classical x₁·x₂ = 0
 * - sign_ = -1: x₁·x₂ ≤ 0 (opposite signs allowed)
 * - sign_ = +1: x₁·x₂ ≥ 0 (same signs required)
 *
 * **MPEC context:**
 * Mathematical Programs with Equilibrium Constraints often have
 * complementarity conditions like x ⊥ (Ax - b) ≥ 0, meaning
 * x ≥ 0, Ax - b ≥ 0, and x·(Ax - b) = 0.
 *
 * @math x₁ ⊥ x₂ ⟺ x₁ ≥ 0, x₂ ≥ 0, x₁·x₂ = 0
 * @complexity O(1) per branch operation
 *
 * @ref Bard, "Practical Bilevel Optimization", 1998
 * @ref Ferris & Pang, "Engineering and Economic Applications of
 *      Complementarity Problems", SIAM Review, 1997
 *
 * @see CouenneComplObject which creates these branching objects
 * @see CouenneBranchingObject base class
 */
#ifndef COUENNECOMPLBRANCHINGOBJECT_HPP
#define COUENNECOMPLBRANCHINGOBJECT_HPP

#include "CouenneBranchingObject.hpp"

namespace Couenne {

/** "Spatial" branching object for complementarity constraints.
 *
 *  Branching on such an object x_1 x_2 = 0 is performed by setting
 *  either x_1=0 or x_2=0
 */

class COUENNELIB_EXPORT CouenneComplBranchingObject: public CouenneBranchingObject {

public:

  /// Constructor
  CouenneComplBranchingObject (OsiSolverInterface *solver,
			       const OsiObject *originalObject,
			       JnlstPtr jnlst,
			       CouenneCutGenerator *c,
			       CouenneProblem *p,
			       expression *var,
			       expression *var2,
			       int way,
			       CouNumber brpoint,
			       bool doFBBT,
			       bool doConvCuts,
			       int sign);

  /// Copy constructor
  CouenneComplBranchingObject (const CouenneComplBranchingObject &src):
    CouenneBranchingObject (src),
    variable2_ (src.variable2_),
    sign_      (src.sign_) {}

  /// cloning method
  virtual OsiBranchingObject *clone () const
  {return new CouenneComplBranchingObject (*this);}

  /** \brief Execute the actions required to branch, as specified by the
	     current state of the branching object, and advance the object's
	     state.
	     Returns change in guessed objective on next branch
  */
  virtual double branch (OsiSolverInterface * solver = NULL);

protected:

  /// use CouenneBranchingObject::variable_ as the first variable to set to 0,
  /// and this one as the second
  expression *variable2_;

  /// -1 if object is for xi * xj <= 0
  /// +1 if object is for xi * xj <= 0
  ///  0 if object is for xi * xj  = 0 (classical)
  int sign_;
};

}

#endif
