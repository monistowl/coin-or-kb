/**
 * @file Mongoose_BoundaryHeap.hpp
 * @brief Boundary vertex heap for FM partition refinement
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Manages heaps of boundary vertices (those with edges crossing cut)
 * for FM algorithm. Two heaps (one per partition) ordered by vertex
 * gain. Operations: load, clear, insert, remove, heapifyUp/Down.
 * Critical for efficient O(n log n) FM refinement.
 *
 * @algorithm Boundary Heap for FM Refinement:
 * Max-heap of boundary vertices ordered by move gain:
 *
 * Structure: Two heaps, one per partition (A and B).
 * - Only boundary vertices (with edges to other partition) are in heap
 * - Interior vertices excluded (moving them always hurts cut)
 *
 * Operations:
 * - bhLoad: Initialize heaps with all boundary vertices, O(n)
 * - bhInsert: Add vertex to appropriate heap, O(log n)
 * - bhRemove: Remove vertex (after move), O(log n)
 * - heapifyUp/Down: Restore heap property after gain update, O(log n)
 *
 * @math Gain ordering enables greedy selection:
 * FM always moves vertex with maximum gain (heap top).
 * gain(v) = external_edges(v) - internal_edges(v)
 * Positive gain → moving v reduces cut.
 *
 * @complexity Each FM pass: O(n log n) for n heap operations.
 * Heap property ensures O(1) access to best move.
 *
 * @see Mongoose_ImproveFM.hpp for FM algorithm using boundary heaps
 * @see Mongoose_EdgeCutProblem.hpp for bhHeap storage
 */

/* ========================================================================== */
/* === Include/Mongoose_BoundaryHeap.hpp ==================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_BOUNDARYHEAP_HPP
#define MONGOOSE_BOUNDARYHEAP_HPP

#include "Mongoose_EdgeCutOptions.hpp"
#include "Mongoose_EdgeCutProblem.hpp"
#include "Mongoose_Internal.hpp"

namespace Mongoose
{

void bhLoad(EdgeCutProblem *, const EdgeCut_Options *);
void bhClear(EdgeCutProblem *);
void bhInsert(EdgeCutProblem *, Int vertex);

void bhRemove(EdgeCutProblem *, const EdgeCut_Options *, Int vertex, double gain, bool partition,
              Int bhPosition);

void heapifyUp(EdgeCutProblem *, Int *bhHeap, double *gains, Int vertex, Int position,
               double gain);

void heapifyDown(EdgeCutProblem *, Int *bhHeap, Int size, double *gains, Int vertex,
                 Int position, double gain);

} // end namespace Mongoose

#endif
