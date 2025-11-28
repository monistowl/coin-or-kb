// Copyright (C) 2004, 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter              IBM    2004-09-24

/**
 * @file IpDefaultIterateInitializer.hpp
 * @brief Standard initialization procedure for IPM iterates
 *
 * DefaultIterateInitializer computes starting points for all primal
 * and dual variables based on user options and problem bounds.
 *
 * Primal initialization (x, s):
 * - Start from user-provided x0 or NLP default
 * - Push away from bounds: x_new = max(x_L + ε, min(x, x_U - ε))
 * - bound_push_, bound_frac_: Absolute/relative push parameters
 * - least_square_init_primal_: Fit linearized constraints
 *
 * Dual initialization:
 * - Equality multipliers (y_c, y_d): Least-squares or zero
 * - eq_mult_calculator_: Computes min ||y|| s.t. KKT gradient
 * - constr_mult_init_max_: Reject large multiplier estimates
 * - Bound multipliers (z_L, z_U, v_L, v_U):
 *   - B_CONSTANT: bound_mult_init_val_
 *   - B_MU_BASED: mu_init_ / slack
 *
 * Warm start:
 * - warm_start_init_point_: Use warm_start_initializer_ instead
 * - Delegates to WarmStartIterateInitializer
 *
 * Static utilities:
 * - push_variables(): Move point away from bounds
 * - least_square_mults(): Compute y from gradient conditions
 *
 * @see IpIterateInitializer.hpp for the base interface
 * @see IpWarmStartIterateInitializer.hpp for warm start
 * @see IpEqMultCalculator.hpp for multiplier computation
 */

#ifndef __IPDEFAULTITERATEINITIALIZER_HPP__
#define __IPDEFAULTITERATEINITIALIZER_HPP__

#include "IpIterateInitializer.hpp"
#include "IpEqMultCalculator.hpp"
#include "IpAugSystemSolver.hpp"

namespace Ipopt
{

/** Class implementing the default initialization procedure (based
 *  on user options) for the iterates.
 *
 *  It is used at the very beginning of the optimization for
 *  determine the starting point for all variables.
 */
class DefaultIterateInitializer: public IterateInitializer
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor.
    *
    *  If eq_mult_calculator is not NULL, it will be
    *  used to compute the initial values for equality constraint
    *  multipliers.  If warm_start_initializer is not NULL, it will
    *  be used to compute the initial values if the option
    *  warm_start_init_point is chosen.
    */
   DefaultIterateInitializer(
      const SmartPtr<EqMultiplierCalculator>& eq_mult_calculator,
      const SmartPtr<IterateInitializer>&     warm_start_initializer,
      const SmartPtr<AugSystemSolver>         aug_system_solver = NULL
   );

   /** Destructor */
   virtual ~DefaultIterateInitializer()
   { }
   ///@}

   /** overloaded from AlgorithmStrategyObject */
   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Compute the initial iterates and set the into the curr field
    *  of the ip_data object.
    */
   virtual bool SetInitialIterates();

   /** Auxiliary function for moving the initial point.
    *
    *  This is declared static so that it can also be used from
    *  WarmStartIterateInitializer.
    */
   static void push_variables(
      const Journalist&       jnlst,
      Number                  bound_push,
      Number                  bound_frac,
      std::string             name,
      const Vector&           orig_x,
      SmartPtr<const Vector>& new_x,
      const Vector&           x_L,
      const Vector&           x_U,
      const Matrix&           Px_L,
      const Matrix&           Px_U
   );

   /** Auxiliary function for computing least_square multipliers.
    *
    *  The multipliers are computed based on the values in the trial
    *  fields (current is overwritten).  On return, the multipliers
    *  are in the trial fields as well.  The value of
    *  constr_mult_init_max determines if the computed least square
    *  estimate should be used, or if the initial multipliers are set
    *  to zero.
    */
   static void least_square_mults(
      const Journalist&                       jnlst,
      IpoptNLP&                               ip_nlp,
      IpoptData&                              ip_data,
      IpoptCalculatedQuantities&              ip_cq,
      const SmartPtr<EqMultiplierCalculator>& eq_mult_calculator,
      Number                                  constr_mult_init_max
   );

   ///@{
   static void RegisterOptions(
      SmartPtr<RegisteredOptions> reg_options
   );
   ///@}

   /** @name Enums of option values */
   ///@{
   enum BoundMultInitMethod
   {
      B_CONSTANT = 0,
      B_MU_BASED
   };
   ///@}
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
   DefaultIterateInitializer();

   /** Copy Constructor */
   DefaultIterateInitializer(
      const DefaultIterateInitializer&
   );

   /** Default Assignment Operator */
   void operator=(
      const DefaultIterateInitializer&
   );
   ///@}

   /**@name Algorithmic Parameters */
   ///@{
   /** Absolute parameter for bumping x0 */
   Number bound_push_;
   /** Relative parameter for bumping x0 */
   Number bound_frac_;
   /** Absolute parameter for bumping s0 */
   Number slack_bound_push_;
   /** Relative parameter for bumping s0 */
   Number slack_bound_frac_;

   /** If max-norm of the initial equality constraint multiplier
    *  estimate is larger than this, the initial y_* variables are
    *  set to zero. */
   Number constr_mult_init_max_;
   /** Initial value for all bound multipliers. */
   Number bound_mult_init_val_;
   /** Flag indicating whether warm_start_initializer should be used
    *  instead of the default initialization */
   bool warm_start_init_point_;
   /** Flag indicating whether the primal variables should be
    *  initialized as least square fit for the linearized
    *  constraints */
   bool least_square_init_primal_;
   /** Flag indicating whether all dual variables should be
    *  initialized as least square fit for the linearized
    *  dual infeasibility */
   bool least_square_init_duals_;
   /** Flag indicating how bound multipliers are initialized */
   BoundMultInitMethod bound_mult_init_method_;
   /** Initial value of barrier parameter */
   Number mu_init_;
   ///@}

   /** object to be used for the initialization of the equality
    *  constraint multipliers.
    */
   SmartPtr<EqMultiplierCalculator> eq_mult_calculator_;

   /** object to be used for a warm start initialization */
   SmartPtr<IterateInitializer> warm_start_initializer_;

   /** Object for solving the augmented system.
    *
    *  This is only required if we use the least square initialization
    *  of primal and all dual variables.
    */
   SmartPtr<AugSystemSolver> aug_system_solver_;

   /** Auxiliary method for computing least square primal variables */
   bool CalculateLeastSquarePrimals(
      Vector& x_ls,
      Vector& s_ls
   );

   /** Auxiliary method for computing least square dual variables */
   bool CalculateLeastSquareDuals(
      Vector& zL_new,
      Vector& zU_new,
      Vector& vL_new,
      Vector& vU_new,
      Vector& yc_new,
      Vector& yd_new
   );
};

} // namespace Ipopt

#endif
