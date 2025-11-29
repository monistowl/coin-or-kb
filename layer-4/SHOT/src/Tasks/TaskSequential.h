/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Tasks/TaskSequential.h
 * @brief Container task that runs subtasks in sequence
 *
 * Composite pattern for building task workflows.
 *
 * **TaskSequential Class:**
 * - addTask()/addTasks(): Build task list
 * - run(): Execute all subtasks in order
 *
 * **Usage in SHOT:**
 * - Main iteration loop as sequential task chain
 * - Groups related operations (all termination checks)
 *
 * @see TaskBase.h for task interface
 * @see TaskConditional.h for branching logic
 */
#pragma once
#include "TaskBase.h"

namespace SHOT
{
class TaskSequential : public TaskBase
{
public:
    TaskSequential(EnvironmentPtr envPtr);
    TaskSequential(EnvironmentPtr envPtr, int numberOfTasks);

    ~TaskSequential() override;

    void addTasks(std::vector<TaskPtr> tasks);
    void addTask(TaskPtr task);

    void run() override;
    std::string getType() override;

private:
    std::vector<TaskPtr> m_tasks;
};
} // namespace SHOT