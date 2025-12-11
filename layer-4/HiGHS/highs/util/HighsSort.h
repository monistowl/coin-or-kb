/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                       */
/*    This file is part of the HiGHS linear optimization suite           */
/*                                                                       */
/*    Available as open-source under the MIT License                     */
/*                                                                       */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/**
 * @file util/HighsSort.h
 * @brief Heap-based sorting routines for HiGHS
 *
 * In-place heapsort implementations for indices and value-index pairs.
 *
 * @algorithm Heapsort (Williams 1964, Floyd 1964):
 *   In-place comparison sort using binary heap:
 *   @math Phase 1 (Build): Bottom-up heapify in O(n)
 *           for i = n/2 downto 1: maxHeapify(i)
 *         Phase 2 (Sort): Extract max n times in O(n log n)
 *           for i = n downto 2: swap(1,i), maxHeapify(1)
 *   @complexity O(n log n) worst-case, O(1) extra space
 *   @ref Williams (1964) "Algorithm 232: Heapsort"
 *
 * @algorithm Bounded Decreasing Heap:
 *   Maintain k largest elements seen in stream:
 *   @math Min-heap of size k, reject if new < heap[1]
 *         Insert: push then sift-up, eject min if full
 *   Used for top-k selection in ratio tests.
 *
 * **Functions:**
 * - maxheapsort(): Combined build + sort
 * - buildMaxheap() + maxHeapsort(): Separate phases
 * - maxHeapify(): Sift-down operation
 *
 * **Overloads:**
 * - (HighsInt*): Sort indices only
 * - (double*, HighsInt*): Sort values with corresponding indices
 * - (HighsInt*, HighsInt*): Sort HighsInt values with indices
 *
 * **Decreasing Heap Utilities:**
 * - addToDecreasingHeap(): Insert into bounded min-heap
 * - sortDecreasingHeap(): Extract in decreasing order
 *
 * **Validation:**
 * - increasingSetOk(): Check sorted order and bounds
 * - sortSetData(): Sort indices and reorder associated data arrays
 *
 * @note Arrays use 1-based indexing: heap[1..n]
 * @see simplex/HEkkDual.h for CHUZC ratio test using heaps
 */
#ifndef UTIL_HIGHSSORT_H_
#define UTIL_HIGHSSORT_H_

#include <vector>

#include "lp_data/HConst.h"

using std::vector;

void addToDecreasingHeap(HighsInt& n, HighsInt mx_n, vector<double>& heap_v,
                         vector<HighsInt>& heap_ix, double v, HighsInt ix);
void sortDecreasingHeap(const HighsInt n, vector<double>& heap_v,
                        vector<HighsInt>& heap_ix);
/**
 * @brief Sort values[1..n] of an array by increasing value
 */
void maxheapsort(HighsInt* heap_v,  //!< HighsInt values to be sorted
                 HighsInt n         //!< Number of values to be sorted
);
/**
 * @brief Sort values[1..n] of an array by increasing value with corresponding
 * indices
 */
void maxheapsort(
    HighsInt* heap_v,  //!< Values to be sorted
    HighsInt* heap_i,  //!< Indices corresponding to (sorted) values
    HighsInt n         //!< Number of values to be sorted
);
/**
 * @brief Sort values[1..n] of an array by increasing value with corresponding
 * indices
 */
void maxheapsort(
    double* heap_v,    //!< Values to be sorted
    HighsInt* heap_i,  //!< Indices corresponding to (sorted) values
    HighsInt n         //!< Number of values to be sorted
);
/**
 * @brief Build a value heap for sorting values[1..n] of an array by increasing
 * value
 */
void buildMaxheap(HighsInt* heap_v,  //!< HighsInt values to be sorted
                  HighsInt n         //!< Number of values to be sorted
);
/**
 * @brief Build a value-index heap for sorting values[1..n] of an array by
 * increasing value
 */
void buildMaxheap(
    HighsInt* heap_v,  //!< Values to be sorted
    HighsInt* heap_i,  //!< Indices corresponding to (sorted) values
    HighsInt n         //!< Number of values to be sorted
);
/**
 * @brief Build a value-index heap for sorting values[1..n] of an array by
 * increasing value
 */
void buildMaxheap(
    double* heap_v,    //!< Values to be sorted
    HighsInt* heap_i,  //!< Indices corresponding to (sorted) values
    HighsInt n         //!< Number of values to be sorted
);
/**
 * @brief Sort by increasing value a heap built with buildMaxheap
 */
void maxHeapsort(HighsInt* heap_v,  //!< HighsInt values to be sorted
                 HighsInt n         //!< Number of values to be sorted
);
/**
 * @brief Sort by increasing value a heap built with buildMaxheap
 */
void maxHeapsort(
    HighsInt* heap_v,  //!< Values to be sorted
    HighsInt* heap_i,  //!< Indices corresponding to (sorted) values
    HighsInt n         //!< Number of values to be sorted
);
/**
 * @brief Sort by increasing value a heap built with buildMaxheap
 */
void maxHeapsort(
    double* heap_v,    //!< Values to be sorted
    HighsInt* heap_i,  //!< Indices corresponding to (sorted) values
    HighsInt n         //!< Number of values to be sorted
);
/**
 * @brief Heapify function for sorting by increasing value
 */
void maxHeapify(HighsInt* heap_v, HighsInt i, HighsInt n);

/**
 * @brief Heapify function for sorting by increasing value
 */
void maxHeapify(HighsInt* heap_v, HighsInt* heap_i, HighsInt i, HighsInt n);

/**%
 * @brief Heapify function for sorting by increasing value
 */
void maxHeapify(double* heap_v, HighsInt* heap_i, HighsInt i, HighsInt n);

/**
 * @brief Check that a set of integers is in increasing order and in bounds
 */
bool increasingSetOk(const vector<HighsInt>& set,
                     const HighsInt set_entry_lower,
                     const HighsInt set_entry_upper, bool strict);

/**
 * @brief Check that a set of doubles is in increasing order and in bounds
 */
bool increasingSetOk(const vector<double>& set, const double set_entry_lower,
                     const double set_entry_upper, bool strict);

void sortSetData(const HighsInt num_entries, vector<HighsInt>& set,
                 const double* data0, const double* data1, const double* data2,
                 double* sorted_data0, double* sorted_data1,
                 double* sorted_data2);

void sortSetData(const HighsInt num_entries, vector<HighsInt>& set,
                 const HighsVarType* data0, HighsVarType* sorted_data0);

#endif /* UTIL_HIGHSSORT_H_ */
