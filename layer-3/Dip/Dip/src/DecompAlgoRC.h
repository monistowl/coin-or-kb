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
 * @file DecompAlgoRC.h
 * @brief Relax-and-Cut algorithm (Lagrangian relaxation with cuts)
 *
 * DecompAlgoRC implements Lagrangian relaxation:
 * - Dualize complicating constraints with multipliers u
 * - Solve Lagrangian subproblem: min (c - u'A'')x s.t. A'x >= b'
 * - Update multipliers via subgradient optimization
 * - Add cuts to improve bounds
 *
 * @algorithm Lagrangian Relaxation with Subgradient Optimization:
 * Dualize complicating constraints to decompose the problem.
 *
 * PROBLEM STRUCTURE:
 *   Original: min c'x s.t. A'x ≥ b' (easy), A''x ≥ b'' (complicating)
 *
 *   Lagrangian: L(u) = min c'x - u'(A''x - b'')  s.t. A'x ≥ b'
 *                    = min (c - u'A'')x + u'b''  s.t. A'x ≥ b'
 *
 *   Lagrangian Dual: max_u L(u)  (u ≥ 0 for ≥ constraints)
 *
 * SUBGRADIENT OPTIMIZATION:
 *   Given x_k solving L(u_k):
 *     g_k = b'' - A''x_k  (subgradient of -L at u_k)
 *     u_{k+1} = max(0, u_k + α_k · g_k)
 *
 *   Step size rule (Held-Karp):
 *     α_k = λ_k · (UB - L(u_k)) / ||g_k||²
 *     λ_k ∈ (0, 2], typically start at 2, halve when stalled
 *
 * @math Weak duality: L(u) ≤ z* for all u ≥ 0
 * Strong duality (linear case): max_u L(u) = LP relaxation value
 * Integrality gap: z* - max_u L(u) (may be positive for IP)
 *
 * @algorithm Relax-and-Cut Enhancement:
 * Add cuts to tighten Lagrangian bound.
 *
 *   During subgradient iterations:
 *     1. Solve Lagrangian subproblem → x_k
 *     2. Check for violated cuts at x_k
 *     3. Add cuts to subproblem (not dualized)
 *     4. Continue until convergence or cut limit
 *
 * @complexity Per iteration: O(subproblem) + O(subgradient update)
 * Convergence: O(1/ε²) iterations for ε-optimal multipliers
 *
 * @ref Held & Karp (1970,1971). "The Traveling Salesman Problem and
 *   Minimum Spanning Trees". Operations Research.
 *
 * @see DecompAlgo.h for base class
 * @see DecompAlgoPC.h for LP-based alternative
 */

//===========================================================================//
#ifndef DecompAlgoRC_h_
#define DecompAlgoRC_h_

/** \todo Next: DecompAlgoVC - use Vol? or write from scratch? */
//===========================================================================//
#include "DecompAlgo.h"

//===========================================================================//
class DecompAlgoRC : public DecompAlgo {

   //----------------------------------------------------------------------//
   /**
    * @name Data.
    * @{
    */
   //----------------------------------------------------------------------//
private:
   /**
    * Store the name of the class (for logging/debugging) - "who am I?"
    */
   const std::string m_classTag;

private:
   std::vector<double>   m_u;   //dual vector
   double*          m_rc;  //reduced cost

   double           m_UB;
   double           m_LB;

   int              m_cntSameLB;
   int              m_iter;
   double           m_step;
   bool             m_zeroSub;

   DecompVar        m_shatVar;
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
   //not pure
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
   DecompStatus solutionUpdate(const DecompPhase phase,
                               const int         maxInnerIter,
                               const int         maxOuterIter);
   int addCutsFromPool();
   int generateVars(DecompVarList&     newVars,
                    double&            mostNegReducedCost);
   bool updateObjBound(const double mostNegRC = -DecompBigNum);

   /**
    * Run the initial phase for processing node.
    */
   DecompPhase phaseInit();
   /**
    * Run the done phase for processing node.
    */
   void phaseDone();


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
   DecompAlgoRC(const DecompAlgoRC&);
   DecompAlgoRC& operator=(const DecompAlgoRC&);

public:
   /**
    * Default constructors.
    */
   DecompAlgoRC(DecompApp*             app,
                UtilParameters&        utilParam):
      DecompAlgo(RELAX_AND_CUT, app, utilParam),
      m_classTag("D-ALGORC"),
      m_u        (),
      m_rc       (NULL),
      m_UB       (m_infinity),
      m_LB       (-m_infinity),
      m_cntSameLB(0),
      m_iter     (0),
      m_step     (2.0), //(0, 2] param?
      m_zeroSub  (false),
      m_shatVar  ()
   {
   }

   /**
    * Destructor.
    */
   ~DecompAlgoRC() {
      UTIL_DELARR(m_rc);
   }
   /**
    * @}
    */
   /**
    * @}
    */


public:
   bool isDone();
   //name - change to getDual?
   const double* getRowPrice() {
      return &m_u[0];
   }
   //user needs to do?
   //STOP
   void setInitObjUB(const double objUB) {
      m_UB = objUB;
   }


};
#endif
