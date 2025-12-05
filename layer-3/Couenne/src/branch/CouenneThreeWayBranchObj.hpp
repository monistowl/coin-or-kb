/*
 *
 * Name:    CouenneThreeWayBranchObj.hpp
 * Authors: Pierre Bonami, IBM Corp.
 *          Pietro Belotti, Carnegie Mellon University
 * Purpose: Three way branching object for auxiliary variables
 *
 * (C) Carnegie-Mellon University, 2006-10.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneThreeWayBranchObj.hpp
 * @brief Three-way spatial branching for continuous variables
 *
 * @algorithm Three-Way Spatial Branching
 *
 * Divides a variable's domain into three parts instead of two,
 * which can provide better convexification around the current
 * LP solution point.
 *
 * **Three-way split:**
 * Given interval [l, u] and dividers lcrop_ and rcrop_:
 * - Left branch:   [l, lcrop_]
 * - Center branch: [lcrop_, rcrop_]
 * - Right branch:  [rcrop_, u]
 *
 * **When useful:**
 * - Current LP solution is interior to [l, u]
 * - Better convexification needed around that point
 * - Two-way split would create very unbalanced children
 *
 * **Branch order (firstBranch_):**
 * - 0: left first
 * - 1: center first (THREE_CENTER default)
 * - 2: right first
 *
 * Center-first often preferred since it contains the current point
 * and may quickly find improving solutions.
 *
 * **Comparison to two-way:**
 * Three-way creates more nodes but can reduce overall tree size
 * by getting better bounds faster near the current solution.
 *
 * @math Split: [l,u] → [l,lcrop_] ∪ [lcrop_,rcrop_] ∪ [rcrop_,u]
 * @complexity O(1) per branch operation; increases node count by 50%
 *
 * @ref Belotti, "Couenne: a user's manual", 2009
 *
 * @see CouenneBranchingObject for standard two-way branching
 * @see CouenneVarObject which can create three-way branches
 */
#ifndef COUENNETHREEWAYBRANCHOBJ_HPP
#define COUENNETHREEWAYBRANCHOBJ_HPP

#include "OsiBranchingObject.hpp"

#include "CouenneExprAux.hpp"
#include "CouenneObject.hpp"

namespace Couenne {

/// \brief Spatial, three-way branching object.
///
/// Branching is performed on continuous variables but a better
/// convexification is sought around the current point by dividing the
/// interval in three parts

class COUENNELIB_EXPORT CouenneThreeWayBranchObj: public OsiBranchingObject {

public:

  /// Constructor
  CouenneThreeWayBranchObj (JnlstPtr jnlst,
			    expression *,
			    CouNumber,
			    CouNumber,
			    int  = THREE_CENTER
			    //bool = false
			    );

  /// Copy constructor
  CouenneThreeWayBranchObj (const CouenneThreeWayBranchObj &src):
    OsiBranchingObject (src),
    brVar_ (src.brVar_),
    lcrop_ (src.lcrop_),
    rcrop_ (src.rcrop_),
    firstBranch_ (src.firstBranch_),
    jnlst_ (src.jnlst_){}

  /// Cloning method
  virtual OsiBranchingObject * clone () const
  {return new CouenneThreeWayBranchObj (*this);}

  /** \brief Execute the actions required to branch, as specified by the
	     current state of the branching object, and advance the object's
	     state.
	     Returns change in guessed objective on next (what does
	     "next" mean here?) branch
  */
  virtual double branch (OsiSolverInterface * solver = NULL);

protected:

  /// The variable this branching object refers to. If the
  /// corresponding CouenneObject was created on w=f(x,y), it is
  /// either x or y.
  expression *brVar_;

  CouNumber lcrop_;  ///< left divider
  CouNumber rcrop_;  ///< right divider

  /// First branch to be performed: 0 is left, 1 is central, 2 is right
  int firstBranch_;

  /// True if the associated variable is integer
  //  bool integer_;

  /// SmartPointer to the Journalist
  JnlstPtr jnlst_;
};

}

#endif
