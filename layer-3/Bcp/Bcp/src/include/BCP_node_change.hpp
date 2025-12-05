// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.

/**
 * @file BCP_node_change.hpp
 * @brief Complete node delta encoding for tree storage
 *
 * @algorithm Node Delta Encoding: Compact Tree Storage via Parent Diffs
 *
 * BCP_node_change aggregates all changes between parent and child nodes
 * for compact tree storage.
 *
 * **Components:**
 * - core_change: Changes to core var/cut bounds (BCP_problem_core_change)
 * - var_change: Changes to algorithmic variables (BCP_obj_set_change)
 * - cut_change: Changes to algorithmic cuts (BCP_obj_set_change)
 * - warmstart: LP warm start information
 *
 * **Purpose:**
 * Enables efficient tree storage by encoding only deltas between
 * parent and child nodes instead of full formulations. Critical for
 * scaling to large trees where each node may have thousands of vars/cuts.
 *
 * **Reconstruction:**
 * To reconstruct a node's formulation, start from root (or checkpoint)
 * and apply node_change deltas along the path to the target node.
 *
 * **Serialization:**
 * pack()/unpack() methods handle inter-process transfer, using
 * BCP_user_pack for user-defined warmstart serialization.
 *
 * @see BCP_problem_core.hpp for core formulation
 * @see BCP_obj_change.hpp for object set deltas
 * @see BCP_tm_node.hpp for TM node representation
 */

#ifndef _BCP_NODE_H
#define _BCP_NODE_H

#include "CoinSmartPtr.hpp"
#include "BCP_problem_core.hpp"
#include "BCP_obj_change.hpp"
#include "BCP_indexed_pricing.hpp"

//#############################################################################

class BCP_warmstart;
class BCP_buffer;
class BCP_user_pack;

//#############################################################################

class BCP_node_change : public Coin::ReferencedObject {
private:
    BCP_node_change(const BCP_node_change&);
    BCP_node_change& operator=(const BCP_node_change&);
public:
    BCP_problem_core_change core_change;
    BCP_obj_set_change var_change;
    BCP_obj_set_change cut_change;
    BCP_warmstart* warmstart;
public:
    BCP_node_change();
    BCP_node_change(BCP_user_pack* packer, const bool def, BCP_buffer& buf);
    ~BCP_node_change();

    void pack(BCP_user_pack* packer, const bool def, BCP_buffer& buf) const;
    void unpack(BCP_user_pack* packer, const bool def, BCP_buffer& buf);
};

#endif
