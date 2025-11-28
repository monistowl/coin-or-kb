/**
 * @file decomp_types.h
 * @brief Data structures for decomposition column generation
 *
 * Types for representing columns in Dantzig-Wolfe decomposition.
 *
 * **col_data (packed column):**
 * - size: Size of coef array
 * - coef: Packed column data
 * - level: Tree level where generated
 * - touches: Inactivity counter for deletion
 *
 * **dcmp_col_set (column batch):**
 * - lb, ub, obj: Column bounds and costs
 * - matbeg, matind, matval: CSC format matrix
 * - num_cols, nzcnt: Dimensions
 * - bd_type, ubnd: Bound type info
 *
 * @see decomp.h for column generation functions
 */
#ifndef _DECOMP_TYPES_H
#define _DECOMP_TYPES_H

#define COL_BLOCK_SIZE 10

typedef struct COL_DATA{
   int  size;    /*the size of the coef array*/
   char *coef;   /*an array which contains the data necessary to construct
		   the column -- it is stored in a packed form. */
   int  level;
   int  touches; /*the number of times (in a row) the column was checked
		   for violation and found not to be violated. This is
		   a measure of the usefulness of the column*/
}col_data;

typedef struct DCMP_COL_SET{
   double *lb;
   double *ub;
   double *obj;
   int *matbeg;
   int *matind;
   double *matval;
   int num_cols;
   int max_cols;
   int nzcnt;
   int max_nzcnt;
   int bd_type;
   int ubnd;
}dcmp_col_set;

#endif
