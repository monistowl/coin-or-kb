// Copyright (C) 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter     IBM    2007-03-01

/**
 * @file IpGenAugSystemSolver.hpp
 * @brief Augmented system solver using GenKKTSolverInterface
 *
 * GenAugSystemSolver adapts the AugSystemSolver interface to use
 * GenKKTSolverInterface, which provides a more generic linear solver
 * interface supporting iterative methods.
 *
 * This class:
 * - Extracts raw Number* arrays from Vector objects
 * - Passes Matrix objects directly from the NLP
 * - Manages caching to avoid redundant matrix updates
 *
 * MultiSolve() implementation:
 * 1. Check if augmented system matrices have changed (via tags)
 * 2. If changed, update solver_interface_ with new matrices
 * 3. Extract RHS vectors to raw arrays
 * 4. Call solver_interface_->Solve()
 * 5. Copy solutions back to Vector objects
 *
 * Tag-based caching tracks:
 * - W matrix and W_factor
 * - Diagonal matrices D_x, D_s, D_c, D_d
 * - Jacobians J_c, J_d
 * - Regularization deltas
 *
 * Inertia and quality:
 * - NumberOfNegEVals(): Query solver for eigenvalue count
 * - ProvidesInertia(): Check if solver supports this
 * - IncreaseQuality(): Request better pivoting/tolerance
 *
 * @algorithm Generic Augmented System Solver (Adapter Pattern):
 * Adapts AugSystemSolver interface to GenKKTSolverInterface:
 * 1. Check matrix change via tag comparison (O(1))
 * 2. If matrices changed:
 *    a. Extract diagonal values to Number* arrays
 *    b. Pass matrices to solver_interface_->InitializeStructure()
 *    c. Update internal tags
 * 3. For each RHS:
 *    a. Extract Vector data to Number* arrays
 *    b. Call solver_interface_->Solve()
 *    c. Copy solution back to Vector objects
 *
 * @math Tag-based caching:
 * Each matrix/vector has monotonic tag that changes on modification.
 * Comparison: current_tag != cached_tag → matrix changed.
 * Avoids redundant matrix assembly/factorization when data unchanged.
 *
 * @complexity Tag check: O(1). Matrix update: O(nnz).
 * Solve dominated by underlying solver: O(nnz·fill) sparse, O(n³) dense.
 *
 * @see IpAugSystemSolver.hpp for base interface
 * @see IpGenKKTSolverInterface.hpp for the solver interface
 */

#ifndef __IP_GENAUGSYSTEMSOLVER_HPP__
#define __IP_GENAUGSYSTEMSOLVER_HPP__

#include "IpAugSystemSolver.hpp"
#include "IpGenKKTSolverInterface.hpp"

namespace Ipopt
{

/** Solver for the augmented system using GenKKTSolverInterfaces.
 *
 *  This takes any Vector values out and provides Number*'s, but
 *  Matrices are provided as given from the NLP.
 */
class GenAugSystemSolver: public AugSystemSolver
{
public:
   /**@name Constructors/Destructors */
   ///@{
   /** Constructor using only a linear solver object */
   GenAugSystemSolver(
      GenKKTSolverInterface& SolverInterface
   );

   /** Destructor */
   virtual ~GenAugSystemSolver();
   ///@}

   /** overloaded from AlgorithmStrategyObject */
   bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** Set up the augmented system and solve it for a set of given
    *  right hand side - implementation for GenTMatrices and
    *  SymTMatrices.
    */
   virtual ESymSolverStatus MultiSolve(
      const SymMatrix*                      W,
      Number                                W_factor,
      const Vector*                         D_x,
      Number                                delta_x,
      const Vector*                         D_s,
      Number                                delta_s,
      const Matrix*                         J_c,
      const Vector*                         D_c,
      Number                                delta_c,
      const Matrix*                         J_d,
      const Vector*                         D_d,
      Number                                delta_d,
      std::vector<SmartPtr<const Vector> >& rhs_xV,
      std::vector<SmartPtr<const Vector> >& rhs_sV,
      std::vector<SmartPtr<const Vector> >& rhs_cV,
      std::vector<SmartPtr<const Vector> >& rhs_dV,
      std::vector<SmartPtr<Vector> >&       sol_xV,
      std::vector<SmartPtr<Vector> >&       sol_sV,
      std::vector<SmartPtr<Vector> >&       sol_cV,
      std::vector<SmartPtr<Vector> >&       sol_dV,
      bool                                  check_NegEVals,
      Index                                 numberOfNegEVals
   );

