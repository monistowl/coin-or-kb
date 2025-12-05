// Copyright (C) 2003, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpNetworkBasis.hpp
 * @brief Specialized factorization for pure network problems
 * @author John Forrest
 *
 * Exploits network structure for O(n) factorization instead of O(n^2-3).
 * Network LPs have constraint matrices that are node-arc incidence matrices
 * of directed graphs - each column has exactly one +1 and one -1.
 *
 * @algorithm Network Simplex Basis Factorization:
 * For pure network LPs, the basis matrix corresponds to a spanning tree,
 * enabling O(m) factorization and O(m) solve instead of O(m²-m³).
 *
 * NETWORK LP STRUCTURE:
 * @math Constraint matrix A is node-arc incidence of digraph G=(V,E):
 *   A[i,j] = +1 if arc j leaves node i
 *   A[i,j] = -1 if arc j enters node i
 *   A[i,j] = 0 otherwise
 *
 * Each column (arc) has exactly one +1 and one -1.
 * Examples: transportation, assignment, shortest path, max flow problems.
 *
 * @algorithm Spanning Tree Basis:
 * Key insight: Any basis B of a network matrix corresponds to a spanning tree T:
 *   - m basic variables = m-1 tree arcs + 1 slack (or m tree arcs with root removed)
 *   - Non-basic arcs either at lower or upper bound
 *
 * TREE REPRESENTATION (rooted at artificial root):
 *   - parent_[i]: parent node of node i in tree
 *   - descendant_[i]: first child of node i
 *   - rightSibling_[i]: next sibling of node i
 *   - leftSibling_[i]: previous sibling of node i
 *   - depth_[i]: distance from root to node i
 *
 * @algorithm FTRAN (Forward Transformation: solve Bx = b):
 * For network, reduces to tree path accumulation:
 *   1. Start with x = b
 *   2. For each node i (bottom-up from leaves to root):
 *      x[parent[i]] += sign[i] * x[i]
 * @complexity O(m) operations
 *
 * @algorithm BTRAN (Backward Transformation: solve B'y = c):
 * Tree path accumulation in opposite direction:
 *   1. Start with y = c
 *   2. For each node i (top-down from root to leaves):
 *      y[i] += sign[i] * y[parent[i]]
 * @complexity O(m) operations
 *
 * @algorithm Basis Update (pivot operation):
 * When arc (u,v) enters basis replacing arc (p,q):
 *   - Create cycle by adding (u,v) to tree
 *   - Remove (p,q) from cycle → new tree
 *   - Update parent/child/sibling pointers along affected path
 * @complexity O(diameter of tree), typically O(√m) for sparse networks
 *
 * @complexity Factorization: O(m) vs O(m²) for general LU
 *   FTRAN/BTRAN: O(m) vs O(m²) for general
 *   Update: O(path length) vs O(m²) for general
 *
 * Uses spanning tree representation:
 * - parent/descendant/sibling arrays encode tree structure
 * - FTRAN/BTRAN reduce to tree traversal operations
 * - Updates are simple tree modifications
 *
 * Requires ClpNetworkMatrix to detect network structure.
 *
 * @see ClpNetworkMatrix for the network matrix representation
 * @see ClpFactorization for the general factorization interface
 */

#ifndef ClpNetworkBasis_H
#define ClpNetworkBasis_H

class ClpMatrixBase;
class CoinIndexedVector;
class ClpSimplex;
#include "CoinTypes.h"
#include "ClpConfig.h"
#ifndef COIN_FAST_CODE
#define COIN_FAST_CODE
#endif

/** This deals with Factorization and Updates for network structures
 */

class CLPLIB_EXPORT ClpNetworkBasis {

public:
  /**@name Constructors and destructor and copy */
  //@{
  /// Default constructor
  ClpNetworkBasis();
  /// Constructor from CoinFactorization
  ClpNetworkBasis(const ClpSimplex *model,
    int numberRows, const CoinFactorizationDouble *pivotRegion,
    const int *permuteBack, const int *startColumn,
    const int *numberInColumn,
    const int *indexRow, const CoinFactorizationDouble *element);
  /// Copy constructor
  ClpNetworkBasis(const ClpNetworkBasis &other);

  /// Destructor
  ~ClpNetworkBasis();
  /// = copy
  ClpNetworkBasis &operator=(const ClpNetworkBasis &other);
  //@}

  /**@name Do factorization */
  //@{
  /** When part of LP - given by basic variables.
     Actually does factorization.
     Arrays passed in have non negative value to say basic.
     If status is okay, basic variables have pivot row - this is only needed
     if increasingRows_ >1.
     If status is singular, then basic variables have pivot row
     and ones thrown out have -1
     returns 0 -okay, -1 singular, -2 too many in basis */
  int factorize(const ClpMatrixBase *matrix,
    int rowIsBasic[], int columnIsBasic[]);
  //@}

  /**@name rank one updates which do exist */
  //@{

  /** Replaces one Column to basis,
      returns 0=OK, 1=Probably OK, 2=singular!!
     */
  int replaceColumn(CoinIndexedVector *column,
    int pivotRow);
  //@}

  /**@name various uses of factorization (return code number elements)
      which user may want to know about */
  //@{
  /** Updates one column (FTRAN) from region,
         Returns pivot value if "pivotRow" >=0
     */
  double updateColumn(CoinIndexedVector *regionSparse,
    CoinIndexedVector *regionSparse2,
    int pivotRow);
  /** Updates one column (FTRAN) to/from array
         ** For large problems you should ALWAYS know where the nonzeros
         are, so please try and migrate to previous method after you
         have got code working using this simple method - thank you!
         (the only exception is if you know input is dense e.g. rhs) */
  int updateColumn(CoinIndexedVector *regionSparse,
    double array[]) const;
  /** Updates one column transpose (BTRAN)
         ** For large problems you should ALWAYS know where the nonzeros
         are, so please try and migrate to previous method after you
         have got code working using this simple method - thank you!
         (the only exception is if you know input is dense e.g. dense objective)
         returns number of nonzeros */
  int updateColumnTranspose(CoinIndexedVector *regionSparse,
    double array[]) const;
  /** Updates one column (BTRAN) from region2 */
  int updateColumnTranspose(CoinIndexedVector *regionSparse,
    CoinIndexedVector *regionSparse2) const;
  //@}
  ////////////////// data //////////////////
private:
  // checks looks okay
  void check();
  // prints data
  void print();
  /**@name data */
  //@{
#ifndef COIN_FAST_CODE
  /// Whether slack value is  +1 or -1
  double slackValue_;
#endif
  /// Number of Rows in factorization
  int numberRows_;
  /// Number of Columns in factorization
  int numberColumns_;
  /// model
  const ClpSimplex *model_;
  /// Parent for each column
  int *parent_;
  /// Descendant
  int *descendant_;
  /// Pivot row
  int *pivot_;
  /// Right sibling
  int *rightSibling_;
  /// Left sibling
  int *leftSibling_;
  /// Sign of pivot
  double *sign_;
  /// Stack
  int *stack_;
  /// Permute into array
  int *permute_;
  /// Permute back array
  int *permuteBack_;
  /// Second stack
  int *stack2_;
  /// Depth
  int *depth_;
  /// To mark rows
  char *mark_;
  //@}
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
