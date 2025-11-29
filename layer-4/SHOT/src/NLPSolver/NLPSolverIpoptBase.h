/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file NLPSolver/NLPSolverIpoptBase.h
 * @brief Ipopt implementation of INLPSolver interface
 *
 * Provides NLP solving for SHOT's primal problem using Ipopt interior point.
 *
 * **IpoptProblem Class (Ipopt::TNLP):**
 * - Implements Ipopt's TNLP interface
 * - Provides callbacks for function/gradient/Hessian evaluation
 * - Sparse Jacobian/Hessian via index placement maps
 *
 * **TNLP Callbacks:**
 * - get_nlp_info(): Problem dimensions and sparsity
 * - get_bounds_info(): Variable and constraint bounds
 * - eval_f(): Objective function value
 * - eval_grad_f(): Objective gradient
 * - eval_g(): Constraint function values
 * - eval_jac_g(): Constraint Jacobian (sparse)
 * - eval_h(): Lagrangian Hessian (sparse)
 * - finalize_solution(): Store optimal point
 *
 * **NLPSolverIpoptBase Class:**
 * - Wraps IpoptApplication for solve control
 * - Variable fixing for integer-fixed NLP subproblems
 * - Starting point management
 *
 * **IpoptJournal:**
 * - Routes Ipopt output through SHOT logging system
 *
 * @note Used for fixed-integer NLP subproblems in primal bound computation
 * @see PrimalSolver.h for NLP subproblem dispatch
 *
 * @algorithm Fixed-Integer NLP Subproblem in SHOT:
 *   Given integer solution x̄_I from MIP relaxation:
 *   @math min f(x) s.t. g(x) <= 0, x_I = x̄_I (fixed)
 *   If feasible solution found → updates primal bound.
 *   Solved via Ipopt interior-point method with reduced space.
 *   @ref Bonami et al. (2008) - BONMIN algorithm description
 *
 * @algorithm Primal-Dual Interior Point (via Ipopt):
 *   Solves NLP by finding KKT point of barrier problem:
 *   @math ∇L(x,λ) = 0 where L = f + λᵀg - μ∑log(s)
 *   - μ: barrier parameter → 0 as solution approaches
 *   - s: slack variables for inequality constraints
 *   @complexity Per iteration: O(n³) for Hessian factorization
 *   @ref Wächter & Biegler (2006) - Ipopt implementation
 *
 * @algorithm Sparse Derivative Evaluation (eval_jac_g, eval_h):
 *   Exploits problem sparsity for efficiency:
 *   @math Jacobian ∂g_i/∂x_j: sparse triplet format
 *         Hessian ∇²L: symmetric lower triangle
 *   jacobianCounterPlacement/lagrangianHessianCounterPlacement
 *   map (row,col) → position in sparse array.
 *   @complexity O(nnz) vs O(n²) for dense evaluation
 *
 * @algorithm Variable Fixing Strategy (fixVariables):
 *   For integer-fixed NLP: sets x_I = x̄_I via bound tightening
 *   @math l_i = u_i = x̄_i for integer variables i ∈ I
 *   Ipopt solves reduced-space problem over continuous variables.
 *   Original bounds restored by unfixVariables().
 *
 * @algorithm Warm Starting (setStartingPoint):
 *   Initialize from previous NLP solution or MIP point:
 *   - Improves convergence for similar subproblems
 *   - Critical for efficiency in repeated NLP solves
 *   @ref Nocedal & Wright (2006) - Warm starting in IPM
 */
#pragma once
#include "NLPSolverBase.h"

#include "IpTNLP.hpp"
#include "IpIpoptApplication.hpp"
#include "IpJournalist.hpp"

#include "../Model/Problem.h"

namespace SHOT
{

class NLPSolverIpoptBase;

// An Ipopt Journal implementation that uses the SHOT routines for output */
class IpoptJournal : public Ipopt::Journal
{
private:
    EnvironmentPtr env;
    char outBuf[10000];
    int outBufPos = 0;

public:
    IpoptJournal(EnvironmentPtr envPtr, /**< SHOT environment */
        const char* name, /**< journalist name */
        Ipopt::EJournalLevel default_level /**< default journal level */
        )
        : Ipopt::Journal(name, default_level), env(envPtr)
    {
    }

protected:
    void PrintImpl(Ipopt::EJournalCategory category, Ipopt::EJournalLevel level, const char* str);

    void PrintfImpl(Ipopt::EJournalCategory category, Ipopt::EJournalLevel level, const char* pformat, va_list ap);

    void FlushBufferImpl();
};

// The following class is adapted from COIN-OR Optimization Services Ipopt interface
class IpoptProblem : public Ipopt::TNLP
{
public:
    VectorInteger fixedVariableIndexes;
    VectorDouble fixedVariableValues;

    VectorInteger startingPointVariableIndexes;
    VectorDouble startingPointVariableValues;

    VectorDouble lowerBounds;
    VectorDouble upperBounds;

    bool hasSolution = false;
    VectorDouble variableSolution;
    double objectiveValue;

    E_NLPSolutionStatus solutionStatus;
    std::string solutionDescription;

    double divergingIterativesTolerance = 1e20;

    /** the IpoptProblemclass constructor */
    IpoptProblem(EnvironmentPtr envPtr, ProblemPtr problem);
    ~IpoptProblem() override = default;

