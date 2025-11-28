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
 * @file sym_master_params.h
 * @brief Master process parameters aggregating all component params
 *
 * Top-level parameter structure containing parameters for all
 * SYMPHONY processes: master, TM, LP, CG, CP, DG, and preprocessing.
 *
 * **params structure contains:**
 * - cp_par: Cut pool parameters
 * - cg_par: Cut generator parameters
 * - lp_par: LP solver parameters
 * - tm_par: Tree manager parameters
 * - dg_par: Draw graph parameters (visualization)
 * - prep_par: Preprocessing parameters
 *
 * **Execution control:**
 * - warm_start: Resume from saved state
 * - verbosity: Global output level
 * - random_seed: For reproducibility
 * - do_branch_and_cut: Enable B&C algorithm
 * - do_draw_graph: Enable visualization
 * - use_permanent_cut_pools: Persistent cut storage
 *
 * **Input/output:**
 * - infile: Problem file (MPS/LP/GMPL)
 * - file_type: MPS_FORMAT, LP_FORMAT, GMPL_FORMAT
 * - datafile: GMPL data file if needed
 * - test_dir: Directory for test problems
 * - obj_offset: Constant added to objective
 *
 * **Multi-criteria optimization:**
 * - multi_criteria: Enable bi-objective mode
 * - mc_search_order: Search strategy
 * - mc_compare_solution_tolerance: Pareto comparison
 * - mc_warm_start: Reuse solutions across objectives
 *
 * **Parallel configuration:**
 * - tm_exe, dg_exe: Process executables
 * - tm_machine, dg_machine: Machine assignments
 * - pvm_trace: PVM debugging
 *
 * @see sym_master.h for master process
 * @see symphony.h for API using these parameters
 */
#ifndef _MASTER_PARAMS_H
#define _MASTER_PARAMS_H

#include "sym_tm_params.h"
#include "sym_cp_params.h"
#include "sym_cg_params.h"
#include "sym_lp_params.h"
#include "sym_dg_params.h"
#include "sym_prep_params.h"

/*===========================================================================*\
 * The params structure contains all of the user-specified parameters
 * to be read in from the parameter file. See the README file for an
 * explanation of the parameters
\*===========================================================================*/

typedef struct PARAMS{
   int        warm_start;
   int        verbosity;
   char       param_file[MAX_FILE_NAME_LENGTH +1];
   int        random_seed;
   cp_params  cp_par;
   cg_params  cg_par;
   lp_params  lp_par;
   tm_params  tm_par;
   dg_params  dg_par;
   prep_params prep_par;

   char       tm_exe[MAX_FILE_NAME_LENGTH +1];
   char       dg_exe[MAX_FILE_NAME_LENGTH +1];
   int        tm_debug;
   int        dg_debug;
   int        tm_machine_set;
   char       tm_machine[MACH_NAME_LENGTH +1];
   int        dg_machine_set;
   char       dg_machine[MACH_NAME_LENGTH +1];
   int        pvm_trace;
   int        do_branch_and_cut;
   int        do_draw_graph;
   int        use_permanent_cut_pools;
   char       infile[MAX_FILE_NAME_LENGTH +1]; /* For MPS file name
						  or GNUMP modelfile */   
   int        file_type; 
   char       datafile[MAX_FILE_NAME_LENGTH +1]; /* GNUMP datafile */
   char       test_dir[MAX_FILE_NAME_LENGTH +1];  /* Test files directory */
   double     obj_offset;

   /* Multi-criteria parameters */
   int        multi_criteria;
   int        mc_search_order;
   double     mc_compare_solution_tolerance;
   double     mc_binary_search_tolerance;
   int        mc_warm_start;
   int        mc_warm_start_rule;
   int        trim_warm_tree;
   int        test;
}params;

#endif
