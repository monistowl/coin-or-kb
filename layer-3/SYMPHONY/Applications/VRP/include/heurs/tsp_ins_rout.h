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
 * @file heurs/tsp_ins_rout.h
 * @brief TSP insertion heuristics (uncapacitated version)
 *
 * Insertion heuristics for pure TSP without capacity constraints.
 * Used to build single vehicle tours within VRP routes.
 *
 * @algorithm TSP Insertion:
 *   Build tour by iteratively inserting unvisited nodes:
 *   @math tsp_nearest_ins_from_to(): Insert nearest unvisited node
 *         tsp_farthest_ins_from_to(): Insert farthest unvisited node
 *         tsp_insert_into_tour(): Insert at minimum cost position
 *           position p* = argmin_{p} (d(prev_p, new) + d(new, next_p) - d(prev_p, next_p))
 *   No capacity check (pure TSP), faster than VRP variants.
 *   @complexity O(n²) for building complete tour
 *
 * @algorithm Best Insertion Position:
 *   Find optimal position to insert new node:
 *   @math For each edge (i,j) in tour, compute:
 *           cost_increase = d(i,new) + d(new,j) - d(i,j)
 *         Insert after position minimizing cost_increase
 *   tsp_fi_insert_edges() and tsp_ni_insert_edges() update neighbor trees.
 *
 * @see ins_routines.h for VRP insertion (with capacity)
 * @see heur_types.h for _node and neighbor structures
 */
#ifndef _TSP_INS_ROUT_H
#define _TSP_INS_ROUT_H

#include "heur_types.h"
#include "sym_proto.h"

int tsp_farthest_ins_from_to PROTO((
			 heur_prob *p, _node *tour, int cost,
			 int from_size, int to_size,
			 int starter, neighbor *nbtree,
			 int *intour, int *last));
int tsp_nearest_ins_from_to PROTO((
			heur_prob *p, _node *tour, int cost,
			int from_size, int to_size,
			int starter, neighbor *nbtree, 
			int *intour, int *last));
int tsp_closest PROTO((
		neighbor *nbtree, int *intour, int *last));
void tsp_ni_insert_edges PROTO((
		     heur_prob *p, int new_node, neighbor *nbtree,
		     int *intour, int *last));
int tsp_farthest PROTO((
		 neighbor *nbtree, int *intour, int *last));
void tsp_fi_insert_edges PROTO((
		     heur_prob *p, int new_node, neighbor *nbtree,
		     int *intour, int *last));
int tsp_insert_into_tour PROTO((
		     heur_prob *p, _node *tour, int starter,
		     int size, int new_node));

#endif
