// Copyright (C) 2008, 2011 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2008-09-05

/**
 * @file IpInexactNewtonNormal.hpp
 * @brief Newton normal step from slack-scaled augmented system
 *
 * InexactNewtonNormalStep computes the normal step component by
 * solving a reduced system derived from the slack-scaled KKT system.
 *
 * @algorithm Newton Normal Step:
 *   ComputeNewtonNormalStep(newton_x, newton_s):
 *   1. Form reduced system in slack-scaled space:
 *      [0, J_c^T, J_d^T; J_c, 0, 0; J_d, 0, -I] [Δx; Δy_c; Δy_d] = -[0; c; d-s].
 *   2. Solve via AugSystemSolver (may be iterative).
 *   3. Return slack-scaled step (caller transforms back).
 *   Note: W=0 in normal step—only feasibility, no optimality.
 *
 * @math Minimum-norm feasibility step:
 *   Normal step minimizes ||Δx||² subject to J·Δx + c = 0 (linearized).
 *   Closed form: Δx_n = -J^T·(J·J^T)^{-1}·c = -J^†·c.
 *   Augmented system equivalent to computing pseudo-inverse times residual.
 *   Slack scaling: Δs̃ = S^{-1}·Δs for better conditioning.
 *
 * @complexity O(nnz·k) for iterative solve, O(m²n) worst-case direct.
 *   Typically k iterations where k depends on preconditioner quality.
 *
 * @see IpInexactDoglegNormal.hpp for dogleg wrapper using this
 * @see IpAugSystemSolver.hpp for the underlying solver interface
 */

#ifndef __IPINEXACTNEWTONNORMAL_HPP__
#define __IPINEXACTNEWTONNORMAL_HPP__

#include "IpAlgStrategy.hpp"
#include "IpAugSystemSolver.hpp"
#include "IpInexactCq.hpp"

namespace Ipopt
{
/** Compute the "Newton" normal step from the (slack-scaled)
 *  augmented system.
 */
class InexactNewtonNormalStep: public AlgorithmStrategyObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor */
   InexactNewtonNormalStep(
      SmartPtr<AugSystemSolver> aug_solver
   );

   /** Destructor */
   virtual ~InexactNewtonNormalStep();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Method for computing the normal step.
    *
    *  The computed step is
    *  returned as normal_x and normal_s, for the x and s variables,
    *  respectively.  These quantities are not in the original space,
    *  but in the space scaled by the slacks.  If the step cannot be
    *  computed, this method returns false.
    */
   virtual bool ComputeNewtonNormalStep(
      Vector& newton_x,
      Vector& newton_s
   );

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

protected:
   /** Method to easily access Inexact data */
   InexactData& InexData()
   {
      InexactData& inexact_data = static_cast<InexactData&>(IpData().AdditionalData());
      DBG_ASSERT(dynamic_cast<InexactData*>(&IpData().AdditionalData()));
      return inexact_data;
   }

   /** Method to easily access Inexact calculated quantities */
   InexactCq& InexCq()
   {
      InexactCq& inexact_cq = static_cast<InexactCq&>(IpCq().AdditionalCq());
      DBG_ASSERT(dynamic_cast<InexactCq*>(&IpCq().AdditionalCq()));
      return inexact_cq;
   }

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
   InexactNewtonNormalStep();

   /** Copy Constructor */
   InexactNewtonNormalStep(
      const InexactNewtonNormalStep&);

   /** Overloaded Assignment Operator */
   void operator=(
      const InexactNewtonNormalStep&
   );
   ///@}

   /** Object to be used to solve the augmented system */
   SmartPtr<AugSystemSolver> aug_solver_;
};

} // namespace Ipopt

#endif
