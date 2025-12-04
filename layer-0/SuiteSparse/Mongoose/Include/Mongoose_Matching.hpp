/**
 * @file Mongoose_Matching.hpp
 * @brief Vertex matching algorithms for graph coarsening
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Implements matching strategies: Random (random neighbor), HEM (heavy
 * edge matching), SR/SRdeg (sorted/degree-sorted heavy edge). Matching
 * pairs vertices for coarsening; heavier edges are preferred to preserve
 * graph structure. Cleanup handles unmatched (orphan) vertices.
 *
 * @algorithm Heavy Edge Matching (HEM):
 * Pairs vertices connected by heaviest edges to preserve structure:
 * 1. Visit vertices in random order (for randomization)
 * 2. For unmatched vertex v, find heaviest edge to unmatched neighbor u
 * 3. Match v with u: match[v] = u, match[u] = v
 * 4. Continue until all vertices matched or isolated
 * 5. Cleanup: handle orphan vertices (no valid matches)
 *
 * @math Heavy edge principle: prefer matching (i,j) if w_ij is large.
 * Rationale: heavy edges likely internal to optimal partition,
 * so collapsing them preserves cut structure on coarser graph.
 *
 * Variants:
 * - Random: match with random neighbor (fastest)
 * - HEM: match with heaviest-edge neighbor
 * - HEMSR: sorted random ordering for HEM
 * - HEMSRdeg: degree-sorted ordering (low-degree first)
 *
 * @complexity O(|E|) for all variants (single pass through edges).
 *
 * @see Mongoose_Coarsening.hpp for graph contraction using matches
 * @see Mongoose_Internal.hpp for MatchingStrategy enum
 */

/* ========================================================================== */
/* === Include/Mongoose_Matching.hpp ======================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_MATCHING_HPP
#define MONGOOSE_MATCHING_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"

namespace Mongoose
{

void match(EdgeCutProblem *, const EdgeCut_Options *);

void matching_Random(EdgeCutProblem *, const EdgeCut_Options *);
void matching_HEM(EdgeCutProblem *, const EdgeCut_Options *);
void matching_SR(EdgeCutProblem *, const EdgeCut_Options *);
void matching_SRdeg(EdgeCutProblem *, const EdgeCut_Options *);
void matching_Cleanup(EdgeCutProblem *, const EdgeCut_Options *);

} // end namespace Mongoose

#endif
