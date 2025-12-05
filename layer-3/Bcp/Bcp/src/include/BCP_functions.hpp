// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
/**
 * @file BCP_functions.hpp
 * @brief Warmstart serialization utilities
 *
 * @algorithm Warmstart Pack/Unpack: Polymorphic Serialization
 *
 * Functions for serializing BCP_warmstart objects:
 *
 * - BCP_pack_warmstart(): Writes warmstart type tag + data to buffer
 * - BCP_unpack_warmstart(): Reads type tag, creates correct subclass
 *
 * Handles polymorphism: packs type indicator so unpack creates
 * the correct BCP_warmstart subclass (basis, dual, primaldual).
 *
 * @see BCP_warmstart.hpp for base class
 * @see BCP_buffer.hpp for serialization buffer
 */

#ifndef _BCP_FUNCTIONS_H_
#define _BCP_FUNCTIONS_H_

class BCP_warmstart;
class BCP_buffer;

void
BCP_pack_warmstart(const BCP_warmstart* ws, BCP_buffer& buf);

BCP_warmstart*
BCP_unpack_warmstart(BCP_buffer& buf);

#endif
