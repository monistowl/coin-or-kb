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
 * @file DecompAlgoC.h
 * @brief Cutting Plane Method algorithm (no column generation)
 *
 * DecompAlgoC implements classic cutting plane method:
 * - Solve LP relaxation
 * - Find violated cuts
 * - Add cuts and resolve
 * - Repeat until integer or no cuts found
 *
 * @algorithm Cutting Plane Method (CPM):
 * Iteratively tighten LP relaxation with valid inequalities.
 *
 * ALGORITHM:
 *   1. Solve LP relaxation: min c'x s.t. Ax ≥ b
 *   2. if x* is integer-feasible: STOP (optimal)
 *   3. Search for violated cut: a'x ≥ β with a'x* < β
 *   4. if cut found: add to LP, goto 1
 *   5. else: BRANCH on fractional variable
 *
 * MASTER PROBLEM STRUCTURE:
 *   Original variables x (not Dantzig-Wolfe lambdas)
 *   Rows grow as cuts are added
 *   Columns remain fixed
 *
 * @math Convergence for polyhedra:
 *   If conv(X) = {x : Ax ≥ b} (LP = IP), CPM finds optimum.
 *   In general, CPM finds optimum over intersection of
 *   LP relaxation with all generated cuts.
 *
 * WHEN TO USE:
 * - LP relaxation is naturally strong
 * - No obvious block structure for decomposition
 * - Want simplicity over Dantzig-Wolfe
 *
 * @complexity Per iteration: O(LP_solve) + O(cut_generation)
 * Iterations bounded by number of extreme points cut off.
 *
 * @ref Kelley (1960). "The Cutting-Plane Method for Solving Convex Programs".
 *
 * @see DecompAlgo.h for base class
 * @see DecompAlgoPC.h for full Price-and-Cut
 * @see DecompAlgoCGL.h for CGL cut integration
 */

//===========================================================================//
#ifndef DecompAlgoC_h_
#define DecompAlgoC_h_

//===========================================================================//
/**
 * \class DecompAlgoC
 * \brief Class for DECOMP algorithm Cutting Plane Method.
 *
 */
//===========================================================================//

//===========================================================================//
#include "Decomp.h"
#include "DecompAlgo.h"

//===========================================================================//
class DecompAlgoC : public DecompAlgo {
private:

   //----------------------------------------------------------------------//
   /**
    * @name Data.
    * @{
    */
   //----------------------------------------------------------------------//
   /**
    * Store the name of the class (for logging/debugging) - "who am I?"
    */
   std::string m_classTag;
   /**
    * @}
    */

   //-----------------------------------------------------------------------//
   /**
    * @name Derived from pure virtual functions of DecompAlgo.
    * @{
    */
   //-----------------------------------------------------------------------//
   /**
    * Create the master problem (all algorithms must define this function).
    */
   void createMasterProblem(DecompVarList& initVars);

   /**
    * Compose solution in x-space from current space.
    *  - PC: this recomposes x from lambda
    *  - C : this just copies over LP solution
    */
   void recomposeSolution(const double* solution,
                          double*        rsolution);

   /**
    * @}
    */

   //-----------------------------------------------------------------------//
   /**
    * @name Derived from virtual functions of DecompAlgo
    * @{
    */
   //-----------------------------------------------------------------------//

   /**
    * Calculate the current objective LB, update the best, and
    * store in history.
    */
   bool updateObjBound(const double mostNegRC = -DecompBigNum);

   void phaseInit(DecompPhase& phase) {
      if (getNodeIndex() == 0) {
         phase = PHASE_CUT;
      }
   }
   void phaseDone();//chance to run DC

   /**
    * Update of the phase for process loop.
    */
   void phaseUpdate(DecompPhase&   phase,
                    DecompStatus& status);
   /**
    * Generate initial variables for master problem (PC/DC/RC).
    *   - in CPM, this does nothing
    */
   int generateInitVars(DecompVarList& initVars) {
      return 0;
   }

   void setMasterBounds(const double* lbs,
                        const double* ubs);
   void setSubProbBounds(const double* lbs,
                         const double* ubs) {};

public:
   virtual DecompSolverResult*
   solveDirect(const DecompSolution* startSol  = NULL);


   /**
    * @}
    */


   //-----------------------------------------------------------------------//
   /**
    * @name Constructors and destructor.
    * @{
    */
   //-----------------------------------------------------------------------//
private:
   /**
    * Disable copy constructors.
    */
   DecompAlgoC(const DecompAlgoC&);
   DecompAlgoC& operator=(const DecompAlgoC&);

public:
   /**
    * Default constructors.
    */
   DecompAlgoC(DecompApp*             app,
               UtilParameters&        utilParam):
   DecompAlgo(CUT, app, utilParam, false),
      m_classTag("D-ALGOC")
   {
      initSetup();
   }

   /**
    * Destructor.
    */
   ~DecompAlgoC() {}
   /**
    * @}
    */
};

#endif
