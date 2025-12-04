/**
 * @file Mongoose_QPNapDown.hpp
 * @brief Downward lambda search in napsack solver
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * QPNapDown searches for lambda in decreasing direction when current
 * solution violates lower balance bound (b < lo). Processes breakpoints
 * via heaps until constraint is satisfied, returning optimal lambda.
 *
 * @algorithm Downward Breakpoint Search:
 * Decreases λ to increase a'x (currently b < lo, need b ≥ lo):
 * 1. Build heaps of breakpoints: λ values where variables hit bounds
 *    - bound_heap: λ where free x_i hits 1 (upper bound)
 *    - free_heap: λ where bound x_i = 0 becomes free
 * 2. Process breakpoints in decreasing λ order:
 *    - At each breakpoint, variable changes status (free↔bound)
 *    - Update b = a'x incrementally
 *    - Stop when b ≥ lo
 * 3. Interpolate final λ if stopping between breakpoints
 *
 * @math Symmetric to QPNapUp but decreasing λ:
 * For free variable i: Δx_i = -a_i·δ (δ < 0) → Δb > 0 for a_i > 0
 * Decreasing λ increases x values, increasing a'x.
 *
 * @complexity O(n log n) for heap operations over n variables.
 *
 * @see Mongoose_QPNapsack.hpp for main napsack solver
 * @see Mongoose_QPNapUp.hpp for upward search
 */

/* ========================================================================== */
/* === Include/Mongoose_QPNapDown.hpp ======================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_QPNAPDOWN_HPP
#define MONGOOSE_QPNAPDOWN_HPP

#include "Mongoose_Internal.hpp"

namespace Mongoose
{

double QPNapDown       /* return lambda */
    (const double *x,  /* holds y on input, not modified */
     Int n,            /* size of x */
     double lambda,    /* initial guess for the shift */
     const double *a,  /* input constraint vector */
     double b,         /* input constraint scalar */
     double *breakpts, /* break points */
     Int *bound_heap,  /* work array */
     Int *free_heap    /* work array */
    );

} // end namespace Mongoose

#endif
