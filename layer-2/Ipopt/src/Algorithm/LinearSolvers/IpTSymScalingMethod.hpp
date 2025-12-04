// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-03-17

/**
 * @file IpTSymScalingMethod.hpp
 * @brief Base class for matrix scaling in triplet format
 *
 * TSymScalingMethod is the abstract base class for computing diagonal
 * scaling factors for symmetric matrices. Scaling improves numerical
 * conditioning of the linear system.
 *
 * Scaling transformation:
 *   Original: A * x = b
 *   Scaled:   (D*A*D) * (D^{-1}*x) = D*b
 * where D = diag(scaling_factors).
 *
 * The ComputeSymTScalingFactors method takes:
 * - n: matrix dimension
 * - nnz: number of nonzeros
 * - airn, ajcn: row/column indices (triplet format)
 * - a: matrix values
 * - scaling_factors: output array of length n
 *
 * Implementations:
 * - Mc19TSymScalingMethod: HSL MC19 equilibration
 * - SlackBasedTSymScalingMethod: Simple slack-based scaling
 *
 * @algorithm Symmetric Matrix Scaling (Row/Column Equilibration):
 * Computes diagonal D to improve κ(DAD) for better solver accuracy:
 * 1. Analyze matrix structure in triplet (i, j, a_ij) format
 * 2. Compute scaling factors d_i (implementation-specific)
 * 3. Apply: Ā = DAD, x̄ = D⁻¹x, b̄ = Db
 * Goal: Reduce condition number and improve pivot selection.
 *
 * @math Symmetric scaling with D = diag(d₁,...,dₙ):
 * $$\bar{A}_{ij} = d_i \cdot A_{ij} \cdot d_j$$
 *
 * Equilibration goal: make row/column norms approximately equal
 * $$\|(\bar{A})_i\| \approx \|(\bar{A})_j\| \approx 1$$
 *
 * Condition number improvement: κ(DAD) << κ(A) typically.
 *
 * @complexity O(nnz) for computing scaling factors.
 * Single pass through nonzero entries required.
 *
 * @ref Duff & Koster (2001). "On algorithms for permuting large entries
 *   to the diagonal of a sparse matrix". SIAM J. Matrix Anal. Appl. 22(4).
 * @ref Curtis & Reid (1972). "On the automatic scaling of matrices for
 *   Gaussian elimination". IMA J. Appl. Math. 10(1):118-124.
 *
 * @see IpMc19TSymScalingMethod.hpp for MC19 implementation
 * @see IpTSymLinearSolver.hpp for usage
 */

#ifndef __IPTSYMSCALINGMETHOD_HPP__
#define __IPTSYMSCALINGMETHOD_HPP__

#include "IpUtils.hpp"
#include "IpAlgStrategy.hpp"

namespace Ipopt
{

DECLARE_STD_EXCEPTION(ERROR_IN_LINEAR_SCALING_METHOD);

/** Base class for the method for computing scaling factors for symmetric
 *  matrices in triplet format.
 */
class TSymScalingMethod: public AlgorithmStrategyObject
{
public:
   /** @name Constructor/Destructor */
   ///@{
   TSymScalingMethod()
   { }

   ~TSymScalingMethod()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

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
   ) = 0;

private:
   /**@name Default Compiler Generated Methods (Hidden to avoid
    * implicit creation/calling).  These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called. */
   ///@{
   /** Copy Constructor */
   TSymScalingMethod(
      const TSymScalingMethod&
   );

   /** Default Assignment Operator */
   void operator=(
      const TSymScalingMethod&
   );
};

} // namespace Ipopt

#endif
