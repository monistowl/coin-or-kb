// Copyright (C) 2003, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpPdcoBase.hpp
 * @brief Abstract base class for PDCO problem customization
 *
 * Strategy pattern interface for defining custom convex objectives in PDCO.
 *
 * @algorithm User-Defined Convex Objectives:
 * Allows PDCO to solve problems with custom separable convex objectives
 * φ(x) = Σᵢ φᵢ(xᵢ) by providing function/gradient/Hessian callbacks.
 *
 * @math Required Callbacks:
 *   getObj(x):      Returns φ(x) = Σᵢ φᵢ(xᵢ)
 *   getGrad(x):     Returns ∇φ(x) = [φ₁'(x₁), ..., φₙ'(xₙ)]
 *   getHessian(x):  Returns diag(H) = [φ₁''(x₁), ..., φₙ''(xₙ)]
 *
 * @algorithm Matrix Operations:
 *   matVecMult(mode=1, x, y): y := y + A·x
 *   matVecMult(mode=2, x, y): x := x + A'·y
 *
 * @algorithm Preconditioning:
 *   matPrecon(delta, x, y): Apply preconditioner
 *   Typically diagonal scaling based on (A·D²·A' + δ²I)
 *
 * REGULARIZATION PARAMETERS:
 *   d1 (primal): Adds ||d₁·x||²/2 to objective, ensures D² > 0
 *   d2 (dual): Adds δ²I to (2,2) block of augmented system
 *
 * @math Effect on KKT system:
 *   Without regularization: A·(H⁻¹)·A' may be singular if H has zeros
 *   With regularization: A·(H + d₁²I)⁻¹·A' + d₂²I always invertible
 *
 * Common objective functions that can be implemented:
 * - Entropy: φ(x) = Σ xᵢ·log(xᵢ)  → H = diag(1/xᵢ)
 * - Barrier: φ(x) = -Σ log(xᵢ)    → H = diag(1/xᵢ²)
 * - Quadratic: φ(x) = x'Qx/2      → H = Q (if diagonal)
 * - Huber: φ(x) = Σ huber(xᵢ)     → H = piecewise
 *
 * @see ClpPdco which uses this interface
 * @see ClpLsqr for the iterative solver
 */

#ifndef ClpPdcoBase_H
#define ClpPdcoBase_H

#include "CoinPragma.hpp"
#include "CoinPackedMatrix.hpp"
#include "CoinDenseVector.hpp"
#include "ClpConfig.h"

class ClpInterior;

/** Abstract base class for tailoring everything for Pcdo

    Since this class is abstract, no object of this type can be created.

    If a derived class provides all methods then all ClpPcdo algorithms
    should work.

    Eventually we should be able to use ClpObjective and ClpMatrixBase.
*/

class CLPLIB_EXPORT ClpPdcoBase {

public:
  /**@name Virtual methods that the derived classes must provide */
  //@{
  virtual void matVecMult(ClpInterior *model, int mode, double *x, double *y) const = 0;

  virtual void getGrad(ClpInterior *model, CoinDenseVector< double > &x, CoinDenseVector< double > &grad) const = 0;

  virtual void getHessian(ClpInterior *model, CoinDenseVector< double > &x, CoinDenseVector< double > &H) const = 0;

  virtual double getObj(ClpInterior *model, CoinDenseVector< double > &x) const = 0;

  virtual void matPrecon(ClpInterior *model, double delta, double *x, double *y) const = 0;

  //@}
  //@{
  ///@name Other
  /// Clone
  virtual ClpPdcoBase *clone() const = 0;
  /// Returns type
  inline int type() const
  {
    return type_;
  };
  /// Sets type
  inline void setType(int type)
  {
    type_ = type;
  };
  /// Returns size of d1
  inline int sizeD1() const
  {
    return 1;
  };
  /// Returns d1 as scalar
  inline double getD1() const
  {
    return d1_;
  };
  /// Returns size of d2
  inline int sizeD2() const
  {
    return 1;
  };
  /// Returns d2 as scalar
  inline double getD2() const
  {
    return d2_;
  };
  //@}

protected:
  /**@name Constructors, destructor<br>
        <strong>NOTE</strong>: All constructors are protected. There's no need
        to expose them, after all, this is an abstract class. */
  //@{
  /** Default constructor. */
  ClpPdcoBase();
  /** Destructor (has to be public) */
public:
  virtual ~ClpPdcoBase();

protected:
  // Copy
  ClpPdcoBase(const ClpPdcoBase &);
  // Assignment
  ClpPdcoBase &operator=(const ClpPdcoBase &);
  //@}

protected:
  /**@name Data members
        The data members are protected to allow access for derived classes. */
  //@{
  /// Should be dense vectors
  double d1_;
  double d2_;
  /// type (may be useful)
  int type_;
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
