/*===========================================================================*/
/*                                                                           */
/* This file is part of a demonstration application for use with the         */
/* SYMPHONY Branch, Cut, and Price Library. This application is a solver for */
/* the Vehicle Routing Problem and the Traveling Salesman Problem.           */
/*                                                                           */
/* This application was developed by Ted Ralphs (ted@lehigh.edu)             */
/* This file was modified by Ali Pilatin January, 2005 (alp8@lehigh.edu)     */
/*                                                                           */
/* (c) Copyright 2000-2005 Ted Ralphs. All Rights Reserved.                  */
/*                                                                           */
/* This software is licensed under the Eclipse Public License. Please see    */
/* accompanying file for terms.                                              */
/*                                                                           */
/*===========================================================================*/

/**
 * @file heurs/lower_bound.h
 * @brief Lower bound computation for VRP branch-and-bound
 *
 * Computes lower bounds for pruning in the B&B tree.
 *
 * @algorithm VRP Lower Bounds:
 *   Compute bounds by relaxing integrality or capacity:
 *   @math 1. LP relaxation: Solve continuous relaxation of VRP
 *         2. 1-tree bound: MST + two shortest edges at depot
 *              LB = MST(V\{depot}) + 2 shortest depot edges
 *         3. Bin packing bound: ⌈Σ demands / capacity⌉ vehicles
 *   Bounds used to prune B&B nodes where LB ≥ UB.
 *   @complexity O(n²) for 1-tree, O(n log n) for bin packing
 *   @ref Christofides, N. et al. (1981). "Exact algorithms for the
 *        vehicle routing problem". Discrete Applied Mathematics.
 *
 * @see vrp_types.h for problem structure
 * @see lb_params.h for bound computation parameters
 */
#ifndef _LOWER_BOUND_H
#define _LOWER_BOUND_H

#include "sym_proto.h"
#include "vrp_types.h"
#include "heur_types.h"
#include "lb_params.h"

void lower_bound PROTO((vrp_problem *vrp, lb_params *lb_par,
			heurs *lh, int ub, int jobs, int *tids, int *sent));

#endif
