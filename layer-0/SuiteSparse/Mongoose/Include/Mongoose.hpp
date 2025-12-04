/**
 * @file Mongoose.hpp
 * @brief Main public API for Mongoose graph partitioning library
 * Copyright (C) 2017-2018, Scott P. Kolodziej, Nuri S. Yeralan,
 * Timothy A. Davis, William W. Hager. GPL-3.0-only license.
 *
 * Mongoose: High-quality graph partitioning via multilevel coarsening
 * with Fiduccia-Mattheyses and quadratic programming refinement.
 * Public interface includes Graph, EdgeCut, EdgeCut_Options classes
 * and read_graph/edge_cut functions for partitioning workflows.
 *
 * @algorithm Multilevel Graph Partitioning (Mongoose):
 * Partitions graph into two balanced sets minimizing edge cut:
 * 1. COARSEN: Repeatedly match vertices (HEM) and contract
 * 2. INITIAL CUT: Partition coarsest graph (QP or random)
 * 3. UNCOARSEN: Project partition up, refine at each level
 * 4. REFINE: Waterdance interleaving FM and QP improvement
 *
 * @math Edge cut minimization with balance constraint:
 * $$\min \sum_{(i,j)\in E} w_{ij} \cdot |x_i - x_j|$$
 * subject to: $$|W_0 - W_1| \leq \epsilon \cdot W$$
 * where x_i ∈ {0,1} is partition assignment, W_k = ∑_{x_i=k} w_i.
 *
 * @complexity O(|E| log |V|) for multilevel algorithm.
 * Coarsening: O(|E|) per level, O(log |V|) levels.
 * FM refinement: O(|E|) per pass.
 *
 * @ref Davis et al. (2020). "Algorithm 1003: Mongoose, a graph coarsening
 *   and partitioning library". ACM Trans. Math. Software 46(1):7.
 * @ref Karypis & Kumar (1998). "A fast and high quality multilevel scheme
 *   for partitioning irregular graphs". SIAM J. Sci. Comput. 20(1):359-392.
 *
 * @see Mongoose_EdgeCut.hpp for partition result structure
 * @see Mongoose_EdgeCutOptions.hpp for algorithm configuration
 */

/* ========================================================================== */
/* === Include/Mongoose.hpp ================================================= */
/* ========================================================================== */

/* -----------------------------------------------------------------------------
 * Mongoose Graph Partitioning Library, Copyright (C) 2017-2018,
 * Scott P. Kolodziej, Nuri S. Yeralan, Timothy A. Davis, William W. Hager
 * Mongoose is licensed under Version 3 of the GNU General Public License.
 * Mongoose is also available under other licenses; contact authors for details.
 * SPDX-License-Identifier: GPL-3.0-only
 * -------------------------------------------------------------------------- */

// #pragma once
#ifndef MONGOOSE_HPP
#define MONGOOSE_HPP

#include "SuiteSparse_config.h"
#include <string>

// Configuration information from CMake
#define Mongoose_VERSION_MAJOR 3
#define Mongoose_VERSION_MINOR 3
#define Mongoose_VERSION_PATCH 6
#define Mongoose_DATE "Nov 1, 2025"

#define Mongoose__VERSION SUITESPARSE__VERCODE(3,3,6)
#if !defined (SUITESPARSE__VERSION) || \
    (SUITESPARSE__VERSION < SUITESPARSE__VERCODE(7,12,0))
#error "Mongoose 3.3.6 requires SuiteSparse_config 7.12.0 or later"
#endif

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

typedef struct cs_sparse /* matrix in compressed-column or triplet form */
{
    Int nzmax; /* maximum number of entries */
    Int m;     /* number of rows */
    Int n;     /* number of columns */
    Int *p;    /* column pointers (size n+1) or col indices (size nzmax) */
    Int *i;    /* row indices, size nzmax */
    double *x; /* numerical values, size nzmax */
    Int nz;    /* # of entries in triplet matrix, -1 for compressed-col */
} cs;

/* Enumerations */
enum MatchingStrategy
{
    Random,
    HEM,
    HEMSR,
    HEMSRdeg
};

enum InitialEdgeCutType
{
    InitialEdgeCut_QP,
    InitialEdgeCut_Random,
    InitialEdgeCut_NaturalOrder
};

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
    bool use_FM;              /* Flag governing the use of FM             */
    Int FM_search_depth;       /* The # of non-positive gain move to make  */
    Int FM_consider_count;     /* The # of heap entries to consider        */
    Int FM_max_num_refinements; /* Max # of times to run FidduciaMattheyes  */

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

class Graph
{
public:
    /** Graph Data ***********************************************************/
    Int n;     /** # vertices                      */
    Int nz;    /** # edges                         */
    Int *p;    /** Column pointers                 */
    Int *i;    /** Row indices                     */
    double *x; /** Edge weight                     */
    double *w; /** Node weight                     */

    /* Constructors & Destructor */
    static Graph *create(const Int _n, const Int _nz, Int *_p = NULL,
                         Int *_i = NULL, double *_x = NULL, double *_w = NULL);
    static Graph *create(cs *matrix);
    ~Graph();

private:
    Graph();

    /** Memory Management Flags ***********************************************/
    bool shallow_p;
    bool shallow_i;
    bool shallow_x;
    bool shallow_w;
};

/**
 * Generate a Graph from a Matrix Market file.
 *
 * Generate a Graph class instance from a Matrix Market file. The matrix
 * contained in the file must be sparse, real, and square. If the matrix
 * is not symmetric, it will be made symmetric with (A+A')/2. If the matrix has
 * more than one connected component, the largest will be found and the rest
 * discarded. If a diagonal is present, it will be removed.
 *
 * @param filename the filename or path to the Matrix Market File.
 */
Graph *read_graph(const std::string &filename);

/**
 * Generate a Graph from a Matrix Market file.
 *
 * Generate a Graph class instance from a Matrix Market file. The matrix
 * contained in the file must be sparse, real, and square. If the matrix
 * is not symmetric, it will be made symmetric with (A+A')/2. If the matrix has
 * more than one connected component, the largest will be found and the rest
 * discarded. If a diagonal is present, it will be removed.
 *
 * @param filename the filename or path to the Matrix Market File.
 */
Graph *read_graph(const char *filename);

struct EdgeCut
{
    bool *partition;     /** T/F denoting partition side     */
    Int n;               /** # vertices                      */

    /** Cut Cost Metrics *****************************************************/
    double cut_cost;    /** Sum of edge weights in cut set    */
    Int cut_size;       /** Number of edges in cut set        */
    double w0;          /** Sum of partition 0 vertex weights */
    double w1;          /** Sum of partition 1 vertex weights */
    double imbalance;   /** Degree to which the partitioning
                            is imbalanced, and this is
                            computed as (0.5 - W0/W).         */

    // desctructor (no constructor)
    ~EdgeCut();
};

EdgeCut *edge_cut(const Graph *);
EdgeCut *edge_cut(const Graph *, const EdgeCut_Options *);

/* Version information */
int major_version();
int minor_version();
int patch_version();
std::string mongoose_version();

} // end namespace Mongoose

#endif
