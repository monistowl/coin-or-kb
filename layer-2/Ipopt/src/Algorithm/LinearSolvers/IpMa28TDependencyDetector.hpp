// Copyright (C) 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2007-04-17

/**
 * @file IpMa28TDependencyDetector.hpp
 * @brief Dependency detector using HSL MA28 unsymmetric solver
 *
 * Ma28TDependencyDetector uses the unsymmetric sparse solver MA28
 * to detect linearly dependent rows in the constraint Jacobian.
 * Unlike the symmetric solvers, MA28 handles general rectangular
 * matrices, making it suitable for analyzing the constraint Jacobian
 * directly.
 *
 * The detection works by attempting LU factorization with threshold
 * pivoting. When a pivot falls below tolerance (ma28_pivtol_), the
 * corresponding row is flagged as linearly dependent.
 *
 * Input format: Triplet (row, col, val) for general matrices
 *
 * Used by Ipopt's constraint degeneracy detection mechanism.
 *
 * @algorithm MA28 Threshold Pivoting Dependency Detection:
 * Direct LU factorization approach for rectangular matrices:
 * 1. Factor J = P·L·U·Q (with row/column permutations P, Q)
 * 2. Use threshold pivoting: accept pivot if |u_ii| ≥ tol·max_row
 * 3. Rows with |u_ii| < ma28_pivtol_ flagged as dependent
 * 4. Return list of numerically rank-deficient rows
 *
 * @math Sparse LU factorization with threshold pivoting:
 * Given J ∈ ℝ^{m×n}, compute P·J·Q = L·U where:
 * - L: unit lower triangular (m×min(m,n))
 * - U: upper triangular (min(m,n)×n)
 *
 * Row i is dependent if during elimination:
 * $$|u_{ii}| < \text{pivtol} \cdot \max_k |a_{ik}^{(i-1)}|$$
 * where a^{(i-1)} denotes the matrix after i-1 elimination steps.
 *
 * @complexity O(nnz + fill-in) for sparse LU.
 * Fill-in can be O(n²) worst case, typically O(nnz·log(n)).
 *
 * @ref Duff (1977). "MA28 - A set of Fortran subroutines for sparse
 *   unsymmetric linear equations". AERE Harwell Report R 8730.
 *
 * @see IpTDependencyDetector.hpp for base interface
 * @see IpTSymDependencyDetector.hpp for symmetric solver approach
 */

#ifndef __IPMA28TDEPENDENCYDETECTOR_HPP__
#define __IPMA28TDEPENDENCYDETECTOR_HPP__

#include "IpTDependencyDetector.hpp"

namespace Ipopt
{

class Ma28TDependencyDetector: public TDependencyDetector
{
public:
   /** @name Constructor/Destructor */
   ///@{
   Ma28TDependencyDetector();

   virtual ~Ma28TDependencyDetector()
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
   /** Copy Constructor */
   Ma28TDependencyDetector(
      const Ma28TDependencyDetector&
   );

   /** Default Assignment Operator */
   void operator=(
      const Ma28TDependencyDetector&
   );
   ///@}

   SmartPtr<const Journalist> jnlst_;

   /** @name Algorithmic parameters */
   ///@{
   /** Pivot tolerance for MA28 */
   Number ma28_pivtol_;
   ///@}
};

} // namespace Ipopt

#endif
