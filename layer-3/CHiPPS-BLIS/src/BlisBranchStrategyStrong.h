/*===========================================================================*
 * This file is part of the BiCePS Linear Integer Solver (BLIS).             *
 *                                                                           *
 * ALPS is distributed under the Eclipse Public License as part of the       *
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
 * @file BlisBranchStrategyStrong.h
 * @brief Strong branching strategy for MILP variable selection
 *
 * @algorithm Strong Branching:
 * Most accurate but expensive branching variable selection.
 * Actually solves child LP relaxations to measure bound improvement.
 *
 *   PROCEDURE:
 *     For each fractional integer variable xⱼ with value x*_j:
 *       1. DOWN: Fix xⱼ ≤ ⌊x*_j⌋, solve LP (limited iterations)
 *          Record ΔDown = z_down - z_parent
 *       2. UP: Fix xⱼ ≥ ⌈x*_j⌉, solve LP (limited iterations)
 *          Record ΔUp = z_up - z_parent
 *
 *   SCORING:
 *     score(j) = μ·min(ΔDown, ΔUp) + (1-μ)·max(ΔDown, ΔUp)
 *     Balances worst-case vs best-case improvement
 *     μ = 1/6 typical (prioritize weak side slightly)
 *
 *   SELECTION:
 *     Choose j* = argmax_j score(j)
 *     Highest score = most balanced bound improvement
 *
 * @math
 *   Ideal: both branches improve bound significantly
 *   If one branch infeasible: even better (immediate pruning)
 *   Expected tree size minimized by strong branching
 *
 * @complexity
 *   Per node: O(k × LP_time) where k = candidates tested
 *   k typically = numIntegerInf (all fractional integers)
 *   With limits: k bounded, LP iterations bounded
 *
 * @see BlisBranchStrategyRel for reliability branching (strong + pseudo-cost hybrid)
 * @see BlisBranchStrategyPseudo for pure pseudo-cost branching
 */

//#############################################################################
// NOTE: Borrow ideas from COIN/Cbc
//#############################################################################


#ifndef BlisBranchStrategyStrong_h_
#define BlisBranchStrategyStrong_h_

#include "BcpsBranchObject.h"
#include "BcpsBranchStrategy.h"
#include "BlisConfig.h"
#include "BlisModel.h"


//#############################################################################


typedef struct {
    int objectIndex;            // object index
    BcpsBranchObject * bObject; // the branching object
    int numIntInfUp;            // without odd ones
    int numObjInfUp;            // just odd ones
    bool finishedUp;            // true if solver finished
    int numIntInfDown;          // without odd ones
    int numObjInfDown;          // just odd ones
    bool finishedDown;          // true if solver finished
} BlisStrong;


//#############################################################################


/** This class implements strong branching. */
class BLISLIB_EXPORT BlisBranchStrategyStrong : public BcpsBranchStrategy {

 private:

    /** Illegal Assignment operator.*/
    BlisBranchStrategyStrong& operator=(const BlisBranchStrategyStrong& rhs);
    
 public:
    
    /** Strong Constructor. */
    BlisBranchStrategyStrong() {
	type_ = static_cast<int>(BlisBranchingStrategyStrong);
    }

    /** Strong Constructor. */
    BlisBranchStrategyStrong(BlisModel *model)
        : BcpsBranchStrategy(model) {
	type_ = static_cast<int>(BlisBranchingStrategyStrong);
    }
    
    /** Destructor. */
    virtual ~BlisBranchStrategyStrong() {}
    
    /** Copy constructor. */
    BlisBranchStrategyStrong(const BlisBranchStrategyStrong &);
    
    /** Clone a brancing strategy. */
    virtual BcpsBranchStrategy * clone() const {
	return new BlisBranchStrategyStrong(*this);
    }
    
    /** Create a set of candidate branching objects. */
    virtual int createCandBranchObjects(int numPassesLeft, double ub);
    
    /** Compare branching object thisOne to bestSoFar. If thisOne is better 
	than bestObject, return branching direction(1 or -1), otherwise
	return 0. 
	If bestSorFar is NULL, then always return branching direction(1 or -1).
    */
    virtual int betterBranchObject(BcpsBranchObject * thisOne,
				   BcpsBranchObject * bestSoFar);
};

#endif
