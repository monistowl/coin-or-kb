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
// Copyright (C) 2002-2019, Lehigh University, Matthew Galati, and Ted Ralphs//
// All Rights Reserved.                                                      //
//===========================================================================//

/**
 * @file DecompAlgoCGL.h
 * @brief Interface to CGL (COIN-OR Cut Generation Library)
 *
 * DecompAlgoCGL wraps CGL cut generators for use in DIP algorithms.
 * Provides automatic generation of standard MIP cuts.
 *
 * **Available CGL Generators:**
 * - CglClique: Clique cuts from conflict graph
 * - CglOddHole: Odd hole inequalities
 * - CglFlowCover: Flow cover cuts
 * - CglKnapsackCover: Knapsack cover cuts
 * - CglMixedIntegerRounding2: MIR cuts
 * - CglGomory: Gomory mixed-integer cuts
 *
 * **Usage:**
 * - Created by DecompAlgo during initialization
 * - Called during PHASE_CUT to generate cuts
 * - Returns cuts via DecompCutOsi wrapper
 *
 * **Configuration:**
 * - Generators enabled/disabled via DecompParam
 * - Per-generator parameters can be set
 * - Different strategies for PC vs C algorithms
 *
 * **Integration:**
 * CGL generates cuts in x-space. For Price-and-Cut, these are
 * reformulated to lambda-space before adding to master.
 *
 * @see DecompCutPool.h for cut storage
 * @see DecompParam.h for CGL configuration
 * @see CglCutGenerator (CGL) for base generator interface
 */

//===========================================================================//
#ifndef DecompAlgoCGL_h_
#define DecompAlgoCGL_h_

//===========================================================================//
/**
 * \class DecompAlgoCGL
 * \brief An interface to CGL cut generator library.
 *
 */
//===========================================================================//

//===========================================================================//
#include "Decomp.h"

//===========================================================================//
//#include "CglProbing.hpp" //TODO
#include "CglClique.hpp"
#include "CglGomory.hpp"
#include "CglOddHole.hpp"
#include "CglFlowCover.hpp"
#include "CglKnapsackCover.hpp"
#include "CglMixedIntegerRounding2.hpp"

//===========================================================================//
class DecompAlgoCGL {

   //----------------------------------------------------------------------//
   /**
    * @name Data.
    * @{
    */
   //----------------------------------------------------------------------//
private:
   int                        m_logLevel;
   std::ostream*                   m_logStream;

   CglClique*                 m_genClique;
   CglOddHole*                m_genOddHole;
   CglFlowCover*              m_genFlowCover;
   CglKnapsackCover*          m_genKnapCover;
   CglMixedIntegerRounding2* m_genMixIntRound;
   CglGomory*                 m_genGomory;

   DecompAlgoType             m_algo;
   /**
    * @}
    */


public:
   //-----------------------------------------------------------------------//
   /**
    * @name Helper functions.
    * @{
    */
   //-----------------------------------------------------------------------//
   int initGenerators(const int doClique,
                      const int doOddHole,
                      const int doFlowCover,
                      const int doKnapCover,
                      const int doMixIntRound,
                      const int doGomory);
   int generateCuts(OsiSolverInterface* cutGenSI,
                    OsiSolverInterface* masterSI,
                    double*              xhat,
                    std::vector<int>&         integerVars,
                    DecompCutList&       newCuts);



   /**
    * @}
    */

public:
   //-----------------------------------------------------------------------//
   /**
    * @name Set/get methods.
    * @{
    */
   //-----------------------------------------------------------------------//
   void setLogLevel(const int logLevel) {
      m_logLevel = logLevel;
   }
   void setLogStream(std::ostream* logStream) {
      m_logStream = logStream;
   }
   /**
    * @}
    */

   //-----------------------------------------------------------------------//
   /**
    * @name Constructors and destructor.
    * @{
    */
   //-----------------------------------------------------------------------//
public:
   /**
    * Default constructors.
    */
   DecompAlgoCGL(int              logLevel  = 0,
                 DecompAlgoType   algo      = CUT,
                 std::ostream*         logStream = &std::cout):
      m_logLevel      (logLevel),
      m_logStream     (logStream),
      m_genClique     (0),
      m_genOddHole    (0),
      m_genFlowCover  (0),
      m_genKnapCover  (0),
      m_genMixIntRound(0),
      m_genGomory     (0),
      m_algo          (algo) {
   }

   /**
    * Destructor.
    */
   ~DecompAlgoCGL() {
      UTIL_DELPTR(m_genClique);
      UTIL_DELPTR(m_genOddHole);
      UTIL_DELPTR(m_genFlowCover);
      UTIL_DELPTR(m_genKnapCover);
      UTIL_DELPTR(m_genMixIntRound);
      UTIL_DELPTR(m_genGomory);
   }
   /**
    * @}
    */
};

#endif