   /** Number of negative eigenvalues detected during last solve.
    *
    * This must not be called if the linear solver does
    * not compute this quantities (see ProvidesInertia).
    *
    * @return the number of negative eigenvalues of the most recent factorized matrix.
    */
   virtual Index NumberOfNegEVals() const;

   /** Query whether inertia is computed by linear solver.
    *
    * @return true, if linear solver provides inertia
    */
   virtual bool ProvidesInertia() const;

   /** Request to increase quality of solution for next solve.
    *
    *  Ask underlying linear solver to increase quality of solution for
    *  the next solve (e.g. increase pivot tolerance).
    *
    *  @return false, if this is not possible (e.g. maximal pivot tolerance
    *  already used.)
    */
   virtual bool IncreaseQuality();

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
   /** Default constructor. */
   GenAugSystemSolver();
   /** Copy Constructor */
   GenAugSystemSolver(
      const GenAugSystemSolver&
   );

   /** Default Assignment Operator */
   void operator=(
      const GenAugSystemSolver&
   );
   ///@}

   /** Check the internal tags and decide if the passed variables are
    *  different from what is in the augmented_system_
    */
   bool AugmentedSystemChanged(
      const SymMatrix* W,
      Number           W_factor,
      const Vector*    D_x,
      Number           delta_x,
      const Vector*    D_s,
      Number           delta_s,
      const Matrix&    J_c,
      const Vector*    D_c,
      Number           delta_c,
      const Matrix&    J_d,
      const Vector*    D_d,
      Number           delta_d
   );

   void UpdateTags(
      const SymMatrix* W,
      Number           W_factor,
      const Vector*    D_x,
      Number           delta_x,
      const Vector*    D_s,
      Number           delta_s,
      const Matrix&    J_c,
      const Vector*    D_c,
      Number           delta_c,
      const Matrix&    J_d,
      const Vector*    D_d,
      Number           delta_d
   );

   /** The linear solver object that is to be used to solve the
    *  linear systems.
    */
   SmartPtr<GenKKTSolverInterface> solver_interface_;

   /**@name Tags and values to track in order to decide whether the
    * matrix has to be updated compared to the most recent call of
    * the Set method.
    */
   ///@{
   /** Tag for W matrix.
    *
    *  If W has been given to Set as NULL, then this tag is set to 0
    */
   TaggedObject::Tag w_tag_;
   /** Most recent value of W_factor */
   Number w_factor_;
   /** Tag for D_x vector, representing the diagonal matrix D_x.
    *
    *  If D_x has been given to Set as NULL, then this tag is set to 0
    */
   TaggedObject::Tag d_x_tag_;
   /** Most recent value of delta_x from Set method */
   Number delta_x_;
   /** Tag for D_s vector, representing the diagonal matrix D_s.
    *
    *  If D_s has been given to Set as NULL, then this tag is set to 0
    */
   TaggedObject::Tag d_s_tag_;
   /** Most recent value of delta_s from Set method */
   Number delta_s_;
   /** Tag for J_c matrix.
    *
    *  If J_c has been given to Set as NULL, then this tag is set to 0
    */
   TaggedObject::Tag j_c_tag_;
   /** Tag for D_c vector, representing the diagonal matrix D_c.
    *
    *  If D_c has been given to Set as NULL, then this tag is set to 0
    */
   TaggedObject::Tag d_c_tag_;
   /** Most recent value of delta_c from Set method */
   Number delta_c_;
   /** Tag for J_d matrix.
    *
    *  If J_d has been given to Set as NULL, then this tag is set to 0
    */
   TaggedObject::Tag j_d_tag_;
   /** Tag for D_d vector, representing the diagonal matrix D_d.
    *
    *  If D_d has been given to Set as NULL, then this tag is set to 0
    */
   TaggedObject::Tag d_d_tag_;
   /** Most recent value of delta_d from Set method */
   Number delta_d_;
   ///@}

   /** @name Space for storing the diagonal matrices.
    *
    *  If the matrix hasn't changed, we can use it from the last call.
    */
   ///@{
   Number* dx_vals_copy_;
   Number* ds_vals_copy_;
   Number* dc_vals_copy_;
   Number* dd_vals_copy_;
   ///@}

   /** @name Algorithmic parameters */
   ///@{
   /** Flag indicating whether the TNLP with identical structure has
    *  already been solved before.
    */
   bool warm_start_same_structure_;
   ///@}
};

} // namespace Ipopt

#endif
