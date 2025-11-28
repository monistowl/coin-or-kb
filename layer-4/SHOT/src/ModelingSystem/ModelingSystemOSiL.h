/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file ModelingSystem/ModelingSystemOSiL.h
 * @brief OSiL XML format reader for optimization problems
 *
 * Reads Optimization Services instance Language (OSiL) files.
 *
 * **ModelingSystemOSiL Class:**
 * - createProblem(): Parse OSiL XML into Problem
 * - augmentSettings(): Add OSiL-specific options
 * - finalizeSolution(): Write OSrL result format
 *
 * **OSiL Format:**
 * - XML-based optimization instance representation
 * - <instanceData> contains variables, objectives, constraints
 * - <nonlinearExpressions> for NLP terms (OSnL format)
 *
 * **XML Parsing:**
 * - Uses tinyxml2 for XML processing
 * - convertNonlinearNode(): OSnL to SHOT expression conversion
 *
 * @note OSiL is part of COIN-OR Optimization Services
 * @see ModelingSystemOS.h for OS library integration
 */
#pragma once
#include "IModelingSystem.h"

#include "../Environment.h"
#include "../Enums.h"
#include "../Structs.h"

#include <memory>
#include <string>

namespace tinyxml2
{
class XMLNode;
}

namespace SHOT
{

class NonlinearExpression;
using NonlinearExpressionPtr = std::shared_ptr<NonlinearExpression>;

class ModelingSystemOSiL : public IModelingSystem
{
public:
    ModelingSystemOSiL(EnvironmentPtr envPtr);
    ~ModelingSystemOSiL() override;

    // Adds modeling system specific settings
    static void augmentSettings(SettingsPtr settings);

    // Get specific settings from modeling system
    void updateSettings(SettingsPtr settings) override;

    // Create the optimization problem by filename in either OSiL or Ampl format
    E_ProblemCreationStatus createProblem(ProblemPtr& problem, const std::string& filename);

    // Move the solution and statistics from SHOT to the modeling system
    void finalizeSolution() override;

private:
    NonlinearExpressionPtr convertNonlinearNode(tinyxml2::XMLNode* node, const ProblemPtr& destination);
};

} // namespace SHOT