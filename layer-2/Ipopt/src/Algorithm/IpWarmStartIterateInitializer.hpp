// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter              IBM    2005-04-01

/**
 * @file IpWarmStartIterateInitializer.hpp
 * @brief Warm start initialization from previous solution
 *
 * WarmStartIterateInitializer initializes IPM iterates from a
 * previously computed solution, enabling faster convergence for
 * related problems (e.g., MPC, parametric optimization).
 *
 * Warm start sources:
 * - warm_start_entire_iterate_: Use GetWarmStartIterate() from NLP
 * - Otherwise: Use initialization vectors from NLP
 *
 * Processing steps:
 * 1. Push primals away from bounds (warm_start_bound_push/frac_)
 * 2. Push slacks (warm_start_slack_bound_push/frac_)
 * 3. Clip multipliers (warm_start_mult_init_max_)
 * 4. Ensure bound multipliers positive (warm_start_mult_bound_push_)
 *
 * Target mu adjustment (warm_start_target_mu_):
 * - Adjusts slack/multiplier pairs toward target complementarity
 * - process_target_mu(): Scales to achieve s*z ≈ target_mu
 * - adapt_to_target_mu(): Fine-tunes pairing
 *
 * Key parameters:
 * - warm_start_bound_push_: Absolute bound push
 * - warm_start_bound_frac_: Relative bound push
 * - warm_start_mult_init_max_: Maximum multiplier magnitude
 * - warm_start_target_mu_: Target barrier parameter
 *
 * @algorithm IPM Warm Start Initialization:
 * Initialize from previous solution for faster convergence:
 * 1. Load iterate from GetWarmStartIterate() or stored vectors
 * 2. Push primals from bounds: x ← max(x_L + κ, min(x, x_U - κ))
 *    where κ = max(warm_start_bound_push, frac·max(1, |x|))
 * 3. Push slacks similarly
 * 4. Clip multipliers: y ← sign(y)·min(|y|, mult_init_max)
 * 5. Ensure bound multipliers positive: z ← max(z, mult_bound_push)
 * 6. If target_mu set, adjust (s,z) pairs to achieve s·z ≈ μ_target:
 *    a. Scale: (s,z) ← √(μ_target/(s·z))·(s,z)
 *    b. Fine-tune via adapt_to_target_mu()
 *
 * @math Target μ adjustment (process_target_mu):
 * Given (s_i, z_i) with s_i·z_i ≠ μ_target:
 *   ratio = √(μ_target / (s_i·z_i))
 *   s_i ← ratio·s_i,  z_i ← ratio·z_i
 * Preserves sign while achieving s_i·z_i = μ_target.
 *
 * @complexity O(n + m) for variable processing. No linear solves.
 * Warm start typically reduces iterations by 50-90% for related problems.
 *
 * @see IpIterateInitializer.hpp for the base interface
 * @see IpDefaultIterateInitializer.hpp for cold start
 */

#ifndef __IPWARMSTARTITERATEINITIALIZER_HPP__
#define __IPWARMSTARTITERATEINITIALIZER_HPP__

#include "IpIterateInitializer.hpp"
#include "IpEqMultCalculator.hpp"

namespace Ipopt
{

/** Class implementing an initialization procedure for warm starts. */
class WarmStartIterateInitializer: public IterateInitializer
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor. */
   WarmStartIterateInitializer();

   /** Destructor */
   virtual ~WarmStartIterateInitializer()
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
   /** Copy Constructor */
   WarmStartIterateInitializer(
      const WarmStartIterateInitializer&
   );

   /** Default Assignment Operator */
   void operator=(
      const WarmStartIterateInitializer&
   );
   ///@}

   /**@name Algorithmic Parameters */
   ///@{
   /** Absolute parameters for bumping x0 in warm start mode */
   Number warm_start_bound_push_;

   /** Relative parameters for bumping x0 in warm start mode */
   Number warm_start_bound_frac_;

   /** Absolute parameters for bumping s0 in warm start mode */
   Number warm_start_slack_bound_push_;

   /** Relative parameters for bumping s0 in warm start mode */
   Number warm_start_slack_bound_frac_;

   /** Parameters for bumping initial bound multipliers */
   Number warm_start_mult_bound_push_;

   /** Maximal size of entries in bound and equality constraint
    *  multipliers in magnitude.
    *
    *  If chosen less of equal to zero, no upper limit is imposed.
    *  Otherwise, the entries exceeding the given limit are set
    *  to the value closest to the limit.
    */
   Number warm_start_mult_init_max_;

   /** Target values for the barrier parameter in warm start option. */
   Number warm_start_target_mu_;

   /** Indicator for which method in the NLP should be used to get
    *  the warm start.
    */
   bool warm_start_entire_iterate_;
   ///@}

   /** @name Auxiliary functions */
   ///@{
   void process_target_mu(
      Number                  factor,
      const Vector&           curr_vars,
      const Vector&           curr_slacks,
      const Vector&           curr_mults,
      const Matrix&           P,
      SmartPtr<const Vector>& ret_vars,
      SmartPtr<const Vector>& ret_mults
   );

   void adapt_to_target_mu(
      Vector& new_s,
      Vector& new_z,
      Number  target_mu
   );
   ///@}
};

} // namespace Ipopt

#endif
