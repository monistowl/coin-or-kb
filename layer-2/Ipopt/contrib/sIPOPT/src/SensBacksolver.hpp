// Copyright 2009, 2011 Hans Pirnay
// All Rights Reserved.
// This code is published under the Eclipse Public License.
/**
 * @file SensBacksolver.hpp
 * @brief sIPOPT backsolver interface for linear systems
 *
 * SensBacksolver: abstract interface for solving linear systems in sIPOPT.
 * Used for Schur complement right-hand side solutions. Implementations
 * leverage existing Ipopt linear solvers for efficient back-substitution.
 */
//
// Date   : 2009-05-14

#ifndef __ASASBACKSOLVER_HPP__
#define __ASASBACKSOLVER_HPP__

#include "IpAlgStrategy.hpp"
#include "IpIteratesVector.hpp"

namespace Ipopt
{

class SIPOPTLIB_EXPORT SensBacksolver: public AlgorithmStrategyObject
{

   /** This class is the interface to all backsolvers that may
    *  be used for the sIPOPT. */
public:
   SensBacksolver()
   { }

   virtual ~SensBacksolver()
   { }

   virtual bool Solve(
      SmartPtr<IteratesVector>       delta_lhs,
      SmartPtr<const IteratesVector> delta_rhs
   ) = 0;
};

}

#endif
