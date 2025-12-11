/*===========================================================================*/
/*                                                                           */
/* This file is part of a demonstration application for use with the         */
/* SYMPHONY Branch, Cut, and Price Library. This application is a solver for */
/* the Set Partitioning Problem.                                             */
/*                                                                           */
/* (c) Copyright 2005-2013 Marta Eso and Ted Ralphs. All Rights Reserved.    */
/*                                                                           */
/* This application was originally developed by Marta Eso and was modified   */
/* Ted Ralphs (ted@lehigh.edu)                                               */
/*                                                                           */
/* This software is licensed under the Eclipse Public License. Please see    */
/* accompanying file for terms.                                              */
/*                                                                           */
/*===========================================================================*/

/**
 * @file spp_cg.h
 * @brief Cut generator for Set Partitioning Problem
 *
 * Implements specialized cut separation for SPP using conflict graph.
 *
 * **Fractional graph (frac_graph):**
 * - Nodes = variables with fractional LP values
 * - Edges connect conflicting (non-orthogonal) columns
 * - Used as intersection graph for cut separation
 *
 * **Level graph (level_graph):**
 * - BFS enumeration from root node
 * - Used for odd hole detection
 *
 * @algorithm Conflict Graph Construction:
 *   Build graph from fractional LP solution:
 *   @math construct_fractional_graph(): Include var i if 0 < x_i < 1
 *         Edge (i,j) if columns i,j share a row (non-orthogonal)
 *         node_node matrix: O(1) adjacency lookup
 *   Edge costs = 1 - x_i - x_j for odd hole weights.
 *   @complexity O(n²·m) for n fractional vars, m rows
 *
 * @algorithm Odd Hole Cuts:
 *   Find violated odd hole inequalities:
 *   @math For odd cycle C = {v_1, ..., v_{2k+1}} in conflict graph:
 *           Σ_{i∈C} x_i ≤ k (odd hole inequality)
 *         find_violated_odd_holes() uses BFS level graph
 *         find_chordless_oh(): Ensure hole has no chords
 *         min_path_to_root(): Shortest path for minimum weight cycle
 *   Violated when Σ x_i > k for odd cycle of length 2k+1.
 *   @complexity O(|V|²·|E|) for exhaustive search
 *   @ref Nemhauser, G. and Sigismondi, G. (1992). "A strong cutting
 *        plane/branch-and-bound algorithm for node packing". JORS.
 *
 * @algorithm Lifted Odd Holes:
 *   Strengthen odd hole cuts by lifting:
 *   @math lift_nonviolated_odd_hole(): Add hub vertices
 *         Hubs are nodes adjacent to multiple hole vertices
 *         max_lhs_of_lifted_odd_hole(): Compute lift coefficients
 *   Lifting strengthens the inequality without losing validity.
 *   @complexity O(k·|V|) per lift for k-hub lifting
 *
 * @algorithm Odd Antiholes:
 *   Cuts from complement graph odd cycles:
 *   @math Odd antihole in G = odd hole in complement G'
 *         construct_complement_graph(): Build G'
 *         find_violated_odd_antiholes(): Search in complement
 *         lift_nonviolated_odd_antihole(): Strengthen cuts
 *   @complexity Same as odd holes on complement graph
 *
 * @see spp_cg_clique.h for clique cuts
 * @see sym_cg.h for cut generator framework
 */
#ifndef _SPP_CG_H
#define _SPP_CG_H

/* system include files */
#include <stdio.h>
#include <sym_proto.h>

/* SPP include files */
#include "spp_constants.h"
#include "spp_types.h"
#include "spp_cg_params.h"

typedef struct FNODE {        /*describes a node of the fractional graph*/
   int          *nbrs;        /* pointer into all_nbr */
   double       *edgecosts;   /*1-x_i-x_j, needed for odd holes, in the same
				order as the adj list, pointer into
				all_edgecost */
   int           degree;       /*degree of the node*/
   int           ind;          /*origind of the node, ie. the index of this
				 variable in the initial problem the lp and
				 the cut generator store*/
   double        val;          /*the value of this variable in the current
				 lp solution*/
}fnode;

typedef struct FRAC_GRAPH {    /*graph corresponding to the current fractional
				 solution. two nodes are adjacent iff their
				 columns are non-orthogonal*/
   int    nodenum;     /*# of nodes = # of fractional values in current sol*/
   int    edgenum;     /*# of edges in the graph*/
   double density;     /*density= edgenum/(nodenum choose 2)*/
   int    min_deg_node;
   int    min_degree;
   int    max_deg_node;
   int    max_degree;
   fnode  *nodes;      /*pointers to the nodes*/
   int    *all_nbr;    /* array of all the neighbors. */
   double *all_edgecost;  /* array of all the costs */
   char   *node_node;  /*node-node incidence matrix of the graph, stored
			 row-ordered in a long vector*/
}frac_graph;


/* a level-graph is derived from another graph by taking one of the nodes
   of the graph as root and listing its connected component in a BFS
   fashion.
    lnodenum is the number of nodes in the level-graph
    levelnum is the number of BFS levels
    root     is the root of the level-graph
    lnodes   is a list of node indices (wrt the original graph) in the order
             they have been marked during BFS
    lbeg     is the position of each level within lnodes (like matbeg for
             matind)
    level_of_node is a list of levels for the nodes of the original graph.
             it is -1 if the node is not in the level-graph (i.e., not
	     in the connected component of the root) */
