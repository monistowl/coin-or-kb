// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter              IBM    2004-09-23

/**
 * @file IpLeastSquareMults.hpp
 * @brief Least-squares estimation of equality constraint multipliers
 *
 * LeastSquareMultipliers computes initial estimates for the equality
 * constraint multipliers y_c and y_d by solving a least-squares problem.
 *
 * Formulation: Find y minimizing ||∇_x L(x,y)||^2 where
 *   ∇_x L = ∇f(x) + J_c^T y_c + J_d^T y_d - z_L + z_U
 *
 * This is equivalent to solving the normal equations:
 *   [J_c J_c^T    0    ] [y_c]   [-J_c (∇f - z_L + z_U)]
 *   [   0     J_d J_d^T] [y_d] = [-J_d (∇f - z_L + z_U)]
 *
 * Actually solved via augmented system:
 *   [0  J_c^T  J_d^T] [r  ]   [∇f - z_L + z_U]
 *   [J_c  0     0   ] [y_c] = [     0        ]
 *   [J_d  0     0   ] [y_d]   [     0        ]
 *
 * Uses AugSystemSolver to solve the linear system with W=0.
 *
 * Usage:
 * - DefaultIterateInitializer: Initial multiplier estimates
 * - MinC_1NrmRestorationPhase: Post-restoration multiplier reset
 *
 * @algorithm Least-Squares Multiplier Estimation:
 * Find y minimizing ||∇_x L(x,y)||² via normal equations:
 * 1. Form gradient residual: g = ∇f(x) - z_L + z_U (bound multiplier contribution)
 * 2. Solve augmented system with W=0:
 *    [0     J_c^T   J_d^T] [r  ]   [g]
 *    [J_c    0       0   ] [y_c] = [0]
 *    [J_d    0       0   ] [y_d]   [0]
 * 3. Discard residual r; extract y_c, y_d as multiplier estimates
 *
 * @math Least-squares formulation:
 * min_y ||∇f + Jᵀy - (z_L - z_U)||²
 *
 * Normal equations: (J·Jᵀ)·y = -J·(∇f - z_L + z_U)
 *
 * Augmented system form solves this without forming JJᵀ explicitly,
 * preserving sparsity: Jᵀy = r, Jx = 0 → y = (JJᵀ)⁻¹J·(-g).
 *
 * Singular case: If J is rank-deficient, minimum-norm solution is obtained.
 *
 * @complexity Same as one augmented system solve: O(nnz(J)·fill) for sparse,
 * O(n³) for dense factorization.
 *
 * @see IpEqMultCalculator.hpp for base interface
 * @see IpAugSystemSolver.hpp for the linear solver
 * @see IpDefaultIterateInitializer.hpp for initialization usage
 */

#ifndef __IPLEASTSQUAREMULTS_HPP__
#define __IPLEASTSQUAREMULTS_HPP__

#include "IpAugSystemSolver.hpp"
#include "IpEqMultCalculator.hpp"

namespace Ipopt
{

/** Class for calculator for the least-square equality constraint multipliers.
 *
 *  The Calculate method of this class computes the
 *  least-square estimate for the y_c and y_d multipliers, based on
 *  the current values of the gradient of the Lagrangian.
 */
class LeastSquareMultipliers: public EqMultiplierCalculator
{
public:
   /**@name Constructors / Destructors */
   ///@{
   /** Constructor.
    *
    *  It needs to be given the strategy object for
    *  solving the augmented system.
    */
   LeastSquareMultipliers(
      AugSystemSolver& augSysSolver
   );

   /** Destructor */
   virtual ~LeastSquareMultipliers()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** This method computes the least-square estimates for y_c and
    *  y_d at the current point.
    *
    *  @return false, if the least square system could not be solved (the linear system is singular)
    */
   virtual bool CalculateMultipliers(
      Vector& y_c,
      Vector& y_d
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
   LeastSquareMultipliers();

   /** Copy Constructor */
   LeastSquareMultipliers(
      const LeastSquareMultipliers&
   );

   void operator=(
      const LeastSquareMultipliers&
   );
   ///@}

   /** augmented system solver to be used for solving the linear system */
   SmartPtr<AugSystemSolver> augsyssolver_;
};

} // namespace Ipopt

#endif
