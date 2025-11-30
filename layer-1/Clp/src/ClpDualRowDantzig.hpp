// Copyright (C) 2002, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpDualRowDantzig.hpp
 * @brief Dantzig's rule for dual simplex pivot selection
 *
 * Implements the simplest pivot row selection: choose the basic variable
 * with the largest primal infeasibility. Simple and fast per iteration,
 * but may require many more iterations than steepest edge on degenerate
 * or difficult problems.
 *
 * This is Dantzig's original 1947 rule applied to dual simplex.
 * Use ClpDualRowSteepest for better performance on most problems.
 *
 * @algorithm Dantzig's Rule (Dual Simplex Leaving Variable Selection):
 * Scans all basic variables and selects the one most infeasible w.r.t. bounds.
 * For variable x_B[i] with bounds [l_i, u_i]:
 * - If x_B[i] < l_i: infeasibility = l_i - x_B[i] (want to increase)
 * - If x_B[i] > u_i: infeasibility = x_B[i] - u_i (want to decrease)
 * Choose the row with maximum infeasibility magnitude.
 * No weight storage needed - stateless selection on current solution.
 *
 * @math In dual simplex, select leaving row i* = argmax{|x_B[i] - bound_i|}
 * over all basic variables violating their bounds.
 * The direction of movement (toward lower or upper bound) determines
 * which reduced costs are candidates for the entering variable.
 * If all basic variables feasible, current solution is optimal.
 *
 * @complexity O(m) per iteration to scan all basic variables.
 * Same worst-case issues as primal Dantzig (exponential on Klee-Minty
 * variants). Dual steepest edge typically 2-3x fewer iterations.
 *
 * @ref Lemke, C.E. (1954). "The dual method of solving the linear programming
 *   problem". Naval Research Logistics Quarterly. [Early dual simplex]
 * @ref Dantzig, G.B. (1963). "Linear Programming and Extensions".
 *   Princeton University Press. [Comprehensive treatment]
 *
 * @see ClpDualRowPivot for the base interface
 * @see ClpDualRowSteepest for recommended steepest edge variant
 * @see ClpSimplexDual for the dual simplex algorithm
 */

#ifndef ClpDualRowDantzig_H
#define ClpDualRowDantzig_H

#include "ClpDualRowPivot.hpp"

//#############################################################################

/** Dual Row Pivot Dantzig Algorithm Class

This is simplest choice - choose largest infeasibility

*/

class CLPLIB_EXPORT ClpDualRowDantzig : public ClpDualRowPivot {

public:
  ///@name Algorithmic methods
  //@{

  /// Returns pivot row, -1 if none
  virtual int pivotRow();

  /** Updates weights and returns pivot alpha.
         Also does FT update */
  virtual double updateWeights(CoinIndexedVector *input,
    CoinIndexedVector *spare,
    CoinIndexedVector *spare2,
    CoinIndexedVector *updatedColumn);
  /** Updates primal solution (and maybe list of candidates)
         Uses input vector which it deletes
         Computes change in objective function
     */
  virtual void updatePrimalSolution(CoinIndexedVector *input,
    double theta,
    double &changeInObjective);
  //@}

  ///@name Constructors and destructors
  //@{
  /// Default Constructor
  ClpDualRowDantzig();

  /// Copy constructor
  ClpDualRowDantzig(const ClpDualRowDantzig &);

  /// Assignment operator
  ClpDualRowDantzig &operator=(const ClpDualRowDantzig &rhs);

  /// Destructor
  virtual ~ClpDualRowDantzig();

  /// Clone
  virtual ClpDualRowPivot *clone(bool copyData = true) const;

  //@}

  //---------------------------------------------------------------------------

private:
  ///@name Private member data
  //@}
};

#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
