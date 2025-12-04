/**
 * @file Mongoose_QPNapsack.hpp
 * @brief Napsack subproblem solver for QP balance constraint
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * QPNapsack solves the napsack subproblem: find lambda such that the
 * projected solution satisfies balance constraint lo <= a'x <= hi.
 * Uses breakpoint method with heaps to efficiently find optimal lambda.
 * Core subroutine in QP gradient projection.
 *
 * @algorithm Continuous Knapsack (Breakpoint Search):
 * Finds Lagrange multiplier λ for balance constraint a'x ∈ [lo, hi]:
 * 1. Initialize: compute a'y for unconstrained projection y
 * 2. If a'y ∈ [lo, hi]: done, λ = 0
 * 3. Otherwise: binary/heap search for breakpoint where constraint binds
 *    - Breakpoints: λ values where some x_i hits 0 or 1
 *    - Track a'x as λ changes (piecewise linear in λ)
 * 4. Return λ such that a'x = lo (or hi)
 *
 * @math Projection with balance constraint:
 * $$x_i = \Pi_{[0,1]}(y_i - \lambda a_i)$$
 * where λ is chosen so $\sum_i a_i x_i \in [lo, hi]$.
 *
 * As λ increases: x_i with positive a_i decrease → a'x decreases.
 * As λ decreases: x_i with positive a_i increase → a'x increases.
 *
 * @complexity O(n log n) due to heap-based breakpoint enumeration.
 * Dominates each QP iteration when balance constraint is tight.
 *
 * @ref Kiwiel (2008). "Breakpoint searching algorithms for the
 *   continuous quadratic knapsack problem". Math Programming 112(2).
 *
 * @see Mongoose_QPNapUp.hpp for upward lambda search
 * @see Mongoose_QPNapDown.hpp for downward lambda search
 */

/* ========================================================================== */
/* === Include/Mongoose_QPNapsack.hpp ======================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_QPNAPSACK_HPP
#define MONGOOSE_QPNAPSACK_HPP

#include "Mongoose_Internal.hpp"

namespace Mongoose
{

double QPNapsack    /* return the final lambda */
    (double *x,     /* holds y on input, and the solution x on output */
     Int n,         /* size of x, constraint lo <= a'x <= hi */
     double lo,     /* partition lower bound */
     double hi,     /* partition upper bound */
     double *a,     /* vector of nodal weights */
     double Lambda, /* initial guess for lambda */
     const Int *FreeSet_status,
     /* FreeSet_status[i] = +1,-1, or 0 on input, for 3 cases:
        x_i = 1, 0, or 0< x_i< 1 */
     double *w,  /* work array of size n */
     Int *heap1, /* work array of size n+1 */
     Int *heap2, /* work array of size n+1 */
     double tol);

} // end namespace Mongoose

#endif
