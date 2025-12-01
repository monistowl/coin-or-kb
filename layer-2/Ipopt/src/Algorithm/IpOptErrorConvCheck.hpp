// Copyright (C) 2004, 2010 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpOptErrorConvCheck.hpp
 * @brief Standard convergence check based on optimality error tolerances
 *
 * OptimalityErrorConvergenceCheck implements the standard termination
 * criteria for Ipopt based on KKT optimality conditions.
 *
 * Optimal convergence (tol):
 * - Dual infeasibility <= dual_inf_tol_
 * - Constraint violation <= constr_viol_tol_
 * - Complementarity <= compl_inf_tol_
 * - Overall scaled error <= tol
 *
 * Acceptable convergence (acceptable_tol):
 * - Less stringent tolerances applied for acceptable_iter_ iterations
 * - Terminates early if stuck near acceptable solution
 * - acceptable_obj_change_tol_: Detects stagnation in objective
 *
 * Failure conditions:
 * - max_iterations_: Iteration limit exceeded
 * - max_wall_time_, max_cpu_time_: Time limits
 * - diverging_iterates_tol_: Primal variables diverging
 * - mu_target_: Target barrier parameter reached
 *
 * CurrentIsAcceptable():
 * - Returns true if acceptable-level tolerances are met
 * - Used by line search to decide on restoration phase
 *
 * @algorithm KKT Optimality Convergence Check:
 * Tests first-order optimality conditions (scaled and unscaled):
 * 1. Optimal convergence (all must hold):
 *    - ||∇L||∞ ≤ dual_inf_tol (dual feasibility)
 *    - ||c(x)||∞ ≤ constr_viol_tol (primal feasibility)
 *    - ||X·Z·e - μ·e||∞ ≤ compl_inf_tol (complementarity)
 *    - Overall scaled error ≤ tol
 * 2. Acceptable convergence (fallback after acceptable_iter_ iterations):
 *    - Same conditions with relaxed tolerances (acceptable_*)
 *    - Plus objective stagnation check: |f_k - f_{k-1}| ≤ acceptable_obj_change_tol
 * 3. Failure conditions:
 *    - iter > max_iterations_
 *    - time > max_wall_time_ or max_cpu_time_
 *    - ||x||∞ > diverging_iterates_tol (divergence)
 *    - μ ≤ mu_target_ (target barrier reached)
 *
 * @math First-order KKT conditions:
 *   ∇f(x) + ∇c(x)ᵀλ + ∇g(x)ᵀν - z = 0  (stationarity)
 *   c(x) = 0                             (equality constraints)
 *   g(x) - s = 0, s ≥ 0                  (inequality slacks)
 *   X·Z·e = μ·e                          (complementarity)
 *   x ≥ 0, z ≥ 0                         (bounds)
 *
 * Scaled error: E_μ(x,λ,z) = max(||∇L||/(s_d+1), ||c||/(s_c+1), ||XZe-μe||/s_c)
 * where s_d, s_c are scaling factors from NLP scaling.
 *
 * @complexity O(n + m) per check for computing norms of residuals.
 * Called once per iteration.
 *
 * @see IpConvCheck.hpp for the base interface
 * @see IpRestoConvCheck.hpp for restoration phase convergence
 */

#ifndef __IPOPTERRORCONVCHECK_HPP__
#define __IPOPTERRORCONVCHECK_HPP__

#include "IpConvCheck.hpp"

namespace Ipopt
{

class OptimalityErrorConvergenceCheck: public ConvergenceCheck
{
public:
   /**@name Constructors / Destructor */
   ///@{
   /** Default Constructor */
   OptimalityErrorConvergenceCheck();

   /** Destructor */
   virtual ~OptimalityErrorConvergenceCheck();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   virtual ConvergenceStatus
   CheckConvergence(
      bool call_intermediate_callback = true
   );

   /** Auxiliary function for testing whether current iterate
    *  satisfies the acceptable level of optimality
    */
   virtual bool CurrentIsAcceptable();

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

protected:
   /** @name Algorithmic parameters */
   ///@{
   /** Maximal number of iterations */
   Index max_iterations_;
   /** Tolerance on unscaled dual infeasibility */
   Number dual_inf_tol_;
   /** Tolerance on unscaled constraint violation */
   Number constr_viol_tol_;
   /** Tolerance on unscaled complementarity */
   Number compl_inf_tol_;
   /** Number of iterations with acceptable level of accuracy, after
    *  which the algorithm terminates.
    *
    *  If 0, this heuristic is disabled.
    */
   Index acceptable_iter_;
   /** Acceptable tolerance for the problem to terminate earlier if
    *  algorithm seems stuck or cycling */
   Number acceptable_tol_;
   /** Acceptable tolerance on unscaled dual infeasibility */
   Number acceptable_dual_inf_tol_;
   /** Acceptable tolerance on unscaled constraint violation */
   Number acceptable_constr_viol_tol_;
   /** Acceptable tolerance on unscaled complementarity */
   Number acceptable_compl_inf_tol_;
   /** Acceptable tolerance for relative objective function change
    *  from iteration to iteration. */
   Number acceptable_obj_change_tol_;
   /** Threshold for primal iterates for divergence test */
   Number diverging_iterates_tol_;
   /** Desired value of the barrier parameter */
   Number mu_target_;
   /** Upper bound on wallclock time */
   Number max_wall_time_;
   /** Upper bound on CPU time */
   Number max_cpu_time_;
   ///@}

private:
   /**@name Default Compiler Generated Methods (Hidden to avoid
    * implicit creation/calling).
    *
    * These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Copy Constructor */
   OptimalityErrorConvergenceCheck(
      const OptimalityErrorConvergenceCheck&
   );

   /** Default Assignment Operator */
   void operator=(
      const OptimalityErrorConvergenceCheck&
   );
   ///@}

   /** Counter for successive iterations in which acceptability
    *  criteria are met.
    */
   Index acceptable_counter_;

   /** Value of the objective function from last iteration.
    *
    * This is for accpetable_obj_change_tol.
    */
   Number last_obj_val_;

   /** Value of the objective function from current iteration.
    *
    * This is for accpetable_obj_change_tol.
    */
   Number curr_obj_val_;

   /** Iteration counter for which last_obj_val most recently updated. */
   Index last_obj_val_iter_;
};

} // namespace Ipopt

#endif
