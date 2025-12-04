// Copyright (C) 2008 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2008-08-31

/**
 * @file IpInexactSearchDirCalc.hpp
 * @brief Search direction via normal-tangential decomposition
 *
 * InexactSearchDirCalculator computes the search direction using
 * iterative linear solvers by decomposing into normal and tangential
 * components, enabling inexact Newton methods.
 *
 * @algorithm Normal-Tangential Step Decomposition:
 *   ComputeSearchDirection():
 *   1. Compute normal step Δx_n via InexactNormalStepCalculator:
 *      - Solves: min ||Δx_n||² s.t. ||A·Δx_n + c|| ≤ κ·||c|| (feasibility).
 *   2. Compute tangential step Δx_t via InexactPDSolver:
 *      - Solves primal-dual system with modified RHS.
 *      - Δx_t ∈ null(A) approximately (tangent to constraints).
 *   3. Combine: Δx = Δx_n + Δx_t, store in InexactData.
 *   4. Check local infeasibility: ||A·Δx_n||₂ ≤ local_inf_Ac_tol.
 *
 * @math Decomposition strategy:
 *   Normal step: Δx_n = -A^†·c(x) (minimum norm solution toward feasibility).
 *   Tangential step: Δx_t = (I - A^†A)·d (projects optimality onto null(A)).
 *   Full step: Δx = Δx_n + Δx_t achieves both feasibility and optimality.
 *   Decomposition modes: ALWAYS, ADAPTIVE, SWITCH_ONCE (based on progress).
 *
 * @complexity Normal step: O(nnz·k_n) for iterative solve.
 *   Tangential step: O(nnz·k_t) for primal-dual solve.
 *   Total: O(nnz·(k_n + k_t)), typically k_n, k_t << n.
 *
 * @see IpInexactNormalStepCalc.hpp for normal step interface
 * @see IpInexactPDSolver.hpp for tangential step solver
 */

#ifndef __IPINEXACTSEARCHDIRCALC_HPP__
#define __IPINEXACTSEARCHDIRCALC_HPP__

#include "IpSearchDirCalculator.hpp"
#include "IpInexactCq.hpp"
#include "IpInexactNormalStepCalc.hpp"
#include "IpInexactPDSolver.hpp"

namespace Ipopt
{
/** Implementation of the search direction calculator that computes
 *  the search direction using iterative linear solvers.
 *
 *  Those steps do not necessarily satisfy the linearized KKT conditions
 *  with high accuracy.
 */
class InexactSearchDirCalculator: public SearchDirectionCalculator
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor */
   InexactSearchDirCalculator(
      SmartPtr<InexactNormalStepCalculator> normal_step_calculator,
      SmartPtr<InexactPDSolver>             inexact_pd_solver
   );

   /** Destructor */
   virtual ~InexactSearchDirCalculator();
   ///@}

   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Method for computing the search direction.
    *
    *  In this version,
    *  we compute a normal and a tangential component, which are
    *  stored in the InexactData object.  The overall step is still
    *  stored in the IpoptData object.
    */
   virtual bool ComputeSearchDirection();

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

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
   InexactSearchDirCalculator();

   /** Copy Constructor */
   InexactSearchDirCalculator(
      const InexactSearchDirCalculator&
   );

   /** Overloaded Assignment Operator */
   void operator=(
      const InexactSearchDirCalculator&
   );
   ///@}

   /** Method to easily access Inexact data */
   InexactData& InexData()
   {
      InexactData& inexact_data = static_cast<InexactData&>(IpData().AdditionalData());
      DBG_ASSERT(dynamic_cast<InexactData*>(&IpData().AdditionalData()));
      return inexact_data;
   }

   /** Method to easily access Inexact calculated quantities */
   InexactCq& InexCq()
   {
      InexactCq& inexact_cq = static_cast<InexactCq&>(IpCq().AdditionalCq());
      DBG_ASSERT(dynamic_cast<InexactCq*>(&IpCq().AdditionalCq()));
      return inexact_cq;
   }

   /** @name Algorithmic options */
   ///@{
   /** termination tolerance for local infeasibility */
   Number local_inf_Ac_tol_;
   ///@}

   /** @name Strategy objects */
   ///@{
   SmartPtr<InexactNormalStepCalculator> normal_step_calculator_;
   SmartPtr<InexactPDSolver> inexact_pd_solver_;
   ///@}

   /** enumeration for decomposition options */
   enum DecompositionTypeEnum
   {
      ALWAYS = 0,
      ADAPTIVE,
      SWITCH_ONCE
   };

   /** Type of decomposition */
   DecompositionTypeEnum decomposition_type_;
};

} // namespace Ipopt

#endif
