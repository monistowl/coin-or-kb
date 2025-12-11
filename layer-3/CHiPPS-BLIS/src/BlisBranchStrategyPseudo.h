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
 * @algorithm Pseudo-Cost Branching:
 * Fast variable selection using learned estimates from history.
 * Key observation: similar variables cause similar objective changes.
 *
 *   PSEUDO-COST DEFINITION:
 *     For variable xⱼ with fractional value f = x*_j - ⌊x*_j⌋:
 *       ψⱼ⁻ = (1/n_down) × Σ (ΔObj_k / f_k)  over down branches
 *       ψⱼ⁺ = (1/n_up) × Σ (ΔObj_k / (1-f_k))  over up branches
 *     Normalized by fractional part for scale-invariance
 *
 *   PREDICTION:
 *     Δ_down ≈ ψⱼ⁻ × f     (expected down degradation)
 *     Δ_up ≈ ψⱼ⁺ × (1-f)   (expected up degradation)
 *
 *   SCORING (same as strong branching):
 *     score(j) = μ·min(Δ_down, Δ_up) + (1-μ)·max(Δ_down, Δ_up)
 *
 *   LEARNING:
 *     After each branch, update pseudo-cost:
 *     ψⱼ⁻ = (old_sum + new_sample) / (old_count + 1)
 *
 * @math
 *   Assumption: ΔObj ∝ fractional part (linear approximation)
 *   Better estimate with more samples: variance ~ 1/n
 *   Initialization problem: no data for variables not yet branched on
 *
 * @complexity
 *   O(k) per node where k = number of fractional integers
 *   No LP solves required (vs O(k × LP_time) for strong branching)
 *   Trade-off: larger tree but faster node processing
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
