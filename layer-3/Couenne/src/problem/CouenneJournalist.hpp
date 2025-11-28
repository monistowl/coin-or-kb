//
// Copyright (C) 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License (EPL).
//
// Author:  Andreas Waechter           IBM    2007-12-04

/**
 * @file CouenneJournalist.hpp
 * @brief Couenne-specific logging categories using Ipopt's Journalist
 *
 * Extends Ipopt's Journalist logging facility with Couenne-specific
 * categories for selective debug output.
 *
 * **Log categories defined:**
 * - J_BRANCHING: Branch-and-bound variable selection
 * - J_BOUNDTIGHTENING: FBBT and OBBT progress
 * - J_CONVEXIFYING: Cut generation and convexification
 * - J_PROBLEM: Problem construction and reformulation
 * - J_NLPHEURISTIC: NLP solve heuristics
 * - J_DISJCUTS: Disjunctive cut generation (CGLP)
 * - J_REFORMULATE: Expression reformulation
 * - J_COUENNE: General Couenne messages
 *
 * **Usage:**
 * ```cpp
 * jnlst->Printf(J_SUMMARY, J_BRANCHING,
 *               "Selected var %d with score %.2f\n", idx, score);
 * ```
 *
 * **Verbosity levels (from Ipopt):**
 * - J_NONE, J_ERROR, J_WARNING, J_SUMMARY, J_DETAILED, ...
 *
 * @see Ipopt::Journalist for full logging API
 */
// This file is a wrapper for the Journalist from the Ipopt project.
// The only thing it adds over the original Journalist class is that
// the names are easier to reach, and that the categories are given
// real names.

#ifndef CouenneJournalist_hpp
#define CouenneJournalist_hpp

#include "IpJournalist.hpp"

namespace Couenne {

typedef Ipopt::SmartPtr<Ipopt::Journalist> JnlstPtr;
typedef Ipopt::SmartPtr<const Ipopt::Journalist> ConstJnlstPtr;

const Ipopt::EJournalCategory J_BRANCHING       (Ipopt::J_USER1);
const Ipopt::EJournalCategory J_BOUNDTIGHTENING (Ipopt::J_USER2);
const Ipopt::EJournalCategory J_CONVEXIFYING    (Ipopt::J_USER3);
const Ipopt::EJournalCategory J_PROBLEM         (Ipopt::J_USER4);
const Ipopt::EJournalCategory J_NLPHEURISTIC    (Ipopt::J_USER5);
const Ipopt::EJournalCategory J_DISJCUTS        (Ipopt::J_USER6);
const Ipopt::EJournalCategory J_REFORMULATE     (Ipopt::J_USER7);
const Ipopt::EJournalCategory J_COUENNE         (Ipopt::J_USER8);

}

#endif
