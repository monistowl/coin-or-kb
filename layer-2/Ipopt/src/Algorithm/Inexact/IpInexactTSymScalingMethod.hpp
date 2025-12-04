// Copyright (C) 2009 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter, Frank E. Curtis         IBM    2009-06-12
//               (based on IpMc19TSymScalingMethod.hpp rev 699)

/**
 * @file IpInexactTSymScalingMethod.hpp
 * @brief Slack-based matrix scaling for inexact algorithm
 *
 * InexactTSymScalingMethod computes symmetric scaling factors for the
 * augmented system, using current slack values for the inexact algorithm.
 *
 * @algorithm Slack-Based Symmetric Scaling:
 *   ComputeSymTScalingFactors(A) → diagonal scaling D:
 *   1. For rows/cols corresponding to slack variables:
 *      D[i] = 1/√(curr_scaling_slacks[i]) from InexactCq.
 *   2. For other rows/cols: D[i] = 1 (no scaling).
 *   3. Scale matrix: Ã = D·A·D (symmetric similarity transform).
 *   Result: better conditioned system for iterative solver.
 *
 * @math Slack scaling rationale:
 *   Augmented system has (1,1) block W and (2,2) block with slack terms.
 *   Slack values s can vary widely (near bounds vs interior).
 *   Scaling by s^{-1/2} equilibrates the blocks.
 *   Improves convergence of Krylov methods (GMRES, CG).
 *
 * @complexity O(nnz) to apply scaling factors.
 *   Scaling factors from cached InexactCq quantities.
 *
 * @see IpTSymScalingMethod.hpp for base scaling interface
 * @see IpInexactCq.hpp for curr_scaling_slacks computation
 */

#ifndef __IPINEXACTTSYMSCALINGMETHOD_HPP__
#define __IPINEXACTTSYMSCALINGMETHOD_HPP__

#include "IpUtils.hpp"
#include "IpTSymScalingMethod.hpp"
#include "IpInexactCq.hpp"

namespace Ipopt
{

/** Class for the method for computing scaling factors for symmetric
 *  matrices in triplet format, specifically for the inexaxct algorithm.
 *  The scaling is only considering the current slacks.
 */
class InexactTSymScalingMethod: public TSymScalingMethod
{
public:
   /** @name Constructor/Destructor */
   ///@{
   InexactTSymScalingMethod()
   { }

   virtual ~InexactTSymScalingMethod()
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
    * implicit creation/calling).
    *
    * These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Copy Constructor */
   InexactTSymScalingMethod(
      const InexactTSymScalingMethod&
   );

   /** Overloaded Assignment Operator */
   void operator=(
      const InexactTSymScalingMethod&
   );

   /** Method to easily access Inexact calculated quantities */
   InexactCq& InexCq()
   {
      InexactCq& inexact_cq = static_cast<InexactCq&>(IpCq().AdditionalCq());
      DBG_ASSERT(dynamic_cast<InexactCq*>(&IpCq().AdditionalCq()));
      return inexact_cq;
   }

};

} // namespace Ipopt

#endif
