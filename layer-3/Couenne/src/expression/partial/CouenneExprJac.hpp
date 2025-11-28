/*
 *
 * Name:    CouenneExprJac.hpp
 * Authors: Pietro Belotti, Lehigh University
 * Purpose: Jacobian expression
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneExprJac.hpp
 * @brief Symbolic Jacobian of constraints via expression DAG
 *
 * Stores the constraint Jacobian as a sparse matrix of expression
 * pointers. Each nonzero ∂g_i/∂x_j is an expression node that can
 * be evaluated at any point.
 *
 * **Sparse structure:**
 * - nnz_: Number of structural nonzeros
 * - iRow_[], jCol_[]: COO format indices
 * - expr_[k]: Expression for the k-th nonzero entry
 *
 * **Construction:**
 * Built from CouenneProblem by differentiating each constraint
 * body expression with respect to each variable it depends on.
 *
 * **Usage:**
 * Called by Ipopt's eval_jac_g() callback to provide the
 * constraint Jacobian. Expression-based representation allows
 * exact derivatives without finite differences.
 *
 * @see ExprHess for the Lagrangian Hessian
 * @see CouenneTNLP which uses ExprJac for NLP solves
 */
#ifndef CouenneExprJac_HPP
#define CouenneExprJac_HPP

#include "CouenneConfig.h"

namespace Couenne {

  class expression;
  class CouenneProblem;

  /// Jacobian of the problem (computed through Couenne expression
  /// classes).

  class COUENNELIB_EXPORT ExprJac {

  private:

    int          nnz_;   ///< number of (symbolic) nonzeroes
    int         *iRow_;  ///< row indices (read this way by eval_jac_g)
    int         *jCol_;  ///< col indices

    expression **expr_;  ///< nonzero expression elements (there are nnz_ of them)

    int          nRows_; ///< number of actual constraints

  public:

    ExprJac  ();
    ExprJac  (CouenneProblem *);
    ~ExprJac ();

    ExprJac  (const ExprJac &);
    ExprJac *clone ();
    ExprJac &operator= (const ExprJac &);

    int  nnz  () const {return nnz_;}
    int *iRow () const {return iRow_;}
    int *jCol () const {return jCol_;}

    expression **expr () const {return expr_;}

    int nRows () const {return nRows_;}
  };
}

#endif
