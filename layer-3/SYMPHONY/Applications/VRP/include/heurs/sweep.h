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
 * @file heurs/sweep.h
 * @brief Sweep heuristic for VRP construction
 *
 * Classic construction heuristic that builds routes by angular sweep.
 *
 * **sweep_data structure:**
 * - angle: Polar angle from depot
 * - cust: Customer identifier
 *
 * @algorithm Sweep Heuristic:
 *   Construct VRP solution by sweeping customers angularly from depot:
 *   @math 1. Compute polar angle θ_i = atan2(y_i - y_depot, x_i - x_depot)
 *         2. Sort customers by angle θ
 *         3. Starting from angle 0, add customers to current route
 *         4. When capacity exceeded, start new route
 *         5. Optimize each route as TSP (via make_tour)
 *   @complexity O(n log n) for sorting + O(n·k) route construction
 *   @ref Gillett, B. and Miller, L. (1974). "A heuristic algorithm for
 *        the vehicle-dispatch problem". Operations Research 22(2):340-349.
 *
 * @see savings.h for alternative construction heuristic
 * @see heur_routines.h for TSP improvement
 */
#ifndef SWEEP_H
#define SWEEP_H

#include <math.h>
#include <stdlib.h>

#include "heur_types.h"
#include "heur_common.h"
#include "sym_constants.h"
#include "heur_routines.h"

typedef struct SWEEP_DATA{
   float angle;
   int cust;
}sweep_data;


void make_tour PROTO((heur_prob *p, sweep_data *data, best_tours *final_tour));

void sweep PROTO((int parent, heur_prob *p));

#endif
