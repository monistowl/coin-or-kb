// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpMuUpdate.hpp
 * @brief Strategy interface for updating barrier parameter mu
 *
 * MuUpdate is the abstract base for strategies that determine the
 * barrier parameter mu and fraction-to-boundary parameter tau for
 * each iteration of the interior point method.
 *
 * @algorithm Barrier Parameter Update Strategies:
 *   Monotone (classical path-following):
 *     μ_{k+1} = σ·μ_k where σ < 1 (typically σ = 0.1 after good progress).
 *     Conservative: ensures superlinear convergence near solution.
 *   Adaptive (LOQO-style / Mehrotra):
 *     μ = (x^T z / n) · σ where σ from affine direction analysis.
 *     Can increase μ if needed for centrality, more aggressive reduction.
 *   Probing: test multiple μ values, select best progress.
 *
 * @math Central path and barrier parameter:
 *   Barrier problem: min f(x) - μ·Σlog(x_i) s.t. c(x) = 0.
 *   Central path: x(μ)·z(μ) = μe for all μ > 0.
 *   As μ → 0: x(μ) → x* (optimal), z(μ) → z* (optimal multipliers).
 *   Complementarity measure: μ_avg = (x^T z + s^T v) / n.
 *   τ = 1 - μ^θ (θ ≈ 1.5): fraction-to-boundary prevents hitting bounds.
 *
 * @complexity O(1) for monotone update.
 *   O(linear_solve) for predictor-corrector (affine direction needed).
 *   Adaptive may require multiple KKT solves per iteration.
 *
 * @see IpMonotoneMuUpdate.hpp for monotone strategy
 * @see IpAdaptiveMuUpdate.hpp for adaptive strategy
 * @see IpMuOracle.hpp for mu computation oracles
 */

#ifndef __IPMUUPDATE_HPP__
#define __IPMUUPDATE_HPP__

#include "IpAlgStrategy.hpp"

namespace Ipopt
{

/** Abstract Base Class for classes that implement methods for computing
 *  the barrier and fraction-to-the-boundary rule parameter for the
 *  current iteration.
 */
class IPOPTLIB_EXPORT MuUpdate: public AlgorithmStrategyObject
{
public:
   /**@name Constructors / Destructor */
   ///@{
   /** Default Constructor */
   MuUpdate()
   { }

   /** Destructor */
   virtual ~MuUpdate()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

   /** Method for determining the barrier parameter for the next
    *  iteration.
    *
    *  A LineSearch object is passed, so that this method
    *  can call the Reset method in the LineSearch object, for
    *  example when then barrier parameter is changed. This method is
    *  also responsible for setting the fraction-to-the-boundary
    *  parameter tau.  This method returns false if the update could
    *  not be performed and the algorithm should revert to an
    *  emergency fallback mechanism.
    */
   virtual bool UpdateBarrierParameter() = 0;

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
   MuUpdate(
      const MuUpdate&
   );

   /** Default Assignment Operator */
   void operator=(
      const MuUpdate&
   );
   ///@}

};

} // namespace Ipopt

#endif
