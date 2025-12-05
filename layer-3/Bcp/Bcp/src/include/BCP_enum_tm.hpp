// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_enum_tm.hpp
 * @brief Tree Manager enumerations for BCP
 *
 * @algorithm TM Enums: Search Strategy and Node Dispatch
 *
 * **BCP_tree_search_method:**
 * Search order for tree exploration:
 * - BestFirstSearch: Best bound first (minimize gap)
 * - BreadthFirstSearch: Level-by-level
 * - DepthFirstSearch: Dive to leaves (finds solutions fast)
 * - PreferredFirstSearch: User-defined comparison
 *
 * **BCP_node_start_result:**
 * Outcome of attempting to dispatch a node:
 * - NoNode: No nodes available
 * - Error: Dispatch failed
 * - OK: Node successfully sent to LP
 *
 * @see BCP_tm.hpp for Tree Manager
 */
#ifndef _BCP_ENUM_TM_H
#define _BCP_ENUM_TM_H

//-----------------------------------------------------------------------------

enum BCP_tree_search_method {
  BCP_BestFirstSearch,
  BCP_BreadthFirstSearch,
  BCP_DepthFirstSearch,
  BCP_PreferredFirstSearch
};

//-----------------------------------------------------------------------------

/** This enumerative constant describes ... */

enum BCP_node_start_result{
   /** */
   BCP_NodeStart_NoNode,
   /** */
   BCP_NodeStart_Error,
   /** */
   BCP_NodeStart_OK
};

#endif
