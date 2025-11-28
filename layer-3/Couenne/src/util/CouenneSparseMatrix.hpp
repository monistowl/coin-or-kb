/*
 *
 * Name:    CouenneSparseMatrix.hpp
 * Authors: Pietro Belotti, Clemson University
 * Purpose: Definition of a sparse Matrix for use in distance
 *          measurements in Feasibility Pump
 *
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneSparseMatrix.hpp
 * @brief Sparse matrix storage for Feasibility Pump distance
 *
 * Simple COO (coordinate) format sparse matrix used to store
 * the Hessian of the Lagrangian at optimum for later use in
 * modified distance computations.
 *
 * **Storage format:**
 * COO (Coordinate list):
 * - val_[k]: Value of k-th nonzero
 * - row_[k]: Row index of k-th nonzero
 * - col_[k]: Column index of k-th nonzero
 * - num_: Total number of nonzeros
 *
 * **Usage in Feasibility Pump:**
 * The Hessian from an NLP solve can be saved and used to modify
 * the distance metric in subsequent MILP solves, biasing the
 * search toward regions where the NLP objective improves.
 *
 * **Note:** This is a simple storage class, not a full sparse
 * matrix implementation. For operations, use CoinPackedMatrix.
 *
 * @see CouenneTNLP::optHessian_ which stores this
 * @see CouenneFeasPump which uses modified distances
 */
#ifndef COUENNESPARSEMATRIX_HPP
#define COUENNESPARSEMATRIX_HPP

namespace Couenne {

  /// Class for sparse Matrixs (used in modifying distances in FP)
  class CouenneSparseMatrix {

  public:

    /// Constructor
    CouenneSparseMatrix ();

    /// Copy constructor
    CouenneSparseMatrix (const CouenneSparseMatrix &);

    /// Assignment
    CouenneSparseMatrix &operator= (const CouenneSparseMatrix &rhs);

    /// Clone
    CouenneSparseMatrix *clone ();

    /// Destructor
    virtual ~CouenneSparseMatrix ();

    /// Get methods
    int     &num () {return num_;} ///< number of elements
    double *&val () {return val_;} ///< values
    int    *&col () {return col_;} ///< column indices
    int    *&row () {return row_;} ///< row indices

  private:

    /// Stores the values of the Matrix of the Lagrangian at optimum for later use
    int     num_; ///< number of elements
    double *val_; ///< values
    int    *col_; ///< column indices
    int    *row_; ///< row indices
  };
}

#endif
