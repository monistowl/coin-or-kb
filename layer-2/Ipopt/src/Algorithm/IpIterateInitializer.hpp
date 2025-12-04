// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter              IBM    2004-09-24

/**
 * @file IpIterateInitializer.hpp
 * @brief Strategy interface for computing initial iterates
 *
 * IterateInitializer is the abstract base for strategies that
 * compute the starting point (x, s, y_c, y_d, z_L, z_U, v_L, v_U)
 * for the interior point algorithm.
 *
 * @algorithm Starting Point Initialization:
 *   1. Primal variables x:
 *      - Use user-provided x₀ if available.
 *      - Project to bounds: x ← max(x_L + κ, min(x, x_U - κ)).
 *      - Push away from bounds by κ = bound_push·max(1, |x_L|).
 *   2. Slack variables s: s ← d(x), projected to [d_L + κ, d_U - κ].
 *   3. Dual variables y_c, y_d:
 *      - Least squares: min ||∇f - J^T y||² to estimate multipliers.
 *      - Or use user-provided values if warm starting.
 *   4. Bound multipliers z_L, z_U, v_L, v_U:
 *      - From complementarity: z_L = μ/(x - x_L), z_U = μ/(x_U - x).
 *      - Clamp to [bound_mult_init_val, ∞) for stability.
 *
 * @math Initial complementarity products:
 *   Want (x - x_L)·z_L ≈ μ, so z_L = μ / (x - x_L).
 *   Initial μ from average: μ₀ = (x - x_L)^T z_L / n_bounds.
 *   Slack complementarity: (s - d_L)·v_L ≈ μ similarly.
 *
 * @complexity O(n + m) for cold start (vector operations).
 *   O(m²) for least-squares dual initialization if done explicitly.
 *   Warm start: O(n + m) using provided values directly.
 *
 * @see IpDefaultIterateInitializer.hpp for standard initialization
 * @see IpWarmStartIterateInitializer.hpp for warm starts
 */

#ifndef __IPITERATEINITIALIZER_HPP__
#define __IPITERATEINITIALIZER_HPP__

#include "IpAlgStrategy.hpp"
#include "IpIpoptNLP.hpp"
#include "IpIpoptData.hpp"
#include "IpIpoptCalculatedQuantities.hpp"

namespace Ipopt
{

/** Base class for all methods for initializing the iterates. */
class IPOPTLIB_EXPORT IterateInitializer: public AlgorithmStrategyObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   IterateInitializer()
   { }

   /** Default destructor */
   virtual ~IterateInitializer()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

   /** Compute the initial iterates and set the into the curr field
    *  of the ip_data object. */
   virtual bool SetInitialIterates() = 0;

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
   IterateInitializer(
      const IterateInitializer&
   );

   /** Default Assignment Operator */
   void operator=(
      const IterateInitializer&
   );
   ///@}

};

} // namespace Ipopt

#endif
