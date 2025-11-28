/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file ModelingSystem/IModelingSystem.h
 * @brief Abstract interface for problem input formats
 *
 * Base interface for parsing optimization problem files.
 *
 * **E_ProblemCreationStatus Enum:**
 * - NormalCompletion: Problem loaded successfully
 * - FileDoesNotExist, ErrorInFile: I/O errors
 * - ErrorInVariables/Constraints/Objective: Parse errors
 * - CapabilityProblem: Unsupported problem features
 *
 * **IModelingSystem Interface:**
 * - augmentSettings(): Add format-specific settings
 * - updateSettings(): Extract settings from problem file
 * - finalizeSolution(): Write solution back to format
 *
 * **Implementations:**
 * - ModelingSystemOSiL: XML OSiL format (Optimization Services)
 * - ModelingSystemAMPL: .nl format from AMPL
 * - ModelingSystemGAMS: GAMS interface
 * - ModelingSystemOS: Optimization Services framework
 *
 * @see Solver.h for setProblem() to load problems
 * @see Results.h for solution output
 */
#pragma once
#include "../Environment.h"
#include "../Enums.h"
#include "../Structs.h"

namespace SHOT
{

enum class E_ProblemCreationStatus
{
    NormalCompletion,
    FileDoesNotExist,
    ErrorInFile,
    CapabilityProblem,
    ErrorInVariables,
    ErrorInConstraints,
    ErrorInObjective,
    Error
};

class IModelingSystem
{
public:
    IModelingSystem(EnvironmentPtr envPtr) : env(envPtr) {};
    virtual ~IModelingSystem() = default;

    // Adds modeling system specific settings
    static void augmentSettings([[maybe_unused]] SettingsPtr settings) {};

    // Get specific settings from modeling system
    virtual void updateSettings(SettingsPtr settings) = 0;

    // Move the solution and statistics from SHOT to the modeling system
    virtual void finalizeSolution() = 0;

protected:
    EnvironmentPtr env;
};
} // namespace SHOT