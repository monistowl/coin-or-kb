// Copyright (C) 2004, 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2004-08-13

/**
 * @file IpZeroSymMatrix.hpp
 * @brief Symmetric matrix with all zero entries
 *
 * ZeroSymMatrix represents a symmetric zero matrix (n x n).
 * No storage required. Inherits from SymMatrix for type safety.
 *
 * @algorithm Zero Symmetric Matrix:
 *   Z = 0 ∈ ℝ^{n×n}, Z = Z^T trivially satisfied.
 *   MultVector: y ← βy (no α term contributes).
 *   Type-safe placeholder preserving symmetry structure.
 *
 * @math Linear objective functions:
 *   f(x) = c^T x has ∇²f = 0 (zero Hessian).
 *   Hessian of Lagrangian: W = ∇²f + Σᵢ λᵢ∇²gᵢ.
 *   When f linear and constraints linear: W = 0.
 *
 * @complexity O(1) storage and O(n) for matvec scaling.
 *   Null Object pattern for symmetric matrices.
 *
 * Used in Ipopt for:
 * - Problems with linear objectives (zero Hessian of objective)
 * - Placeholder in CompoundSymMatrix for zero blocks
 * - Default Hessian when user doesn't provide one
 *
 * @see IpZeroMatrix.hpp for non-symmetric version
 * @see IpSymMatrix.hpp for base class
 */

#ifndef __IPZEROSYMMATRIX_HPP__
#define __IPZEROSYMMATRIX_HPP__

#include "IpUtils.hpp"
#include "IpSymMatrix.hpp"

namespace Ipopt
{

/** Class for Symmetric Matrices with only zero entries. */
class IPOPTLIB_EXPORT ZeroSymMatrix: public SymMatrix
{
public:
   /**@name Constructors / Destructors */
   ///@{
   /** Constructor, taking the corresponding matrix space. */
   ZeroSymMatrix(
      const SymMatrixSpace* owner_space
   );

   /** Destructor */
   ~ZeroSymMatrix();
   ///@}

protected:
   /**@name Methods overloaded from matrix */
   ///@{
   virtual void MultVectorImpl(
      Number        alpha,
      const Vector& x,
      Number        beta,
      Vector&       y
   ) const;

   virtual void TransMultVectorImpl(
      Number        alpha,
      const Vector& x,
      Number        beta,
      Vector&       y
   ) const;

   virtual void ComputeRowAMaxImpl(
      Vector& /*rows_norms*/,
      bool    /*init*/
   ) const
   { }

   virtual void ComputeColAMaxImpl(
      Vector& /*cols_norms*/,
      bool    /*init*/
   ) const
   { }

   virtual void PrintImpl(
      const Journalist&  jnlst,
      EJournalLevel      level,
      EJournalCategory   category,
      const std::string& name,
      Index              indent,
      const std::string& prefix
   ) const;
   ///@}

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    * These methods are not implemented and
    * we do not want the compiler to implement
    * them for us, so we declare them private
    * and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Default Constructor */
   ZeroSymMatrix();

   /** Copy Constructor */
   ZeroSymMatrix(
      const ZeroSymMatrix&
   );

   /** Default Assignment Operator */
   void operator=(
      const ZeroSymMatrix&
   );
   ///@}
};

/** Class for matrix space for ZeroSymMatrix. */
class IPOPTLIB_EXPORT ZeroSymMatrixSpace: public SymMatrixSpace
{
public:
   /** @name Constructors / Destructors */
   ///@{
   /** Constructor, given the number of row and columns. */
   ZeroSymMatrixSpace(
      Index dim
   )
      : SymMatrixSpace(dim)
   { }

   /** Destructor */
   virtual ~ZeroSymMatrixSpace()
   { }
   ///@}

   virtual Matrix* MakeNew() const
   {
      return MakeNewZeroSymMatrix();
   }

   virtual SymMatrix* MakeNewSymMatrix() const
   {
      return MakeNewZeroSymMatrix();
   }

   /** Method for creating a new matrix of this specific type. */
   ZeroSymMatrix* MakeNewZeroSymMatrix() const
   {
      return new ZeroSymMatrix(this);
   }

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    * These methods are not implemented and
    * we do not want the compiler to implement
    * them for us, so we declare them private
    * and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Default Constructor */
   ZeroSymMatrixSpace();

   /** Copy Constructor */
   ZeroSymMatrixSpace(
      const ZeroSymMatrixSpace&
   );

   /** Default Assignment Operator */
   void operator=(
      const ZeroSymMatrixSpace&
   );
   ///@}
};

} // namespace Ipopt
#endif
