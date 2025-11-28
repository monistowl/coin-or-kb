/*===========================================================================*/
/*                                                                           */
/* This file is part of the SYMPHONY Branch, Cut, and Price Library.         */
/*                                                                           */
/* SYMPHONY was jointly developed by Ted Ralphs (ted@lehigh.edu) and         */
/* Laci Ladanyi (ladanyi@us.ibm.com).                                        */
/*                                                                           */
/* The author of this file is Menal Guzelsoy                                 */
/*                                                                           */
/* (c) Copyright 2006-2022 Lehigh University. All Rights Reserved.           */
/*                                                                           */
/* This software is licensed under the Eclipse Public License. Please see    */
/* accompanying file for terms.                                              */
/*                                                                           */
/*===========================================================================*/

/**
 * @file sym_prep_params.h
 * @brief Preprocessing parameters for SYMPHONY
 *
 * Parameters controlling MIP presolve operations.
 *
 * **prep_params structure:**
 * - level: Preprocessing aggressiveness (0=off)
 * - dive_level: Bound propagation depth
 * - impl_dive_level: Implication chain depth
 * - impl_limit: Max implications to explore
 * - do_probe: Enable probing
 * - verbosity: Output detail level
 * - reduce_mip: Enable full problem reduction
 *
 * **Probing control:**
 * - probe_verbosity: Probing output level
 * - probe_level: Probing aggressiveness
 *
 * **Single-row relaxation:**
 * - do_single_row_rlx: Enable SR bounds
 * - single_row_rlx_ratio: Sparsity threshold
 * - max_sr_cnt: Max rows to analyze
 *
 * **Aggregated row relaxation:**
 * - do_aggregate_row_rlx: Combine rows for bounds
 * - max_aggr_row_ratio: Density limit
 * - max_aggr_row_cnt: Max aggregations
 *
 * **Resource limits:**
 * - iteration_limit: Max preprocessing passes
 * - time_limit: Preprocessing time budget
 * - etol: Numerical tolerance
 *
 * **Output:**
 * - display_stats: Show preprocessing summary
 * - write_mps/write_lp: Save preprocessed problem
 *
 * @see sym_prep.h for preprocessing functions
 */
#ifndef _PREP_PARAMS_H
#define _PREP_PARAMS_H

/*---------------------------------------------------------------------------*\
| The list of parameters associated with pre-processing                       |
|                                                                             |
\*---------------------------------------------------------------------------*/
typedef struct PREP_PARAMS{
   int               level;
   int               dive_level; 
   int               impl_dive_level; 
   int               impl_limit;
   int               do_probe;
   int               verbosity;
   int               reduce_mip;
   int               probe_verbosity;
   int               probe_level;
   int               display_stats;
   double            etol; 
   int               keep_row_ordered; 
   int               do_single_row_rlx; 
   double            single_row_rlx_ratio;
   int               max_sr_cnt;
   char              do_aggregate_row_rlx; 
   double            max_aggr_row_ratio;   
   int               max_aggr_row_cnt;
   int               iteration_limit; 
   int               keep_track; 
   int               write_mps;
   int               write_lp; 
   int               time_limit;
}prep_params;

#endif
