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
 * @file sym_pack_array.h
 * @brief Array serialization for PVM communication
 *
 * Pack/unpack functions for SYMPHONY data structures in parallel mode.
 *
 * **Array packing:**
 * - pack_array_desc(): Serialize array_desc (int list)
 * - unpack_array_desc(): Deserialize array_desc
 * - pack_double_array_desc(): Serialize with double stats
 * - unpack_double_array_desc(): Deserialize double array
 *
 * **Basis packing:**
 * - pack_basis(): Serialize basis_desc for warm start
 * - unpack_basis(): Deserialize basis_desc
 *
 * @see sym_proccomm.h for communication functions
 * @see sym_types.h for array_desc, basis_desc
 */
#ifndef _PACK_ARRAY_H
#define _PACK_ARRAY_H

#include "sym_proto.h"
#include "sym_types.h"

void pack_array_desc PROTO((array_desc *adesc));
array_desc *unpack_array_desc PROTO((array_desc *padesc));
void pack_double_array_desc PROTO((double_array_desc *dad,
				   char explicit_packing));
void unpack_double_array_desc PROTO((double_array_desc *dad,
				     char explicit_packing));
void pack_basis PROTO((basis_desc *basis, char explicit_packing));
basis_desc *unpack_basis PROTO((basis_desc *pbasis, char explicit_packing));

#endif
