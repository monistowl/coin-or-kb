// Copyright (C) 2006, 2007 International Business Machines
// Corporation and others.  All Rights Reserved.

/**
 * @file BonLpBranchingSolver.hpp
 * @brief LP-based strong branching solver using ECP cuts
 *
 * Implements strong branching by solving LP relaxations enhanced with
 * Extended Cutting Plane (ECP) cuts, avoiding full NLP solves.
 *
 * **Algorithm:**
 * 1. markHotStart(): Extract LP from NLP, generate initial ECP cuts
 * 2. solveFromHotStart(): Re-solve LP with bound changes + new ECP cuts
 * 3. unmarkHotStart(): Clean up LP solver
 *
 * **Parameters:**
 * - maxCuttingPlaneIterations_: Max ECP iterations per strong branch
 * - abs_ecp_tol_, rel_ecp_tol_: Tolerances for ECP convergence
 * - warm_start_mode_: Basis or Clone warm starting
 *
 * @see StrongBranchingSolver for base class
 * @see EcpCuts for the cut generator used
 */
#ifndef BonLpBranchingSolver_H
#define BonLpBranchingSolver_H

#include "BonStrongBranchingSolver.hpp"
#include "BonEcpCuts.hpp"

namespace Bonmin
{

  /** Implementation of BonChooseVariable for curvature-based braching.
  */

  class BONMINLIB_EXPORT LpBranchingSolver : public StrongBranchingSolver
  {

  public:

    /// Constructor from setup 
    LpBranchingSolver (BabSetupBase *b);
    /// Copy constructor
    LpBranchingSolver (const LpBranchingSolver &);

    /// Assignment operator
    LpBranchingSolver & operator= (const LpBranchingSolver& rhs);

    /// Destructor
    virtual ~LpBranchingSolver ();

    /// Called to initialize solver before a bunch of strong branching
    /// solves
    virtual void markHotStart(OsiTMINLPInterface* tminlp_interface);

    /// Called to solve the current TMINLP (with changed bound information)
    virtual TNLPSolver::ReturnStatus solveFromHotStart(OsiTMINLPInterface* tminlp_interface);

    /// Called after all strong branching solves in a node
    virtual void unmarkHotStart(OsiTMINLPInterface* tminlp_interface);

    void setMaxCuttingPlaneIter(int num)
    {
      maxCuttingPlaneIterations_ = num;
    }

    static void registerOptions(Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);

  private:
    /// Default Constructor
    LpBranchingSolver ();

    /// Linear solver
    OsiSolverInterface* lin_;

    /// Warm start object for linear solver
    CoinWarmStart* warm_;

    /// Ecp cut generate
    EcpCuts* ecp_;

    /// Number of maximal ECP cuts
    int maxCuttingPlaneIterations_;

    /// absolute tolerance for ECP cuts
    double abs_ecp_tol_;

    /// relative tolerance for ECP cuts
    double rel_ecp_tol_;


   enum WarmStartMethod {
     Basis=0 /** Use basis*/,
     Clone /** clone problem*/
   };
   /// Way problems are warm started
   WarmStartMethod warm_start_mode_;
  };

}
#endif
