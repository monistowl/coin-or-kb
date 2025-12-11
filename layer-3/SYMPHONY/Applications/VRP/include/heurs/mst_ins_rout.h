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
 * @file heurs/mst_ins_rout.h
 * @brief MST-based insertion and k-tree lower bound for VRP
 *
 * Minimum spanning tree based routines for bounds and construction.
 *
 * @algorithm k-Tree Lower Bound:
 *   Compute lower bound via k-degree constrained MST:
 *   @math 1-tree bound: MST on customers + 2 edges at depot
 *         k-tree bound: MST where depot has exactly degree k
 *         make_k_tree() builds k-tree via Prim's algorithm
 *   Lagrangian relaxation improves bound via lambda multipliers.
 *   new_lamda() updates multipliers via subgradient optimization.
 *   @complexity O(n² log n) for MST construction
 *   @ref Held, M. and Karp, R. (1971). "The traveling-salesman problem
 *        and minimum spanning trees: Part II". Math Programming 1(1).
 *
 * @algorithm MST-Based Insertion:
 *   Build tour by inserting nodes from MST edges:
 *   @math 1. Compute MST of all customers
 *         2. Traverse MST in some order (e.g., DFS)
 *         3. Insert nodes into tour following traversal order
 *   ni_insert_edges() inserts based on nearest neighbor in tree.
 *   @complexity O(n² log n) for MST + O(n²) for insertions
 *
 * @see ins_routines.h for standard insertion heuristics
 * @see lb_types.h for lower bound data structures
 */
#ifndef _MST_INS_ROUT_H
#define _MST_INS_ROUT_H

#include "sym_proto.h"
#include "lb_types.h"
#include "heur_types.h"

int make_k_tree PROTO((lb_prob *p, int *tree, int *lamda, int k));
int closest PROTO((neighbor *nbtree, int *intree, int *last, int *host));
void ni_insert_edges PROTO((lb_prob *p, int new_node, neighbor *nbtree,
	int *intree, int *last, int *lamda, int mu));
int new_lamda PROTO((lb_prob *p, int upper_bound, int cur_bound, int *lamda,
	int numroutes, int *tree, edge_data *cur_edges, int alpha));

#endif
