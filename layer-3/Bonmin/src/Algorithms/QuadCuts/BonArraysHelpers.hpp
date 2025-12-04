/**
 * @file BonArraysHelpers.hpp
 * @brief Array resize and copy utilities for Bonmin
 * Copyright (C) International Business Machines Corporation 2007.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * Template functions for resizing arrays while preserving content:
 * - resizeAndCopyArray: Resize and copy up to min(old,new) elements
 * - resizeAndCopyArray with capacity: Only reallocate if needed
 *
 * Authors: Pierre Bonami, IBM
 * Date: October 6, 2007
 *
 * @see TMat for primary user of these utilities
 */

#include "CoinHelperFunctions.hpp"
#ifndef BonArraysHelpers_H
#define BonArraysHelpers_H

namespace Bonmin {
template <class X> void
resizeAndCopyArray(X *& array, unsigned int oldSize, unsigned int newSize){
 if(newSize == 0){
   if(oldSize > 0){
     delete [] array;
     array = NULL;
   }
   return;
 }
 X * buffy = new X[newSize];
 if(oldSize > 0){
   if(oldSize < newSize)
     CoinCopyN(array, oldSize, buffy);
   else
     CoinCopyN(array, newSize, buffy);
   delete [] array;
 }
 array = buffy;
}

template <class X> void
resizeAndCopyArray(X *& array, unsigned int oldSize, unsigned int newSize,
                   unsigned int& capacity){
 if(newSize > capacity){
   X * buffy = new X[newSize];
   if(oldSize > 0){
     CoinCopyN(array, oldSize, buffy);
     delete [] array;
    }
   array = buffy;
  }
  else {
    newSize = oldSize;
  }
}
}// Ends Bonmin namespace
#endif

