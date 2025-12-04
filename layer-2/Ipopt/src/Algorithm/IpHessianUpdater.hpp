// Copyright (C) 2005, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2005-12-26

/**
 * @file IpHessianUpdater.hpp
 * @brief Strategy interface for Hessian computation/approximation
 *
 * HessianUpdater is the abstract base for strategies that provide
 * the Hessian of the Lagrangian (or an approximation) to the algorithm.
 * The result is stored in IpData.W().
 *
 * @algorithm Hessian Approximation Strategies:
 *   Exact: W = ∇²_xx L(x, y) evaluated via NLP second derivatives.
 *   L-BFGS: W ≈ D + Σ (yᵢyᵢᵀ/yᵢᵀsᵢ - Bsᵢsᵢᵀ/sᵢᵀBsᵢ) (secant updates).
 *   L-SR1: W ≈ D + Σ ((y-Bs)(y-Bs)ᵀ/(y-Bs)ᵀs) (symmetric rank-1).
 *   Store m recent {sₖ, yₖ} pairs where sₖ = xₖ₊₁ - xₖ, yₖ = ∇Lₖ₊₁ - ∇Lₖ.
 *   Limited memory: O(m·n) storage vs O(n²) for full Hessian.
 *
 * @math Hessian of Lagrangian:
 *   L(x,y) = f(x) - y_c^T c(x) - y_d^T d(x) (Lagrangian function).
 *   W = ∇²f(x) - Σᵢ yc_i·∇²c_i(x) - Σⱼ yd_j·∇²d_j(x).
 *   Secant equation: B_{k+1}·s_k = y_k (quasi-Newton condition).
 *   Positive definiteness: BFGS maintains if y^T s > 0; damped BFGS if not.
 *
 * @complexity Exact: O(eval_hess) user-provided, often O(nnz_H).
 *   L-BFGS/L-SR1: O(m·n) per update, O(m·n) per matvec via two-loop.
 *   Trade-off: exact more accurate, L-BFGS cheaper when n >> m pairs.
 *
 * @see IpExactHessianUpdater.hpp for exact Hessian
 * @see IpLimMemQuasiNewtonUpdater.hpp for quasi-Newton
 * @see IpLowRankUpdateSymMatrix.hpp for L-BFGS matrix representation
 */

#ifndef __IPHESSIANUPDATER_HPP__
#define __IPHESSIANUPDATER_HPP__

#include "IpAlgStrategy.hpp"

namespace Ipopt
{

/** Abstract base class for objects responsible for updating the
 *  Hessian information.
 *
 *  This can be done using exact second
 *  derivatives from the NLP, or by a quasi-Newton Option.  The
 *  result is put into the W field in IpData.
 */
class IPOPTLIB_EXPORT HessianUpdater: public AlgorithmStrategyObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   HessianUpdater()
   { }

   /** Destructor */
   virtual ~HessianUpdater()
   { }
   ///@}

   /** overloaded from AlgorithmStrategyObject */
   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

   /** Update the Hessian based on the current information in IpData,
    *  and possibly on information from previous calls.
    */
   virtual void UpdateHessian() = 0;

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
   HessianUpdater(
      const HessianUpdater&
   );

   /** Default Assignment Operator */
   void operator=(
      const HessianUpdater&
   );
   ///@}

};

} // namespace Ipopt

#endif
