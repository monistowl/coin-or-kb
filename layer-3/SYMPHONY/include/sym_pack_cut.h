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
 * @file sym_pack_cut.h
 * @brief Cut serialization for PVM communication
 *
 * Pack/unpack functions for cut_data in parallel mode.
 *
 * **Cut packing:**
 * - pack_cut(): Serialize cut_data for transmission
 * - unpack_cut(): Deserialize received cut_data
 *
 * @see sym_proccomm.h for communication functions
 * @see sym_types.h for cut_data structure
 * @see sym_cp.h for cut pool using these functions
 */
#ifndef _PACK_CUT_H
#define _PACK_CUT_H

#include "sym_proto.h"
#include "sym_types.h"

void pack_cut PROTO((cut_data *cut));
cut_data *unpack_cut PROTO((cut_data *cut));

#endif
