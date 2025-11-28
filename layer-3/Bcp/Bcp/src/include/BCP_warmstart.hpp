// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.

/**
 * @file BCP_warmstart.hpp
 * @brief LP warm start information for BCP Branch-Cut-Price
 *
 * BCP_warmstart is the abstract base for storing LP warm start data.
 * Enables efficient LP resolves when moving between tree nodes.
 *
 * **Storage modes (BCP_storage_t):**
 * - Explicit: Full warm start data
 * - WrtParent: Changes relative to parent node
 * - WrtCore: Changes relative to core formulation
 *
 * **Key methods:**
 * - convert_to_CoinWarmStart(): Get Osi-compatible warm start
 * - storage(): Query how data is stored
 * - update(): Apply incremental changes
 * - as_change(): Compute delta from previous warm start
 * - clone(): Deep copy
 * - storage_size(): Memory footprint for storage decisions
 *
 * **Node transitions:**
 * When LP dives from parent to child, warm start may be stored
 * as delta to save space. When backtracking, explicit form needed.
 *
 * Implementations: BCP_warmstart_basis (simplex basis),
 * BCP_warmstart_primaldual (interior point)
 *
 * @see BCP_lp.hpp for LP process using warm starts
 * @see CoinWarmStart for underlying OSI interface
 */

#ifndef _BCP_WARMSTART_H
#define _BCP_WARMSTART_H

// This file is fully docified.

#include "BCP_error.hpp"
#include "BCP_enum.hpp"
#include "BCP_vector.hpp"

//#############################################################################

class CoinWarmStart;

//#############################################################################

/** Warmstarting information for the LP solver.
    A realization of the warmstarting information must done in a way that
    allows to keep the information either in an explicit way or as a change
    relative to another warmstarting information.
*/

class BCP_warmstart {
public:
   /** The destructor is pure virtual. (There are no data members here.) */
   virtual ~BCP_warmstart() {}

   /** Return an OsiWarmStart object that can be fed to the LP engine */
   virtual CoinWarmStart* convert_to_CoinWarmStart() const = 0;

   /** Return how the warmstarting info is stored. */
   virtual BCP_storage_t storage() const = 0;

   /** Update the current data with the one in the argument.
       If the argument is of explicit storage then just replace the current
       data. If it is relative and the current data is explicit then perform
       the update. Otherwise throw an exception. */
   virtual void update(const BCP_warmstart* const change) = 0;

   /** Return a pointer to a warmstart info describing the currently stored
       data as a change with respect to that stored in <code>old_ws</code>.
       However, if the currently stored data is shorter to store than the
       change, then this method can return a copy of the current data!
       The current data must be explicitly stored and <code>old_ws</code> must
       be either explicit or can contain no data. Otherwise an exception must
       be thrown.
       @param old_ws the old warmstart info
       @param del_vars the indices of the variables that are deleted from the
              formulation <code>old_ws</code> was created for
       @param del_cuts same for the cuts
       @param petol primal zero tolerance
       @param detol dual zero tolerance
   */
   virtual BCP_warmstart* as_change(const BCP_warmstart* const old_ws,
				    const BCP_vec<int>& del_vars,
				    const BCP_vec<int>& del_cuts,
				    const double petol,
				    const double detol) const = 0;

   /** Make a replica of the current warmstart information. */
   virtual BCP_warmstart* clone() const = 0;

   /** Create a warmstart info describing that no change should be done. This
       is really the task of a constructor, but BCP does not know the type of
       warmstart the user will use, so it will invoke this method for a
       warmstart that was created by the user. Tricky, isn't it? */
   virtual BCP_warmstart* empty_wrt_this() const = 0;

   /** Return how much memory it'll take to pack this warmstart info. It is
       used when comparing which sort of storage is smaller. */
   virtual int storage_size() const = 0;
};

#endif
