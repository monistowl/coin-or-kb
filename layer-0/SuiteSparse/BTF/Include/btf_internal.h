/**
 * @file btf_internal.h
 * @brief Internal definitions for BTF (Block Triangular Form) permutation
 * Copyright (c) 2004-2023, University of Florida. LGPL-2.1+ license.
 *
 * BTF finds permutation matrices P and Q such that P·A·Q has block upper
 * triangular form with square diagonal blocks that are irreducible
 * (strongly connected components). Essential preprocessing for sparse LU.
 *
 * @algorithm Block Triangular Form (BTF/Dulmage-Mendelsohn):
 * Decomposes sparse matrix into block upper triangular structure:
 * 1. MAXIMUM TRANSVERSAL: Find maximum matching in bipartite graph
 *    - Row i matched to column j if A(i,j) nonzero and selected
 *    - Hopcroft-Karp or DFS-based augmenting path algorithm
 * 2. STRONGLY CONNECTED COMPONENTS:
 *    - Build directed graph from A with matched edges
 *    - Tarjan's algorithm finds SCCs (diagonal blocks)
 * 3. TOPOLOGICAL SORT: Order SCCs so dependencies flow downward
 *
 * @math Dulmage-Mendelsohn decomposition:
 * P·A·Q = [A_11  A_12  ...  A_1k]
 *         [0     A_22  ...  A_2k]
 *         [⋮      ⋱    ⋱    ⋮  ]
 *         [0     0    ...  A_kk]
 * Each A_ii is square and structurally nonsingular (irreducible).
 * Singular matrices have zero diagonal blocks (structural rank deficiency).
 *
 * @complexity O(n + nz) for finding BTF permutation.
 * Matching: O(n·√nz) using Hopcroft-Karp.
 *
 * @ref Duff & Reid (1978). "Algorithm 529: Permutations to Block Triangular
 *   Form". ACM TOMS 4(2):189-192.
 *
 * @see KLU for sparse LU using BTF preprocessing
 * @see AMD for ordering within diagonal blocks
 */

//------------------------------------------------------------------------------
// BTF/Include/btf_internsl.h: internal include file for BTF
//------------------------------------------------------------------------------

// BTF, Copyright (c) 2004-2023, University of Florida.  All Rights Reserved.
// Author: Timothy A. Davis.
// SPDX-License-Identifier: LGPL-2.1+

//------------------------------------------------------------------------------

#ifndef _BTF_INTERNAL_H
#define _BTF_INTERNAL_H

/* Not to be included in any user program. */

#ifdef DLONG
#define Int int64_t
#define Int_id "%" PRId64
#define BTF(name) btf_l_ ## name
#else
#define Int int32_t
#define Int_id "%d"
#define BTF(name) btf_ ## name
#endif

/* ========================================================================== */
/* make sure debugging and printing is turned off */

#ifndef NDEBUG
#define NDEBUG
#endif
#ifndef NPRINT
#define NPRINT
#endif

/* To enable debugging and assertions, uncomment this line: 
 #undef NDEBUG
*/
/* To enable diagnostic printing, uncomment this line: 
 #undef NPRINT
*/

/* ========================================================================== */

#include <stdio.h>
#include <assert.h>
#define ASSERT(a) assert(a)

#undef TRUE
#undef FALSE
#undef PRINTF
#undef MIN

#ifndef NPRINT
#define PRINTF(s) { printf s ; } ;
#else
#define PRINTF(s)
#endif

#define TRUE 1
#define FALSE 0
#define EMPTY (-1)
#define MIN(a,b) (((a) < (b)) ?  (a) : (b))

#endif
