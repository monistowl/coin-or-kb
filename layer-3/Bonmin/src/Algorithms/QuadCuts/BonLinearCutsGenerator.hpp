/**
 * @file BonLinearCutsGenerator.hpp
 * @brief Composite cut generator managing multiple linear cut generators
 * Copyright (C) International Business Machines Corporation 2007.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * @algorithm Cut Generation Orchestration:
 * Frequency-based dispatch of multiple cut generators.
 *
 * COMPOSITE PATTERN:
 *   Each CuttingMethod bundles:
 *   - cgl: Pointer to CglCutGenerator (GMI, MIR, lift-and-project, etc.)
 *   - frequency: How often to call (every N nodes, 0=disabled)
 *   - id: String identifier for logging/debugging
 *   - atSolution: Generate when integer solution found
 *   - normal: Generate during normal branching
 *
 * DISPATCH LOGIC in generateCuts():
 *   For each method in methods_:
 *     if (atSolution && have_solution) OR (normal && at_frequency):
 *       method.cgl->generateCuts(solver, cuts, info)
 *
 * @algorithm Frequency Control:
 * Balance cut generation cost vs. bound improvement.
 *
 *   frequency = 1: Every node (expensive, tight bounds)
 *   frequency = 10: Every 10 nodes (cheaper, weaker bounds)
 *   frequency = 0: Disabled
 *   frequency = -1: Root node only
 *
 * Common frequency settings:
 *   GMI cuts: frequent (usually 1-5)
 *   MIR cuts: moderate (5-10)
 *   Lift-and-project: rare (10-100, expensive)
 *
 * @complexity O(sum over generators of per-generator complexity)
 * Total work bounded by sum of individual generator complexities
 * at their respective frequencies.
 *
 * Authors: Pierre Bonami, IBM
 * Date: October 6, 2007
 *
 * @see CglCutGenerator for individual cut generator interface
 * @see BabSetupBase for cut generator configuration
 */

#ifndef BonLinearCutsGenerator_H
#define BonLinearCutsGenerator_H

#include "CglCutGenerator.hpp"
#include "CoinSmartPtr.hpp"
#include "BonOuterApprox.hpp"
#include "BonBonminSetup.hpp"
#include <list>

namespace Bonmin {
class BONMINLIB_EXPORT LinearCutsGenerator : public CglCutGenerator {
   public:
    /** Type for cut generation method with its frequency and string identification. */
    struct CuttingMethod : public Coin::ReferencedObject 
    {
      int frequency;
      std::string id;
      CglCutGenerator * cgl;
      bool atSolution;
      bool normal;
      CuttingMethod():
          atSolution(false),
          normal(true)
      {}

      CuttingMethod(const CuttingMethod & other):
          frequency(other.frequency),
          id(other.id),
          cgl(other.cgl),
          atSolution(other.atSolution),
          normal(other.normal)
      {}
    };
   LinearCutsGenerator():
     CglCutGenerator(),
     methods_(){
   }


   LinearCutsGenerator(const LinearCutsGenerator & other):
    CglCutGenerator(other),
     methods_(other.methods_){
   }

   CglCutGenerator * clone() const {
     return new LinearCutsGenerator(*this);
   }

   virtual ~LinearCutsGenerator(){
   }

   bool needsOptimalBasis() { return false;}

   void initialize(BabSetupBase& s);

   void generateCuts(const OsiSolverInterface &solver, OsiCuts &cs,
		     const CglTreeInfo info = CglTreeInfo());

   private:
     std::list<Coin::SmartPtr<CuttingMethod> > methods_; 
};

}/* Ends Bonmin namespace.*/

#endif

