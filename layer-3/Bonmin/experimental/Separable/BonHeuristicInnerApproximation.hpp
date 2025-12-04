// (C) Copyright CNRS and others 2010
// All Rights Reserved.
// This code is published under the Eclipse Public License.
/**
 * @file BonHeuristicInnerApproximation.hpp
 * @brief Bonmin inner approximation heuristic for MINLP
 *
 * Primal heuristic using inner approximation of feasible region.
 * Generates feasible MINLP solutions from LP relaxations.
 *
 * @algorithm Inner Approximation Heuristic:
 *   Constructs feasible MINLP solutions by solving restricted MILPs:
 *   1. Build polyhedral inner approximation of nonlinear feasible region
 *   2. Sample points on convex hull of nonlinear constraints
 *   3. Solve MILP on inner approximation to get integer-feasible point
 *   4. Project MILP solution to NLP feasible region via local NLP solve
 *   5. Return best feasible solution found
 *
 * @math Inner approximation construction:
 *   For convex g(x) ≤ 0: sample boundary points x_1,...,x_k with g(x_i) = 0
 *   Inner approx: conv{x_1,...,x_k} ⊆ {x : g(x) ≤ 0}
 *   MILP feasible → can project to NLP feasible (convexity)
 *
 * @complexity O(MILP_solve + k·NLP_project) per heuristic call.
 *   k = number of sample points for inner approximation.
 *   Typically called at root node and periodically during B&B.
 *
 * @ref Bonami et al. (2008). "An algorithmic framework for convex mixed integer
 *      nonlinear programs". Discrete Optimization 5(2):186-204.
 *
 * @see HeuristicInnerApproximation::solution for main heuristic method
 * @see BonOuterDescription for complementary outer approximation
 */
//
// Authors :
// Pierre Bonami, Université de la Méditérannée
// Hassan Hijazi, Orange Labs
//
// Date : 05/22/2010

#ifndef BonHeuristicInnerApproximation_HPP
#define BonHeuristicInnerApproximation_HPP
#include "BonOsiTMINLPInterface.hpp"
#include "BonBonminSetup.hpp"
#include "CbcHeuristic.hpp"
#include "CbcStrategy.hpp"

namespace Bonmin {
class SubMipSolver;
class HeuristicInnerApproximation: public CbcHeuristic {
public:

	/// Constructor with setup
	HeuristicInnerApproximation(BonminSetup * setup);

	/// Copy constructor
	HeuristicInnerApproximation(const HeuristicInnerApproximation &copy);

	/// Destructor
	~HeuristicInnerApproximation();

	/// Assignment operator
	HeuristicInnerApproximation & operator=(
			const HeuristicInnerApproximation & rhs);

	/// Clone
	virtual CbcHeuristic * clone() const {
		return new HeuristicInnerApproximation(*this);
	}

	/// Initialize method 
	void Initialize(BonminSetup * setup);

	/// Resets stuff if model changes
	virtual void resetModel(CbcModel * model) {
		setModel(model);
	}

	/// Performs heuristic
	virtual int solution(double &solutionValue, double *betterSolution);

	/** Register the options common to all local search based heuristics.*/
	static void registerOptions(
			Ipopt::SmartPtr<Bonmin::RegisteredOptions> roptions);

protected:
	/** Setup to use for local searches (will make copies).*/
	BonminSetup * setup_;

private:
	/// How often to do (code can change)
	int howOften_;

	/// A subsolver for MIP
	SubMipSolver * mip_;

        /// Number of Approximation points
        int nbAp_;

        void extractInnerApproximation(OsiTMINLPInterface & nlp, OsiSolverInterface &si,
                                       const double * x, bool getObj);

        bool getMyInnerApproximation(OsiTMINLPInterface &si, OsiCuts &cs, int ind,
                const double * x, const double * x2);


};
}

#endif
