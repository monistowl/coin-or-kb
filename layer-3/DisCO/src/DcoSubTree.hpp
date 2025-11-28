/*===========================================================================*
 * This file is part of the Discrete Conic Optimization (DisCO) Solver.      *
 *                                                                           *
 * DisCO is distributed under the Eclipse Public License as part of the      *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *          Aykut Bulut, Lehigh University                                   *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Copyright (C) 2001-2018, Lehigh University, Aykut Bulut, Yan Xu, and      *
 *                          Ted Ralphs.                                      *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

/**
 * @file DcoSubTree.hpp
 * @brief Subtree representation for parallel search
 *
 * DcoSubTree extends BcpsSubTree to represent a portion of the
 * branch-and-bound tree for parallel distribution.
 *
 * **Inheritance:** DcoSubTree -> BcpsSubTree -> AlpsSubTree
 *
 * **Usage in Parallel:**
 * - Subtrees are work units distributed to workers
 * - Contains subset of tree nodes for processing
 * - Supports encode/decode for network transmission
 *
 * Note: Currently minimal implementation - most logic in base class.
 *
 * @see DcoTreeNode.hpp for tree node implementation
 * @see BcpsSubTree (BCPS) for base class
 * @see AlpsSubTree (ALPS) for parallel infrastructure
 */

#ifndef DcoSubTree_hpp_
#define DcoSubTree_hpp_

#include <BcpsSubTree.h>

class DcoSubTree: public BcpsSubTree {
public:
  DcoSubTree();
  virtual ~DcoSubTree();
};

#endif
