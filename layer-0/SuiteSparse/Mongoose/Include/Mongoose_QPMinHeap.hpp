/**
 * @file Mongoose_QPMinHeap.hpp
 * @brief Min-heap for QP napsack breakpoint processing
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * QPMinHeap provides min-heap operations (build, delete, add, heapify)
 * for efficient breakpoint processing in napsack solver. Extracts
 * breakpoints in ascending order to find optimal lambda for balance
 * constraint satisfaction.
 *
 * @see Mongoose_QPNapsack.hpp for napsack solver using heaps
 * @see Mongoose_QPMaxHeap.hpp for complementary max-heap
 */

/* ========================================================================== */
/* === Include/Mongoose_QPMinHeap.hpp ======================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_QPMINHEAP_HPP
#define MONGOOSE_QPMINHEAP_HPP

#include "Mongoose_Internal.hpp"

namespace Mongoose
{

void QPMinHeap_build(Int *heap, /* on input, an unsorted set of elements */
                     Int size,  /* size of the heap */
                     double *x);

Int QPMinHeap_delete /* return new size of heap */
    (Int *heap,      /* containing indices into x, 1..n on input */
     Int size,       /* size of the heap */
     const double *x /* not modified */
    );

void QPMinHeapify(Int p,          /* start at vertex p in the heap */
                  Int *heap,      /* size n, containing indices into x */
                  Int size,       /* heap [ ... nheap] is in use */
                  const double *x /* not modified */
);

Int QPMinHeap_add(Int leaf,        /* the new leaf */
                  Int *heap,       /* size n, containing indices into x */
                  const double *x, /* not modified */
                  Int size /* number of elements in heap not counting new one */
);

void QPminheap_check(Int *heap,   /* vector of size n+1 */
                     double *x,   /* vector of size n */
                     Int size,    /* # items in heap */
                     Int n, Int p /* start checking at heap [p] */
);

} // end namespace Mongoose

#endif
