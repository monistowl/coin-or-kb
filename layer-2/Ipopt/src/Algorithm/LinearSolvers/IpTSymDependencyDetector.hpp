// Copyright (C) 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2007-04-18

/**
 * @file IpTSymDependencyDetector.hpp
 * @brief Dependency detection using symmetric linear solver
 *
 * TSymDependencyDetector detects linearly dependent constraint rows
 * by using a TSymLinearSolver that provides degeneracy detection.
 *
 * Method:
 * Some symmetric linear solvers (e.g., MA57 via ProvidesDegeneracyDetection)
 * can identify dependent rows during factorization. This class
 * leverages that capability.
 *
 * Algorithm:
 * 1. Form symmetric matrix J*J^T (or equivalent structure)
 * 2. Attempt factorization with the TSymLinearSolver
 * 3. If solver detects singularity, query dependent row indices
 * 4. Return list of dependent rows in c_deps
 *
 * Requirements:
 * - The underlying linear solver must implement
 *   ProvidesDegeneracyDetection() returning true
 * - Must implement DetermineDependentRows() for the sparse format
 *
 * This is preferred over MA28-based detection when using a solver
 * that already provides this capability.
 *
 * @see IpTDependencyDetector.hpp for base interface
 * @see IpTSymLinearSolver.hpp for symmetric solver
 */

#ifndef __IPTSYMDEPENDENCYDETECTOR_HPP__
#define __IPTSYMDEPENDENCYDETECTOR_HPP__

#include "IpTDependencyDetector.hpp"
#include "IpTSymLinearSolver.hpp"

namespace Ipopt
{

/** Base class for all derived algorithms for detecting linearly
 *  dependent rows in the constraint Jacobian.
 */
class TSymDependencyDetector: public TDependencyDetector
{
public:
   /** @name Constructor/Destructor */
   ///@{
   TSymDependencyDetector(
      TSymLinearSolver& tsym_linear_solver);

   virtual ~TSymDependencyDetector()
   { }
   ///@}

   /** Has to be called to initialize and reset these objects. */
   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Method determining the number of linearly dependent rows in
    *  the matrix and the indices of those rows.
    *
    *  We assume that the
    *  matrix is available in "Triplet" format (MA28 format), and
    *  that the arrays given to this method can be modified
    *  internally, i.e., they are not used by the calling program
    *  anymore after this call.
    *
    *  @return false if there was a problem with the underlying linear solver
    */
   virtual bool DetermineDependentRows(
      Index             n_rows,
      Index             n_cols,
      Index             n_jac_nz,
      Number*           jac_c_vals,
      Index*            jac_c_iRow,
      Index*            jac_c_jCol,
      std::list<Index>& c_deps
   );

   /** This must be called to make the options for this class known */
   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

private:
   /**@name Default Compiler Generated Methods
    * (Hidden to avoid implicit creation/calling).
    * These methods are not implemented and
    * we do not want the compiler to implement
    * them for us, so we declare them private
    * and do not define them. This ensures that
    * they will not be implicitly created/called. */
   ///@{
   /** Default Constructor */
   TSymDependencyDetector();

   /** Copy Constructor */
   TSymDependencyDetector(
      const TSymDependencyDetector&
   );

   /** Default Assignment Operator */
   void operator=(
      const TSymDependencyDetector&
   );
   ///@}

   SmartPtr<const Journalist> jnlst_;

   SmartPtr<TSymLinearSolver> tsym_linear_solver_;
};

} // namespace Ipopt

#endif
