/*===========================================================================*/
/*                                                                           */
/* This file is part of the SYMPHONY MILP Solver Framework.                  */
/*                                                                           */
/* SYMPHONY was jointly developed by Ted Ralphs (ted@lehigh.edu) and         */
/* Laci Ladanyi (ladanyi@us.ibm.com).                                        */
/*                                                                           */
/* (c) Copyright 2000-2022 Ted Ralphs. All Rights Reserved.                  */
/*                                                                           */
/* This software is licensed under the Eclipse Public License. Please see    */
/* accompanying file for terms.                                              */
/*                                                                           */
/*===========================================================================*/

/**
 * @file sym_tm_params.h
 * @brief Tree manager parameters for SYMPHONY
 *
 * Parameters controlling the branch-and-cut search tree exploration.
 *
 * **Process configuration:**
 * - lp_exe, cg_exe, cp_exe: Worker executables
 * - lp/cg/cp_mach_num: Number of machines per type
 * - lp/cg/cp_machs: Machine name arrays
 * - max_active_nodes: Parallelism limit
 * - max_cp_num: Maximum cut pools
 *
 * **Node selection (node_selection_rule):**
 * - LOWEST_LP_FIRST: Best-bound search
 * - DEPTH_FIRST_SEARCH: Deep diving
 * - BREADTH_FIRST_SEARCH: Level-by-level
 * - BEST_FIRST_SEARCH: Estimate-based
 *
 * **Diving strategy:**
 * - unconditional_dive_frac: Always dive this fraction
 * - diving_strategy: How to choose dive vs backtrack
 * - diving_k, diving_threshold: Diving parameters
 *
 * **Termination criteria:**
 * - time_limit: Maximum solve time
 * - gap_limit: Optimality tolerance
 * - node_limit: Maximum nodes to explore
 * - find_first_feasible: Stop at first solution
 *
 * **Logging and warm start:**
 * - logging, logging_interval: Progress logging
 * - warm_start: Resume from saved state
 * - warm_start_node_limit: Nodes to load
 * - tree_log_file_name, cut_log_file_name: State files
 * - vbc_emulation: Visualization output
 *
 * **Column generation:**
 * - colgen_strat[2]: Strategy for two phases
 * - price_in_root: Column generation at root
 *
 * **Solution pool:**
 * - max_sp_size: Maximum solutions to keep
 *
 * @see sym_tm.h for tree manager process
 * @see sym_constants.h for selection rule values
 */
#ifndef _TM_PARAMS_H
#define _TM_PARAMS_H

#include "sym_proto.h"

/*===========================================================================*\
 * The params structure contains all of the user-specified parameters   
 * to be read in from the parameter file.
\*===========================================================================*/

typedef struct TM_PARAMS{
   int         verbosity;
   double      granularity;
   char        lp_exe[MAX_FILE_NAME_LENGTH +1];
   char        cg_exe[MAX_FILE_NAME_LENGTH +1];
   char        cp_exe[MAX_FILE_NAME_LENGTH +1];
   int         lp_debug;
   int         cg_debug;
   int         cp_debug;
   int         max_active_nodes;
   int         max_cp_num;

   /* if a ..._machine_num is not 0 and there MUST be that many machine
      names listed in ..._machines (one name can be listed more than once) */
   int         lp_mach_num;
   char      **lp_machs;
   int         cg_mach_num;
   char      **cg_machs;
   int         cp_mach_num;
   char      **cp_machs;

   int         use_cg;

   int         random_seed;
   double      unconditional_dive_frac;
   int         diving_strategy;
   int         diving_k;
   double      diving_threshold;
   int         node_selection_rule;

   int         keep_description_of_pruned;
   int         vbc_emulation;
   char        vbc_emulation_file_name[MAX_FILE_NAME_LENGTH +1];
   int         warm_start;
   int         warm_start_node_limit;
   int         warm_start_node_level;
   double      warm_start_node_level_ratio;
   double      warm_start_node_ratio;
   int         logging;
   int         logging_interval;
   int         status_interval;
   int         cp_logging;
   char        pruned_node_file_name[MAX_FILE_NAME_LENGTH +1];
   char        warm_start_tree_file_name[MAX_FILE_NAME_LENGTH +1];
   char        warm_start_cut_file_name[MAX_FILE_NAME_LENGTH +1];
   char        tree_log_file_name[MAX_FILE_NAME_LENGTH +1];
   char        cut_log_file_name[MAX_FILE_NAME_LENGTH +1];
   int         price_in_root;
   int         trim_search_tree;

   int         colgen_strat[2]; /* the column generattion strategy for the LP
				   in the two phases */
   int         not_fixed_storage_size;
   double      time_limit;
   double      gap_limit;
   int         node_limit;
   int         find_first_feasible;
   int         rs_mode_enabled;
   int         rs_lp_iter_limit;
   
   int         sensitivity_analysis;
   int         sensitivity_bounds;
   int         sensitivity_rhs;
   int         output_mode;
   int         keep_cut_pools;

   int         tighten_root_bounds;

   int         max_sp_size;
}tm_params;

#endif
