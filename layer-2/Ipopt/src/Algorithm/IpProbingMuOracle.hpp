// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpProbingMuOracle.hpp
 * @brief Mehrotra's probing heuristic for barrier parameter selection
 *
 * ProbingMuOracle implements Mehrotra's predictor-corrector approach
 * to compute the barrier parameter mu. This is the strategy used in
 * many interior point codes like LOQO and PCx.
 *
 * Algorithm:
 * 1. Compute affine scaling direction (predictor step) with sigma=0
 * 2. Find maximum step to boundary (alpha_aff)
 * 3. Compute complementarity after affine step: mu_aff
 * 4. Compute centering parameter: sigma = (mu_aff/mu)^3
 * 5. Use sigma in corrector step
 *
 * The centering parameter sigma controls the balance between:
 * - sigma=0: Pure affine scaling (aggressive, may overshoot)
 * - sigma=1: Pure centering (conservative, slow progress)
 *
 * Key parameter:
 * - sigma_max_: Upper bound on sigma to prevent excessive centering
 *
 * @algorithm Mehrotra Predictor-Corrector (Probing):
 * Adaptively select centering parameter by probing pure Newton direction:
 * 1. Solve predictor (affine) system with μ=0 to get Δ_aff
 * 2. Compute α_aff = max step to boundary for affine direction
 * 3. Compute μ_aff = complementarity after affine step:
 *    μ_aff = (x + α_aff·Δx_aff)ᵀ(z + α_aff·Δz_aff) / n
 * 4. Set centering: σ = (μ_aff / μ)³
 * 5. Solve corrector with μ_new = σ · μ_aff
 *
 * @math Centering parameter derivation (Mehrotra):
 *   σ = (μ_aff / μ)³
 *
 * Intuition:
 * - Large α_aff → small μ_aff → small σ → aggressive
 * - Small α_aff → large μ_aff → large σ → centering
 *
 * Cube power: empirically good balance across problem classes.
 * Safeguard: σ ← min(σ, σ_max) prevents excessive centering.
 *
 * @complexity One affine solve O(n³) + O(n) for step length and μ_aff.
 * Total: similar to one Newton iteration.
 *
 * @ref Mehrotra (1992). "On the Implementation of a Primal-Dual Interior
 *   Point Method". SIAM J. Optim. 2(4):575-601.
 *
 * @see IpMuOracle.hpp for base interface
 * @see IpQualityFunctionMuOracle.hpp for alternative mu strategy
 */

#ifndef __IPPROBINGMUORACLE_HPP__
#define __IPPROBINGMUORACLE_HPP__

#include "IpMuOracle.hpp"
#include "IpPDSystemSolver.hpp"

namespace Ipopt
{

/** Implementation of the probing strategy for computing the
 *  barrier parameter.
 */
class ProbingMuOracle: public MuOracle
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor */
   ProbingMuOracle(
      const SmartPtr<PDSystemSolver>& pd_solver
   );

   /** Destructor */
   virtual ~ProbingMuOracle();
   ///@}

   /** overloaded from AlgorithmStrategyObject */
   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Method for computing the value of the barrier parameter that
    *  could be used in the current iteration (using Mehrotra's
    *  probing heuristic).
    */
   virtual bool CalculateMu(
      Number  mu_min,
      Number  mu_max,
      Number& new_mu
   );

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
   ProbingMuOracle();

   /** Copy Constructor */
   ProbingMuOracle(
      const ProbingMuOracle&
   );

   /** Default Assignment Operator */
   void operator=(
      const ProbingMuOracle&
   );
   ///@}

   /** Pointer to the object that should be used to solve the
    *  primal-dual system.
    */
   SmartPtr<PDSystemSolver> pd_solver_;

   /** Auxiliary function for computing the average complementarity
    *  at a point, given step sizes and step
    */
   Number CalculateAffineMu(
      Number                alpha_primal,
      Number                alpha_dual,
      const IteratesVector& step
   );

   /** @name Algorithmic parameters */
   ///@{
   /** safeguarding upper bound on centering parameter sigma */
   Number sigma_max_;
   ///@}
};

} // namespace Ipopt

#endif
