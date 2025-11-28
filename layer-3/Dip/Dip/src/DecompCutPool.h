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
 * @file DecompCutPool.h
 * @brief Pool of generated cuts (DecompCut) for cut management
 *
 * DecompCutPool manages cuts waiting to enter the master problem.
 * Inherits from std::vector<DecompWaitingRow> for storage.
 *
 * **Key Functions:**
 * - reExpand(): Regenerate row coefficients when columns change
 * - createRowReform(): Transform x-space cut to lambda-space
 * - setViolations(): Calculate cut violations vs current solution
 *
 * **Cut Selection:**
 * - is_greater_thanD comparator sorts by violation
 * - Most violated cuts enter master first
 * - Duplicate cuts filtered via hash
 *
 * **Reformulation:**
 * Cuts in x-space must be reformulated to lambda-space for
 * Dantzig-Wolfe master: a'x >= b becomes a'(sum_s s*lambda_s) >= b
 * createRowReform() handles this transformation.
 *
 * **Validity Flag:**
 * - m_rowsAreValid: Track if cuts need re-expansion
 * - Set false when column set changes
 * - reExpand() regenerates coefficients
 *
 * @see DecompCut.h for cut representation
 * @see DecompWaitingRow.h for pool entry wrapper
 * @see DecompAlgoCGL.h for CGL cut generators
 */

#ifndef DECOMP_CUT_POOL_INCLUDE
#define DECOMP_CUT_POOL_INCLUDE

#include "DecompWaitingRow.h"

#include <functional>

class DecompConstraintSet;

// --------------------------------------------------------------------- //
//TODO: switch to distance
class is_greater_thanD { //member of class instead??
public:
   //TODO: design, waitingcol, rc is member of var, not waiting col,
   //but for waitingrow, distance is member of wr, not of cut - why?
   bool operator()( const DecompWaitingRow& x,
                    const DecompWaitingRow& y) {
      return x.getViolation() > y.getViolation();
   }
};

// --------------------------------------------------------------------- //
class DecompCutPool : public std::vector<DecompWaitingRow> {
private:
   DecompCutPool(const DecompCutPool&);
   DecompCutPool& operator=(const DecompCutPool&);

private:
   static const char* classTag;
   bool m_rowsAreValid;

public:
   const inline bool rowsAreValid() const {
      return m_rowsAreValid;
   }
   inline void setRowsAreValid(bool rowsAreValid) {
      m_rowsAreValid = rowsAreValid;
   }

   void print(std::ostream* os = &std::cout) const;  //THINK: virtual??
   void reExpand(const DecompVarList& vars,
                 const int             n_coreCols,
                 const int             n_artCols);

   CoinPackedVector* createRowReform(const int                n_coreCols,
                                     //const int                n_artCols,
                                     const CoinPackedVector* row,
                                     const DecompVarList&     vars);

   //THINK
   //bool isDuplicate(const DecompWaitingRow & wcol);

   bool calcViolations(const double*             x,
                       DecompCutPool::iterator   first,
                       DecompCutPool::iterator   last);
   bool calcViolations(const double*             x) {
      return calcViolations(x, begin(), end());
   }

public:
   DecompCutPool() :
      m_rowsAreValid(true) {}

   ~DecompCutPool() {
      //---
      //--- delete any memory that is left in the waiting rows
      //---
      std::vector<DecompWaitingRow>::iterator vi;

      for (vi = begin(); vi != end(); vi++) {
         (*vi).deleteCut();
         (*vi).deleteRow();
         (*vi).deleteRowReform();
      }
   }

};

#endif
