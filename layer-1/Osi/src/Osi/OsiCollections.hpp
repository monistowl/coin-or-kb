/**
 * @file OsiCollections.hpp
 * @brief STL container typedefs for Osi cut and data collections
 * Copyright (C) 2000, International Business Machines Corporation.
 * EPL-1.0 license.
 *
 * Standard typedefs: OsiVectorInt, OsiVectorDouble, OsiVectorColCutPtr,
 * OsiVectorRowCutPtr, OsiVectorCutPtr. Provides cleaner syntax for
 * frequently-used vector types throughout Osi code.
 */

// Copyright (C) 2000, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

#ifndef OsiCollections_H
#define OsiCollections_H

#include <vector>

//Forward declarations
class OsiColCut;
class OsiRowCut;
class OsiCut;

/* Collection Classes */

/**@name Typedefs for Standard Template Library collections of Osi Objects. */
//@{
/// Vector of int
typedef std::vector< int > OsiVectorInt;
/// Vector of double
typedef std::vector< double > OsiVectorDouble;
/// Vector of OsiColCut pointers
typedef std::vector< OsiColCut * > OsiVectorColCutPtr;
/// Vector of OsiRowCut pointers
typedef std::vector< OsiRowCut * > OsiVectorRowCutPtr;
/// Vector of OsiCut pointers
typedef std::vector< OsiCut * > OsiVectorCutPtr;
//@}

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
