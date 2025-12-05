// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_vector_sanity.hpp
 * @brief Position vector validation utility
 *
 * @algorithm Index Validation: BCP_vec_sanity_check
 *
 * Validates position vectors used in delta operations:
 * - Positions must be strictly increasing (sorted, no duplicates)
 * - No negative indices
 * - All indices < maxsize
 *
 * Throws BCP_fatal_error on invalid input.
 * Used to catch programming errors in delta encoding early.
 *
 * @see BCP_vector_change.hpp for delta vector operations
 */
#ifndef _BCP_VECTOR_SANITY_H
#define _BCP_VECTOR_SANITY_H

// This file is fully docified.

#include "BCP_vector.hpp"

/** A helper function to test whether a set positions is sane for a vector.

    The set of positions consists of the entries in
    <code>[firstpos,lastpos)</code>. The length of the vector is
    <code>maxsize</code>. 

    The set of positions is defined to be sane if and only if the entries are
    in increasing order, there are no duplicate entries, no negative entries
    and the largest entry is smaller than <code>maxsize</code>.

    If the sanity check fails the function throws a 
    \URL[<code>BCP_fatal_error</code>]{BCP_fatal_error.html} exception.
*/
void BCP_vec_sanity_check(BCP_vec<int>::const_iterator firstpos,
			  BCP_vec<int>::const_iterator lastpos,
			  const int maxsize);

#endif
