// Copyright (C) 2007, International Business Machines
// Corporation and others.  All Rights Reserved.

/**
 * @file BonQpBranchingSolver.hpp
 * @brief QP-based strong branching solver
 *
 * Implements strong branching by solving QP approximations of the NLP
 * subproblems. Faster than full NLP but more accurate than LP.
 *
 * @algorithm QP Strong Branching for MINLP:
 * Use second-order approximation to estimate branching impact.
 *
 * MOTIVATION:
 *   Full NLP strong branching: accurate but O(k · NLP_solve) per node
 *   LP strong branching: fast but ignores nonlinearity
 *   QP strong branching: balance accuracy and speed
 *
 * APPROXIMATION:
 *   At current NLP solution x*, build QP:
 *     min  f(x*) + ∇f(x*)ᵀ(x-x*) + ½(x-x*)ᵀH(x-x*)
 *     s.t. g(x*) + ∇g(x*)ᵀ(x-x*) ≤ 0
 *          l ≤ x ≤ u
 *
 *   where H = ∇²L(x*, λ*) is the Hessian of the Lagrangian
 *
 * STRONG BRANCHING PROCEDURE:
 *   markHotStart(): Build BranchingTQP from current NLP point
 *   For each candidate variable x_j:
 *     solveFromHotStart(x_j ≤ ⌊x*_j⌋): Get Δz⁻_j
 *     solveFromHotStart(x_j ≥ ⌈x*_j⌉): Get Δz⁺_j
 *   unmarkHotStart(): Clean up
 *   Select j* = argmax score(Δz⁻_j, Δz⁺_j)
 *
 * @math QP provides second-order Taylor approximation:
 *   Error is O(||x - x*||³) vs O(||x - x*||²) for LP
 *   Captures curvature that LP misses
 *
 * @complexity O(k · QP) per node where k = #candidates.
 * QP solve is O(n²) to O(n³) depending on structure (n = variables).
 * Much faster than O(k · NLP) for full NLP strong branching.
 *
 * @ref Requires FilterSQP or BQPD QP solver (BONMIN_HAS_FILTERSQP)
 *
 * @see StrongBranchingSolver for base class
 * @see BranchingTQP for the QP subproblem formulation
 * @see BqpdSolver for the underlying QP solver
 */
#ifndef BonQpBranchingSolver_H
#define BonQpBranchingSolver_H

#include "BonminConfig.h"
#include "BonStrongBranchingSolver.hpp"
#include "BonBranchingTQP.hpp"

#ifdef BONMIN_HAS_FILTERSQP
#include "BonFilterSolver.hpp"
#include "BonBqpdSolver.hpp"
#endif

namespace Bonmin
{

  /** This class chooses a variable to branch on

      This implementation solves the Qp model for different branches
      (strong branching).
  */

  class QpBranchingSolver : public StrongBranchingSolver
  {

  public:

    /// Constructor from solver (so we can set up arrays etc)
    QpBranchingSolver (OsiTMINLPInterface * solver);

    /// Copy constructor
    QpBranchingSolver (const QpBranchingSolver &);

    /// Assignment operator
    QpBranchingSolver & operator= (const QpBranchingSolver& rhs);

    /// Destructor
    virtual ~QpBranchingSolver ();

    /// Called to initialize solver before a bunch of strong branching
    /// solves
    virtual void markHotStart(OsiTMINLPInterface* tminlp_interface);

    /// Called to solve the current TMINLP (with changed bound information)
    virtual TNLPSolver::ReturnStatus solveFromHotStart(OsiTMINLPInterface* tminlp_interface);

    /// Called after all strong branching solves in a node
    virtual void unmarkHotStart(OsiTMINLPInterface* tminlp_interface);

  private:
    /// Default Constructor
    QpBranchingSolver ();

    Ipopt::SmartPtr<BranchingTQP> branching_tqp_;

    Ipopt::SmartPtr<TNLPSolver> tqp_solver_;

#ifdef TIME_BQPD
    BqpdSolver::Times times_;
#endif

    bool first_solve_;
  };

}

#endif
