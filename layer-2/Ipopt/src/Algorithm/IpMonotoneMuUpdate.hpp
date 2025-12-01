// Copyright (C) 2004, 2010 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpMonotoneMuUpdate.hpp
 * @brief Standard monotone barrier parameter update strategy
 *
 * MonotoneMuUpdate implements the classical IPM approach where the
 * barrier parameter mu is reduced monotonically as the subproblem
 * converges.
 *
 * Update rule:
 * 1. Solve barrier subproblem to tolerance barrier_tol_factor_ * mu
 * 2. Reduce mu: new_mu = max(mu_target_, min(kappa_mu * mu, mu^theta_mu))
 *    where kappa_mu = mu_linear_decrease_factor_
 *    and theta_mu = mu_superlinear_decrease_power_
 * 3. Update tau (fraction-to-boundary): tau = max(tau_min_, 1 - mu)
 *
 * Key parameters:
 * - mu_init_: Initial barrier parameter
 * - mu_linear_decrease_factor_: Linear decrease factor kappa_mu
 * - mu_superlinear_decrease_power_: Superlinear power theta_mu
 * - tau_min_: Minimum fraction-to-boundary parameter
 * - mu_target_: Target mu for termination
 *
 * Fast decrease heuristic:
 * - mu_allow_fast_monotone_decrease_: Allow faster decrease when
 *   complementarity is already small
 *
 * Interactions:
 * - Calls linesearch_->Reset() when mu changes
 * - Filter is cleared on barrier parameter update
 *
 * @algorithm Monotone Barrier Parameter Update (Classical IPM):
 * Standard approach where μ decreases monotonically each outer iteration:
 * 1. Solve barrier subproblem: minimize f(x) - μ·Σlog(x_i) to tolerance ε(μ)
 * 2. When converged (E(μ) ≤ barrier_tol_factor·μ), reduce μ
 * 3. Repeat until μ < μ_target and KKT conditions satisfied
 *
 * @math Barrier parameter update formula:
 *   μ_{k+1} = max(μ_target, min(κ_μ · μ_k, μ_k^{θ_μ}))
 * where κ_μ ∈ (0,1) is linear factor, θ_μ > 1 gives superlinear decrease.
 *
 * Fraction-to-boundary parameter:
 *   τ_k = max(τ_min, 1 - μ_k)
 * ensures iterates stay strictly positive: x_{k+1} ≥ (1-τ_k)·x_k > 0.
 *
 * @complexity O(1) per update: simple formula evaluation after convergence
 * check. The work is in the inner iterations (Newton steps per μ value).
 *
 * @ref Fiacco & McCormick (1968). "Nonlinear Programming: Sequential
 *   Unconstrained Minimization Techniques". Wiley. [Original barrier method]
 * @ref Wright (1997). "Primal-Dual Interior-Point Methods". SIAM.
 *   Chapter 6: Practical algorithms. [Modern IPM treatment]
 *
 * @see IpMuUpdate.hpp for the base interface
 * @see IpAdaptiveMuUpdate.hpp for non-monotone alternative
 */

#ifndef __IPMONOTONEMUUPDATE_HPP__
#define __IPMONOTONEMUUPDATE_HPP__

#include "IpMuUpdate.hpp"
#include "IpLineSearch.hpp"
#include "IpRegOptions.hpp"

namespace Ipopt
{

/** Monotone Mu Update.
 *
 * This class implements the standard monotone mu update approach.
 */
class MonotoneMuUpdate: public MuUpdate
{
public:
   /**@name Constructors / Destructor */
   ///@{
   /** Default Constructor */
   MonotoneMuUpdate(
      const SmartPtr<LineSearch>& linesearch
   );

   /** Destructor */
   virtual ~MonotoneMuUpdate();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Method for determining the barrier parameter for the next
    *  iteration.
    *
    *  When the optimality error for the current barrier
    *  parameter is less than a tolerance, the barrier parameter is
    *  reduced, and the Reset method of the LineSearch object
    *  linesearch is called.
    */
   virtual bool UpdateBarrierParameter();

   static void RegisterOptions(
      const SmartPtr<RegisteredOptions>& roptions
   );

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    *
    * These methods are not implemented and
    * we do not want the compiler to implement
    * them for us, so we declare them private
    * and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   MonotoneMuUpdate();

   /** Copy Constructor */
   MonotoneMuUpdate(
      const MonotoneMuUpdate&
   );

   void operator=(
      const MonotoneMuUpdate&);
   ///@}

   /** Internal method for computing the new values for mu and tau */
   void CalcNewMuAndTau(
      Number& new_mu,
      Number& new_tau
   );

   /** @name Algorithmic parameters */
   ///@{
   /** Initial value of the barrier parameter */
   Number mu_init_;
   Number barrier_tol_factor_;
   Number mu_linear_decrease_factor_;
   Number mu_superlinear_decrease_power_;
   bool mu_allow_fast_monotone_decrease_;
   /** Tau_min for fraction to boundary rule */
   Number tau_min_;
   Number compl_inf_tol_;
   Number mu_target_;
   ///@}

   SmartPtr<LineSearch> linesearch_;

   /** Flag indicating whether the method has been called at least once so far. */
   bool initialized_;

   /** If true, no modification of the barrier parameter will be done
    *  at the first call of Update (fix for the restoration phase -
    *  we should clean that up!)
    */
   bool first_iter_resto_;
};

} // namespace Ipopt

#endif
