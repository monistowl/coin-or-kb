/*
 *
 * Name:    CouenneSOSObject.hpp
 * Authors: Pietro Belotti, Lehigh University
 * Purpose: SOS Object
 *
 * (C) Carnegie-Mellon University, 2008-09.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneSOSObject.hpp
 * @brief Special Ordered Set (SOS) branching for Couenne
 *
 * Extends OsiSOS to include Couenne-specific functionality like
 * bound tightening and convexification cut generation at branching.
 *
 * **SOS Types:**
 * - SOS Type 1: At most one variable can be nonzero
 * - SOS Type 2: At most two adjacent variables can be nonzero
 *
 * **CouenneSOSObject:**
 * Wraps OsiSOS with:
 * - problem_: Link to CouenneProblem for bound tightening
 * - reference_: Associated auxiliary variable
 * - doFBBT_: Enable FBBT at branching
 * - doConvCuts_: Add convexification cuts at branching
 *
 * **CouenneSOSBranchingObject:**
 * Executes the SOS branching, dividing variables into sets
 * where the SOS constraint can be separately enforced.
 *
 * **TODO in code:**
 * Notes extension to handle Σxᵢ ≤ k constraints with small k
 * using SOS-like branching instead of individual variable branching.
 *
 * @see OsiSOS base class
 * @see CbcSOS for CBC's SOS implementation
 */
#ifndef COUENNESOSOBJECT_HPP
#define COUENNESOSOBJECT_HPP

#include "OsiBranchingObject.hpp"
#include "CouenneJournalist.hpp"
#include "CouenneConfig.h"

namespace Couenne {

class CouenneProblem;
class CouenneSOSObject;
class exprVar;


// TODO: SOS of the form sum x_i \le k with k small. Instead of
// branching on a single variable do a SOS-like branching

class COUENNELIB_EXPORT CouenneSOSBranchingObject: public OsiSOSBranchingObject {

protected:

  /// pointer to Couenne problem
  CouenneProblem *problem_;

  /// The (auxiliary) variable this branching object refers to. If the
  /// expression is w=f(x,y), this is w, as opposed to
  /// CouenneBranchingObject, where it would be either x or y.
  exprVar *reference_;

  /// SmartPointer to the Journalist
  JnlstPtr jnlst_;

  /// shall we do Feasibility based Bound Tightening (FBBT) at branching?
  bool doFBBT_;

  /// shall we add convexification cuts at branching?
  bool doConvCuts_;

public:

  // Default Constructor
  CouenneSOSBranchingObject () {}

  // Useful constructor
  CouenneSOSBranchingObject (CouenneProblem *p,
			     exprVar *ref,
			     OsiSolverInterface *solver,
			     const OsiSOS *originalObject,
			     int way,
			     double separator,
			     JnlstPtr jnlst,
			     bool doFBBT,
			     bool doConvCuts):

    OsiSOSBranchingObject (solver, originalObject, way, separator),
    problem_   (p),
    reference_ (ref),
    jnlst_ (jnlst),
    doFBBT_ (doFBBT),
    doConvCuts_ (doConvCuts) {}


  // Copy constructor
  CouenneSOSBranchingObject (const CouenneSOSBranchingObject &src):
    OsiSOSBranchingObject (src),
    problem_    (src.problem_),
    reference_  (src.reference_),
    jnlst_      (src.jnlst_),
    doFBBT_     (src.doFBBT_),
    doConvCuts_ (src.doConvCuts_) {}


  /// Clone
  virtual OsiBranchingObject * clone() const
  {return new CouenneSOSBranchingObject (*this);}

  /// Does next branch and updates state
  virtual double branch (OsiSolverInterface * solver);
};


///
///
///

class COUENNELIB_EXPORT CouenneSOSObject: public OsiSOS {

protected:

  /// pointer to Couenne problem
  CouenneProblem *problem_;

  /// The (auxiliary) variable this branching object refers to. If the
  /// expression is w=f(x,y), this is w, as opposed to
  /// CouenneBranchingObject, where it would be either x or y.
  exprVar *reference_;

  /// SmartPointer to the Journalist
  JnlstPtr jnlst_;

  /// shall we do Feasibility based Bound Tightening (FBBT) at branching?
  bool doFBBT_;

  /// shall we add convexification cuts at branching?
  bool doConvCuts_;

public:

  CouenneSOSObject (OsiSolverInterface *solver, int nelem, int *indices, double *weights, int type,
		    CouenneProblem *problem,
		    exprVar *ref,
		    JnlstPtr jnlst,
		    bool doFBBT,
		    bool doConvCuts):

    OsiSOS      (solver, nelem, indices, weights, type),
    problem_    (problem),
    reference_  (ref),
    jnlst_      (jnlst),
    doFBBT_     (doFBBT),
    doConvCuts_ (doConvCuts) {}


  /// Copy constructor
  CouenneSOSObject (const CouenneSOSObject &src):
    OsiSOS      (src),
    problem_    (src.problem_),
    reference_  (src.reference_),
    jnlst_      (src.jnlst_),
    doFBBT_     (src.doFBBT_),
    doConvCuts_ (src.doConvCuts_) {}

  /// Cloning method
  virtual OsiObject * clone () const
  {return new CouenneSOSObject (*this);}

  /// create branching objects
  OsiBranchingObject *createBranch (OsiSolverInterface* si,
				    const OsiBranchingInformation* info, int way) const;

  /// return reference auxiliary variable
  //exprVar *Reference () const
  //{return reference_;}
};

}

#endif
