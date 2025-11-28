// Copyright (C) 2009 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter                   IBM    2009-11-13
//               (based on IpInexactTSymScalingMethod.hpp)

/**
 * @file IpSlackBasedTSymScalingMethod.hpp
 * @brief Simple scaling based on current slack values
 *
 * SlackBasedTSymScalingMethod computes scaling factors using only
 * the current slack values, without requiring external HSL routines.
 * Designed for use with inexact/iterative linear solvers.
 *
 * Unlike MC19 which performs full equilibration, this method uses
 * a simpler heuristic based on:
 * - Current slack variable values s
 * - Diagonal elements of the KKT system
 *
 * Benefits:
 * - No external library dependencies
 * - Lightweight computation
 * - Suitable when full equilibration is unnecessary
 *
 * Limitations:
 * - May not achieve as good conditioning as MC19
 * - Best for problems where slacks dominate scaling needs
 *
 * @see IpTSymScalingMethod.hpp for base interface
 * @see IpMc19TSymScalingMethod.hpp for full equilibration
 */

#ifndef __IPSLACKBASEDTSYMSCALINGMETHOD_HPP__
#define __IPSLACKBASEDTSYMSCALINGMETHOD_HPP__

#include "IpUtils.hpp"
#include "IpTSymScalingMethod.hpp"

namespace Ipopt
{

/** Class for the method for computing scaling factors for symmetric
 *  matrices in triplet format, specifically for the inexact algorithm.
 *  The scaling is only considering the current slacks.
 */
class SlackBasedTSymScalingMethod: public TSymScalingMethod
{
public:
   /** @name Constructor/Destructor */
   ///@{
   SlackBasedTSymScalingMethod()
   { }

   virtual ~SlackBasedTSymScalingMethod()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Method for computing the symmetric scaling factors, given the
    *  symmetric matrix in triplet (MA27) format.
    */
   virtual bool ComputeSymTScalingFactors(
      Index         n,
      Index         nnz,
      const Index*  airn,
      const Index*  ajcn,
      const Number* a,
      Number*       scaling_factors
   );

private:
   /**@name Default Compiler Generated Methods (Hidden to avoid
    * implicit creation/calling).  These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called. */
   ///@{
   /** Copy Constructor */
   SlackBasedTSymScalingMethod(
      const SlackBasedTSymScalingMethod&
   );

   /** Default Assignment Operator */
   void operator=(
      const SlackBasedTSymScalingMethod&
   );
};

} // namespace Ipopt

#endif
