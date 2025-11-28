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
 * @file sym_proto.h
 * @brief Function prototype and path length macros
 *
 * Defines the PROTO macro for ANSI C function prototypes
 * and standard path/line length constants.
 *
 * **Length constants:**
 * - MAX_FILE_NAME_LENGTH (255): File path buffer size
 * - MACH_NAME_LENGTH (255): Machine name buffer size
 * - MAX_LINE_LENGTH (255): Line buffer size
 *
 * **PROTO macro:**
 * - PROTO(x) expands to x for ANSI C prototypes
 * - Allows: `int foo PROTO((int a, int b));`
 * - Legacy support for K&R C compilers (commented out)
 *
 * @see sym_types.h for data types
 */
#ifndef _PROTO_H
#define _PROTO_H

#define MAX_FILE_NAME_LENGTH 255
#define MACH_NAME_LENGTH     255
#define MAX_LINE_LENGTH      255


#ifdef PROTO
#undef PROTO
#endif
/*#ifdef __GNUC__*/
#define PROTO(x) x
/*#else
#define PROTO(x) ()
#endif*/

#endif
