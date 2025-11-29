/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSimple.h
 * @brief Lightweight task wrapper for lambda functions
 *
 * Adapts arbitrary callable to task interface.
 *
 * **TaskSimple Class:**
 * - setFunction(fn): Set callable to execute
 * - run(): Invoke the stored function
 *
 * **Usage:**
 * - Quick inline tasks without subclassing
 * - Adapts existing functions to task framework
 *
 * @see TaskBase.h for task interface
 */
#pragma once
#include "TaskBase.h"

#include <functional>

namespace SHOT
{
class TaskSimple : public TaskBase
{
public:
    TaskSimple(EnvironmentPtr envPtr, std::function<bool()> taskFunction);
    TaskSimple(EnvironmentPtr envPtr);
    ~TaskSimple() override;

    void setFunction(std::function<bool()> taskFunction);

    void run() override;
    std::string getType() override;

private:
    std::function<bool()> task;
};
} // namespace SHOT