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
 * @file heurs/exchange_heur.h
 * @brief Inter-route exchange improvement heuristic for VRP
 *
 * Local search heuristic that improves VRP solutions via customer exchanges.
 *
 * @algorithm Inter-Route Exchange:
 *   Improve VRP solution by moving/swapping customers between routes:
 *   @math Exchange moves:
 *           - Relocate: Move customer i from route r to route s
 *           - Swap: Exchange customer i in route r with j in route s
 *           - 2-opt*: Reconnect route tails (cross-exchange)
 *         Accept move if:
 *           - Total distance decreases
 *           - Both routes remain capacity-feasible
 *         Iterate until no improving move found.
 *   @complexity O(n² · k) per pass for n customers, k routes
 *   @ref Van Breedam, A. (2001). "Comparing descent heuristics and
 *        metaheuristics for the vehicle routing problem".
 *
 * @see cluster_heur.h for construction phase
 * @see route_heur.h for intra-route improvement
 */
#ifndef _EXCHANGE_HEUR_H
#define _EXCHANGE_HEUR_H

#include "sym_proto.h"
#include "vrp_types.h"

void exchange_heur PROTO((vrp_problem *vrp, heurs *eh, int trials, 
			  int jobs, int which, int *tids, int *sent));

#endif
