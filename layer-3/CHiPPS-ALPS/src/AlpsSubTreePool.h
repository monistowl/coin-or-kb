/*===========================================================================*
 * This file is part of the Abstract Library for Parallel Search (ALPS).     *
 *                                                                           *
 * ALPS is distributed under the Eclipse Public License as part of the       *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Aykut Bulut, Lehigh University                                   *
 *          Ted Ralphs, Lehigh University                                    *
 *                                                                           *
 * Conceptual Design:                                                        *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
 *          Ted Ralphs, Lehigh University                                    *
 *          Laszlo Ladanyi, IBM T.J. Watson Research Center                  *
 *          Matthew Saltzman, Clemson University                             *
 *                                                                           *
 *                                                                           *
 * Copyright (C) 2001-2023, Lehigh University, Yan Xu, Aykut Bulut, and      *
 *                          Ted Ralphs.                                      *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

/**
 * @file AlpsSubTreePool.h
 * @brief Pool of subtrees for work distribution in parallel search
 *
 * AlpsSubTreePool stores subtrees for load balancing between processes.
 * Key component for parallel scalability in ALPS.
 *
 * **Storage:**
 * - subTreeList_: Priority queue of AlpsSubTree pointers
 * - Ordering by subtree quality for work distribution
 *
 * **Key operations:**
 * - addKnowledge(): Add subtree from work donation
 * - getKnowledge()/popKnowledge(): Get subtree for processing
 * - setComparison(): Set subtree selection strategy
 * - getBestQuality(): Get quality of best subtree
 *
 * **Parallel use:**
 * - Serial: Single subtree in pool
 * - Parallel: Multiple subtrees for load balancing
 * - Subtrees split/merged for work sharing
 *
 * @see AlpsSubTree for subtree structure
 * @see AlpsKnowledgePool for base interface
 * @see AlpsKnowledgeBroker::subTreePool_ for broker's pool
 */

#ifndef AlpsSubTreePool_h_
#define AlpsSubTreePool_h_

#include "AlpsConfig.h"

#include "AlpsHelperFunctions.h"
#include "AlpsPriorityQueue.h"
#include "AlpsKnowledgePool.h"
#include "AlpsSubTree.h"
/*!

  The subtree pool is used to store subtrees

*/
class ALPSLIB_EXPORT AlpsSubTreePool: public AlpsKnowledgePool {
  AlpsPriorityQueue<AlpsSubTree*> subTreeList_;

public:
  ///@name Constructor and destructor.
  //@{
  /// Default constructor.
  AlpsSubTreePool();
  /// Destructor.
  virtual ~AlpsSubTreePool();
  //@}

  ///@name Querry methods
  //@{
  /// Query the number of subtrees in the pool.
  virtual int getNumKnowledges() const;
  /// Get a subtree from subtree pool, doesn't remove it from the pool.
  virtual std::pair<AlpsKnowledge*, double> getKnowledge() const;
  /// Check whether there is a subtree in the subtree pool.
  virtual bool hasKnowledge() const{ return ! (subTreeList_.empty()); }
  /// Query the quantity limit of knowledges.
  virtual int getMaxNumKnowledges() const { return INT_MAX; }
  /// Query the best knowledge in the pool.
  virtual std::pair<AlpsKnowledge*, double> getBestKnowledge() const;
  /// Get a reference to all the knowledges in the pool.*/
  virtual void getAllKnowledges (std::vector<std::pair<AlpsKnowledge*,
                                 double> >& kls) const;
  //@}

  ///@name Knowledge manipulation
  //@{
  /// Add a subtree to the subtree pool.
  virtual void addKnowledge(AlpsKnowledge* subTree, double priority);
  /// Remove a subtree from the pool.
  virtual void popKnowledge() { subTreeList_.pop(); }
  //@}

  ///@name Other functions
  //@{
  /// Set the quantity limit of knowledges that can be stored in the pool.
  virtual void setMaxNumKnowledges(int num);
  //@}

  /// Return the container of subtrees.
  virtual AlpsPriorityQueue< AlpsSubTree*> const & getSubTreeList() const;
  /// Set comparison function and resort heap.
  void setComparison(AlpsSearchStrategy<AlpsSubTree*>& compare);
  /// Delete the subtrees in the pool.
  void deleteGuts();
  /// Get the quality of the best subtree.
  double getBestQuality();

private:
  /// Disable copy constructor.
  AlpsSubTreePool(AlpsSubTreePool const &);
  /// Disable copy assignment operator.
  AlpsSubTreePool& operator=(const AlpsSubTreePool &);
};

#endif
