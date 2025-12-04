/**
 * @file BonCbcLpStrategy.hpp
 * @brief Cbc strategy for configuring cut generators in OA
 * Copyright (C) Carnegie Mellon University 2006. All Rights Reserved.
 * This code is published under the Eclipse Public License.
 *
 * CbcStrategyChooseCuts: Strategy class extending CbcStrategyDefault
 * to configure cut generators (Gomory, MIR, etc.) for use in Outer
 * Approximation LP subproblems. Sets generator frequencies based on
 * BabSetupBase configuration.
 *
 * Authors: Pierre Bonami, Carnegie Mellon University
 * Date: March 15, 2006
 *
 * @see CbcStrategyDefault for base strategy
 * @see BabSetupBase for cut generator configuration
 */

#ifndef CbcOaStrategy_HPP
#define CbcOaStrategy_HPP

#include "CbcStrategy.hpp"
#include <string>
#include "BonBabSetupBase.hpp"
namespace Bonmin
{
  /** A class to setup default strategy for Cbc specifying which cut generators to use.*/
  class BONMINLIB_EXPORT CbcStrategyChooseCuts : public CbcStrategyDefault {
     public:
     /** Default constructor.*/
     CbcStrategyChooseCuts();
     /** Constructor with a setup. */
     CbcStrategyChooseCuts(BabSetupBase &s, const std::string & prefix);
     /** Copy constructor.*/
     CbcStrategyChooseCuts(const CbcStrategyChooseCuts &other);
     /** Virtual copy constructor.*/
     CbcStrategy * clone() const{
       return new CbcStrategyChooseCuts(*this);
     }
     /** Setup strategy.*/
     void setup(BabSetupBase &s, const std::string &prefix);
    
     /// Setup cut generators
     virtual void setupCutGenerators(CbcModel & model);
  
     private:
    /** Generators frequencies.*/
    int gen_freqs_[6];
       /** Flag to say which cut generators to use.*/
       int genFlag_;
  };
}
#endif
