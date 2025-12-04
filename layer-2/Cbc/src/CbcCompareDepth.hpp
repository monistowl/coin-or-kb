/**
 * @file CbcCompareDepth.hpp
 * @brief Depth-first node selection strategy
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * CbcCompareDepth: Implements depth-first search (DFS).
 * Default strategy before first solution is found.
 *
 * test(x,y) returns true if y is deeper than x in the tree.
 * Deepest nodes explored first -> LIFO stack behavior.
 *
 * @algorithm Depth-First Search (DFS) Node Selection:
 *   test(x, y) comparison for heap ordering:
 *   Returns true if depth(y) > depth(x).
 *   Effect: Deepest nodes processed first (LIFO behavior).
 *   Memory: O(depth) nodes stored vs O(breadth) for best-first.
 *   Finds feasible solution quickly; weak bounds until backtrack.
 *
 * @math Complexity trade-off:
 *   DFS memory: O(d) where d = tree depth.
 *   Best-first memory: O(2^d) worst case.
 *   DFS bound gap: May be large until substantial backtracking.
 *   Best-first bound: Optimal LP bound tracked throughout.
 *
 * Advantages:
 * - Low memory (linear in depth)
 * - Fast to first feasible solution
 * - Good for proving feasibility
 *
 * Disadvantages:
 * - May miss better solutions at other branches
 * - Weak objective bounds early in search
 *
 * @see CbcCompareObjective for best-bound search
 * @see CbcCompareDefault for hybrid approach
 *
 * Edwin 11/24/09 carved out of CbcCompareActual
 */

#ifndef CbcCompareDepth_H
#define CbcCompareDepth_H

//#############################################################################
/*  These are alternative strategies for node traversal.
    They can take data etc for fine tuning

    At present the node list is stored as a heap and the "test"
    comparison function returns true if node y is better than node x.

*/
#include "CbcNode.hpp"
#include "CbcCompareBase.hpp"
#include "CbcCompare.hpp"
class CbcModel;
// This is default before first solution
class CBCLIB_EXPORT CbcCompareDepth : public CbcCompareBase {
public:
  // Default Constructor
  CbcCompareDepth();

  ~CbcCompareDepth();
  // Copy constructor
  CbcCompareDepth(const CbcCompareDepth &rhs);

  // Assignment operator
  CbcCompareDepth &operator=(const CbcCompareDepth &rhs);

  /// Clone
  virtual CbcCompareBase *clone() const;
  /// Create C++ lines to get to current state
  virtual void generateCpp(FILE *fp);

  // This returns true if the depth of node y is greater than depth of node x
  virtual bool test(CbcNode *x, CbcNode *y);
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
