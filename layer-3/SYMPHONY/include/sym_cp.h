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
 * @file sym_cp.h
 * @brief Cut Pool process for SYMPHONY
 *
 * The Cut Pool (CP) stores generated cuts for potential reuse
 * across multiple B&C nodes. Manages cut quality and deduplication.
 *
 * @algorithm Cut Pool Management in Branch-and-Cut:
 * Store and reuse cuts across the B&B tree.
 *
 * MOTIVATION:
 *   - Cut generation is expensive (separation algorithms)
 *   - Same cuts often violated at multiple nodes
 *   - Pool enables cut reuse without re-separation
 *   - Memory vs computation tradeoff
 *
 * CUT LIFECYCLE:
 *   1. Generated: Cut created by CG at some node
 *   2. Stored: Added to pool with metadata
 *   3. Checked: Tested for violation at new nodes
 *   4. Reused: If violated, added to LP
 *   5. Aged: Quality decreases if unused
 *   6. Deleted: Removed when quality too low
 *
 * @algorithm Cut Quality Scoring:
 * Prioritize useful cuts, remove dead weight.
 *
 * @math Quality factors:
 *   - touches: Times cut was binding (higher = better)
 *   - level: Tree depth where generated (root cuts more valuable)
 *   - check_num: How often checked without being useful
 *
 *   Effective cuts: touches >> check_num
 *   Ineffective cuts: touches << check_num
 *
 * @algorithm Pool Size Management:
 * Prevent memory exhaustion from unbounded cut storage.
 *
 *   delete_ineffective_cuts():
 *     Remove cuts with quality below threshold
 *     Called when pool exceeds size limit
 *
 *   delete_duplicate_cuts():
 *     Hash-based comparison via cutcmp()
 *     Keep one copy of identical cuts
 *
 *   order_cuts_by_quality():
 *     High-quality cuts checked first
 *     Improves separation efficiency
 *
 * @complexity
 *   check_cut: O(nnz(cut)) per cut
 *   delete_duplicates: O(n log n) with sorting
 *   order_by_quality: O(n log n) sort
 *
 * @see sym_cg.h for cut generation
 * @see sym_lp.h for cut addition to LP
 */
#ifndef _CUT_POOL_H
#define _CUT_POOL_H

#include "symphony.h"
#include "sym_proto.h"
#include "sym_types.h"
#include "sym_cp_params.h"
#include "sym_cp_u.h"

#define PREPARE_TO_CHECK_CUTS  0
#define CHECK_ONE_CUT          1
#define FINISH_TO_CHECK_CUTS   2

/*===========================================================================*\
 * This data structure contains the cut pool itself
\*===========================================================================*/

typedef struct CP_CUT_DATA{
   cut_data      cut;
   int           touches;
   int           level;
   int           check_num;
   double        quality;
}cp_cut_data;

/*===========================================================================*/

typedef struct CUT_POOL{
   void         *user;
   int           master;
   int           tree_manager;
   double        cut_pool_time;
   int           msgtag;        /* the message tag of the last message */
   double        lpetol;        /* the zero tolerance in the lp process */
   cp_params     par;           /* cut pool parameters */
   int           size;          /* the total size of all the cuts in the pool*/
   int           cut_num;       /* the number of cuts in the pool */
   int           allocated_cut_num;   /* the possible number of cuts */
   cp_cut_data **cuts;          /* the list of all the cuts in the pool*/
   int           total_cut_num;
   int           reorder_count; /* Only reorder the cuts periodically */
   lp_sol        cur_sol;
#ifdef SYM_COMPILE_IN_CP
   int           cuts_to_add_num;
   cut_data    **cuts_to_add;
   int           cuts_to_add_size;
#endif
}cut_pool;

/*===========================================================================*/
/*==================== CP basic functions (cp_func.c) =======================*/
/*===========================================================================*/

cut_pool *get_cp_ptr PROTO((cut_pool ** cp_list, int index));
void cp_initialize PROTO((cut_pool *cp, int master_tid));

/*------- Functions related to deletion of cuts (size management) -----------*/

int unsigned_memcmp PROTO((char *coef0, char *coef1, int size));
int cutcmp PROTO((const void *cut0ptr, const void *cut1ptr));
int delete_ineffective_cuts PROTO((cut_pool *cp));
int delete_duplicate_cuts PROTO((cut_pool *cp));
int which_cut_to_delete PROTO((cut_data *cut1, cut_data *cut2));

/*---------------------- Checking the cuts ----------------------------------*/

int cut_quality_cmp PROTO((const void *cut0ptr, const void *cut1ptr));
void order_cuts_by_quality PROTO((cut_pool *cp));

/*--------------- Functions related to logging ------------------------------*/

int write_cp_cut_list PROTO((cut_pool *cp, char *file, char append));
int read_cp_cut_list PROTO((cut_pool *cp, char *file));
int cp_read_tm_cut_list PROTO((cut_pool *cp, char *file));

/*---------------------------- Closing --------------------------------------*/

void cp_close PROTO((cut_pool *cp));

/*===========================================================================*/
/*=============== CP communication functions (cp_proccomm.c) ================*/
/*===========================================================================*/

void cp_process_message PROTO((cut_pool *cp, int r_bufid));
void cut_pool_send_cut PROTO((cut_pool *cp, cut_data *cut, int tid));
void cut_pool_receive_cuts PROTO((cut_pool *cp, int bc_level));

/*===========================================================================*/
/*================= CP wrapper functions (cp_wrapper.c) =====================*/
/*===========================================================================*/

int receive_cp_data_u PROTO((cut_pool *cp));
int receive_lp_solution_cp_u PROTO((cut_pool *cp));
void free_cut_pool_u PROTO((cut_pool *cp));
int check_cuts_u PROTO((cut_pool *cp, lp_sol *cur_sol, double *x));
int check_cut_u PROTO((cut_pool *cp, lp_sol *cur_sol, cut_data *cut,
		       int *is_violated, double *quality, double *x));

#endif
