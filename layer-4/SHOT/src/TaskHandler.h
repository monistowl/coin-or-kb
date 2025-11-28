/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file TaskHandler.h
 * @brief Task scheduling and execution control
 *
 * Orchestrates the modular task-based algorithm workflow.
 *
 * **Task Management:**
 * - addTask(): Register task with string identifier
 * - getTask(): Retrieve task by ID
 * - clearTasks(): Reset for new solve
 *
 * **Execution Control:**
 * - getNextTask(): Dequeue next task to run
 * - setNextTask(): Jump to specific task (for goto/branching)
 * - terminate(): Signal algorithm termination
 * - isTerminated(): Check termination flag
 *
 * **Workflow Pattern:**
 * 1. SolutionStrategy adds tasks in order
 * 2. Solver calls getNextTask() in loop
 * 3. Tasks execute and may setNextTask() for control flow
 * 4. Termination tasks set terminate()
 *
 * **Task ID Naming:**
 * - "InitializeIteration", "SolveIteration"
 * - "CheckTimeLimit", "CheckAbsoluteGap"
 * - "SelectHyperplanes", "AddHyperplanes"
 *
 * @see TaskBase.h for task interface
 * @see SolutionStrategy/ for task configuration
 */
#pragma once

#include <list>
#include <string>
#include <utility>

#include "Tasks/TaskBase.h"
#include "Tasks/TaskException.h"

namespace SHOT
{
class TaskBase;

class TaskHandler
{
public:
    TaskHandler(EnvironmentPtr envPtr);
    ~TaskHandler() = default;

    void addTask(TaskPtr task, std::string taskID);
    bool getNextTask(TaskPtr& task);
    void setNextTask(std::string taskID);
    void clearTasks();

    TaskPtr getTask(std::string taskID);

    void terminate() { terminated = true; }
    inline bool isTerminated() { return terminated; }

private:
    std::list<std::pair<std::string, TaskPtr>>::iterator nextTask;
    std::string nextTaskID;
    std::list<std::pair<std::string, TaskPtr>> taskIDMap;
    std::list<TaskPtr> allTasks;

    EnvironmentPtr env;

    bool terminated = false;
};
}