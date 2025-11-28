// Copyright (C) 2005, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2005-12-26

/**
 * @file IpExactHessianUpdater.hpp
 * @brief Hessian updater using exact second derivatives from NLP
 *
 * ExactHessianUpdater is a trivial HessianUpdater implementation that
 * simply retrieves the exact Hessian of the Lagrangian from the NLP
 * at each iteration.
 *
 * The Hessian is:
 *   W = ∇²f(x) + Σ y_c[i] * ∇²c_i(x) + Σ y_d[j] * ∇²d_j(x)
 *
 * UpdateHessian() method:
 * - Calls IpoptNLP::h() with current x and multipliers
 * - Stores result in IpData for use by PDSystemSolver
 *
 * Requirements:
 * - User NLP must provide eval_h callback (TNLP) or h() method
 * - Option hessian_approximation must be "exact"
 *
 * Advantages over quasi-Newton:
 * - Quadratic local convergence rate
 * - Accurate curvature for non-convex problems
 * - Better inertia detection
 *
 * Disadvantages:
 * - User must implement second derivatives
 * - More function evaluations per iteration
 * - Hessian evaluation can be expensive
 *
 * @see IpHessianUpdater.hpp for the base interface
 * @see IpLimMemQuasiNewtonUpdater.hpp for L-BFGS alternative
 */

#ifndef __IPEXACTHESSIANUPDATER_HPP__
#define __IPEXACTHESSIANUPDATER_HPP__

#include "IpHessianUpdater.hpp"

namespace Ipopt
{

/** Implementation of the HessianUpdater for the use of exact second
 *  derivatives.
 */
class ExactHessianUpdater: public HessianUpdater
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   ExactHessianUpdater()
   { }

   /** Destructor */
   virtual ~ExactHessianUpdater()
   { }
   ///@}

   /** overloaded from AlgorithmStrategyObject */
   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Update the Hessian based on the current information in IpData. */
   virtual void UpdateHessian();

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
   ExactHessianUpdater(
      const ExactHessianUpdater&
   );

   /** Default Assignment Operator */
   void operator=(
      const ExactHessianUpdater&
   );
   ///@}

};

} // namespace Ipopt

#endif
