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
 * @file BlisBranchStrategyBilevel.h
 * @brief Branching strategy for bilevel programming problems
 *
 * Specialized branching for bilevel optimization problems where there
 * is a leader (upper-level) and follower (lower-level) decision maker.
 *
 * **Bilevel programming:**
 * - Leader optimizes over (x, y) where y solves follower's problem
 * - min_x { F(x, y) : G(x, y) ≥ 0, y ∈ argmin_y { f(x, y) : g(x, y) ≥ 0 } }
 * - MILP reformulation uses complementarity or indicator constraints
 *
 * **Branching approach:**
 * Typically branches on complementarity-related variables or
 * uses specialized selection for leader vs. follower variables.
 *
 * @see BlisBranchObjectBilevel for bilevel branching objects
 * @see BlisBranchStrategyStrong for standard strong branching
 */

#ifndef BlisBranchStrategyBilevel_h_
#define BlisBranchStrategyBilevel_h_

#include "BcpsBranchObject.h"
#include "BcpsBranchStrategy.h"
#include "BlisConfig.h"
#include "BlisModel.h"

/** This class implements maximum infeasibility branching. */
class BLISLIB_EXPORT BlisBranchStrategyBilevel : public BcpsBranchStrategy {

 private:

    /** Illegal Assignment operator.*/
    BlisBranchStrategyBilevel& operator=(const BlisBranchStrategyBilevel& rhs);
    
 public:
    
    /** Bilevel Constructor. */
    BlisBranchStrategyBilevel(){
	type_ = static_cast<int>(BlisBranchingStrategyBilevel);
    }
  
    /** Bilevel Constructor. */
    BlisBranchStrategyBilevel(BlisModel *model) : BcpsBranchStrategy(model) {
	type_ = static_cast<int>(BlisBranchingStrategyBilevel);
    }
  
    /** Destructor. */
    virtual ~BlisBranchStrategyBilevel() {}
  
    /** Copy constructor. */
    BlisBranchStrategyBilevel(const BlisBranchStrategyBilevel &);
    
    /** Clone a brancing strategy. */
    virtual BcpsBranchStrategy * clone() const {
	return new BlisBranchStrategyBilevel(*this);
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
