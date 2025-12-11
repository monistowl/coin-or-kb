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
 * @file heurs/savings.h
 * @brief Clarke-Wright Savings heuristic for VRP
 *
 * Classic construction heuristic for Vehicle Routing Problem.
 *
 * @algorithm Clarke-Wright Savings:
 *   Build VRP solution by merging routes based on savings:
 *   @math savings(i,j) = d(depot,i) + d(depot,j) - d(i,j)
 *         Start with n routes (depot → customer → depot)
 *         Sort customer pairs by savings (descending)
 *         Merge routes i-depot and depot-j if:
 *           - i is last on its route, j is first on its route
 *           - Merged route satisfies capacity constraint
 *         Repeat until no feasible merges remain
 *   @complexity O(n² log n) for sorting + O(n²) for merges
 *   @ref Clarke, G. and Wright, J. (1964). "Scheduling of vehicles
 *        from a central depot to a number of delivery points".
 *        Operations Research 12(4):568-581.
 *
 * @see savings2.h, savings3.h for variants
 * @see heur_types.h for heur_prob structure
 */
#ifndef SAVINGS_H
#define SAVINGS_H

#include "heur_types.h"
#include "heur_common.h"

void savings PROTO((int parent, heur_prob *p));

#endif
