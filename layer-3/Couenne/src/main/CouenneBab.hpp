/*
 *
 * Name:    CouenneBab.hpp
 * Author:  Pietro Belotti
 * Purpose: B&B object
 * Created: 2012-01-25
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneBab.hpp
 * @brief Main Branch-and-Bound driver for Couenne
 *
 * Extends Bonmin::Bab to add Couenne-specific functionality
 * for spatial branch-and-bound on nonconvex MINLPs.
 *
 * **Inheritance:**
 * CouenneBab → Bonmin::Bab → CbcModel
 *
 * **Key additions over Bonmin::Bab:**
 * - Stores CouenneProblem pointer for access to expression DAG
 * - Overrides bestSolution() and bestObj() for proper handling
 * - bestBound() returns min of parent bound and best objective
 *
 * **Usage:**
 * Called from BonCouenneSetup after problem setup.
 * The branchAndBound() method runs the full spatial B&B algorithm,
 * using Couenne's convexification, bound tightening, and
 * branching strategies.
 *
 * **Solution retrieval:**
 * - bestSolution(): Optimal variable values (or best known)
 * - bestObj(): Objective value at best solution
 * - bestBound(): Lower bound on optimal value
 *
 * @see BonCouenneSetup which configures and launches this
 * @see Bonmin::Bab base class
 * @see CouenneProblem for the problem representation
 */
#ifndef COUENNEBAB_H
#define COUENNEBAB_H

#include "BonCbc.hpp"
#include "BonBabSetupBase.hpp"
#include "CouenneConfig.h"

namespace Couenne {

  class CouenneProblem;

  class COUENNELIB_EXPORT CouenneBab: public Bonmin::Bab {

  public:

    CouenneBab (); ///< Constructor

    virtual ~CouenneBab(); ///< Destructor

    void setProblem (CouenneProblem *p);

    virtual void branchAndBound (Bonmin::BabSetupBase &s); ///< Carry out branch and bound

    /// Get the best solution known to the problem (is optimal if
    /// MipStatus is FeasibleOptimal).  If no solution is known
    /// returns NULL.
    const double * bestSolution() const;

    /// Return objective value of the bestSolution
    double bestObj() const;

    /** return the best known lower bound on the objective value*/
    double bestBound() { return CoinMin(Bonmin::Bab::bestBound(), bestObj()); }

  protected:

    CouenneProblem *problem_;

  };
}

#endif
