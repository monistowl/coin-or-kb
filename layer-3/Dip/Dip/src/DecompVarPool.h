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
 * @file DecompVarPool.h
 * @brief Pool of generated columns (DecompVar) for column generation
 *
 * DecompVarPool manages columns waiting to enter the master problem.
 * Inherits from std::vector<DecompWaitingCol> for storage.
 *
 * @algorithm Column Pool Management in Branch-and-Price:
 * Efficiently manage generated columns across pricing iterations.
 *
 * COLUMN LIFECYCLE:
 *   1. Subproblem oracle generates column s with rc < 0
 *   2. Column enters pool as DecompWaitingCol
 *   3. Pool sorted by reduced cost (most negative first)
 *   4. Duplicate/parallel columns filtered
 *   5. Best columns added to restricted master
 *   6. Column may persist in pool for future iterations
 *
 * COLUMN SELECTION CRITERIA:
 *   Primary: Reduced cost r̄(s) = c's - π'(As) - μ_block
 *   Filter 1: Duplicates (hash-based detection)
 *   Filter 2: Near-parallel columns (cosine similarity > threshold)
 *
 * @algorithm Duplicate and Parallel Column Detection:
 * Avoid redundant columns that slow convergence.
 *
 *   isDuplicate(): Hash comparison O(1) per column
 *     Two columns equivalent if m_strHash matches
 *
 *   isParallel(): Cosine similarity check
 *     cos(s1, s2) = (s1·s2)/(||s1||·||s2||)
 *     If cos > maxCosine threshold, columns too similar
 *
 * @math Why filter parallel columns:
 *   Near-parallel columns provide marginal improvement
 *   Adding both increases master LP size without benefit
 *   Better to diversify column set for faster convergence
 *
 * @algorithm Column Re-expansion (reExpand):
 * When master constraints change, column coefficients may be stale.
 *
 *   m_colsAreValid flag tracks validity
 *   When cuts added: setColsAreValid(false)
 *   Before pricing: if !colsAreValid, call reExpand()
 *   reExpand(): Recompute As for each stored s
 *
 * @complexity
 *   isDuplicate: O(pool_size) hash comparisons
 *   isParallel: O(pool_size × column_nnz) for dot products
 *   setReducedCosts: O(pool_size × num_duals)
 *   reExpand: O(pool_size × nnz(A))
 *
 * @see DecompVar.h for column representation
 * @see DecompWaitingCol.h for pool entry wrapper
 * @see DecompAlgoPC.h for column generation driver
 */

#ifndef DECOMP_VAR_POOL_INCLUDE
#define DECOMP_VAR_POOL_INCLUDE

#include "Decomp.h"
#include "DecompWaitingCol.h"

class DecompConstraintSet;

// --------------------------------------------------------------------- //
class is_less_thanD { //member of class instead??
public:
   bool operator()( const DecompWaitingCol& x,
                    const DecompWaitingCol& y) {
      return x.getVarPtr()->getReducedCost() < y.getVarPtr()->getReducedCost();
   }
};

// --------------------------------------------------------------------- //
class DecompVarPool : public std::vector<DecompWaitingCol> {
private:
   DecompVarPool(const DecompVarPool&);
   DecompVarPool& operator=(const DecompVarPool&);

private:
   static const char* classTag;
   bool m_colsAreValid;

public:
   const inline bool colsAreValid() const {
      return m_colsAreValid;
   }
   inline void setColsAreValid(bool colsAreValid) {
      m_colsAreValid = colsAreValid;
   }

   void print(double infinity, std::ostream* os = &std::cout) const;  //THINK: virtual??
   void reExpand(const DecompConstraintSet& modelCore,
                 const double                tolZero);
   bool isDuplicate(const DecompWaitingCol& wcol);
   bool isDuplicate(const DecompVarList&     vars,
                    const DecompWaitingCol& wcol);
   bool isParallel(const DecompVarList&     vars,
                   const DecompWaitingCol& wcol,
                   const double             maxCosine);
   bool setReducedCosts(const double*             u,
                        const DecompStatus          stat,
                        DecompVarPool::iterator   first,
                        DecompVarPool::iterator   last);
   bool setReducedCosts(const double*             u,
                        const DecompStatus          stat) {
      return setReducedCosts(u, stat, begin(), end());
   }

public:
   DecompVarPool() :
      m_colsAreValid(true) {}

   ~DecompVarPool() {
      //---
      //--- delete any memory that is left in the waiting cols
      //---
      std::vector<DecompWaitingCol>::iterator vi;

      for (vi = begin(); vi != end(); vi++) {
         (*vi).deleteVar();
         (*vi).deleteCol();
      }
   }

};

#endif
