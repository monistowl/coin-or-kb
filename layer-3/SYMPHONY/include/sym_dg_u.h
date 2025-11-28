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
 * @file sym_dg_u.h
 * @brief User callbacks for Draw Graph visualization
 *
 * Defines callbacks for custom visualization behavior.
 *
 * **User callbacks:**
 * - user_initialize_dg(): Global DG initialization
 * - user_free_dg(): Global DG cleanup
 * - user_dg_init_window(): Per-window setup
 * - user_dg_free_window(): Per-window cleanup
 * - user_dg_process_message(): Handle custom messages
 * - user_interpret_text(): Process text input
 *
 * @see sym_dg.h for draw graph process
 * @see sym_dg_params.h for message constants
 */
#ifndef DG_U_H
#define DG_U_H

#include <stdio.h>

#include "sym_proto.h"

struct WINDOW;

/*===========================================================================*/
/*====================== User supplied functions ============================*/
/*===========================================================================*/

int user_dg_process_message PROTO((void *user, struct WINDOW *win,
				   FILE *write_to));
int user_dg_init_window PROTO((void **user, struct WINDOW *win));
int user_dg_free_window PROTO((void **user, struct WINDOW *win));
int user_initialize_dg PROTO((void **user));
int user_free_dg PROTO((void **user));
int user_interpret_text PROTO((void *user, int text_length, char *text,
			       int owner_tid));

#endif


