/*
 *
 * Name:    CouenneInfeasCut.hpp
 * Author:  Pietro Belotti
 * Purpose: An infeasible cut to tell the node solver this node is infeasible
 *
 * (C) Pietro Belotti, 2010.
 * This file is licensed under the Eclipse Public License (EPL)
 */

/**
 * @file CouenneInfeasCut.hpp
 * @brief Signal infeasibility via fictitious cut
 *
 * Mechanism for bound tighteners to signal detected infeasibility
 * to the node solver without early termination.
 *
 * **WipeMakeInfeas():**
 * Adds a fictitious cut 1 ≤ x₀ ≤ -1 to the cut set. This
 * impossible constraint signals to subsequent components that
 * the node is infeasible.
 *
 * **isWiped():**
 * Checks whether the cut set contains the infeasibility signal.
 * Cut generators should check this before expensive operations.
 *
 * **Why needed:**
 * In Cgl's cut generator framework, generators cannot directly
 * prune nodes. This sentinel cut mechanism allows bound tighteners
 * to signal infeasibility discovered during FBBT/OBBT.
 *
 * @see CouenneFixPoint which may detect infeasibility
 * @see CouenneAggrProbing which may detect infeasibility
 */
#ifndef COUENNEINFEASCUT_HPP
#define COUENNEINFEASCUT_HPP

#include "OsiCuts.hpp"

/// Add a fictitious cut 1<= x_0 <= -1 as a signal to the node solver
/// that this node is deemed infeasible by this cut generator (most
/// likely a bound tightener).

void WipeMakeInfeas (OsiCuts &cs);


/// Check whether the previous cut generators have added an infeasible
/// cut.

bool isWiped (OsiCuts &cs);

#endif
