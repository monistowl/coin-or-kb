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
 * @file sym_cp_u.h
 * @brief User callbacks for cut pool process
 *
 * Defines callbacks for custom cut checking in the cut pool.
 * Cut pool stores cuts for reuse across B&C nodes.
 *
 * **User callbacks:**
 * - user_receive_cp_data(): Receive problem-specific data
 * - user_free_cp(): Clean up user data
 * - user_receive_lp_solution_cp(): Custom solution handling
 *
 * **Cut checking protocol (three-phase):**
 * 1. user_prepare_to_check_cuts(): Initialize with LP solution
 * 2. user_check_cut(): Check single cut for violation
 *    - Sets is_violated flag
 *    - Optionally computes quality score
 * 3. user_finished_checking_cuts(): Cleanup after checking
 *
 * **Default behavior:**
 * Returns USER_DEFAULT for built-in EXPLICIT_ROW handling.
 * User cuts need custom checking implementation.
 *
 * @see sym_cp.h for cut pool process
 * @see sym_cg_u.h for cut generation callbacks
 */
#ifndef _CP_U_H
#define _CP_U_H

#include "sym_proto.h"
#include "sym_types.h"

/*===========================================================================*/
/*====================== User supplied functions ============================*/
/*===========================================================================*/

int user_receive_cp_data PROTO((void **user));
int user_free_cp PROTO((void **user));
int user_prepare_to_check_cuts PROTO((void *user, int varnum, int *indices,
				      double *values));
int user_check_cut PROTO((void *user, double lpetol, int varnum, int *indices,
			  double *values, cut_data *cut, int *is_violated,
			  double *quality));
int user_finished_checking_cuts PROTO((void *user));
int user_receive_lp_solution_cp PROTO((void *user));

#endif
