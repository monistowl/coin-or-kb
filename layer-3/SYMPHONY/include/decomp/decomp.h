/**
 * @file decomp.h
 * @brief Decomposition-based column generation for SYMPHONY
 *
 * Implements column generation via Dantzig-Wolfe decomposition
 * for problems with special structure.
 *
 * **Core functions:**
 * - decomp(): Main decomposition algorithm
 * - create_initial_lp(): Build restricted master problem
 * - generate_new_cols(): Solve pricing subproblem
 * - generate_cuts(): Cut generation in master
 * - add_dcmp_cols(): Add columns to master LP
 *
 * **Column management:**
 * - receive_cols(): Receive columns from subproblems
 * - get_cols_from_pool(): Retrieve from column pool
 * - free_dcmp_col_set(): Cleanup column set
 *
 * **User callbacks:**
 * - user_generate_new_cols(): Custom pricing routine
 * - user_unpack_col(): Expand packed column
 * - user_pack_col(): Compress column for storage
 * - user_check_col(): Verify column validity
 * - user_set_rhs(): Define subproblem RHS
 * - user_send_to_sol_pool(): Store promising columns
 *
 * @algorithm Dantzig-Wolfe Decomposition:
 *   Reformulate MIP by representing feasible region as convex hull:
 *   @math Original: min c'x s.t. Ax ≥ b, Dx ≥ d, x ∈ Z
 *         Master: min Σ(c'x^k)λ_k s.t. Σ(Ax^k)λ_k ≥ b, Σλ_k = 1
 *         where {x^k} are extreme points of {x : Dx ≥ d}
 *   Linking constraints (Ax ≥ b) in master, block constraints (Dx ≥ d)
 *   handled implicitly via extreme point enumeration.
 *   @complexity Depends on subproblem; master LP has exponential columns
 *   @ref Dantzig, G. and Wolfe, P. (1960). "Decomposition principle for
 *        linear programs". Operations Research 8(1):101-111.
 *
 * @algorithm Column Generation:
 *   Solve master LP with subset of columns, add improving columns:
 *   @math Pricing subproblem: min (c - π'A)x s.t. Dx ≥ d
 *         If reduced cost < 0, add column to restricted master
 *         Terminate when no negative reduced cost column exists
 *   generate_new_cols() solves pricing via user_generate_new_cols().
 *   @complexity Each master solve is O(m²·|active_cols|)
 *   @ref Lübbecke, M. and Desrosiers, J. (2005). "Selected topics in
 *        column generation". Operations Research 53(6):1007-1023.
 *
 * @algorithm Column Pool Management:
 *   Store and retrieve columns across B&B tree:
 *   @math Pool stores (column, reduced_cost) pairs
 *         get_cols_from_pool() retrieves columns with negative reduced cost
 *         user_send_to_sol_pool() archives promising columns
 *   Avoids regenerating columns found in other nodes.
 *   @complexity O(pool_size) per lookup
 *
 * @see decomp_types.h for col_data, dcmp_col_set
 * @see decomp_lp.h for LP interface
 * @see sp_params.h for column pool parameters
 */
#ifndef _DECOMP_H
#define _DECOMP_H

#include "sym_proto.h"
#include "sym_cg.h"
#include "decomp_types.h"

int create_initial_lp PROTO((cg_prob *p));
int decomp PROTO((cg_prob *p));
int receive_cols PROTO((cg_prob *p));
int dcmp_process_message PROTO((cg_prob *p, int sender, int msgtag,
				dcmp_col_set *cols, int *sol_id));
void open_decomp_lp PROTO((cg_prob *p, int varnum));
void close_decomp_lp PROTO((cg_prob *p));
int generate_cuts PROTO((cg_prob *p));
/*int add_cols PROTO((cg_prob *p, col_data **cols, int num_cols));*/
void get_cols_from_pool PROTO((cg_prob *p, int tid));
int generate_new_cols PROTO((cg_prob *p));
void add_dcmp_cols PROTO((LPdata *lp_data, dcmp_col_set *cols,
			 int col_block_size, int mat_block_size));
void free_dcmp_col_set PROTO((dcmp_col_set *cols));

/*===== User supplied routines ======================================*/

dcmp_col_set *user_generate_new_cols PROTO((cg_prob *p));
void user_unpack_col PROTO((cg_prob *p, col_data *col, int *nzcnt,
			    int *matind));
void user_display_col PROTO((cg_prob *p, col_data *col));
int user_check_col PROTO((cg_prob *p, int *colind, double *colval,
			  int collen));
void user_pack_col PROTO((int *colind, int collen, col_data *packed_col));
void user_free_decomp_data_structures PROTO((cg_prob *p, void **user));
char user_set_rhs PROTO((int varnum, double *rhs, int length, int *ind,
			 double *val, void *user));
void user_send_to_sol_pool PROTO((cg_prob *p));

#endif
