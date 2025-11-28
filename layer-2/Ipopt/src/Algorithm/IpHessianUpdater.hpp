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
 * Options:
 * - Exact Hessian: Uses second derivatives from NLP (hessian_approximation=exact)
 * - Limited-memory BFGS: L-BFGS approximation (hessian_approximation=limited-memory)
 *
 * For quasi-Newton methods, the updater maintains history of
 * {s_k, y_k} pairs and computes B_k or H_k approximations.
 *
 * Implementations:
 * - ExactHessianUpdater: Evaluates exact Hessian from NLP
 * - LimMemQuasiNewtonUpdater: L-BFGS or L-SR1 approximation
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
