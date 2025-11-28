// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter              IBM    2004-09-24

/**
 * @file IpIterateInitializer.hpp
 * @brief Strategy interface for computing initial iterates
 *
 * IterateInitializer is the abstract base for strategies that
 * compute the starting point (x, s, y_c, y_d, z_L, z_U, v_L, v_U)
 * for the interior point algorithm.
 *
 * Initialization tasks:
 * - Project x into bounds (push away from bounds by slack_bound_push)
 * - Initialize slack variables s from d(x)
 * - Compute initial dual estimates (y_c, y_d) via least squares
 * - Initialize bound multipliers (z, v) from complementarity
 *
 * Implementations:
 * - DefaultIterateInitializer: Standard cold-start initialization
 * - WarmStartIterateInitializer: Uses provided starting point
 *
 * @see IpDefaultIterateInitializer.hpp for standard initialization
 * @see IpWarmStartIterateInitializer.hpp for warm starts
 */

#ifndef __IPITERATEINITIALIZER_HPP__
#define __IPITERATEINITIALIZER_HPP__

#include "IpAlgStrategy.hpp"
#include "IpIpoptNLP.hpp"
#include "IpIpoptData.hpp"
#include "IpIpoptCalculatedQuantities.hpp"

namespace Ipopt
{

/** Base class for all methods for initializing the iterates. */
class IPOPTLIB_EXPORT IterateInitializer: public AlgorithmStrategyObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor */
   IterateInitializer()
   { }

   /** Default destructor */
   virtual ~IterateInitializer()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

   /** Compute the initial iterates and set the into the curr field
    *  of the ip_data object. */
   virtual bool SetInitialIterates() = 0;

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    *
    * These methods are not implemented and
    * we do not want the compiler to implement
    * them for us, so we declare them private
    * and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Copy Constructor */
   IterateInitializer(
      const IterateInitializer&
   );

   /** Default Assignment Operator */
   void operator=(
      const IterateInitializer&
   );
   ///@}

};

} // namespace Ipopt

#endif
