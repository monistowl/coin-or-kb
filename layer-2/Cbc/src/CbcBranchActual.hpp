/**
 * @file CbcBranchActual.hpp
 * @brief Aggregator for concrete branching classes
 *
 * @algorithm Branching Object Implementation Collection
 * Copyright (C) 2002, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * Convenience header that includes all concrete branching implementations:
 * - CbcSimpleInteger, CbcSimpleIntegerPseudoCost: Integer variables
 * - CbcClique, CbcSOS, CbcNWay: Constraint branching
 * - CbcFollowOn, CbcFixVariable: Derived bound manipulation
 * - CbcGeneral, CbcGeneralDepth: Advanced branching strategies
 *
 * Most code should include CbcBranchBase.hpp instead for just the
 * abstract interfaces; use this header when concrete classes are needed.
 *
 * @see CbcBranchBase.hpp for abstract interface aggregation
 */

#ifndef CbcBranchActual_H
#define CbcBranchActual_H

#include "CbcBranchBase.hpp"
#include "CoinPackedMatrix.hpp"
#include "CbcClique.hpp"
#include "CbcSOS.hpp"
#include "CbcSimpleInteger.hpp"
#include "CbcNWay.hpp"
#include "CbcSimpleIntegerPseudoCost.hpp"
#include "CbcBranchDefaultDecision.hpp"
#include "CbcFollowOn.hpp"
#include "CbcFixVariable.hpp"
#include "CbcDummyBranchingObject.hpp"
#include "CbcGeneral.hpp"
#include "CbcGeneralDepth.hpp"
#include "CbcSubProblem.hpp"
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
