/**
 * @file Mongoose_Internal.hpp
 * @brief Internal type definitions and enumerations for Mongoose
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Defines Int type (int64_t), matching strategies (Random, HEM, HEMSR,
 * HEMSRdeg), initial cut types (QP, Random, NaturalOrder), and match
 * types (Orphan, Standard, Brotherly, Community) used throughout Mongoose.
 *
 * @algorithm Enumeration Definitions:
 *
 * MatchingStrategy - How to pair vertices during coarsening:
 * - Random: Random neighbor selection, O(1) per vertex
 * - HEM: Heavy Edge Matching, O(degree) per vertex
 * - HEMSR: HEM with Stall Ratio, retries on mismatch
 * - HEMSRdeg: HEMSR with degree ordering
 *
 * InitialEdgeCutType - How to partition coarsest graph:
 * - QP: Quadratic programming relaxation (best quality)
 * - Random: Random assignment (fastest)
 * - NaturalOrder: First half vs second half
 *
 * MatchType - Classification of matched vertices:
 * - Orphan: Unmatched (creates singleton coarse vertex)
 * - Standard: Paired with single neighbor
 * - Brotherly: 3-way match forming cycle
 * - Community: 4-way match forming clique
 *
 * @see Mongoose_Matching.hpp for matching algorithm implementations
 */

/* ========================================================================== */
/* === Include/Mongoose_Internal.hpp ======================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_INTERNAL_HPP
#define MONGOOSE_INTERNAL_HPP

#define FREESET_DEBUG 0

#if __cplusplus > 199711L
#define CPP11_OR_LATER true
#else
#define CPP11_OR_LATER false
#endif

/* Dependencies */
#include <climits>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <algorithm>

/* Memory Management */
#include "SuiteSparse_config.h"

#if !defined (SUITESPARSE_VERSION) || \
    (SUITESPARSE_VERSION < SUITESPARSE_VER_CODE(7,4))
#error "Mongoose requires SuiteSparse_config 7.4.0 or later"
#endif

#ifndef MAX_INT
#define MAX_INT INT64_MAX
#endif

#ifndef MONGOOSE_HPP
// avoid collision with symbols that are declared in Mongoose.hpp

#if defined (_MSC_VER) && ! defined (__INTEL_COMPILER)
    #if defined (MONGOOSE_STATIC)
        #define MONGOOSE_API
    #else
        #if defined (MONGOOSE_BUILDING)
            #define MONGOOSE_API __declspec ( dllexport )
        #else
            #define MONGOOSE_API __declspec ( dllimport )
        #endif
    #endif
#else
    // for other compilers
    #define MONGOOSE_API
#endif

namespace Mongoose
{

/* Type definitions */
typedef int64_t Int;

/* Enumerations */
enum MatchingStrategy
{
    Random   = 0,
    HEM      = 1,
    HEMSR    = 2,
    HEMSRdeg = 3
};

enum InitialEdgeCutType
{
    InitialEdgeCut_QP           = 0,
    InitialEdgeCut_Random       = 1,
    InitialEdgeCut_NaturalOrder = 2
};

enum MatchType
{
    MatchType_Orphan    = 0,
    MatchType_Standard  = 1,
    MatchType_Brotherly = 2,
    MatchType_Community = 3
};

} // end namespace Mongoose
#endif

#endif
