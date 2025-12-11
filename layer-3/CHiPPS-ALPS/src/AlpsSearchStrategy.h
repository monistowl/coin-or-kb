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
 * @file AlpsSearchStrategy.h
 * @brief Node and subtree selection strategies for ALPS tree search
 *
 * @algorithm Search Tree Node Selection:
 * Strategies for choosing which node to explore next in branch-and-bound.
 *
 *   BEST-FIRST (AlpsNodeSelectionBest):
 *     Select node with best (lowest) bound
 *     Minimizes dual gap, proves optimality fastest
 *     Memory: O(nodes) - may keep many open nodes
 *
 *   DEPTH-FIRST (AlpsNodeSelectionDepth):
 *     Select deepest node (LIFO stack)
 *     Finds feasible solutions quickly
 *     Memory: O(depth) - very memory efficient
 *
 *   BREADTH-FIRST (AlpsNodeSelectionBreadth):
 *     Select shallowest node (FIFO queue)
 *     Explores level by level
 *     Memory: O(branching_factor^depth) - exponential
 *
 *   HYBRID:
 *     Combines best-first with diving phases
 *     Dives to find solutions, then switches to best-first
 *
 * @math
 *   Best-first: priority = node.bound
 *   Depth-first: priority = node.depth (higher = earlier)
 *   Estimate: priority = estimated_solution_value
 *
 * @complexity
 *   Selection: O(log n) with priority queue
 *   Insertion: O(log n) with priority queue
 *   Best-first typically explores fewer nodes but uses more memory
 *
 * compare(x,y) returns true if y should be processed before x.
 *
 * @see AlpsSearchStrategyBase for template base class
 * @see AlpsKnowledgeBroker::setNodeSelection() for configuration
 * @see AlpsSubTree::setNodeSelection() for per-subtree override
 */

#ifndef AlpsSearchStrategy_h_
#define AlpsSearchStrategy_h_

#include "AlpsConfig.h"

#include "AlpsSearchStrategyBase.h"
#include "AlpsSubTree.h"
#include "AlpsTreeNode.h"

//#############################################################################
//#############################################################################

class ALPSLIB_EXPORT AlpsTreeSelection : public AlpsSearchStrategy<AlpsSubTree*>
{
public:
    /** Default Constructor. */
    AlpsTreeSelection() {}

    /** Default Destructor. */
    virtual ~AlpsTreeSelection() {}

    /** This returns true if the quality of the subtree y is better
        (the less the better) than that the subtree x. */
    virtual bool compare(AlpsSubTree * x, AlpsSubTree * y) = 0;
};

//#############################################################################

class ALPSLIB_EXPORT AlpsNodeSelection : public AlpsSearchStrategy<AlpsTreeNode*>
{
public:
    /** Default Constructor. */
    AlpsNodeSelection() {}

    /** Default Destructor. */
    virtual ~AlpsNodeSelection() {}

    /** This returns true if the depth of node y is lesser
        than that of node x */
    virtual bool compare(AlpsTreeNode * x, AlpsTreeNode * y) = 0;

    /* Select the next node to be processed. */
    virtual AlpsTreeNode* selectNextNode(AlpsSubTree *subTree);

    /* Create new nodes from pregnant node and store them in node pool. */
    virtual void createNewNodes(AlpsSubTree *subTree, AlpsTreeNode *node);
};

//#############################################################################
// SUBTREE SELECTION RULES
//#############################################################################

class ALPSLIB_EXPORT AlpsTreeSelectionBest : public AlpsTreeSelection
{
public:
    /** Default Constructor. */
    AlpsTreeSelectionBest() { type_ = AlpsSearchTypeBestFirst; }

    /** Default Destructor. */
    virtual ~AlpsTreeSelectionBest() {}

    /** This returns true if the quality of the subtree y is better
        (the less the better) than that the subtree x. */
    virtual bool compare(AlpsSubTree * x, AlpsSubTree * y);
};

//#############################################################################

class ALPSLIB_EXPORT AlpsTreeSelectionBreadth : public AlpsTreeSelection
{
public:
    /** Default Constructor */
    AlpsTreeSelectionBreadth() { type_ = AlpsSearchTypeBreadthFirst; }

    /** Default Destructor. */
    virtual ~AlpsTreeSelectionBreadth() {}

    /** This returns true if the depth of the root node in subtree y
        is smaller than that of the root node in subtree x. */
    virtual bool compare(AlpsSubTree * x, AlpsSubTree * y);
};

