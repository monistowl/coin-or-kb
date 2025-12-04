// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-03-17

/**
 * @file IpMc19TSymScalingMethod.hpp
 * @brief Matrix scaling using HSL MC19 equilibration
 *
 * Mc19TSymScalingMethod uses the HSL subroutine MC19 to compute
 * equilibration scaling factors for symmetric matrices.
 *
 * @algorithm MC19 Iterative Row/Column Equilibration:
 *   MC19 computes diagonal scaling D such that ||D·A·D||_∞ ≈ 1.
 *   Algorithm iteratively updates scaling factors:
 *   1. Compute r_i = max_j |a_ij| (row infinity norms)
 *   2. Update D_i = D_i / sqrt(r_i)
 *   3. Repeat until convergence (typically 3-5 iterations)
 *   Result: scaled matrix has row/column norms near 1.
 *
 * @math Equilibration reduces condition number κ(A):
 *   For sparse symmetric A, equilibration typically reduces κ by factor
 *   of 10-1000. Better conditioning → fewer delayed pivots, more accurate
 *   factorization, better convergence of iterative refinement.
 *   D returned as exp(R) where R is in single precision.
 *
 * @complexity O(nnz) per iteration, typically 3-5 iterations = O(nnz).
 *   Memory: O(n) for scaling factors.
 *
 * @ref Duff & Koster (1999). "The design and use of algorithms for
 *      permuting large entries to the diagonal of sparse matrices".
 *      SIAM J. Matrix Anal. Appl. 20(4):889-901.
 *
 * MC19 interface (Fortran):
 *   MC19A(N, NZ, A, IRN, ICN, R, C, W)
 * Note: R, C, W are single precision (float) even in double version.
 *
 * Library loading:
 * - Can be linked at compile time
 * - Or loaded dynamically via LibraryLoader at runtime
 * - SetFunctions() allows setting function pointer globally
 *
 * The scaling factors returned satisfy ||D*A*D||_inf ≈ 1 where
 * D = diag(exp(R)) and the matrix is approximately equilibrated.
 *
 * @see IpTSymScalingMethod.hpp for base interface
 * @see IpEquilibrationScaling.hpp for NLP-level scaling
 */

#ifndef __IPMC19TSYMSCALINGMETHOD_HPP__
#define __IPMC19TSYMSCALINGMETHOD_HPP__

#include "IpUtils.hpp"
#include "IpTSymScalingMethod.hpp"
#include "IpLibraryLoader.hpp"
#include "IpTypes.h"

// note that R,C,W are single-precision also in the double-precision version of MC19 (MC19AD)
// here we assume that float corresponds to Fortran's single precision
/// @since 3.14.0
#define IPOPT_DECL_MC19A(x) void (x)( \
   const ipindex* N,   \
   const ipindex* NZ,  \
   ipnumber*      A,   \
   ipindex*       IRN, \
   ipindex*       ICN, \
   float*         R,   \
   float*         C,   \
   float*         W    \
)

namespace Ipopt
{

/** Class for the method for computing scaling factors for symmetric
 *  matrices in triplet format, using MC19.
 */
class Mc19TSymScalingMethod: public TSymScalingMethod
{
public:
   /** @name Constructor/Destructor */
   ///@{
   Mc19TSymScalingMethod(
      SmartPtr<LibraryLoader> hslloader_  ///< @since 3.14.0
   ) : hslloader(hslloader_),
      mc19a(NULL)
   { }

   virtual ~Mc19TSymScalingMethod()
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

   /// set MC19 function to use for every instantiation of this class
   /// @since 3.14.0
   static void SetFunctions(
      IPOPT_DECL_MC19A(*mc19a)
   );

   /// get MC19A function that has been set via SetFunctions
   ///
   /// this does not return a MC19A that has been linked in or loaded from a library at runtime
   /// @since 3.14.0
   static IPOPT_DECL_MC19A(*GetMC19A());

private:
   /**@name Default Compiler Generated Methods (Hidden to avoid
    * implicit creation/calling).  These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called. */
   ///@{
   /** Copy Constructor */
   Mc19TSymScalingMethod(
      const Mc19TSymScalingMethod&
   );

   /** Default Assignment Operator */
   void operator=(
      const Mc19TSymScalingMethod&
   );

   /**@name MC19 function pointer
    * @{
    */
   SmartPtr<LibraryLoader> hslloader;

   IPOPT_DECL_MC19A(*mc19a);
   /**@} */
};

} // namespace Ipopt

#endif
