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
 * @file BlisBranchStrategyPseudo.h
 * @brief Pseudo-cost branching strategy based on historical LP degradation
 *
 * Pseudo-cost branching uses learned estimates of objective degradation
 * to select branching variables without solving child LPs.
 *
 * **Pseudo-cost definition:**
 * For variable xⱼ with fractional value fⱼ = xⱼ* - floor(xⱼ*):
 * - ψⱼ⁻ = average (ΔObj / fⱼ) over down branches
 * - ψⱼ⁺ = average (ΔObj / (1-fⱼ)) over up branches
 *
 * **Algorithm:**
 * 1. For each fractional integer variable xⱼ with value xⱼ*:
 *    - Estimate down degradation: Δ⁻ = ψⱼ⁻ · fⱼ
 *    - Estimate up degradation: Δ⁺ = ψⱼ⁺ · (1-fⱼ)
 *    - Score = μ·min(Δ⁻, Δ⁺) + (1-μ)·max(Δ⁻, Δ⁺)
 * 2. Select variable with highest score
 *
 * **Initialization:**
 * Before enough observations, uses default pseudo-costs or
 * falls back to other criteria (objective coefficient, etc.)
 *
 * **Complexity:** O(n) where n = number of integer variables
 * Much faster than strong branching but less accurate.
 *
 * @see BlisPseudo for pseudo-cost data structure
 * @see BlisBranchStrategyRel for reliability branching (hybrid approach)
 * @see BlisBranchStrategyStrong for strong branching
 */

//#############################################################################
// NOTE: Borrow ideas from COIN/Cbc
//#############################################################################


#ifndef BlisBranchStrategyPseudo_h_
#define BlisBranchStrategyPseudo_h_

#include "BcpsBranchObject.h"
#include "BcpsBranchStrategy.h"
#include "BlisConfig.h"
#include "BlisModel.h"


/** Blis branching strategy.
    This class implements pseudocost branching. */
class BLISLIB_EXPORT BlisBranchStrategyPseudo : public BcpsBranchStrategy {

 private:
    /** Illegal Assignment operator.*/
    BlisBranchStrategyPseudo& operator=(const BlisBranchStrategyPseudo& rhs);

    int relibility_;
    
 public:

    /** Default Constructor. */
    BlisBranchStrategyPseudo() : relibility_(1) {
	relibility_ = 1;
	type_ = static_cast<int>(BlisBranchingStrategyPseudoCost);
    }

    /** Useful Constructor. */
    BlisBranchStrategyPseudo(BlisModel *model, int rel)
	: BcpsBranchStrategy(model) {
        relibility_ = rel;
	type_ = static_cast<int>(BlisBranchingStrategyPseudoCost);
    }

    /** Destructor. */
    virtual ~BlisBranchStrategyPseudo() {}
    
    /** Copy constructor. */
    BlisBranchStrategyPseudo(const BlisBranchStrategyPseudo &);
    
    /** Set relibility. */
    void setRelibility(int rel) { relibility_ = rel; }    

    /** Clone a brancing strategy. */
    virtual BcpsBranchStrategy * clone() const {
	return new BlisBranchStrategyPseudo(*this);
    }
    
    /** Compare branching object thisOne to bestSoFar. If thisOne is better 
	than bestObject, return branching direction(1 or -1), otherwise
	return 0. 
	If bestSorFar is NULL, then always return branching direction(1 or -1).
    */
    virtual int betterBranchObject(BcpsBranchObject * thisOne,
				   BcpsBranchObject * bestSoFar);

    /** Create a set of candidate branching objects. */
    virtual int createCandBranchObjects(int numPassesLeft, double ub);
};

#endif
