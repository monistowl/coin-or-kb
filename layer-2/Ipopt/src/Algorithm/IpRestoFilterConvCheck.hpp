// Copyright (C) 2004, 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13
//
//           A Waechter: moved most code to IpRestoConvCheck.cpp 2008-06-24

/**
 * @file IpRestoFilterConvCheck.hpp
 * @brief Restoration phase convergence check for filter line search
 *
 * RestoFilterConvergenceCheck specializes restoration phase termination
 * for use with the filter globalization mechanism. It checks whether
 * the current restoration point would be acceptable to the original
 * problem's filter.
 *
 * @algorithm Filter-Based Restoration Termination:
 *   TestOrigProgress(φ_trial, θ_trial) from restoration iterate:
 *   1. Query original filter acceptor: IsAcceptableToCurrentFilter(θ, φ).
 *   2. Check: (θ_trial, φ_trial) not dominated by any filter entry.
 *   3. Also check: IsAcceptableToCurrentIterate() for Armijo-like decrease.
 *   4. If acceptable to original → exit restoration with CONVERGED.
 *   5. Otherwise continue restoration iterations.
 *
 * @math Filter acceptance from restoration:
 *   Let F = {(θ_i, φ_i)} be the original filter.
 *   Accept if: ∀i: θ_trial < θ_i OR φ_trial < φ_i - γ_φ·θ_i (envelope check).
 *   Ensures restoration doesn't return to points worse than filter history.
 *
 * Termination criteria (via TestOrigProgress):
 * 1. Current point acceptable to original filter
 * 2. Current point shows sufficient decrease vs original iterate
 * 3. Constraint violation reduced below tolerance
 *
 * The orig_filter_ls_acceptor_ reference is used to query:
 * - IsAcceptableToCurrentIterate(): Armijo or θ-type improvement
 * - IsAcceptableToCurrentFilter(): Point not dominated by filter
 *
 * Important: SetOrigLSAcceptor() must be called before Initialize()
 * to establish the link to the original problem's filter.
 *
 * Note: Uses raw pointer to avoid circular reference with line search.
 *
 * @see IpRestoConvCheck.hpp for the base restoration convergence class
 * @see IpFilterLSAcceptor.hpp for filter acceptance methods
 * @see IpRestoMinC_1Nrm.hpp for the restoration phase algorithm
 */

#ifndef __IPRESTOFILTERCONVCHECK_HPP__
#define __IPRESTOFILTERCONVCHECK_HPP__

#include "IpRestoConvCheck.hpp"
#include "IpFilterLSAcceptor.hpp"

namespace Ipopt
{

/** This is the implementation of the restoration convergence check
 *  is the original algorithm used the filter globalization
 *  mechanism.
 */
class RestoFilterConvergenceCheck: public RestoConvergenceCheck
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   RestoFilterConvergenceCheck();

   /** Destructor */
   virtual ~RestoFilterConvergenceCheck();
   ///@}

   /** Set the object for the original filter line search.
    *
    *  Here, orig_filter_ls_acceptor must be the same strategy object
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
      SmartPtr<RegisteredOptions> roptions);

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
   RestoFilterConvergenceCheck(
      const RestoFilterConvergenceCheck&
   );

   /** Default Assignment Operator */
   void operator=(
      const RestoFilterConvergenceCheck&
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
    *  @attention We must not hold on to this object
    *  with a SmartPtr, because have otherwise circular references
    *  that prevent the destructor of the line search object to be
    *  called!
    */
   const FilterLSAcceptor* orig_filter_ls_acceptor_;
};

} // namespace Ipopt

#endif
