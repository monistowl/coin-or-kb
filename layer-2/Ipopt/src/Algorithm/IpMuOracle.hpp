// Copyright (C) 2004, 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpMuOracle.hpp
 * @brief Strategy interface for suggesting barrier parameter values
 *
 * MuOracle is the abstract interface for components that compute
 * suggested values for the barrier parameter mu in adaptive (non-monotone)
 * barrier updates.
 *
 * @algorithm Barrier Parameter Oracle Interface:
 *   CalculateMu(mu_min, mu_max) → new_mu ∈ [mu_min, mu_max]:
 *   1. Analyze current iterate: complementarity gap, progress, quality.
 *   2. Compute target mu balancing centrality vs progress toward optimum.
 *   3. Clamp to [mu_min, mu_max] to respect globalization bounds.
 *   4. Return false if computation fails (e.g., linear solve needed).
 *
 * @math Adaptive vs monotone barrier strategies:
 *   Monotone: μ_{k+1} = σ·μ_k with fixed σ < 1 (predictable decrease).
 *   Adaptive: μ chosen per-iteration to balance feasibility and optimality.
 *   Quality function oracles: min_σ q(σ) where q measures solution quality.
 *   Probing oracles: try μ candidates, pick best by predicted progress.
 *
 * @complexity O(linear_solve) per oracle call for predictor-based methods.
 *   Simpler oracles (LOQO-style) are O(1) using only current complementarity.
 *
 * Interface:
 * - CalculateMu(mu_min, mu_max, new_mu): Compute suggested mu in [mu_min, mu_max]
 * - Returns false if suggestion cannot be computed (e.g., linear solve fails)
 *
 * Implementations:
 * - QualityFunctionMuOracle: Minimize quality function over sigma
 * - ProbingMuOracle: Try candidate mu values and select best
 * - LoqoMuOracle: LOQO-style adaptive rule
 *
 * Usage in AdaptiveMuUpdate:
 * - free_mu_oracle_: Computes mu in free (non-monotone) mode
 * - fix_mu_oracle_: Optional, computes mu when switching to fixed mode
 *
 * The oracle is called each iteration in free mode. If it returns
 * false or the suggested mu doesn't satisfy globalization, the
 * algorithm may switch to fixed (monotone) mode.
 *
 * @see IpAdaptiveMuUpdate.hpp for usage
 * @see IpQualityFunctionMuOracle.hpp for quality function approach
 */

#ifndef __IPMUORACLE_HPP__
#define __IPMUORACLE_HPP__

#include "IpAlgStrategy.hpp"

namespace Ipopt
{

/** Abstract Base Class for classes that are able to compute a
 *  suggested value of the barrier parameter that can be used
 *  as an oracle in the NonmontoneMuUpdate class.
 */
class MuOracle: public AlgorithmStrategyObject
{
public:
   /**@name Constructors / Destructor */
   ///@{
   /** Default Constructor */
   MuOracle()
   { }

   /** Destructor */
   virtual ~MuOracle()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

   /** Method for computing the value of the barrier parameter that
    *  could be used in the current iteration.
    *
    *  Here, mu_min and
    *  mu_max are the lower and upper bounds on acceptable values for
    *  the barrier parameter.  The new value of mu is returned in
    *  new_mu, and the method returns false if a new value could not
    *  be determined (e.g., because the linear system could not be
    *  solved for a predictor step).
    */
   virtual bool CalculateMu(
      Number  mu_min,
      Number  mu_max,
      Number& new_mu
   ) = 0;

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
   MuOracle(
      const MuOracle&
   );

   void operator=(
      const MuOracle&
   );
   ///@}

};

} // namespace Ipopt

#endif