typedef struct LEVEL_GRAPH {
   int               lnodenum;
   int               levelnum;
   int               root;           /* lnodes[0] = root */
   int              *lnodes;         /* length: lnodenum */
   int              *lbeg;           /* length: levelnum + 1 */
   int              *level_of_node;  /* length: nodenum of orig. graph */
}level_graph;

typedef struct CUT_COLLECTION {
   int               size;
   int               max_size;
   cut_data        **cuts;      /* a collection of cuts that have been sent
				   to the lp */
   double           *violation; /* degree of violation for these cuts */
   int              *mult;      /* the multiplicity of the cut -- just STAT */
}cut_collection;

typedef struct SPP_CG_TMP {
   int                *itmp_m;        
   int               **istartmp_m;
   /* the following must be reallocated if nodenum grows */
   int                *itmp_8nodenum;
   double             *dtmp_2nodenum;
   char               *ctmp_2nodenum;
   cut_data           *cuttmp;
}spp_cg_tmp;


/*
  tmp:  temporary data structures, space is allocated for them only once
        at the beginning and freed at the end only. Some fields are
	variable length
  soln: pointer to the current lp solution. needed only to simplify the
        arguments passed on to functions invoked from find_cuts
  cm_frac, rm_frac: column and row ordered versions of the problem matrix
        restricted to the columns in the fractional solution. matbeg, matind
	and rmatind are variable length.
  fgraph: pointer to the fractional graph that corresponds to the current
          lp solution. Fields are variable length.
  lgraph: a BFS enumeration of a connected component of fgraph, starting from
          a special node, the root. Fields are variable length.
  cut_coll: a local cut pool that contains the cuts that have been sent back
            to the lp. Originally allocated for 20 cuts but it is reallocated
	    later as needed.
  
 */
typedef struct SPP_CG_PROBLEM {
   spp_cg_params      *par;
   spp_cg_tmp         *tmp;
   int                 dg_id;  /* tid of the graph drawing process */
   char                wname[MAX_FILE_NAME_LENGTH +1];
                          /* name of window in which frac solns are displd */
   char                lname[MAX_FILE_NAME_LENGTH +1];
                          /* name of window in which level graph is displd */
   col_ordered        *cmatrix;

   int                 max_sol_length;  /* space is allocated for fgraph and
					   rmatrix according to this value */
   col_ordered        *cm_frac;
   row_ordered        *rm_frac;
   frac_graph         *fgraph;
   frac_graph         *cfgraph;
   level_graph        *lgraph;
   cut_collection     *cut_coll;

   int                *num_cuts; 
   int                *alloc_cuts;
   cut_data         ***cuts;
	


}spp_cg_problem;

void allocate_var_length_structures PROTO((spp_cg_problem *spp, int max_ln));
void free_var_length_structures PROTO((spp_cg_problem *spp));
void construct_fractional_graph PROTO((spp_cg_problem *spp, int number,
				       int *indices, double *values));
void construct_cm_frac PROTO((spp_cg_problem *spp));
void construct_rm_frac PROTO((spp_cg_problem *spp));
void construct_complement_graph PROTO((frac_graph *fgraph,
				       frac_graph *cfgraph));
void construct_level_graph PROTO((frac_graph *fgraph, int root,
				  level_graph *lgraph));
int register_and_send_cut PROTO((spp_cg_problem *spp, cut_data *new_cut,
				 double violation, double etol));

void extend_clique_on_fgraph PROTO((spp_cg_problem *spp, cut_data *new_cut,
				    double *pviolation));
void translate_cut_to_indices PROTO((spp_cg_problem *spp, cut_data *cut));
void rotate_odd_hole PROTO((int length, int *indices, int *itmp));

int enumerate_maximal_cliques PROTO((spp_cg_problem *spp, int pos, double etol));
void spp_delete_node PROTO((spp_cg_problem *spp, int del_ind,
			    int *pcurrent_nodenum, int *current_indices,
			    int *current_degrees, double *current_values));
int choose_next_node PROTO((spp_cg_problem *spp, int current_nodenum,
			    int *current_indices, int *current_degrees,
			    double *current_values));
int find_violated_star_cliques PROTO((spp_cg_problem *spp, double etol));
int find_violated_row_cliques PROTO((spp_cg_problem *spp, double etol));
int greedy_maximal_clique PROTO((spp_cg_problem *spp, cut_data *new_cut,
				 int length, int *indices, int pos, double etol));
int find_violated_odd_holes PROTO((spp_cg_problem *spp, double etol));
double find_chordless_oh PROTO((spp_cg_problem *spp, frac_graph *fgraph,
				int u, int w, int *oh));
void min_path_to_root PROTO((spp_cg_problem *spp, frac_graph *fgraph,
			     int u, int *path_u, double *pcost));
double lift_nonviolated_odd_hole PROTO((spp_cg_problem *spp, int oh_len,
					int *oh, double lhs_oh, int *phub_len,
					int *hubs, int *hub_coef));
int max_lhs_of_lifted_odd_hole PROTO((spp_cg_problem *spp, int oh_len,
				      int *oh, int hub, int hub_len, int *hubs,
				      int *hub_coef, char *label, int pos));
int find_violated_odd_antiholes PROTO((spp_cg_problem *spp, double etol));
double lift_nonviolated_odd_antihole PROTO((spp_cg_problem *spp, int oah_len,
					    int *oah, double lhs_oah,
					    int *phub_len, int *hubs,
					    int *hub_coef, double etol));
void translate_cut_to_indices PROTO((spp_cg_problem *spp, cut_data *cut));
void rotate_odd_hole PROTO((int length, int *indices, int *itmp));

#endif
