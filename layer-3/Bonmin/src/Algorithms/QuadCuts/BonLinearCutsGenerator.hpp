/**
 * @file BonLinearCutsGenerator.hpp
 * @brief Composite cut generator managing multiple linear cut generators
 * Copyright (C) International Business Machines Corporation 2007.
 * All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * LinearCutsGenerator: Aggregates multiple CglCutGenerator instances
 * with frequency and identification. Provides unified interface for
 * generating cuts from various sources (GMI, MIR, etc.) at specified
 * frequencies during branch-and-bound.
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

