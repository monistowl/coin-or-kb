/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file EventHandler.h
 * @brief Observer pattern for algorithm events and callbacks
 *
 * Allows external code to respond to solver events.
 *
 * **Event Types (E_EventType):**
 * - NewPrimalSolution: New feasible solution found
 * - UserTerminationCheck: Allow user to request termination
 *
 * **Callback Registration:**
 * - registerCallback(event, callback): Register handler
 * - Callback signature: void()
 * - Multiple callbacks per event supported
 *
 * **Event Notification:**
 * - notify(event): Invoke all registered callbacks
 * - Called by solver at appropriate points
 *
 * **Usage Example:**
 * ```cpp
 * eventHandler->registerCallback(E_EventType::NewPrimalSolution,
 *     [&]() { std::cout << "New solution found!" << std::endl; });
 * ```
 *
 * @see Solver.h for event handler access
 * @see Enums.h for E_EventType definition
 */
#pragma once
#include "Environment.h"
#include "Enums.h"

#include <functional>
#include <map>
#include <vector>
#include <utility>

namespace SHOT
{

class EventHandler
{
public:
    inline EventHandler(EnvironmentPtr envPtr) : env(envPtr) {};

    template <typename Callback> void registerCallback(const E_EventType& event, Callback&& callback)
    {
        registeredCallbacks[event].push_back(std::forward<Callback>(callback));
    }

    template <typename Callback> void registerCallback(E_EventType&& event, Callback&& callback)
    {
        registeredCallbacks[std::move(event)].push_back(std::forward<Callback>(callback));
    }

    inline void notify(const E_EventType& event) const
    {
        if(registeredCallbacks.size() == 0)
            return;

        if(registeredCallbacks.find(event) == registeredCallbacks.end())
            return;

        for(const auto& C : registeredCallbacks.at(event))
            C();
    }

private:
    std::map<E_EventType, std::vector<std::function<void()>>> registeredCallbacks;

    EnvironmentPtr env;
};
} // namespace SHOT