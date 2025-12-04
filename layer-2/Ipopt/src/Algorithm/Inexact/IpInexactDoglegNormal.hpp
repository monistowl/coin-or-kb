// Copyright (C) 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2008-08-31

/**
 * @file IpInexactDoglegNormal.hpp
 * @brief Dogleg trust region method for normal step computation
 *
 * InexactDoglegNormalStep computes the normal step using a dogleg
 * approach that combines steepest descent and Newton directions
 * within a trust region.
 *
 * @algorithm Dogleg Normal Step:
 *   ComputeNormalStep():
 *   1. Compute Cauchy point: x_c = x - α_c·A^T·c (steepest descent).
 *      α_c = ||A^T·c||² / ||A·A^T·c||² (optimal step along gradient).
 *   2. Compute Newton point: x_n via InexactNewtonNormalStep.
 *   3. If ||x_c - x|| ≥ ω (trust region): return scaled Cauchy step.
 *   4. If ||x_n - x|| ≤ ω: return Newton step (inside trust region).
 *   5. Else: interpolate on dogleg path between Cauchy and Newton.
 *      x = x_c + τ·(x_n - x_c) where τ chosen so ||x - x₀|| = ω.
 *
 * @math Dogleg path geometry:
 *   Dogleg: piecewise linear path from 0 → Cauchy → Newton.
 *   Trust region: ||Δx|| ≤ ω (current trust radius).
 *   ω updated based on ratio: ρ = actual_reduction / predicted_reduction.
 *   If ρ high → expand ω; if ρ low → contract ω.
 *
 * @complexity Cauchy point: O(nnz) for A^T·c and A·(A^T·c).
 *   Newton point: O(nnz·k) for iterative solve.
 *   Interpolation: O(n) for linear combination.
 *
 * @see IpInexactNewtonNormal.hpp for Newton step computation
 * @see IpInexactNormalStepCalc.hpp for base normal step interface
 */

#ifndef __IPINEXACTDOGLEGNORMAL_HPP__
#define __IPINEXACTDOGLEGNORMAL_HPP__

#include "IpInexactNormalStepCalc.hpp"
#include "IpInexactNewtonNormal.hpp"
#include "IpInexactNormalTerminationTester.hpp"

namespace Ipopt
{
/** Compute the normal step using a dogleg approach.
 */
class InexactDoglegNormalStep: public InexactNormalStepCalculator
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   InexactDoglegNormalStep(
      SmartPtr<InexactNewtonNormalStep>        newton_step,
      SmartPtr<InexactNormalTerminationTester> normal_tester = NULL
   );

   /** Destructor */
   virtual ~InexactDoglegNormalStep();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

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
   InexactDoglegNormalStep();

   /** Copy Constructor */
   InexactDoglegNormalStep(
      const InexactDoglegNormalStep&
   );

   /** Overloaded Assignment Operator */
   void operator=(
      const InexactDoglegNormalStep&
   );
   ///@}

   /** Pointer to object for computing the "Newton" step in the dogleg
    *  method
    */
   SmartPtr<InexactNewtonNormalStep> newton_step_;

   /** Pointer to object that is used by the newton_step computation
    *  object to determine if iterative solver is done.
    *
    *  This is needed here because this dogleg object is setting the
    *  value of the linearized constraint violation at the cauchy point
    *  if normal_tester is not NULL.
    */
   SmartPtr<InexactNormalTerminationTester> normal_tester_;

   /** @name Algorithmic options */
   ///@{
   Number omega_max_;
   ///@}

   /** Current value of the trust region factor */
   Number curr_omega_;

   /** Flag indicating if trust region was active in last iteration */
   bool last_tr_inactive_;
};

} // namespace Ipopt

#endif
