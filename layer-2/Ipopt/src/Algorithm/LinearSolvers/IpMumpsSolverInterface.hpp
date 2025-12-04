// Copyright (C) 2006, 2007 Damien Hocking, KBC Advanced Technologies
// All Rights Reserved.
// This code is published under the Eclipse Public License.
/**
 * @file IpMumpsSolverInterface.hpp
 * @brief Interface to MUMPS parallel sparse direct solver
 *
 * MumpsSolverInterface wraps MUMPS (MUltifrontal Massively Parallel
 * sparse direct Solver) for Ipopt. Supports MPI parallelism, hybrid
 * MPI+OpenMP mode, and out-of-core factorization for large problems.
 * Default open-source solver when HSL unavailable.
 */
//
// Authors: Damien Hocking                 KBC    2006-03-20
//        (included his original contribution into Ipopt package on 2006-03-25)
//          Andreas Waechter               IBM    2006-03-25
//           (minor changes and corrections)
//          Scott Turnberg                 CMU    2006-05-12
//           (major revision)
//           (incorporated by AW on 2006-11-11 into Ipopt package)

/**
 * @file IpMumpsSolverInterface.hpp
 * @brief Interface to MUMPS parallel sparse direct solver
 *
 * MumpsSolverInterface wraps MUMPS (MUltifrontal Massively Parallel
 * sparse direct Solver), a freely available solver supporting MPI
 * parallelism for distributed memory systems.
 *
 * @algorithm Distributed-Memory Multifrontal LDL^T Factorization:
 *   MUMPS computes A = P·L·D·L^T·P^T using multifrontal method with:
 *   - MPI parallelism: distributes frontal matrices across processes
 *   - Hybrid mode: MPI between nodes + OpenMP within nodes
 *   - Out-of-core: stores factors on disk for very large problems
 *   Supports both symmetric indefinite and positive definite modes.
 *
 * @math Distributed factorization strategy:
 *   - Master process coordinates analysis and distribution
 *   - Worker processes hold portions of L and D factors
 *   - Frontal matrices assembled from child contributions via MPI
 *   - Parallel triangular solves with pipelined communication
 *   Degeneracy detection: identifies nearly-zero pivots for constraint deletion.
 *
 * @complexity O(n·f²/p) with p MPI processes. Communication: O(f²·log(p)).
 *   Scales to hundreds of cores for large problems (n > 100,000).
 *
 * @ref Amestoy, Duff, L'Excellent & Koster (2001). "A Fully Asynchronous
 *      Multifrontal Solver Using Distributed Dynamic Scheduling".
 *      SIAM J. Matrix Anal. Appl. 23(1):15-41.
 *
 * MUMPS characteristics:
 * - Parallel: MPI-based (also sequential mode)
 * - Input format: Triplet_Format (lower triangular)
 * - Provides inertia
 * - Provides degeneracy detection (ProvidesDegeneracyDetection)
 * - Open source (CeCILL-C license)
 *
 * Job codes in MUMPS:
 * - Job 1: Analysis (symbolic factorization)
 * - Job 2: Numerical factorization
 * - Job 3: Solve phase
 *
 * Key parameters:
 * - mumps_permuting_scaling_: Permutation and scaling method
 * - mumps_pivot_order_: Pivot ordering (AMD, METIS, etc.)
 * - mumps_scaling_: Additional scaling options
 * - mumps_dep_tol_: Threshold for dependency detection
 *
 * Often the default linear solver for Ipopt when HSL is unavailable.
 *
 * @see IpMa57TSolverInterface.hpp for HSL alternative
 * @see IpMa97SolverInterface.hpp for parallel HSL solver
 */

#ifndef __IPMUMPSSOLVERINTERFACE_HPP__
#define __IPMUMPSSOLVERINTERFACE_HPP__

#include "IpSparseSymLinearSolverInterface.hpp"

namespace Ipopt
{

/** Interface to the linear solver Mumps, derived from
 *  SparseSymLinearSolverInterface.
 */
class MumpsSolverInterface: public SparseSymLinearSolverInterface
{
public:
   /** @name Constructor/Destructor */
   ///@{
   /** Constructor */
   MumpsSolverInterface();

