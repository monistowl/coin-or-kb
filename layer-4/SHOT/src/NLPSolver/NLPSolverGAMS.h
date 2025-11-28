/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Stefan Vigerske, GAMS Development Corp.

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file NLPSolver/NLPSolverGAMS.h
 * @brief GAMS-based NLP solver for fixed-integer subproblems
 *
 * Uses GAMS modeling system to call NLP solvers.
 *
 * **NLPSolverGAMS Class:**
 * - Uses gmoHandle_t from GAMS modeling system
 * - Calls user-selected NLP solver (CONOPT, IPOPT, etc.)
 * - Manages variable bounds and starting points
 *
 * **GAMS Handles:**
 * - modelingObject: GMO for problem data
 * - modelingEnvironment: GEV for GAMS environment
 *
 * **Solver Configuration:**
 * - nlpsolver: Solver name (e.g., "CONOPT", "IPOPT")
 * - timelimit, iterlimit: Resource limits
 * - solvelink: Execution mode
 *
 * @note Requires GAMS license for commercial NLP solvers
 * @see ModelingSystemGAMS.h for GAMS input processing
 */
#pragma once
#include "NLPSolverBase.h"

#include "gmomcc.h"
#include "gevmcc.h"
#include "palmcc.h"

namespace SHOT
{
class NLPSolverGAMS : public NLPSolverBase
{
private:
    gmoHandle_t modelingObject;
    gevHandle_t modelingEnvironment;

    std::string nlpsolver;
    std::string nlpsolveropt;
    double timelimit;
    int iterlimit;
    bool showlog;
    int solvelink;

public:
    NLPSolverGAMS(EnvironmentPtr envPtr, gmoHandle_t modelingObject, palHandle_t auditLicensing);

    ~NLPSolverGAMS() override;

    void setStartingPoint(VectorInteger variableIndexes, VectorDouble variableValues) override;
    void clearStartingPoint() override;

    void fixVariables(VectorInteger variableIndexes, VectorDouble variableValues) override;

    void unfixVariables() override;

    void saveOptionsToFile(std::string fileName) override;

    void saveProblemToFile(std::string fileName) override;

    VectorDouble getSolution() override;
    double getSolution(int i) override;

    double getObjectiveValue() override;

    void updateVariableLowerBound(int variableIndex, double bound) override;
    void updateVariableUpperBound(int variableIndex, double bound) override;

    std::string getSolverDescription() override;

protected:
    E_NLPSolutionStatus solveProblemInstance() override;

    VectorDouble getVariableLowerBounds() override;
    VectorDouble getVariableUpperBounds() override;

private:
    std::string selectedNLPSolver = "";
};
} // namespace SHOT