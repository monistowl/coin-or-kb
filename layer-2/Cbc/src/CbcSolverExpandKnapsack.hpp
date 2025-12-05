/**
 * @file CbcSolverExpandKnapsack.hpp
 * @brief Knapsack constraint expansion for tighter formulations
 *
 * @algorithm Knapsack Enumeration Reformulation
 * Copyright (C) 2007, IBM Corporation and others. All Rights Reserved.
 * This code is licensed under the terms of the Eclipse Public License (EPL).
 *
 * expandKnapsack(): Transforms x*y products (both integer) into knapsack form.
 *
 * Creates tighter formulation by:
 * - Enumerating possible x*y values
 * - Creating auxiliary binary variables for each value
 * - Adding SOS constraints for mutual exclusion
 *
 * Outputs:
 * - whichColumn: Mapping from new to original columns
 * - knapsackStart/knapsackRow: Structure of expanded knapsacks
 * - stored: Generated cuts from expansion
 * - tightenedModel: Reformulated CoinModel
 *
 * afterKnapsack(): Recovers original solution from expanded form.
 * Maps knapsackSolution back to original variable values.
 *
 * @see CoinModel for model representation
 * @see CglStored for storing generated cuts
 */

#ifndef CbcSolverExpandKnapsack_H
#define CbcSolverExpandKnapsack_H

OsiSolverInterface *
expandKnapsack(CoinModel &model, int *whichColumn, int *knapsackStart,
  int *knapsackRow, int &numberKnapsack,
  CglStored &stored, int logLevel,
  int fixedPriority, int SOSPriority, CoinModel &tightenedModel);

void afterKnapsack(const CoinModel &coinModel2, const int *whichColumn, const int *knapsackStart,
  const int *knapsackRow, int numberKnapsack,
  const double *knapsackSolution, double *solution, int logLevel);

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
