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
