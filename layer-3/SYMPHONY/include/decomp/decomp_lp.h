/**
 * @file decomp_lp.h
 * @brief LP interface for decomposition master problem
 *
 * Load/unload functions for the restricted master LP.
 *
 * **Functions:**
 * - load_decomp_lp(): Initialize master LP with initial columns
 * - unload_decomp_lp(): Cleanup master LP
 *
 * @see decomp.h for column generation algorithm
 * @see sym_lp_solver.h for LPdata structure
 */
#ifndef _DECOMP_LP_H
#define _DECOMP_LP_H

#include<sym_lp_solver.h>

void load_decomp_lp PROTO((LPdata *lp_data));
void unload_decomp_lp PROTO((LPdata *lp_data));

#endif
