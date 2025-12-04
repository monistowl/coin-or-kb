// Copyright (C) 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2008-08-31

/**
 * @file IpInexactNormalStepCalc.hpp
 * @brief Abstract base class for normal step computation
 *
 * InexactNormalStepCalculator defines the interface for computing
 * the normal step component in the inexact Newton decomposition.
 *
 * @algorithm Normal Step Interface:
 *   ComputeNormalStep(normal_x, normal_s):
 *   1. Compute step toward constraint feasibility.
 *   2. Return (Δx_n, Δs_n) satisfying feasibility reduction target.
 *   3. Target: ||c(x) + J·Δx_n|| ≤ κ·||c(x)|| for some κ < 1.
 *   Implementations: dogleg (trust region), Newton (direct solve).
 *
 * @math Normal step goal:
 *   Minimize ||Δx_n||² subject to linearized feasibility improvement.
 *   Δx_n = argmin ||Δx||² s.t. ||J·Δx + c|| ≤ κ·||c|| (trust region).
 *   Or: Δx_n = -J^†·c(x) (minimum norm, pseudo-inverse solution).
 *   Normal step lies in range(J^T), orthogonal to null(J).
 *
 * @complexity Implementation-dependent: O(nnz·k) for iterative.
 *
 * @see IpInexactDoglegNormal.hpp for dogleg trust-region implementation
 * @see IpInexactNewtonNormal.hpp for Newton-based implementation
 */

#ifndef __IPINEXACTNORMALSTEPCALC_HPP__
#define __IPINEXACTNORMALSTEPCALC_HPP__

#include "IpAlgStrategy.hpp"
#include "IpInexactCq.hpp"

namespace Ipopt
{
/** Base class for computing the normal step for the inexact step
 *  calculation algorithm.
 */
class InexactNormalStepCalculator: public AlgorithmStrategyObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   InexactNormalStepCalculator()
   { }

   /** Destructor */
   virtual ~InexactNormalStepCalculator()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

   /** Method for computing the normal step.
    *
    *  The computed step is
    *  returned as normal_x and normal_s, for the x and s variables,
    *  respectively.  These quantities are not slack-scaled.  If the
    *  step cannot be computed, this method returns false.
    */
   virtual bool ComputeNormalStep(
      SmartPtr<Vector>& normal_x,
      SmartPtr<Vector>& normal_s
   ) = 0;

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
   /** Copy Constructor */
   InexactNormalStepCalculator(
      const InexactNormalStepCalculator&
   );

   /** Overloaded Assignment Operator */
   void operator=(
      const InexactNormalStepCalculator&
   );
   ///@}
};

} // namespace Ipopt

#endif
