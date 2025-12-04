// Copyright (C) 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2008-06-24
//             based on IpRestoFilterConvCheck.hpp

/**
 * @file IpRestoPenaltyConvCheck.hpp
 * @brief Restoration phase convergence for penalty line search
 *
 * RestoPenaltyConvergenceCheck extends RestoConvergenceCheck for use
 * when the original algorithm uses penalty function globalization
 * (as opposed to filter method).
 *
 * @algorithm Penalty-Based Restoration Termination:
 *   TestOrigProgress(φ_trial, θ_trial) from restoration iterate:
 *   1. Query original penalty acceptor: IsAcceptableToCurrentIterate(θ, φ).
 *   2. Check Armijo-like decrease: φ_trial ≤ φ_ref - η·Δφ_pred.
 *   3. Check infeasibility: θ_trial ≤ θ_ref (or sufficient reduction).
 *   4. If acceptable to original penalty → exit restoration with CONVERGED.
 *   5. Otherwise continue restoration iterations.
 *
 * @math Penalty acceptance from restoration:
 *   Merit function: ψ(x) = φ(x) + ν·θ(x) where ν = penalty parameter.
 *   Accept if ψ_trial ≤ ψ_ref - η·α·∇ψ^T·d (Armijo on merit).
 *   Penalty method has no filter history, simpler acceptance test.
 *
 * Purpose:
 * During restoration phase, check if current point would be
 * acceptable to the original penalty line search acceptor.
 *
 * Termination:
 * - Restoration succeeds when IsAcceptableToCurrentIterate() returns
 *   true for the original penalty acceptor
 * - This tests if trial_barr and trial_theta would be accepted
 *
 * Setup requirement:
 * - SetOrigLSAcceptor() must be called before Initialize()
 * - Links to the PenaltyLSAcceptor from the original algorithm
 *
 * Note: Uses raw pointer (not SmartPtr) to avoid circular reference
 * between restoration phase and original algorithm objects.
 *
 * @see IpRestoConvCheck.hpp for base restoration convergence
 * @see IpRestoFilterConvCheck.hpp for filter-based restoration
 * @see IpPenaltyLSAcceptor.hpp for penalty line search
 */

#ifndef __IPRESTOPENALTYCONVCHECK_HPP__
#define __IPRESTOPENALTYCONVCHECK_HPP__

#include "IpRestoConvCheck.hpp"
#include "IpPenaltyLSAcceptor.hpp"

namespace Ipopt
{

/** This is the implementation of the restoration convergence check
 *  is the original algorithm used the filter globalization
 *  mechanism.
 */
class RestoPenaltyConvergenceCheck: public RestoConvergenceCheck
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   RestoPenaltyConvergenceCheck();

   /** Destructor */
   virtual ~RestoPenaltyConvergenceCheck();
   ///@}

   /** Set the object for the original penalty line search.
    *
    *  Here, orig_penalty_ls_acceptor must be the same strategy object
    *  to which the restoration phase object with this object is given.
    *  This method must be called to finish the definition of the
    *  algorithm, before Initialize is called.
    */
   void SetOrigLSAcceptor(
      const BacktrackingLSAcceptor& orig_ls_acceptor
   );

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    *
    * These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Copy Constructor */
   RestoPenaltyConvergenceCheck(
      const RestoPenaltyConvergenceCheck&
   );

   /** Default Assignment Operator */
   void operator=(
      const RestoPenaltyConvergenceCheck&
   );
   ///@}

   /** Method for checking progress with original filter
    *  globalization mechanism.
    */
   virtual ConvergenceStatus TestOrigProgress(
      Number orig_trial_barr,
      Number orig_trial_theta
   );

   /** Strategy object for the filter line search method for the
    *  original NLP.
    *
    *  \attention We must not hold on to this object
    *  with a SmartPtr, because have otherwise circular references
    *  that prevent the destructor of the line search object to be
    *  called!
    */
   const PenaltyLSAcceptor* orig_penalty_ls_acceptor_;
};

} // namespace Ipopt

#endif
