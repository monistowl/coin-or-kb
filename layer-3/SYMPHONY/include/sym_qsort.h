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
 * @file sym_qsort.h
 * @brief Quicksort variants and utility functions
 *
 * Specialized quicksort implementations for common data patterns.
 *
 * **Quicksort variants:**
 * - qsort_i(): Sort integer array
 * - qsort_id(): Sort int array, permute double array
 * - qsort_ic(): Sort int array, permute char array
 * - qsort_ii(): Sort int array, permute second int array
 * - qsort_di(): Sort double array, permute int array
 *
 * **Utility functions:**
 * - sym_gcd(): Greatest common divisor
 * - d_gap(): Compute optimality gap percentage
 *
 * @algorithm Paired Quicksort:
 *   Sort array while maintaining correspondence with secondary array:
 *   @math qsort_id(keys, vals, n): sort keys[0..n-1], permute vals accordingly
 *         Partitions both arrays around pivot, recurses on subarrays
 *   Used for sorting variable indices by reduced cost, etc.
 *   @complexity O(n log n) average, O(n²) worst case
 *
 * @algorithm Optimality Gap Calculation:
 *   Compute relative gap between bounds:
 *   @math d_gap(ub, lb, offset, sense) =
 *         100 · |ub - lb| / max(|ub|, |lb|, 1)
 *   Handles minimization/maximization via sense parameter.
 *   Used for termination criteria in B&B.
 *
 * @see sym_lp.h for LP process using sort functions
 */
#ifndef _QSORT_H
#define _QSORT_H

//void qsort(char *bot, unsigned int nmemb, int size,
//	   int (*compar)(const void *, const void *));

void qsort_i(int *bot, int nmemb);
void qsort_id(int *bot, double *botd, int nmemb);
void qsort_ic(int *bot, char *botc, int nmemb);
void qsort_ii(int *bot, int *bota, int nmemb);
void qsort_di(double *botd, int *boti, int nmemb);
/* TODO: replace with some function from CoinUtils */
int sym_gcd(int i1, int i2);
double d_gap(double obj_ub, double obj_lb, double obj_offset, char obj_sense);
#endif
