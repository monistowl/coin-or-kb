/**
 * @file CbcSolverAnalyze.hpp
 * @brief Problem analysis for integer constraint detection
 * Copyright (C) 2007, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * analyze(): Examines model to detect integer structure.
 *
 * Looks for constraints where:
 * - All variables are integer
 * - All coefficients are integer
 * - RHS is integer
 *
 * Such constraints can be strengthened or exploited specially.
 * If changeInt is true, may change continuous variables to integer
 * when they only appear in integer-coefficient constraints.
 *
 * Returns array of changed variable indices.
 * Sets numberChanged to count of modifications.
 * Sets increment to objective coefficient GCD for integer solutions.
 *
 * @see CbcModel for problem analysis during solve
 * @see CoinPackedMatrix for constraint access
 */

#ifndef CbcSolverAnalyze_H
#define CbcSolverAnalyze_H

int *analyze(OsiClpSolverInterface *solverMod, int &numberChanged,
  double &increment, bool changeInt,
  CoinMessageHandler *generalMessageHandler, bool noPrinting);

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