//#############################################################################

class ALPSLIB_EXPORT AlpsTreeSelectionDepth : public AlpsTreeSelection
{
public:
    /** Default Constructor */
    AlpsTreeSelectionDepth() { type_ = AlpsSearchTypeDepthFirst; }

    /** Default Destructor. */
    virtual ~AlpsTreeSelectionDepth() {}

    /** This returns true if the depth of the root node in subtree y
        is greater than that of the root node in subtree x. */
    virtual bool compare(AlpsSubTree * x, AlpsSubTree * y);
};

//#############################################################################

class ALPSLIB_EXPORT AlpsTreeSelectionEstimate : public AlpsTreeSelection
{
public:
    /** Default Constructor. */
    AlpsTreeSelectionEstimate() { type_ = AlpsSearchTypeBestEstimate; }

    /** Default Destructor. */
    virtual ~AlpsTreeSelectionEstimate() {}

    /** This returns true if the estimated quality of the subtree y is better
        (the less the better) than that the subtree x. */
    virtual bool compare(AlpsSubTree * x, AlpsSubTree * y);
};

//#############################################################################
// NODE SELECTION RULES
//#############################################################################

class ALPSLIB_EXPORT AlpsNodeSelectionBest : public AlpsNodeSelection
{
public:
    /** Default Constructor. */
    AlpsNodeSelectionBest() { type_ = AlpsSearchTypeBestFirst; }

    /** Default Destructor. */
    virtual ~AlpsNodeSelectionBest() {}

    /** This returns true if quality of node y is better (the less the better)
        than that of node x. */
    virtual bool compare(AlpsTreeNode * x, AlpsTreeNode * y) {
        return (x->getQuality() > y->getQuality());
    }
};

//#############################################################################

class ALPSLIB_EXPORT AlpsNodeSelectionBreadth : public AlpsNodeSelection
{
public:
    /** Default Constructor. */
    AlpsNodeSelectionBreadth() { type_ = AlpsSearchTypeBreadthFirst; }

    /** Default Destructor. */
    virtual ~AlpsNodeSelectionBreadth() {}

    /** This returns true if the depth of node y is lesser
        than that of node x */
    virtual bool compare(AlpsTreeNode * x, AlpsTreeNode * y) {
        return x->getDepth() > y->getDepth();
    }
};

//#############################################################################

class ALPSLIB_EXPORT AlpsNodeSelectionDepth : public AlpsNodeSelection
{
 public:
    /** Default Constructor. */
    AlpsNodeSelectionDepth() { type_ = AlpsSearchTypeDepthFirst; }

    /** Default Destructor. */
    virtual ~AlpsNodeSelectionDepth() {}

    /** This returns true if the depth of node y is greater than
        that of node x. */
    virtual bool compare(AlpsTreeNode * x, AlpsTreeNode * y) {
        return (x->getDepth() < y->getDepth());
    }
};

//#############################################################################

class ALPSLIB_EXPORT AlpsNodeSelectionEstimate : public AlpsNodeSelection
{
 public:
    /** Default Constructor. */
    AlpsNodeSelectionEstimate() { type_ = AlpsSearchTypeBestEstimate; }

    /** Default Destructor. */
    virtual ~AlpsNodeSelectionEstimate() {}

    /** This returns true if the estimate quality of node y is better
        (the lesser the better) than that of node x. */
    virtual bool compare (AlpsTreeNode * x, AlpsTreeNode * y) {
        return (x->getSolEstimate() > y->getSolEstimate());
    }
};

//#############################################################################

class ALPSLIB_EXPORT AlpsNodeSelectionHybrid : public AlpsNodeSelection
{
public:
    /** Default Constructor. */
    AlpsNodeSelectionHybrid() { type_ = AlpsSearchTypeHybrid; }

    /** Default Destructor. */
    virtual ~AlpsNodeSelectionHybrid() {}

    /** This returns true if the quality of node y is better (the lesser
        the better) than that of node x. */
    virtual bool compare(AlpsTreeNode * x, AlpsTreeNode * y) {
        // best first
        return (x->getQuality() > y->getQuality());
    }

    /* Select the next node to be processed. */
    virtual AlpsTreeNode* selectNextNode(AlpsSubTree *subTree);

    /* Create new nodes from pregnant node and store them in node pool. */
    virtual void createNewNodes(AlpsSubTree *subTree, AlpsTreeNode *node);
};

//#############################################################################
#endif
