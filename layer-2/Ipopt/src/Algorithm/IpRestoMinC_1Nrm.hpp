// Copyright (C) 2004, 2010 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpRestoMinC_1Nrm.hpp
 * @brief Restoration phase minimizing 1-norm of constraint violation
 *
 * MinC_1NrmRestorationPhase is the main restoration phase implementation.
 * When the line search cannot make progress, it minimizes constraint
 * violation to find a feasible point from which optimization can continue.
 *
 * Restoration NLP formulation:
 *   min  ρ * ||[p_c; n_c; p_d; n_d]||_1 + (η/2) * ||D_r(x - x_ref)||_2^2
 *   s.t. c(x) - p_c + n_c = 0
 *        d_L <= d(x) - p_d + n_d <= d_U
 *        x_L <= x <= x_U
 *        p_c, n_c, p_d, n_d >= 0
 *
 * Where:
 * - ρ: Penalty on infeasibility (resto_penalty_parameter)
 * - η: Proximity weight (resto_proximity_weight * sqrt(mu))
 * - D_r: Diagonal scaling based on reference point
 * - x_ref: Starting point for restoration
 *
 * Key behaviors:
 * - Uses nested IpoptAlgorithm to solve restoration NLP
 * - eq_mult_calculator_ reinitializes multipliers after restoration
 * - bound_mult_reset_threshold_: Limits post-restoration bound multipliers
 * - count_restorations_: Tracks restoration phase calls
 *
 * @algorithm Restoration Phase (ℓ₁ Feasibility Minimization):
 * Solve modified NLP to find feasible point when main algorithm stuck:
 * 1. Formulate restoration NLP (RestoIpoptNLP):
 *    - Add slack pairs (p,n) to each constraint: c(x) = p - n
 *    - Minimize ρ·(Σp + Σn) (penalized infeasibility)
 *    - Add proximity term η·||D(x - x_ref)||² (stay near reference)
 * 2. Run nested Ipopt on restoration NLP:
 *    - Uses its own filter, barrier parameter, line search
 *    - Converges when infeasibility sufficiently reduced
 * 3. Post-processing:
 *    - Reset constraint multipliers via least-squares (eq_mult_calculator_)
 *    - Cap bound multipliers at threshold to prevent blow-up
 *    - Return to main algorithm with new feasible iterate
 *
 * @math Restoration NLP (smooth ℓ₁ via slack decomposition):
 *   min_{x,p,n} ρ·eᵀ(p+n) + (ζ/2)·||D_R·(x - x_R)||²
 *   s.t. c(x) - p + n = 0
 *        x_L ≤ x ≤ x_U
 *        p ≥ 0, n ≥ 0
 *
 * where D_R = diag(min(1, 1/|x_R|)) provides scaling,
 * ρ penalizes constraint violation, ζ prevents wandering.
 *
 * ℓ₁ equivalence: At solution, either p_i=0 or n_i=0 for each i,
 * so ||p+n||₁ = ||c(x)||₁ at optimum (complementarity).
 *
 * @complexity Same as main Ipopt: O(n³) per iteration for linear algebra.
 * Restoration may require many iterations; worst case certifies infeasibility.
 *
 * @ref Wächter & Biegler (2006). "On the implementation of an interior-point
 *   filter line-search algorithm for large-scale nonlinear programming".
 *   Mathematical Programming 106(1):25-57. [Section 3.3: Restoration phase]
 *
 * @see IpRestoPhase.hpp for the base interface
 * @see IpRestoIpoptNLP.hpp for the restoration NLP formulation
 * @see IpRestoFilterConvCheck.hpp for restoration convergence criteria
 */

#ifndef __IPRESTOC_1NRM_HPP__
#define __IPRESTOC_1NRM_HPP__

#include "IpRestoPhase.hpp"
#include "IpIpoptAlg.hpp"
#include "IpEqMultCalculator.hpp"

namespace Ipopt
{

/** Restoration Phase that minimizes the 1-norm of the constraint
 *  violation - using the interior point method (Ipopt).
 */
class MinC_1NrmRestorationPhase: public RestorationPhase
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor, taking strategy objects.
    *
    *  The resto_alg strategy object is the restoration phase Ipopt
    *  algorithm.  The eq_mult_calculator is used to reinitialize the
    *  equality constraint multipliers after the restoration phase
    *  algorithm has finished - unless it is NULL, in which case the
    *  multipliers are set to 0.
    */
   MinC_1NrmRestorationPhase(
      IpoptAlgorithm&                         resto_alg,
      const SmartPtr<EqMultiplierCalculator>& eq_mult_calculator
   );

   /** Destructor */
   virtual ~MinC_1NrmRestorationPhase();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

protected:
   virtual bool PerformRestoration();

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
   /** Default Constructor */
   MinC_1NrmRestorationPhase();

   /** Copy Constructor */
   MinC_1NrmRestorationPhase(
      const MinC_1NrmRestorationPhase&
   );

   /** Default Assignment Operator */
   void operator=(
      const MinC_1NrmRestorationPhase&
   );
   ///@}

   /** @name Strategy objects */
   ///@{
   SmartPtr<IpoptAlgorithm> resto_alg_;
   SmartPtr<EqMultiplierCalculator> eq_mult_calculator_;
   ///@}

   /** Copy of original options, which is required to initialize the
    *  Ipopt algorithm strategy object before restoration phase is
    *  started.
    */
   SmartPtr<OptionsList> resto_options_;

   /** @name Algorithmic parameters */
   ///@{
   Number constr_mult_reset_threshold_;

   /** Maximal allowed value of a bound multiplier after restoration
    *  phase.
    */
   Number bound_mult_reset_threshold_;

   /** Indicates whether problem can be expected to be infeasible.
    *
    *  This will request to set kappa_resto to a small value for
    *  the first time the restoration phase is called.  (ToDo)
    */
   bool expect_infeasible_problem_;

   /** Constraint violation tolerance */
   Number constr_viol_tol_;

   /** Time limits */
   Number max_wall_time_;
   Number max_cpu_time_;

   /** Primal infeasibility tolerance for declaring failure of
    *  restoration phase when the non-regular termination tests are
    *  met.
    */
   Number resto_failure_feasibility_threshold_;
   ///@}

   /** Counter for the number of time that PerformRestoration is
    *  called.
    */
   Index count_restorations_;

   /** @name Auxiliary methods */
   ///@{
   /** Method for computing "primal-dual" step in bound multipliers,
    *  given step in slacks.
    */
   void ComputeBoundMultiplierStep(
      Vector&       delta_z,
      const Vector& curr_z,
      const Vector& curr_slack,
      const Vector& trial_slack
   );
   ///@}
};

} // namespace Ipopt

#endif
