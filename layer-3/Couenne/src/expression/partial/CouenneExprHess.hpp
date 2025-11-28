/*
 *
 * Name:    CouenneExprHess.hpp
 * Authors: Pietro Belotti, Lehigh University
 * Purpose: Hessian of the Lagrangian, definition
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprHess.hpp
 * @brief Symbolic Hessian of Lagrangian via expression DAG
 *
 * Stores the Hessian of the Lagrangian:
 * ∇²L(x,λ) = ∇²f(x) + Σᵢ λᵢ ∇²gᵢ(x)
 *
 * **Sparse structure:**
 * - nnz_: Number of structural nonzeros (lower triangle)
 * - iRow_[], jCol_[]: COO format indices
 * - numL_[k]: How many λᵢ contribute to position k
 * - lamI_[k][]: Indices of contributing λᵢ
 * - expr_[k][j]: Expression for ∂²gⱼ/∂x_iRow[k]∂x_jCol[k]
 *
 * **Evaluation:**
 * For each nonzero position (i,j), sum over all constraints:
 * H[i,j] = expr_obj[i,j] + Σₖ λ[lamI[k]] * expr[k][...]
 *
 * **Feasibility pump extension:**
 * Can be extended with gg' term for feasibility pump objectives
 * by augmenting the objective with ||x - x̄||² + gradient terms.
 *
 * @see ExprJac for the constraint Jacobian
 * @see CouenneTNLP which uses ExprHess for NLP solves
 */
#ifndef CouenneExprHess_HPP
#define CouenneExprHess_HPP

#include "CouenneConfig.h"

namespace Couenne {

  class expression;
  class CouenneProblem;

  /// expression matrices. Used to evaluate the Hessian of the
  /// Lagrangian function at an optimal solution of the NLP

  class COUENNELIB_EXPORT ExprHess {

  private:

    int   nnz_;  ///< number of (symbolic) nonzeroes
    int  *iRow_; ///< row indices (read this way by eval_h)
    int  *jCol_; ///< col indices

    /// There are m+1 (m constraints + 1 obj) components:
    ///
    /// \f$ \nabla^2 \mathcal L (x,\lambda) = \nabla^2 f(x) + \lambda^\top \nabla^2 g(x) \f$
    ///
    /// Implementing a FP requires adding one for gg', the gradient
    /// again being set up at the beginning (at least its expression
    /// members are known).
    ///
    /// This can simply be hacked by the FP itself. Same for the
    /// changed hessian, simply replace the CouenneProblem's objective
    /// with sum (objective, norm)
    ///
    /// Actually, we could do the gg' trick by replacing the objective
    /// with sum (objective, norm, gg')

    int  *numL_; ///< size of each lamI_

    int **lamI_; ///< vector of indices in the lambda vector
                 ///< whose constraint has nonzero entry in
                 ///< this position of the hessian

    expression ***expr_; ///< list of lists of pointers to expression

  public:

    ExprHess  ();
    ExprHess  (CouenneProblem *);

    ExprHess  (const ExprHess &);
    ExprHess  &operator=(const ExprHess &);
    ExprHess  *clone ();

    ~ExprHess ();

    int   nnz  () {return nnz_;}
    int  *iRow () {return iRow_;}
    int  *jCol () {return jCol_;}
    int  *numL () {return numL_;}
    int **lamI () {return lamI_;}

    expression ***expr () {return expr_;}
  };
}

#endif
