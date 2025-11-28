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
 * @file sym_cg_params.h
 * @brief Cut generator process parameters
 *
 * Minimal parameter structure for the cut generator process.
 * Most cut generation parameters are in sym_lp_params.h (cgl_params).
 *
 * **cg_params:**
 * - verbosity: Output level for cut generation
 * - do_findcuts: Enable/disable user cut generation
 *
 * @see sym_cg.h for cut generator process
 * @see sym_lp_params.h for CGL cut parameters
 */
#ifndef _CUT_GEN_PARAMS_H
#define _CUT_GEN_PARAMS_H

/*stores the parameters needed by the cut generator*/
typedef struct CG_PARAMS{
   int     verbosity;
   int     do_findcuts;
}cg_params;

#endif
