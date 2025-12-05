// Copyright (C) 2003, International Business Machines
// Corporation and others.  All Rights Reserved.
// This code is licensed under the terms of the Eclipse Public License (EPL).

/**
 * @file ClpPredictorCorrector.hpp
 * @brief Mehrotra's predictor-corrector interior point algorithm
 * @author John Forrest
 *
 * Implements the primal-dual interior point method for LP/QP using
 * Mehrotra's predictor-corrector with Gondzio's multiple centrality corrections.
 *
 * @algorithm Mehrotra Predictor-Corrector Interior Point Method:
 * Solves LP/QP by following central path to optimum with predictor-corrector steps.
 *
 * @math KKT CONDITIONS for LP (primal min c'x s.t. Ax=b, x≥0):
 *   Primal feasibility:   Ax = b
 *   Dual feasibility:     A'y + s = c
 *   Complementarity:      X·S·e = 0 (component-wise x_i·s_i = 0)
 *   Non-negativity:       x ≥ 0, s ≥ 0
 *
 * @algorithm Newton System for Central Path:
 * Instead of XSe=0, follow parameterized central path XSe = μe where μ→0:
 *
 *   | 0   A'  I  | | Δx |   |   c - A'y - s   |
 *   | A   0   0  | | Δy | = |     b - Ax      |
 *   | S   0   X  | | Δs |   | μe - X·S·e      |
 *
 * After eliminating Δs = X⁻¹(μe - S·Δx - XSe), reduces to "normal equations":
 *   (A·D²·A') Δy = rhs    where D² = X·S⁻¹
 *
 * PREDICTOR STEP (Affine Scaling):
 *   1. Set μ=0 in Newton system → pure Newton toward optimum
 *   2. Solve for (Δx_aff, Δy_aff, Δs_aff)
 *   3. Find max step α_aff maintaining x+αΔx≥0, s+αΔs≥0
 *
 * CENTERING PARAMETER:
 *   σ = (μ_aff / μ)³ where μ_aff = gap after affine step
 *   Small σ: aggressive (toward optimum)
 *   Large σ: conservative (toward central path)
 *
 * CORRECTOR STEP:
 *   1. Modify RHS: μe → σμe - Δx_aff·Δs_aff (Mehrotra correction)
 *   2. Solve corrected system
 *   3. Combine for final direction
 *
 * @algorithm Gondzio's Multiple Centrality Corrections:
 * After corrector, additional corrections keep iterates well-centered:
 *   - If any (x+Δx)(s+Δs) too small: push toward center
 *   - If any (x+Δx)(s+Δs) too large: no correction needed
 *   - Typically 1-3 corrections improve robustness
 *
 * @complexity Per iteration: O(m²n + m³) dominated by Cholesky factorization
 *   of m×m normal equations (m=rows, n=cols).
 *   Total iterations: O(√n·log(1/ε)) for ε-optimality (polynomial).
 *
 * @ref Mehrotra (1992). "On the implementation of a primal-dual interior
 *   point method". SIAM J. Optimization 2(4):575-601.
 * @ref Gondzio (1996). "Multiple centrality corrections in a primal-dual
 *   method for LP". Comput. Optim. Appl. 6:137-156.
 * @ref Wright (1997). "Primal-Dual Interior-Point Methods". SIAM.
 *
 * Key methods:
 * - solve(): Main predictor-corrector iteration loop
 * - findStepLength(): Compute max step maintaining positivity
 * - complementarityGap(): Measure of optimality (should → 0)
 *
 * @see ClpInterior for the base interior point class
 * @see ClpCholeskyBase for the linear system solver
 * @see ClpPdco for PDCO alternative algorithm
 */

#ifndef ClpPredictorCorrector_H
#define ClpPredictorCorrector_H

#include "ClpInterior.hpp"

/** This solves LPs using the predictor-corrector method due to Mehrotra.
    It also uses multiple centrality corrections as in Gondzio.

    See;
    S. Mehrotra, "On the implementation of a primal-dual interior point method",
    SIAM Journal on optimization, 2 (1992)
    J. Gondzio, "Multiple centraility corrections in a primal-dual method for linear programming",
    Computational Optimization and Applications",6 (1996)


    It is rather basic as Interior point is not my speciality

    It inherits from ClpInterior.  It has no data of its own and
    is never created - only cast from a ClpInterior object at algorithm time.

    It can also solve QPs



*/

class ClpPredictorCorrector : public ClpInterior {

public:
  /**@name Description of algorithm */
  //@{
  /** Primal Dual Predictor Corrector algorithm

         Method

         Big TODO
     */

  int solve();
  //@}

  /**@name Functions used in algorithm */
  //@{
  /// findStepLength.
  //phase  - 0 predictor
  //         1 corrector
  //         2 primal dual
  CoinWorkDouble findStepLength(int phase);
  /// findDirectionVector.
  CoinWorkDouble findDirectionVector(const int phase);
  /// createSolution.  Creates solution from scratch (- code if no memory)
  int createSolution();
  /// complementarityGap.  Computes gap
  //phase 0=as is , 1 = after predictor , 2 after corrector
  CoinWorkDouble complementarityGap(int &numberComplementarityPairs, int &numberComplementarityItems,
    const int phase);
  /// setupForSolve.
  //phase 0=affine , 1 = corrector , 2 = primal-dual
  void setupForSolve(const int phase);
  /** Does solve. region1 is for deltaX (columns+rows), region2 for deltaPi (rows) */
  void solveSystem(CoinWorkDouble *region1, CoinWorkDouble *region2,
    const CoinWorkDouble *region1In, const CoinWorkDouble *region2In,
    const CoinWorkDouble *saveRegion1, const CoinWorkDouble *saveRegion2,
    bool gentleRefine);
  /// sees if looks plausible change in complementarity
  bool checkGoodMove(const bool doCorrector, CoinWorkDouble &bestNextGap,
    bool allowIncreasingGap);
  ///:  checks for one step size
  bool checkGoodMove2(CoinWorkDouble move, CoinWorkDouble &bestNextGap,
    bool allowIncreasingGap);
  /// updateSolution.  Updates solution at end of iteration
  //returns number fixed
  int updateSolution(CoinWorkDouble nextGap);
  ///  Save info on products of affine deltaT*deltaW and deltaS*deltaZ
  CoinWorkDouble affineProduct();
  ///See exactly what would happen given current deltas
  void debugMove(int phase, CoinWorkDouble primalStep, CoinWorkDouble dualStep);
  //@}
};
#endif

/* vi: softtabstop=2 shiftwidth=2 expandtab tabstop=2
*/
