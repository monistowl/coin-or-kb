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
 * @file sym_cp_params.h
 * @brief Cut pool process parameters
 *
 * Parameters for managing the global cut pool storage.
 *
 * **cp_params structure:**
 * - verbosity: Output level
 * - warm_start: Load cuts from file at start
 * - warm_start_file_name: Saved cut pool file
 * - logging: Save cut pool during solve
 * - log_file_name: Cut pool log file
 *
 * **Size management:**
 * - block_size: Allocation granularity
 * - max_size: Maximum memory for cuts
 * - max_number_of_cuts: Hard limit on cut count
 *
 * **Quality control:**
 * - cuts_to_check: How many cuts to check for violations
 * - delete_which: Deletion strategy (quality/touches)
 * - touches_until_deletion: Inactivity threshold
 * - min_to_delete: Minimum cuts to remove at once
 * - check_which: Which cuts to check (level/touches)
 *
 * @see sym_cp.h for cut pool process
 * @see sym_constants.h for CHECK_* and DELETE_* values
 */
#ifndef _CUT_POOL_PARAMS_H
#define _CUT_POOL_PARAMS_H

/*===========================================================================*\
 * Contains the parameters necessary for the functioning of the cut pool
\*===========================================================================*/

typedef struct CP_PARAMS{
   int     verbosity;
   int     warm_start;
   char    warm_start_file_name[MAX_FILE_NAME_LENGTH +1];
   int     logging;
   char    log_file_name[MAX_FILE_NAME_LENGTH +1];
   int     block_size;
   int     max_size;
   int     max_number_of_cuts;
   int     cuts_to_check;
   int     delete_which;
   int     touches_until_deletion;
   int     min_to_delete;
   int     check_which;
}cp_params;

#endif
