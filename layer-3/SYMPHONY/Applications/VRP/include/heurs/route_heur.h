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
 * @file heurs/route_heur.h
 * @brief Route-first cluster-second heuristic for VRP
 *
 * Two-phase heuristic that builds giant tour then partitions into routes.
 *
 * @algorithm Route-First Cluster-Second:
 *   Build VRP solution by routing all customers then partitioning:
 *   @math Phase 1 (Route): Build giant TSP tour through all customers
 *           - Ignores vehicle capacity
 *           - Uses insertion heuristic or 2-opt improvement
 *         Phase 2 (Cluster): Partition tour into feasible routes
 *           - Split tour at capacity-violating positions
 *           - Each segment becomes one vehicle route
 *   Giant tour quality affects final solution quality.
 *   @complexity O(n²) TSP construction + O(n) partitioning
 *   @ref Beasley, J. (1983). "Route first--cluster second methods for
 *        vehicle routing". Omega 11(4):403-408.
 *
 * @see cluster_heur.h for cluster-first approach
 * @see ins_routines.h for TSP insertion methods
 */
#ifndef ROUTE_HEUR_H
#define ROUTE_HEUR_H 

#include "vrp_types.h"
#include "heur_types.h"

void route_heur PROTO((vrp_problem *vrp, heur_params *heur_par, 
		      heurs *rh, int trials, int jobs,  int *tids, 
		       int *sent, best_tours *solutions));

#endif
