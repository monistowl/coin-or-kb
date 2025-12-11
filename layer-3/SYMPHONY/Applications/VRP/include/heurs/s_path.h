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
 * @file heurs/s_path.h
 * @brief Shortest path computation for VRP tour splitting
 *
 * Dijkstra-based shortest path for partitioning TSP tours into routes.
 *
 * **adj_list structure:**
 * - custnum: Adjacent customer number
 * - cost: Edge cost to adjacent customer
 * - next: Pointer to next adjacency
 *
 * @algorithm Shortest Path Tour Split:
 *   Partition giant tour into capacity-feasible routes via shortest path:
 *   @math Build auxiliary graph G' where:
 *           - Nodes = positions in TSP tour + depot
 *           - Edge (i,j) exists if customers i..j fit in one route
 *           - Edge cost = travel cost of route serving i..j
 *         Shortest path depot→depot in G' = optimal split
 *   sp() computes shortest path using Dijkstra's algorithm.
 *   @complexity O(n² log n) for dense auxiliary graph
 *   @ref Ulusoy, G. (1985). "The fleet size and mix problem for
 *        capacitated arc routing". European J. Operational Research.
 *
 * @see route_heur.h for route-first cluster-second heuristic
 * @see heur_types.h for _node structure
 */
#ifndef _S_PATH_H
#define _S_PATH_H

#include "sym_proto.h"
#include "heur_types.h"

typedef struct ADJ_LIST{
  int custnum;
  int cost;
  struct ADJ_LIST *next;
}adj_list;

        int *sp PROTO((adj_list **adj, int numnodes, int origin, int dest));
        void make_routes PROTO((heur_prob *p, _node *tsp_tour, int start, 
				 best_tours *new_tour));

#endif
