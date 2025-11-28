/*===========================================================================*
 * This file is part of the BiCePS Linear Integer Solver (BLIS).             *
 *                                                                           *
 * BLIS is distributed under the Eclipse Public License as part of the       *
 * COIN-OR repository (http://www.coin-or.org).                              *
 *                                                                           *
 * Authors:                                                                  *
 *                                                                           *
 *          Yan Xu, Lehigh University                                        *
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
 * Copyright (C) 2001-2023, Lehigh University, Yan Xu, and Ted Ralphs.       *
 * All Rights Reserved.                                                      *
 *===========================================================================*/

/**
 * @file BlisTreeNode.h
 * @brief Concrete branch-and-bound tree node for MILP solving
 *
 * BlisTreeNode extends BcpsTreeNode with LP-based bounding and cut generation.
 * Implements the main node processing loop for branch-and-cut.
 *
 * **Node processing (process()):**
 * 1. installSubProblem(): Set up LP with current bounds
 * 2. bound(): Solve LP relaxation
 * 3. callHeuristics(): Search for integer solutions
 * 4. generateConstraints(): Add cutting planes
 * 5. selectBranchObject(): Choose branching variable
 * 6. branch(): Create child nodes
 *
 * **Cut generation workflow:**
 * - generateConstraints(): Call registered CglCutGenerators
 * - getViolatedConstraints(): Check for violated cuts
 * - applyConstraints(): Add cuts to LP and re-solve
 * - parallel(): Remove duplicate/parallel cuts
 *
 * **Bound tightening:**
 * - reducedCostFix(): Fix variables using reduced costs
 *
 * **Node descriptions:**
 * - convertToExplicit(): Full bound/cut information
 * - convertToRelative(): Delta from parent (space-efficient)
 *
 * **Branching:**
 * - selectBranchObject(): Use model's BcpsBranchStrategy
 * - branch(): Create children with modified bounds
 *
 * @see BlisModel for the model containing LP solver and generators
 * @see BlisNodeDesc for node description structure
 * @see BcpsBranchStrategy for branching variable selection
 */

#ifndef BlisTreeNode_h_
#define BlisTreeNode_h_

//#############################################################################

#include "AlpsNodeDesc.h"

#include "BcpsObjectPool.h"
#include "BcpsTreeNode.h"

#include "BcpsNodeDesc.h"
#include "BlisConfig.h"
#include "BlisNodeDesc.h"

class BcpsModel;
class BlisModel;


//#############################################################################
/** This is the class in which we are finally able to concretely define the
    bounding procedure. Here we can assume that we have an LP solver and that
    the objects are cuts and variables, etc. */
//#############################################################################


class BLISLIB_EXPORT BlisTreeNode : public BcpsTreeNode {
private:
    
    /** No copy constructor, assignment operator. */
    BlisTreeNode(const BlisTreeNode&);
    
    BlisTreeNode& operator=(const BlisTreeNode&);
    
    /** Constraint pool. */
    //BcpsConstraintPool *constraintPool_;
    
    /** Variable pool. */
    //BcpsVariablePool *variablePool_;

    /** Save an explicit node description. */
    //void saveExplicit();
    
    /** Check and remove parallel constraints. */
    bool parallel(BlisModel *model,
		  BcpsConstraintPool &conPool,
		  int lastNew,
		  BlisConstraint *aCon);

    /** Estimate quality of a feasible solution. */
    double estimateSolution(BlisModel *model,
                            const double *lpSolution,
                            double lpObjValue) const;
    
public:

    /** Default constructor. */
    BlisTreeNode() 
        : 
        BcpsTreeNode() 
        { init(); }
    
    /** Useful constructor. */
    BlisTreeNode(BlisModel* m) {
        init();
        desc_ = new BlisNodeDesc(m);
    }

    /** Useful constructor. */
    BlisTreeNode(AlpsNodeDesc *&desc) {
        init();
        desc_ = desc;
        desc = NULL;
    }

    /** Destructor. */
    virtual ~BlisTreeNode() {
	//std::cout << "------ Delete blis part of node" << std::endl;
    }
    
    /** Initilize member data when constructing a node. */
    void init() {
        //constraintPool_ = new BcpsConstraintPool;
        //variablePool_ = new BcpsVariablePool;
    }
    
    /** Create a new node based on given desc. */
    AlpsTreeNode* createNewTreeNode(AlpsNodeDesc *&desc) const;

    /** Convert explicit description to difference, and vise-vesa */
    ///@{
    virtual void convertToExplicit();
    virtual void convertToRelative();
    ///@}
    
    /** intall subproblem */
    virtual int installSubProblem(BcpsModel *mode);
    
    /** Performing the bounding operation. */
    virtual int process(bool isRoot = false, bool rampUp = false);
    
    /** Bounding procedure */
    virtual int bound(BcpsModel *model);

    /** Takes the explicit description of the current active node and 
        creates the children's descriptions, which contain information 
        about how the branching is to be done. The stati of the children
        are AlpsNodeStatusCandidate. */
    virtual std::vector< CoinTriple<AlpsNodeDesc*, AlpsNodeStatus, double> > 
	branch();
    
    /** Select a branching object based on give branching strategy. */
    int selectBranchObject(BlisModel *model, 
                           bool& foundSol, 
                           int numPassesLeft);

    /** To be defined. */
    virtual int chooseBranchingObject(BcpsModel*) { return AlpsReturnStatusOk;}
    
    // Why need below?
    //using BcpsTreeNode::generateConstraints ;

    /** Generate constraints. */
    int generateConstraints(BlisModel *model, BcpsConstraintPool &conPool);

    /** Call heuristic to search solutions.
     *  0: no solution; 1: found solutions; 2: fathom this node.
     *  onlyBeforeRoot is for heuristics like feasibility pump.
     */
    int callHeuristics(BlisModel *model, bool onlyBeforeRoot=false);

    /** Get violated constraints. */
    void getViolatedConstraints(BlisModel *model, 
				const double *currLpSolution, 
				BcpsConstraintPool & conPool);

    /** Select and apply constraints. */
    BlisReturnStatus applyConstraints(BlisModel *model,
				      const double *solution,
                                      BcpsConstraintPool & conPool); 

    /** Fix and tighten varaibles based optimality conditions. */
    BlisReturnStatus reducedCostFix(BlisModel *model);

    /** Return constraint pool. */
    //BcpsConstraintPool * constraintPool() { return constraintPool_; }

    /** Return variable pool. */
    //BcpsVariablePool * variablePool() { return variablePool_; }
    
    using AlpsKnowledge::encode ;
    /** Encode this node for message passing. */
    virtual AlpsEncoded* encode() const;

    /** Decode a node from an encoded object. */
    virtual AlpsKnowledge* decode(AlpsEncoded&) const;
};

#endif
