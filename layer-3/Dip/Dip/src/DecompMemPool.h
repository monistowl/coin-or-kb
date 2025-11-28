//===========================================================================//
// This file is part of the DIP Solver Framework.                            //
//                                                                           //
// DIP is distributed under the Eclipse Public License as part of the        //
// COIN-OR repository (http://www.coin-or.org).                              //
//                                                                           //
// Authors: Matthew Galati, SAS Institute Inc. (matthew.galati@sas.com)      //
//          Ted Ralphs, Lehigh University (ted@lehigh.edu)                   //
//          Jiadong Wang, Lehigh University (jiw408@lehigh.edu)              //
//                                                                           //
// Copyright (C) 2002-2019, Lehigh University, Matthew Galati, Ted Ralphs    //
// All Rights Reserved.                                                      //
//===========================================================================//

/**
 * @file DecompMemPool.h
 * @brief Pre-allocated memory arrays for performance
 *
 * DecompMemPool provides reusable scratch arrays to avoid repeated
 * allocations during the inner loops of the algorithm.
 *
 * **Pre-allocated Arrays:**
 * - dblArrNCoreCols: Double array sized for core columns
 * - dblArrNCoreRows: Double array sized for core rows
 *
 * **Usage:**
 * Rather than allocating temporary arrays in hot paths like
 * reduced cost calculation or constraint evaluation, use these
 * pre-allocated buffers for better cache performance.
 *
 * **Memory Management:**
 * - allocateMemory(): Size arrays based on problem dimensions
 * - Destructor frees all allocated memory
 * - Single allocation at algorithm start
 *
 * @see DecompAlgo.h where memory pool is used
 */

//===========================================================================//
#ifndef DecompMemPool_h_
#define DecompMemPool_h_

#include "CoinError.hpp"

// --------------------------------------------------------------------- //
class DecompMemPool {
public:
   double* dblArrNCoreCols;
   double* dblArrNCoreRows;

public:
   void allocateMemory(const int nCoreCols,
                       const int nCoreRows) {
      if (nCoreCols > 0) {
         dblArrNCoreCols = new double[nCoreCols];
         CoinAssertHint(dblArrNCoreCols, "Error: Out of Memory");
      }

      if (nCoreRows > 0) {
         dblArrNCoreRows = new double[nCoreRows];
         CoinAssertHint(dblArrNCoreRows, "Error: Out of Memory");
      }
   }

public:
   DecompMemPool() :
      dblArrNCoreCols(0),
      dblArrNCoreRows(0) {
   }
   ~DecompMemPool() {
      UTIL_DELARR(dblArrNCoreCols);
      UTIL_DELARR(dblArrNCoreRows);
   }
};

#endif
