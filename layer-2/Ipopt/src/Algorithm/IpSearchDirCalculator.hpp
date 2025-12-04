// Copyright (C) 2005, 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2005-10-13

/**
 * @file IpSearchDirCalculator.hpp
 * @brief Strategy interface for computing the Newton search direction
 *
 * SearchDirectionCalculator is the strategy interface for computing
 * the search direction at each IPM iteration. The computed direction
 * is stored in IpData().delta() (an IteratesVector).
 *
 * @algorithm Newton Search Direction Computation:
 *   Given current iterate w = (x, s, y_c, y_d, z_L, z_U, v_L, v_U):
 *   1. Form KKT system with current W (Hessian), J_c, J_d (Jacobians).
 *   2. Compute RHS from gradient, constraint residuals, complementarity.
 *   3. Solve KKT system: K·Δw = -r (via PDSystemSolver).
 *   4. Store Δw in IpData().delta() for line search.
 *   For predictor-corrector: compute affine direction (μ=0), then corrected.
 *
 * @math Newton direction satisfies linearized KKT conditions:
 *   ∇²L·Δx + A^T·Δy + Δz = -∇L (stationarity)
 *   A·Δx = -c(x) (feasibility)
 *   X·Δz + Z·Δx = σμe - XZe (complementarity)
 *   where σ ∈ (0,1) is centering parameter, μ is barrier parameter.
 *
 * @complexity O(n²) to O(n³) per iteration depending on KKT structure.
 *   Dominated by linear system solve (see PDSystemSolver, AugSystemSolver).
 *
 * @see IpPDSearchDirCalc.hpp for the standard implementation
 * @see IpPDSystemSolver.hpp for the linear system solver
 * @see IpIpoptAlg.hpp for where ComputeSearchDirection() is called
 */

#ifndef __IPSEARCHDIRCALCULATOR_HPP__
#define __IPSEARCHDIRCALCULATOR_HPP__

#include "IpAlgStrategy.hpp"

namespace Ipopt
{

/** Base class for computing the search direction for the line
 *  search.
 */
class IPOPTLIB_EXPORT SearchDirectionCalculator: public AlgorithmStrategyObject
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor */
   SearchDirectionCalculator()
   { }

   /** Destructor */
   virtual ~SearchDirectionCalculator()
   { }
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

   /** Pure virtual method for computing the search direction.
    *
    *  The computed direction is stored in IpData().delta().
    */
   virtual bool ComputeSearchDirection() = 0;

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
   /** Default Constructor */
   //    SearchDirectionCalculator();

   /** Copy Constructor */
   SearchDirectionCalculator(
      const SearchDirectionCalculator&
   );

   /** Default Assignment Operator */
   void operator=(
      const SearchDirectionCalculator&
   );
   ///@}

};

} // namespace Ipopt

#endif
