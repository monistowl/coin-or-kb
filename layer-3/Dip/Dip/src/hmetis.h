/**
 * @file hmetis.h
 * @brief C declarations for hMETIS hypergraph partitioning library
 *
 * Declares external hMETIS functions for k-way and recursive bisection
 * hypergraph partitioning. Used by DIP for decomposing constraint
 * matrices into block structures for Dantzig-Wolfe decomposition.
 *
 * @note Requires linking against hMETIS library
 * @see UtilGraphLib.h for graph-based problem utilities
 */
void  HMETIS_PartKway(int nvtxs, int nhedges, int* vwgts, int* eptr,
                      int* eind, int* hewgts, int nparts, int ubfactor,
                      int* options, int* part, int* edgecut);

void  HMETIS_PartRecursive(int nvtxs, int nhedges, int* vwgts, int* eptr,
                           int* eind, int* hewgts, int nparts, int ubfactor,
                           int* options, int* part, int* edgecut);
