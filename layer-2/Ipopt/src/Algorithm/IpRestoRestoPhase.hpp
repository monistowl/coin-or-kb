// Copyright (C) 2004, 2006 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Carl Laird, Andreas Waechter     IBM    2005-02-11

/**
 * @file IpRestoRestoPhase.hpp
 * @brief Recursive restoration for separable n,p variable initialization
 *
 * RestoRestorationPhase provides a specialized "restoration within
 * restoration" procedure for the MinC_1NrmRestorationPhase. It computes
 * optimal values for the slack variables (n_c, p_c, n_d, p_d) by
 * treating them as separable from x and s.
 *
 * @algorithm Separable Slack Optimization:
 *   Given current x (fixed), find optimal n, p for restoration problem:
 *   1. Compute constraint residuals: r_c = c(x), r_d = d(x) - s.
 *   2. For each component i, solve: v² + 2aᵢ·v - bᵢ = 0
 *      where aᵢ, bᵢ derived from residual and complementarity target.
 *   3. Extract n, p from solution: v = p - n, use sign of residual.
 *   4. Ensures n ≥ 0, p ≥ 0 with n·p close to target complementarity.
 *
 * @math Quadratic subproblem:
 *   For fixed x: min_{n,p≥0} ρ(||n||₁ + ||p||₁) + barrier(n,p)
 *   s.t. c(x) + n - p = 0.
 *   Separable → each component independent quadratic in v = p - n.
 *   Closed-form: v = -a + √(a² + b) (positive root).
 *
 * @complexity O(m) for m constraints, no linear solve needed.
 *   Much cheaper than full restoration iteration for slack initialization.
 *
 * The restoration feasibility problem has structure:
 *   min ||p + n||_1  s.t.  c(x) + n - p = 0
 *
 * For fixed x, optimal n and p can be computed by solving a quadratic
 * equation v^2 + 2a*v - b = 0 element-wise, where:
 * - a relates to constraint values
 * - b relates to complementarity conditions
 *
 * This avoids full nested optimization when only n,p need updating.
 *
 * @see IpRestoMinC_1Nrm.hpp for main restoration phase
 * @see IpRestoPhase.hpp for base restoration interface
 */

#ifndef __IPRESTORESTOPHASE_HPP__
#define __IPRESTORESTOPHASE_HPP__

#include "IpRestoPhase.hpp"
#include "IpIpoptAlg.hpp"
#include "IpEqMultCalculator.hpp"

namespace Ipopt
{

/** Recursive Restoration Phase for the MinC_1NrmRestorationPhase.
 *
 *  This procedure chooses the n and p variables in the
 *  MinC_1NrmRestorationPhase problem formulation by treating the
 *  problem as separable (assuming that the x and s variables are
 *  fixed).
 */
class RestoRestorationPhase: public RestorationPhase
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Default Constructor. */
   RestoRestorationPhase();

   /** Destructor */
   virtual ~RestoRestorationPhase();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

protected:
   virtual bool PerformRestoration();

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    *
    * These methods are not implemented
    * and we do not want the compiler to implement them for us, so we
    * declare them private and do not define them. This ensures that
    * they will not be implicitly created/called.
    */
   ///@{
   /** Copy Constructor */
   RestoRestorationPhase(
      const RestoRestorationPhase&
   );

   /** Default Assignment Operator */
   void operator=(
      const RestoRestorationPhase&
   );
   ///@}

   /** @name Auxiliary methods */
   ///@{
   /** Method for solving the quadratic vector equation v^2 + 2a*v - b = 0 */
   void solve_quadratic(
      const Vector& a,
      const Vector& b,
      Vector&       v
   );
   ///@}
};

} // namespace Ipopt

#endif
