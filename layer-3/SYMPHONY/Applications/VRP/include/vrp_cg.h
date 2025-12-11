/*===========================================================================*/
/*                                                                           */
/* This file is part of a demonstration application for use with the         */
/* SYMPHONY Branch, Cut, and Price Library. This application is a solver for */
/* the Vehicle Routing Problem and the Traveling Salesman Problem.           */
/*                                                                           */
/* (c) Copyright 2000-2013 Ted Ralphs. All Rights Reserved.                  */
/*                                                                           */
/* This application was developed by Ted Ralphs (ted@lehigh.edu)             */
/*                                                                           */
/* This software is licensed under the Eclipse Public License. Please see    */
/* accompanying file for terms.                                              */
/*                                                                           */
/*===========================================================================*/

/**
 * @file vrp_cg.h
 * @brief Cut generator for VRP branch-and-cut
 *
 * Implements specialized cut separation algorithms for capacitated VRP.
 *
 * @algorithm Capacity Cuts (Rounded Capacity Inequalities):
 *   Enforce vehicle capacity on customer subsets:
 *   @math For customer set S ⊆ V\{depot}:
 *           x(δ(S)) ≥ 2·⌈Σ_{i∈S} d_i / Q⌉
 *         where Q = vehicle capacity, d_i = demand, δ(S) = cut edges
 *   check_connectivity() finds violated cuts via connected components.
 *   @complexity O(|E|·α(|V|)) using union-find for connectivity
 *   @ref Laporte, G. et al. (1985). "Optimal routing under capacity
 *        and distance restrictions". Operations Research 33(5).
 *
 * @algorithm Greedy Shrinking Heuristic:
 *   Find violated capacity cuts by shrinking graph:
 *   @math greedy_shrinking1/6(): Iteratively merge vertices
 *         - Combine adjacent vertices with high edge weight
 *         - Check capacity violation after each merge
 *         - Report cut when violation found
 *   Randomization via trial_num and prob parameters.
 *   @complexity O(|V|² · |E|) for full shrinking sequence
 *
 * @algorithm Biconnected Components:
 *   Identify cut vertices and blocks for connectivity cuts:
 *   @math biconnected(): Tarjan's algorithm via DFS
 *         depth_first_search(): Compute dfnumber, low values
 *         compute_comp_nums(): Label biconnected components
 *   Used to decompose graph for cut separation.
 *   @complexity O(|V| + |E|) via single DFS pass
 *   @ref Tarjan, R. (1972). "Depth-first search and linear graph
 *        algorithms". SIAM J. Computing 1(2):146-160.
 *
 * @algorithm TSP Cuts:
 *   Subtour elimination for TSP subproblems:
 *   @math tsp_cuts(): Find violated subtour elimination constraints
 *           x(E(S)) ≤ |S| - 1 for S ⊂ V
 *         Equivalent to connectivity: x(δ(S)) ≥ 2
 *   @complexity O(|V|·|E|) via min-cut computation
 *
 * @see network.h for support graph representation
 * @see sym_cg.h for cut generator framework
 */
#ifndef _VRP_CG_H
#define _VRP_CG_H

/* system include files */
#include <stdio.h>

/* SYMPHONY include files */
#include "sym_types.h"
#include "sym_proto.h"

/* VRP include files */
#include "network.h"
#include "vrp_cg_params.h"

typedef struct VRP_CG_PROBLEM{
   vrp_cg_params par;
   int           dg_id;   /*contains the tid of the graphics window*/
   int           vertnum;  /*the number of nodes in the problem,
			      including the depot                */
   int          *demand;   /* alist of the customer demands*/
   int           capacity; /*the capacity of the trucks*/
   int           numroutes;/*contains the number of routes that the problem
			      is to be solved with. can be prespecified.  */
   int          *edges;    /*contains a list of the edges in the current
			      subproblem*/
   network      *n;
   int           orig_edgenum;
   int          *cost;
   int          *ref;      /* the last five  are for the shrinking routines; */
   char         *in_set;   /* They are here to optimize/speed up things */
   int          *new_demand;
   double       *cut_val;
   char         *cut_list;

/*__BEGIN_EXPERIMENTAL_SECTION__*/
   int          *dec_data;
   int           last_decomp_index;
   double        last_objval;
   FILE         *decomp_res; 
   /* the next four arrays pertain to storing no-columns cuts - kind of an
      auxiliary  cutpool*/ 
   int         **data;
   char        **indicators;
   int          *ones;
   int          *size;
   int           num_nocolscuts;
/*___END_EXPERIMENTAL_SECTION___*/

#ifdef CHECK_CUT_VALIDITY
   int           feas_sol_size;
   int          *feas_sol;
#endif
}vrp_cg_problem;

/*===========================================================================*/
/*========================= Other user subroutines =========================*/
/*===========================================================================*/

void check_connectivity PROTO((network *n, double etol, int capacity,
			      int numroutes, cut_data ***cuts,
			      int *num_cuts, int *alloc_cuts));

/*===========================================================================*/
/*=============================== shrink.c ==================================*/
/*===========================================================================*/

void reduce_graph PROTO((network *n, double etol, int *demand));
int greedy_shrinking1 PROTO((network *n, double truck_cap, double etol,
			     int max_num_cuts, cut_data *new_cut,
			     int *compnodes, int *compmembers, int compnum,
			     char *in_set, double *cut_val,int *ref,
			     char *cut_list, int *demand, cut_data ***cuts,
			     int *num_cuts, int *alloc_cuts));
int greedy_shrinking6 PROTO((network *n, double truck_cap,
			     double etol, cut_data *new_cut,
			     int *compnodes,
			     int *compmembers, int compnum, char *in_set,
			     double *cut_val,int *ref, char *cut_list,
			     int max_num_cuts, int *demand, int trial_num,
			     double prob, cut_data ***cuts, int *num_cuts,
			     int *alloc_cuts));
int greedy_shrinking1_one PROTO((network *n, double truck_cap,
				 double etol, int max_num_cuts,
				 cut_data *new_cut, char *in_set,
				 double *cut_val, char *cut_list,
				 int num_routes, int *demand, cut_data ***cuts,
				 int *num_cuts, int *alloc_cuts));
int greedy_shrinking6_one PROTO((network *n, double truck_cap,
				 double etol, cut_data *new_cut,
				 char *in_set, double *cut_val, int num_routes,
				 char *cut_list, int max_num_cuts,
				 int *demand,int trial_num, double prob,
				 cut_data ***cuts, int *num_cuts,
				 int *alloc_cuts));
int greedy_shrinking2_one PROTO((network *n, double truck_cap,
				 double etol, cut_data *new_cut,
				 char *in_set, double *cut_val, int num_routes,
				 int *demand, cut_data ***cuts, int *num_cuts,
				 int *alloc_cuts));

/*===========================================================================*/
/*============================ biconnected.c ================================*/
/*===========================================================================*/

void depth_first_search PROTO((vertex *v, int *count1, int *count2));
int biconnected PROTO((network *n, int *compnodes, int
			   *compdemands, double *compcuts));
void compute_comp_nums PROTO((vertex *v, int parent_comp, int *num_comps,
		       char parent_is_art_point));

/*===========================================================================*/
/*================================ tsp.c ====================================*/
/*===========================================================================*/

int tsp_cuts PROTO((network *n, int verbosity, char tsp_prob, int which_cuts,
		    cut_data ***cuts, int *num_cuts, int *alloc_cuts));

#endif
