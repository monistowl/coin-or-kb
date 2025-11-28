/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file simplex/HSimplex.h
 * @brief Simplex utility functions
 *
 * Standalone functions for simplex basis and scaling operations.
 *
 * **Basis Extension:**
 * - appendNonbasicColsToBasis(): Add new columns as nonbasic
 * - appendBasicRowsToBasis(): Add new rows as basic (slack variables)
 * Works with both HighsBasis and SimplexBasis.
 *
 * **Solution Status:**
 * - getUnscaledInfeasibilities(): Compute infeasibilities in original space
 * - setSolutionStatus(): Set primal/dual solution status in HighsInfo
 *
 * **Scaling:**
 * - scaleSimplexCost(): Scale objective coefficients
 * - unscaleSimplexCost(): Reverse objective scaling
 *
 * **Validation:**
 * - isBasisRightSize(): Check SimplexBasis dimensions match LP
 *
 * @see simplex/HEkk.h for main simplex solver class
 * @see simplex/SimplexStruct.h for SimplexBasis definition
 */
#ifndef SIMPLEX_HSIMPLEX_H_
#define SIMPLEX_HSIMPLEX_H_

#include "lp_data/HighsInfo.h"
#include "lp_data/HighsLp.h"

void appendNonbasicColsToBasis(HighsLp& lp, HighsBasis& highs_basis,
                               HighsInt XnumNewCol);
void appendNonbasicColsToBasis(HighsLp& lp, SimplexBasis& basis,
                               HighsInt XnumNewCol);

void appendBasicRowsToBasis(HighsLp& lp, HighsBasis& highs_basis,
                            HighsInt XnumNewRow);
void appendBasicRowsToBasis(HighsLp& lp, SimplexBasis& basis,
                            HighsInt XnumNewRow);

void getUnscaledInfeasibilities(const HighsOptions& options,
                                const HighsScale& scale,
                                const SimplexBasis& basis,
                                const HighsSimplexInfo& info,
                                HighsInfo& highs_info);

void setSolutionStatus(HighsInfo& highs_info);
// SCALE:

void scaleSimplexCost(const HighsOptions& options, HighsLp& lp,
                      double& cost_scale);
void unscaleSimplexCost(HighsLp& lp, double cost_scale);

bool isBasisRightSize(const HighsLp& lp, const SimplexBasis& basis);

#endif  // SIMPLEX_HSIMPLEX_H_
