// (C) Copyright CNRS and others 2010
// All Rights Reserved.
// This code is published under the Eclipse Public License.
/**
 * @file BonOuterDescription.hpp
 * @brief Bonmin outer approximation description for convex MINLP
 *
 * Outer approximation (OA) cut management for MINLP.
 * Linearization-based approach for convex MINLP.
 *
 * @algorithm Outer Approximation (OA) Cut Generation:
 *   Linearizes nonlinear constraints at solution points:
 *   1. Given NLP solution x*, for each nonlinear constraint g_i(x) ≤ 0:
 *      Generate gradient cut: g_i(x*) + ∇g_i(x*)ᵀ(x - x*) ≤ 0
 *   2. For objective f(x): linearize as f(x*) + ∇f(x*)ᵀ(x - x*) ≤ θ
 *   3. Add cuts to MILP relaxation and resolve
 *   4. Iterate until convergence (gap < tolerance)
 *
 * @math OA cut validity (convexity required):
 *   For convex g_i: g_i(x) ≥ g_i(x*) + ∇g_i(x*)ᵀ(x - x*) for all x
 *   Cut is valid: any x violating g_i(x) ≤ 0 also violates linearization.
 *   Multiple linearization points → polyhedral outer approximation.
 *
 * @complexity O(m·n) per cut generation where m = constraints, n = variables.
 *   Total iterations: typically O(log(1/ε)) for ε-optimal solution.
 *
 * @ref Duran & Grossmann (1986). "An outer-approximation algorithm for a class
 *      of mixed-integer nonlinear programs". Math. Programming 36:307-339.
 *
 * @see OsiTMINLPInterface for NLP interface
 * @see BonCutStrengthener for cut improvement
 */
//
// Authors :
// Pierre Bonami, Université de la Méditérannée
// Hassan Hijazi, Orange Labs
//
// Date : 05/22/2010

#ifndef OuterDescription_H
#define OuterDescription_H

#define INT_BIAS 0e-8

#include <string>
#include <iostream>

#include "BonOsiTMINLPInterface.hpp"
#include "CoinWarmStartBasis.hpp"

#include "BonCutStrengthener.hpp"

namespace Bonmin {

	/** Get the outer approximation constraints at provided point and only for the specified constraint (ind is the constraint or row number).
	 If x2 is different from NULL only add cuts violated by x2 by more than delta. **/
	void getMyOuterApproximation(OsiTMINLPInterface &si,
                                     OsiCuts &cs, int ind, const double * x,
			             int getObj, const double * x2,
                                     double theta, bool global);

/** Adds an outer description of problem to linear formulation.*/
void addOuterDescription(OsiTMINLPInterface &nlp, OsiSolverInterface &si,
		const double * x, int nbAp, bool getObj);

}
#endif