   /** Destructor */
   virtual ~MumpsSolverInterface();
   ///@}

   bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   );

   /** @name Methods for requesting solution of the linear system. */
   ///@{
   virtual ESymSolverStatus InitializeStructure(
      Index        dim,
      Index        nonzeros,
      const Index* airn,
      const Index* ajcn
   );

   virtual Number* GetValuesArrayPtr();

   virtual ESymSolverStatus MultiSolve(
      bool         new_matrix,
      const Index* airn,
      const Index* ajcn,
      Index        nrhs,
      Number*      rhs_vals,
      bool         check_NegEVals,
      Index        numberOfNegEVals
   );

   virtual Index NumberOfNegEVals() const;
   ///@}

   //* @name Options of Linear solver */
   ///@{
   virtual bool IncreaseQuality();

   virtual bool ProvidesInertia() const
   {
      return true;
   }

   EMatrixFormat MatrixFormat() const
   {
      return Triplet_Format;
   }
   ///@}

   static void RegisterOptions(
      SmartPtr<RegisteredOptions> roptions
   );

   /// give name of MUMPS with version info
   /// @since 3.14.0
   static std::string GetName();

   virtual bool ProvidesDegeneracyDetection() const;

   virtual ESymSolverStatus DetermineDependentRows(
      const Index*      ia,
      const Index*      ja,
      std::list<Index>& c_deps
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
   /** Copy Constructor */
   MumpsSolverInterface(
      const MumpsSolverInterface&
   );

   /** Default Assignment Operator */
   void operator=(
      const MumpsSolverInterface&
   );
   ///@}

   /** @name Information about the matrix */
   ///@{
   /** Primary MUMP data structure */
   void* mumps_ptr_;
   ///@}

   /** @name Information about most recent factorization/solve */
   ///@{
   /** Number of negative eigenvalues */
   Index negevals_;
   ///@}

   /** @name Initialization flags */
   ///@{
   /** Flag indicating if internal data is initialized.
    *  For initialization, this object needs to have seen a matrix.
    */
   bool initialized_;
   /** Flag indicating if the matrix has to be refactorized because
    *  the pivot tolerance has been changed.
    */
   bool pivtol_changed_;
   /** Flag that is true if we just requested the values of the
    *  matrix again (SYMSOLVER_CALL_AGAIN) and have to factorize
    *  again.
    */
   bool refactorize_;
   ///@}

   /** @name Solver specific data/options */
   ///@{
   /** Pivot tolerance */
   Number pivtol_;

   /** Maximal pivot tolerance */
   Number pivtolmax_;

   /** Percent increase in memory */
   Index mem_percent_;

   /** Permutation and scaling method in MUMPS */
   Index mumps_permuting_scaling_;

   /** Pivot order in MUMPS. */
   Index mumps_pivot_order_;

   /** Scaling in MUMPS */
   Index mumps_scaling_;

   /** Threshold in MUMPS to state that a constraint is linearly dependent */
   Number mumps_dep_tol_;

   /** Flag indicating whether the TNLP with identical structure has
    *  already been solved before.
    */
   bool warm_start_same_structure_;
   ///@}

   /** Flag indicating if symbolic factorization has already been called */
   bool have_symbolic_factorization_;

   /** @name Internal functions */
   ///@{
   /** Call MUMPS (job=1) to perform symbolic manipulations, and reserve
    *  memory.
    */
   ESymSolverStatus SymbolicFactorization();

   /** Call MUMPS (job=2) to factorize the Matrix.
    *  It is assumed that the first nonzeros_ element of a_ contain the values
    *  of the matrix to be factorized.
    */
   ESymSolverStatus Factorization(
      bool  check_NegEVals,
      Index numberOfNegEVals
   );

   /** Call MUMPS (job=3) to do the solve. */
   ESymSolverStatus Solve(
      Index   nrhs,
      Number* rhs_vals
   );
   ///@}
};

} // namespace Ipopt
#endif
