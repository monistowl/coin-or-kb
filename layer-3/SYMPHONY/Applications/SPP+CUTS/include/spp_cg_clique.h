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
 * @file spp_cg_clique.h
 * @brief Clique cut separation for Set Partitioning Problem
 *
 * Specialized clique finding algorithms for SPP cut generation.
 *
 * @algorithm Star Cliques:
 *   Find cliques containing a high-degree center node:
 *   @math For center node v with high degree:
 *         Find maximal clique containing v and its neighbors
 *         Clique inequality: Σ_{i∈C} x_i ≤ 1 (for clique C)
 *   find_violated_star_cliques() searches from degree-ordered nodes.
 *   @complexity O(|V|·d_max²) where d_max = maximum degree
 *
 * @algorithm Row Cliques:
 *   Find cliques from row structure of constraint matrix:
 *   @math Columns sharing a row are conflicting (non-orthogonal)
 *         Such columns form cliques in the conflict graph
 *   find_violated_row_cliques() exploits problem structure.
 *   @complexity O(m·k²) for m rows with average k columns
 *
 * @algorithm Maximal Clique Enumeration:
 *   Enumerate all maximal cliques via backtracking:
 *   @math enumerate_maximal_cliques(): Bron-Kerbosch style enumeration
 *         choose_next_node(): Branching variable selection
 *         spp_delete_node(): Pruning and graph update
 *   Used for thorough cut separation.
 *   @complexity O(3^{n/3}) worst case for n-node graph
 *   @ref Bron, C. and Kerbosch, J. (1973). "Finding all cliques
 *        of an undirected graph". CACM 16(9):575-577.
 *
 * @algorithm Greedy Maximal Clique:
 *   Fast heuristic clique construction:
 *   @math greedy_maximal_clique(): Iteratively add highest-degree node
 *         from common neighbors until no extension possible
 *   Trade-off: faster than enumeration but may miss violations.
 *   @complexity O(|V|²) per clique
 *
 * @see spp_cg.h for fractional graph representation
 * @see sym_cg.h for cut generator framework
 */
#ifndef _SPP_CG_CLIQUE_H
#define _SPP_CG_CLIQUE_H

int find_violated_star_cliques PROTO((spp_cg_problem *spp, double etol));
void spp_delete_node PROTO((spp_cg_problem *spp, int del_ind,
			    int *pcurrent_nodenum, int *current_indices,
			    int *current_degrees, double *current_values));
int choose_next_node PROTO((spp_cg_problem *spp, int current_nodenum,
			    int *current_indices, int *current_degrees,
			    double *current_values));
int find_violated_row_cliques PROTO((spp_cg_problem *spp, double etol));
int enumerate_maximal_cliques PROTO((spp_cg_problem *spp, int pos, double etol));
int greedy_maximal_clique PROTO((spp_cg_problem *spp, cut_data *new_cut,
				 int length, int *indices, int pos, double etol));
#endif
