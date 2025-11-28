/**
 * @file sp_params.h
 * @brief Solution/column pool parameters for decomposition
 *
 * Parameters controlling column storage and management.
 *
 * **sp_params structure:**
 * - verbosity: Output level
 * - etol: Numerical tolerance
 * - block_size: Allocation granularity
 * - max_size: Maximum pool memory
 * - max_number_of_sols: Hard limit on columns
 * - min_to_delete: Minimum batch deletion size
 * - touches_until_deletion: Inactivity threshold
 * - compress_num/ratio: When to compress pool
 *
 * **Check strategies (check_which):**
 * - CHECK_ALL_COLS: Check everything
 * - CHECK_COL_LEVEL: By tree depth
 * - CHECK_COL_TOUCHES: By activity
 * - CHECK_COL_LEVEL_AND_TOUCHES: Combined
 *
 * **Delete strategies (delete_which):**
 * - DELETE_DUPLICATE_COLS: Only duplicates
 * - DELETE_DUPLICATE_AND_INEFFECTIVE_COLS: Also inactive
 *
 * @see decomp.h for column generation using pool
 */
#ifndef _SOL_POOL_PARAMS_H
#define _SOL_POOL_PARAMS_H

typedef struct SOL_POOL_PARAMS{
   int     verbosity;
   double  etol;
   int     block_size;
   int     delete_which;
   int     max_size;
   int     max_number_of_sols;
   int     min_to_delete;
   int     check_which;
   int     touches_until_deletion;
   int     compress_num;
   double  compress_ratio;
}sp_params;

/* parameter values for "check_which_cuts" */
#define CHECK_ALL_COLS              0
#define CHECK_COL_LEVEL             1
#define CHECK_COL_TOUCHES           2
#define CHECK_COL_LEVEL_AND_TOUCHES 3

/* parameter values for "delete_which_cuts" */
#define DELETE_DUPLICATE_COLS                  1
#define DELETE_DUPLICATE_AND_INEFFECTIVE_COLS  2

#endif
