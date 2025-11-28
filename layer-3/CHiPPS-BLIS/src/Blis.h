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
 * @file Blis.h
 * @brief Core enumerations and constants for BLIS (BiCePS Linear Integer Solver)
 *
 * BLIS is a concrete implementation of the CHiPPS framework for MILP.
 * Hierarchy: ALPS (parallel search) → BiCePS (branch-cut-price) → BLIS (MILP).
 *
 * **BlisLpStatus enum:**
 * LP relaxation solve outcomes (Optimal, Infeasible, IterLim, etc.)
 *
 * **BlisReturnStatus enum:**
 * Node processing outcomes (Ok, ErrLp, Feasible, Branch, etc.)
 *
 * **BlisCutStrategy enum:**
 * - NotSet, None: No cut generation
 * - Root: Generate cuts only at root node
 * - Auto: Automatic frequency selection
 * - Periodic: Generate every cutGenerationFrequency_ nodes
 *
 * **BlisHeurStrategy enum:**
 * Same as cut strategy plus BeforeRoot (e.g., feasibility pump)
 *
 * **BlisBranchingStrategy enum:**
 * - MaxInfeasibility: Branch on most fractional variable
 * - PseudoCost: Use pseudo-costs from LP degradation
 * - Reliability: Pseudo-costs with strong branching fallback
 * - Strong: Full strong branching (solve child LPs)
 * - Bilevel: For bilevel programming problems
 *
 * **BlisBranchingObjectType enum:**
 * Integer variables, SOS constraints, bilevel variables
 *
 * @see BlisModel for the MILP model class
 * @see BlisTreeNode for node processing
 * @see BlisParams for parameter configuration
 */

//#############################################################################

#ifndef Blis_h_
#define Blis_h_

#include "AlpsConfig.h"
#include "BcpsConfig.h"
#include "BlisConfig.h"

//#############################################################################

enum BlisLpStatus{
   BlisLpStatusOptimal,
   BlisLpStatusAbandoned,
   BlisLpStatusPrimalInfeasible,
   BlisLpStatusDualInfeasible,
   BlisLpStatusPrimalObjLim,
   BlisLpStatusDualObjLim,
   BlisLpStatusIterLim,
   BlisLpStatusUnknown
};

//#############################################################################

enum BlisReturnStatus {
   BlisReturnStatusOk = 0,
   BlisReturnStatusErrLp,
   BlisReturnStatusInfeasible,
   BlisReturnStatusUnbounded,
   BlisReturnStatusOverObjLim,
   BlisReturnStatusFeasible,
   BlisReturnStatusBranch,
   BlisReturnStatusUnknown
};

#if 0
#define BLIS_ERR_LP         100
#define BLIS_INF            200
#define BLIS_UNBOUND        201
#define BLIS_OPTIMAL          0
#define BLIS_UNKNOWN        202
#endif

//#############################################################################

enum BlisCutStrategy{
   BlisCutStrategyNotSet = -1,
   BlisCutStrategyNone = 0,
   BlisCutStrategyRoot,
   BlisCutStrategyAuto,
   BlisCutStrategyPeriodic
};

enum BlisHeurStrategy{
   BlisHeurStrategyNotSet = -1,
   BlisHeurStrategyNone = 0,
   BlisHeurStrategyRoot,
   BlisHeurStrategyAuto,
   BlisHeurStrategyPeriodic,
   BlisHeurStrategyBeforeRoot // Before solving first relaxation
};

#if 0
#define BLIS_NOT_SET       -555
#define BLIS_ROOT            -2
#define BLIS_AUTO            -1
#define BLIS_NONE             0
#endif

//#############################################################################

enum BlisHotStartStrategy{
   BlisHotStartBranchIncorrect,
   BlisHotStartBranchCorrect
};

//#############################################################################

enum BlisBranchingStrategy{
   BlisBranchingStrategyMaxInfeasibility,
   BlisBranchingStrategyPseudoCost,
   BlisBranchingStrategyReliability,   
   BlisBranchingStrategyStrong,
   BlisBranchingStrategyBilevel
};

//#############################################################################

enum BlisSolutionType {
    BlisSolutionTypeBounding,
    BlisSolutionTypeBranching,
    BlisSolutionTypeDiving,
    BlisSolutionTypeHeuristic,
    BlisSolutionTypeStrong
};

//#############################################################################

/** Branching object type. */
enum BlisBranchingObjectType {
    BlisBranchingObjectTypeNone = 0,
    BlisBranchingObjectTypeInt,
    BlisBranchingObjectTypeSos,
    BlisBranchingObjectTypeBilevel
};

//#############################################################################

#define BLIS_CUT_DISABLE            20

#define BLIS_HEUR_ROUND_DISABLE     1000000

#define BLIS_PSEUDO                 21

//#############################################################################

#endif
