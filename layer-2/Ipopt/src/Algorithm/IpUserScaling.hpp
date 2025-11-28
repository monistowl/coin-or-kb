// Copyright (C) 2005, 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2005-06-25

/**
 * @file IpUserScaling.hpp
 * @brief NLP scaling using user-provided scaling factors
 *
 * UserScaling obtains scaling factors directly from the NLP interface
 * via the get_scaling_parameters callback (TNLP) or GetScalingParameters
 * method (NLP).
 *
 * This allows users to specify problem-specific scaling based on:
 * - Prior knowledge of variable magnitudes
 * - Physical units of constraints
 * - Problem structure
 *
 * Scaling factors:
 * - df: Objective function scaling
 * - dx: Variable scaling (per-variable)
 * - dc: Equality constraint scaling (per-constraint)
 * - dd: Inequality constraint scaling (per-constraint)
 *
 * The NLP should implement get_scaling_parameters() returning:
 * - use_x_scaling, use_g_scaling flags
 * - obj_scaling factor
 * - x_scaling array (length n)
 * - g_scaling array (length m)
 *
 * Note: If user doesn't provide scaling, falls back to no scaling.
 *
 * @see IpNLPScaling.hpp for scaling framework
 * @see IpGradientScaling.hpp for automatic scaling
 */

#ifndef __IPUSERSCALING_HPP__
#define __IPUSERSCALING_HPP__

#include "IpNLPScaling.hpp"
#include "IpNLP.hpp"

namespace Ipopt
{
/** This class does problem scaling by getting scaling parameters
 *  from the user (through the NLP interface).
 */
class UserScaling: public StandardScalingBase
{
public:
   /**@name Constructors/Destructors */
   ///@{
   UserScaling(
      const SmartPtr<const NLP>& nlp)
      : StandardScalingBase(),
        nlp_(nlp)
   { }

   /** Destructor */
   virtual ~UserScaling()
   { }
   ///@}

protected:
   virtual void DetermineScalingParametersImpl(
      const SmartPtr<const VectorSpace>    x_space,
      const SmartPtr<const VectorSpace>    c_space,
      const SmartPtr<const VectorSpace>    d_space,
      const SmartPtr<const MatrixSpace>    jac_c_space,
      const SmartPtr<const MatrixSpace>    jac_d_space,
      const SmartPtr<const SymMatrixSpace> h_space,
      const Matrix&                        Px_L,
      const Vector&                        x_L,
      const Matrix&                        Px_U,
      const Vector&                        x_U,
      Number&                              df,
      SmartPtr<Vector>&                    dx,
      SmartPtr<Vector>&                    dc,
      SmartPtr<Vector>&                    dd
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
   /** Copy Constructor */
   UserScaling(
      const UserScaling&
   );

   /** Default Assignment Operator */
   void operator=(
      const UserScaling&
   );
   ///@}

   /** pointer to the NLP to get scaling parameters */
   SmartPtr<const NLP> nlp_;
};
} // namespace Ipopt
#endif
