// Copyright (C) 2007 International Business Machines and others.
// All Rights Reserved.
// This code is published under the Eclipse Public License.
//
// Authors:  Andreas Waechter            IBM    2007-04-17

/**
 * @file IpTDependencyDetector.hpp
 * @brief Base class for detecting linearly dependent constraint rows
 *
 * TDependencyDetector is the abstract base class for algorithms that
 * detect linearly dependent rows in the constraint Jacobian. This is
 * needed to handle degenerate problems where some constraints are
 * redundant.
 *
 * Purpose:
 * If rank(J_c) < m_c, the KKT system is singular. Detecting and
 * removing dependent rows allows the solver to proceed.
 *
 * Interface:
 * - DetermineDependentRows(): Takes Jacobian in triplet format,
 *   returns list of dependent row indices in c_deps
 *
 * Input format (MA28 style triplet):
 * - n_rows, n_cols: Jacobian dimensions
 * - n_jac_nz: Number of nonzeros
 * - jac_c_vals, jac_c_iRow, jac_c_jCol: Values and indices
 *
 * The input arrays may be modified internally (working space).
 *
 * @see IpTSymDependencyDetector.hpp for symmetric solver-based detection
 * @see IpMa28TDependencyDetector.hpp for MA28-based detection
 */

#ifndef __IPTDEPENDENCYDETECTOR_HPP__
#define __IPTDEPENDENCYDETECTOR_HPP__

#include "IpAlgStrategy.hpp"
#include <list>

namespace Ipopt
{

/** Base class for all derived algorithms for detecting linearly
 *  dependent rows in the constraint Jacobian.
 */
class TDependencyDetector: public AlgorithmStrategyObject
{
public:
   /** @name Constructor/Destructor */
   ///@{
   TDependencyDetector()
   { }

   virtual ~TDependencyDetector()
   { }
   ///@}

   /** Has to be called to initialize and reset these objects. */
   virtual bool InitializeImpl(
      const OptionsList& options,
      const std::string& prefix
   ) = 0;

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
   ) = 0;

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
   TDependencyDetector(
      const TDependencyDetector&
   );

   /** Default Assignment Operator */
   void operator=(
      const TDependencyDetector&
   );
   ///@}

};

} // namespace Ipopt

#endif
