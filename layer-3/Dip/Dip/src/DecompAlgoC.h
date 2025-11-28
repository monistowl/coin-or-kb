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
 * **When to Use:**
 * - Problems where LP relaxation is strong
 * - No natural block structure for decomposition
 * - Simpler than PC when pricing isn't needed
 *
 * **Algorithm Flow:**
 * 1. Solve initial LP relaxation
 * 2. Start in PHASE_CUT (no pricing phases)
 * 3. Generate cuts via CGL or user methods
 * 4. Re-solve LP with new cuts
 * 5. Branch if no cuts found and not integer
 *
 * **Key Differences from DecompAlgoPC:**
 * - No pricing/column generation
 * - No Phase 1/Phase 2 distinction
 * - Master problem contains original variables (not lambdas)
 * - Simpler master structure, faster per-iteration
 *
 * **Cut Generation:**
 * Uses same cut pool and CGL integration as PC variant.
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
