// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter              IBM    2004-09-24

/**
 * @file IpRestoIterateInitializer.hpp
 * @brief Iterate initialization for restoration phase
 *
 * RestoIterateInitializer computes starting values for all variables
 * in the restoration phase feasibility problem. This includes the
 * original variables (x, s) and the slack variables (n_c, p_c, n_d, p_d).
 *
 * @algorithm Restoration Phase Variable Initialization:
 *   SetInitialIterates() initializes all restoration variables:
 *   1. Copy x, s from point where main algorithm entered restoration.
 *   2. Compute n_c, p_c satisfying: c(x) = p_c - n_c (equality residual split).
 *   3. Compute n_d, p_d satisfying: d(x) - s + n_d - p_d ∈ [d_L, d_U].
 *   4. solve_quadratic(): Finds n, p with n,p ≥ 0 minimizing ||n||+||p||.
 *   5. Initialize z, v bound multipliers for n, p bounds (μ/bound).
 *   6. Optionally: y_c, y_d via resto_eq_mult_calculator_ (least squares).
 *
 * @math Slack initialization:
 *   Given residual r = c(x): need n - p = -r with n, p ≥ 0.
 *   If r ≥ 0: p = r + ε, n = ε (constraint violation positive).
 *   If r < 0: n = -r + ε, p = ε (constraint violation negative).
 *   ε = small positive to stay away from bounds.
 *
 * Initialization procedure:
 * 1. Take x, s from the point where main algorithm entered restoration
 * 2. Compute n, p slacks to satisfy: c(x) + n - p = 0
 * 3. Initialize bound multipliers (z, v) for new bounds
 * 4. Optionally compute equality multipliers via least squares
 *
 * The slack computation solves quadratic equation v^2 + 2a*v - b = 0
 * to find feasible n, p values.
 *
 * Key parameter:
 * - constr_mult_init_max_: If initial multiplier estimate exceeds
 *   this, reset to zero to avoid ill-conditioning
 *
 * @see IpDefaultIterateInitializer.hpp for standard cold start
 * @see IpRestoIpoptNLP.hpp for restoration problem structure
 */

#ifndef __IPRESTOITERATEINITIALIZER_HPP__
#define __IPRESTOITERATEINITIALIZER_HPP__

#include "IpIterateInitializer.hpp"
#include "IpEqMultCalculator.hpp"

namespace Ipopt
{
/** Class implementing the default initialization procedure (based
 *  on user options) for the iterates.
 *
 *  It is used at the very beginning of the optimization for
 *  determine the starting point for all variables.
 */
class RestoIterateInitializer: public IterateInitializer
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor.
    *
    *  If eq_mult_calculator is not NULL, it will be
    *  used to compute the initial values for equality constraint
    *  multipliers.
    */
   RestoIterateInitializer(
      const SmartPtr<EqMultiplierCalculator>& eq_mult_calculator
   );

   /** Destructor */
   virtual ~RestoIterateInitializer()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Compute the initial iterates and set the into the curr field
    *  of the ip_data object.
    */
   virtual bool SetInitialIterates();

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
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
   /** Default Constructor */
   RestoIterateInitializer();

   /** Copy Constructor */
   RestoIterateInitializer(
      const RestoIterateInitializer&
   );

   /** Default Assignment Operator */
   void operator=(
      const RestoIterateInitializer&
   );
   ///@}

   /**@name Parameters for bumping x0 */
   ///@{
   /** If max-norm of the initial equality constraint multiplier
    *  estimate is larger than this, the initial y_* variables are
    *  set to zero.
    */
   Number constr_mult_init_max_;
   ///@}

   /** object to be used for the initialization of the equality
    *  constraint multipliers.
    */
   SmartPtr<EqMultiplierCalculator> resto_eq_mult_calculator_;

   /** @name Auxiliary functions */
   ///@{
   /** Method for solving the quadratic vector equation v^2 + 2a*v - b = 0 */
   void solve_quadratic(
      const Vector& a,
      const Vector& b,
      Vector&     v
   );
   ///@}
};

} // namespace Ipopt

#endif
