/**
 * @file lu_file.h
 * @brief Sparse matrix file management for dynamic row/column storage
 *
 * Manages dynamic sparse storage where rows/columns can grow during
 * factorization. Uses a file-based metaphor where each "line" (row or column)
 * occupies a contiguous range in the index/value arrays.
 *
 * **Storage Layout:**
 * - begin[i], end[i]: Range of entries for line i
 * - next[i], prev[i]: Doubly linked list for memory management
 * - index[], value[]: Actual sparse data
 *
 * **Operations:**
 * - lu_file_empty: Initialize empty file structure
 * - lu_file_reappend: Move line to end with extra space for growth
 * - lu_file_compress: Garbage collection to reclaim fragmented space
 * - lu_file_diff: Compute storage difference between row/column views
 *
 * The reappend operation adds padding (xstore[BASICLU_PAD] + nz × stretch)
 * to reduce frequency of moves as fill-in occurs during elimination.
 *
 * @see lu_internal.h for W array usage (Wi, Wx, Wbegin, Wend, Wflink, Wblink)
 */
#ifndef _LU_FILE_H
#define _LU_FILE_H

void lu_file_empty(
    lu_int nlines, lu_int *begin, lu_int *end, lu_int *next, lu_int *prev,
    lu_int fmem);

void lu_file_reappend(
    lu_int line, lu_int nlines, lu_int *begin, lu_int *end, lu_int *next,
    lu_int *prev, lu_int *index, double *value, lu_int extra_space);

lu_int lu_file_compress(
    lu_int nlines, lu_int *begin, lu_int *end, const lu_int *next,
    lu_int *index, double *value, double stretch, lu_int pad);

lu_int lu_file_diff(
    lu_int nrow, const lu_int *begin_row, const lu_int *end_row,
    const lu_int *begin_col, const lu_int *end_col, const lu_int *index,
    const double *value);

#endif