    /** IPOpt specific methods for defining the nlp problem */
    bool get_nlp_info(Ipopt::Index& n, Ipopt::Index& m, Ipopt::Index& nnz_jac_g, Ipopt::Index& nnz_h_lag,
        IndexStyleEnum& index_style) override;

    /** Method to return the bounds for my problem */
    bool get_bounds_info(

        Ipopt::Index n, Ipopt::Number* x_l, Ipopt::Number* x_u, Ipopt::Index m, Ipopt::Number* g_l,
        Ipopt::Number* g_u) override;

    /** Method to get the linearity of variables */
    bool get_variables_linearity(Ipopt::Index n, LinearityType* var_types) override;

    /** Method to get the linearity of constraints */
    bool get_constraints_linearity(Ipopt::Index m, LinearityType* const_types) override;

    /** Method to return the starting point for the algorithm */
    bool get_starting_point(Ipopt::Index n, bool init_sx, Ipopt::Number* x, bool init_z, Ipopt::Number* z_L,
        Ipopt::Number* z_U, Ipopt::Index m, bool init_lambda, Ipopt::Number* lambda) override;

    /** Method to get the number of nonlinear variables in the problem */
    Ipopt::Index get_number_of_nonlinear_variables() override;

    /** Method to get a list of the nonlinear variable indices */
    bool get_list_of_nonlinear_variables(Ipopt::Index num_nonlin_vars, Ipopt::Index* pos_nonlin_vars) override;

    /** Method to return the objective value */
    bool eval_f(Ipopt::Index n, const Ipopt::Number* x, bool new_x, Ipopt::Number& obj_value) override;

    /** Method to return the gradient of the objective */
    bool eval_grad_f(Ipopt::Index n, const Ipopt::Number* x, bool new_x, Ipopt::Number* grad_f) override;

    /** Method to return the constraint residuals */
    bool eval_g(Ipopt::Index n, const Ipopt::Number* x, bool new_x, Ipopt::Index m, Ipopt::Number* g) override;

    /** Method to return:
     *   1) The structure of the jacobian (if "values" is NULL)
     *   2) The values of the jacobian (if "values" is not NULL)
     */
    bool eval_jac_g(Ipopt::Index n, const Ipopt::Number* x, bool new_x, Ipopt::Index m, Ipopt::Index nele_jac,
        Ipopt::Index* iRow, Ipopt::Index* jCol, Ipopt::Number* values) override;

    /** Method to return:
     *   1) The structure of the hessian of the lagrangian (if "values" is NULL)
     *   2) The values of the hessian of the lagrangian (if "values" is not NULL)
     */
    bool eval_h(Ipopt::Index n, const Ipopt::Number* x, bool new_x, Ipopt::Number obj_factor, Ipopt::Index m,
        const Ipopt::Number* lambda, bool new_lambda, Ipopt::Index nele_hess, Ipopt::Index* iRow, Ipopt::Index* jCol,
        Ipopt::Number* values) override;

    /*bool get_scaling_parameters(Ipopt::Number& obj_scaling, bool& use_x_scaling, Ipopt::Index n,
        Ipopt::Number* x_scaling, bool& use_g_scaling, Ipopt::Index m, Ipopt::Number* g_scaling) override;*/

    /** This method is called when the algorithm is complete so the TNLP can store/write the solution */
    void finalize_solution(Ipopt::SolverReturn status, Ipopt::Index n, const Ipopt::Number* x, const Ipopt::Number* z_L,
        const Ipopt::Number* z_U, Ipopt::Index m, const Ipopt::Number* g, const Ipopt::Number* lambda,
        Ipopt::Number obj_value, const Ipopt::IpoptData* ip_data, Ipopt::IpoptCalculatedQuantities* ip_cq) override;

private:
    EnvironmentPtr env;

    ProblemPtr sourceProblem;

    std::map<std::pair<int, int>, int> lagrangianHessianCounterPlacement;
    std::map<std::pair<int, int>, int> jacobianCounterPlacement;
};

class NLPSolverIpoptBase : virtual public INLPSolver
{

private:
    bool hasBeenSolved = false;

protected:
    Ipopt::SmartPtr<IpoptProblem> ipoptProblem;
    ProblemPtr sourceProblem;

    Ipopt::SmartPtr<Ipopt::IpoptApplication> ipoptApplication;

    E_NLPSolutionStatus solveProblemInstance() override;

    void fixVariables(VectorInteger variableIndexes, VectorDouble variableValues) override;
    void unfixVariables() override;

    virtual void setInitialSettings();
    virtual void setSolverSpecificInitialSettings() = 0;
    virtual void updateSettings();

    VectorDouble getVariableLowerBounds() override;
    VectorDouble getVariableUpperBounds() override;

    void updateVariableLowerBound(int variableIndex, double bound) override;
    void updateVariableUpperBound(int variableIndex, double bound) override;

    VectorDouble lowerBoundsBeforeFix;
    VectorDouble upperBoundsBeforeFix;

    std::vector<E_VariableType> originalVariableType;

public:
    ~NLPSolverIpoptBase() = default;

    void setStartingPoint(VectorInteger variableIndexes, VectorDouble variableValues) override;
    void clearStartingPoint() override;

    VectorDouble getSolution() override;
    double getSolution(int i) override;
    double getObjectiveValue() override;

    void saveOptionsToFile(std::string fileName) override;
    void saveProblemToFile(std::string fileName) override;

    std::string getSolverDescription() override;
};
} // namespace SHOT