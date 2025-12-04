/**
 * @file Mongoose_EdgeCutOptions.hpp
 * @brief Configuration options for edge cut partitioning algorithms
 * Copyright (C) 2017-2023, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * EdgeCut_Options controls all algorithm parameters: coarsening (limit,
 * matching strategy, community detection), initial cut type (QP/random),
 * Fiduccia-Mattheyses (search depth, refinement count), QP gradient
 * projection (tolerance, iteration limit), and partition targets
 * (split ratio, balance tolerance).
 *
 * @algorithm Configuration Parameter Groups:
 * Controls algorithm behavior at each phase:
 *
 * Coarsening phase:
 * - coarsen_limit: Stop coarsening at this size (default ~64)
 * - matching_strategy: HEM, SHEM, or random (HEM usually best)
 * - do_community_matching: Enable 3-4 vertex community detection
 *
 * Initial partition:
 * - initial_cut_type: QP (best quality) or Random (fast)
 *
 * Refinement phase:
 * - num_dances: FM/QP alternation count (1-3 typical)
 * - FM_search_depth: Non-improving moves before stopping
 * - FM_max_num_refinements: FM passes per level
 * - gradproj_tolerance: QP convergence threshold
 * - gradproj_iteration_limit: Max QP iterations
 *
 * Target metrics:
 * - target_split: Desired partition ratio (0.5 = balanced)
 * - soft_split_tolerance: Acceptable imbalance range
 *
 * @complexity O(1) to create/access options.
 *
 * @see Mongoose_ImproveFM.hpp for FM algorithm
 * @see Mongoose_ImproveQP.hpp for QP refinement
 */

/* ========================================================================== */
/* === Include/Mongoose_EdgeCutOptions.hpp ================================== */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2023,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_EDGECUTOPTIONS_HPP
#define MONGOOSE_EDGECUTOPTIONS_HPP

#include "Mongoose_Internal.hpp"

namespace Mongoose
{

struct EdgeCut_Options
{
    Int random_seed;

    /** Coarsening Options ***************************************************/
    Int coarsen_limit;
    MatchingStrategy matching_strategy;
    bool do_community_matching;
    double high_degree_threshold;

    /** Guess Partitioning Options *******************************************/
    InitialEdgeCutType initial_cut_type; /* The guess cut type to use */

    /** Waterdance Options ***************************************************/
    Int num_dances; /* The number of interplays between FM and QP
                      at any one coarsening level. */

    /**** Fidducia-Mattheyes Options *****************************************/
    bool use_FM;              /* Flag governing the use of FM               */
    Int FM_search_depth;       /* The # of non-positive gain move to make    */
    Int FM_consider_count;     /* The # of heap entries to consider          */
    Int FM_max_num_refinements; /* Max # of times to run Fiduccia-Mattheyses  */

    /**** Quadratic Programming Options **************************************/
    bool use_QP_gradproj;         /* Flag governing the use of gradproj       */
    double gradproj_tolerance;   /* Convergence tol for projected gradient   */
    Int gradproj_iteration_limit; /* Max # of iterations for gradproj         */

    /** Final Partition Target Metrics ***************************************/
    double target_split;        /* The desired split ratio (default 50/50)  */
    double soft_split_tolerance; /* The allowable soft split tolerance.      */
                               /* Cuts within this tolerance are treated   */
                               /* equally.                                 */

    /* Constructor & Destructor */
    static EdgeCut_Options *create();
    ~EdgeCut_Options();
};

} // end namespace Mongoose

#endif
