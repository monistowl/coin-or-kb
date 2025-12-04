/**
 * @file Mongoose_Coarsening.hpp
 * @brief Graph coarsening via vertex matching for multilevel partitioning
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Coarsening reduces graph size while preserving structure by contracting
 * matched vertices. Given a matching (HEM, random, etc.), creates coarser
 * graph with merged vertices and aggregated edge weights. Essential for
 * multilevel partitioning to handle large graphs efficiently.
 *
 * @algorithm Graph Coarsening (Vertex Contraction):
 * Creates smaller graph G' from G by merging matched vertex pairs:
 * 1. Use matching (match[i] = j means vertices i,j are paired)
 * 2. Create supervertex for each matched pair (or singleton)
 * 3. Aggregate vertex weights: w'_k = w_i + w_j
 * 4. Combine edges: e'(k,l) = e(i,l) + e(j,l) for matched pair (i,j)
 * 5. Remove self-loops (edges within matched pairs become internal)
 *
 * @math Coarsening preserves cut structure:
 * For partition P of G inducing P' on G':
 * cut(P) = cut(P') + internal edges (contracted)
 * Since internal edges can't be cut, optimizing on G' approximates G.
 *
 * @complexity O(|E|) per coarsening level.
 * Total levels: O(log |V|) until |V'| < coarsen_limit.
 *
 * @see Mongoose_Matching.hpp for vertex matching algorithms
 * @see Mongoose_Refinement.hpp for uncoarsening/projection
 */

/* ========================================================================== */
/* === Include/Mongoose_Coarsening.hpp ====================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_COARSENING_HPP
#define MONGOOSE_COARSENING_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"
#include "Mongoose_Matching.hpp"

namespace Mongoose
{

EdgeCutProblem *coarsen(EdgeCutProblem *, const EdgeCut_Options *);

} // end namespace Mongoose

#endif
