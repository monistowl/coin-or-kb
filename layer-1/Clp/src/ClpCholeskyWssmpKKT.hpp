// Copyright (C) 2004, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpCholeskyWssmpKKT.hpp
 * @brief WSSMP solver for KKT system (augmented system) formulation
 *
 * Variant of ClpCholeskyWssmp that solves the KKT/augmented system directly
 * instead of forming and factoring the normal equations A*D*A'.
 *
 * @algorithm Augmented System vs Normal Equations:
 * Two approaches to solve interior point step directions.
 *
 * @math KKT SYSTEM (Augmented):
 *   [ -D   A' ] [ Δx ]   [ r₁ ]
 *   [  A   0  ] [ Δy ] = [ r₂ ]
 *
 * This is an indefinite symmetric system (saddle point).
 *
 * @math NORMAL EQUATIONS (Alternative):
 *   (A·D⁻¹·A')·Δy = r₂ - A·D⁻¹·r₁
 *
 * @algorithm When to Use KKT vs Normal:
 *
 * PREFER KKT when:
 *   - A has dense columns → A·D·A' fills in heavily
 *   - m ≈ n (square-ish) → KKT not much larger
 *   - Need regularization → add δI to (2,2) block
 *   - A already sparse structured
 *
 * PREFER NORMAL when:
 *   - m << n (many more variables than constraints)
 *   - A·D·A' stays sparse
 *   - Want positive definite factorization
 *
 * @algorithm Indefinite Factorization:
 * KKT matrix is symmetric indefinite → use LDL' with pivoting.
 * WSSMP handles this with Bunch-Kaufman pivoting.
 *
 * @complexity KKT: O((m+n)^α) where α depends on sparsity
 * Often better constant than forming A·D·A' explicitly.
 *
 * @see ClpCholeskyWssmp for the normal equations variant
 * @see ClpCholeskyBase for the abstract interface
 * @see ClpInterior which uses this factorization
 */

#ifndef ClpCholeskyWssmpKKT_H
#define ClpCholeskyWssmpKKT_H

#include "ClpCholeskyBase.hpp"
class ClpMatrixBase;
class ClpCholeskyDense;

/** WssmpKKT class for Clp Cholesky factorization

*/
class CLPLIB_EXPORT ClpCholeskyWssmpKKT : public ClpCholeskyBase {

public:
  /**@name Virtual methods that the derived classes provides  */
  //@{
  /** Orders rows and saves pointer to matrix.and model.
      Returns non-zero if not enough memory */
  virtual int order(ClpInterior *model);
  /** Does Symbolic factorization given permutation.
         This is called immediately after order.  If user provides this then
         user must provide factorize and solve.  Otherwise the default factorization is used
         returns non-zero if not enough memory */
  virtual int symbolic();
  /** Factorize - filling in rowsDropped and returning number dropped.
         If return code negative then out of memory */
  virtual int factorize(const double *diagonal, int *rowsDropped);
  /** Uses factorization to solve. */
  virtual void solve(double *region);
  /** Uses factorization to solve. - given as if KKT.
      region1 is rows+columns, region2 is rows */
  virtual void solveKKT(double *region1, double *region2, const double *diagonal,
    double diagonalScaleFactor);
  //@}

  /**@name Constructors, destructor */
  //@{
  /** Constructor which has dense columns activated.
         Default is off. */
  ClpCholeskyWssmpKKT(int denseThreshold = -1);
  /** Destructor  */
  virtual ~ClpCholeskyWssmpKKT();
  // Copy
  ClpCholeskyWssmpKKT(const ClpCholeskyWssmpKKT &);
  // Assignment
  ClpCholeskyWssmpKKT &operator=(const ClpCholeskyWssmpKKT &);
  /// Clone
  virtual ClpCholeskyBase *clone() const;
  //@}

private:
  /**@name Data members */
  //@{
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
