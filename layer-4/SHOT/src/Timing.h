/**
   The Supporting Hyperplane Optimization Toolkit (SHOT).

   @author Andreas Lundell, Åbo Akademi University

   @section LICENSE
   This software is licensed under the Eclipse Public License 2.0.
   Please see the README and LICENSE files for more information.
*/
/**
 * @file Timing.h
 * @brief Named timer registry for profiling solver phases
 *
 * Collection of named timers for performance analysis.
 *
 * **Timing Class:**
 * - createTimer(): Register new timer with name/description
 * - startTimer()/stopTimer(): Control by name
 * - getElapsedTime(): Query accumulated time
 *
 * **Typical Timers:**
 * - "Total": Overall solve time
 * - "DualMIP": MIP solver calls
 * - "PrimalNLP": NLP subproblem solves
 * - "Reformulation": Problem transformation
 *
 * **Thread Safety:**
 * - Timers are not thread-safe
 * - Use in single-threaded solver context
 *
 * @see Timer.h for individual timer class
 * @see Environment.h for accessing via env->timing
 */
#pragma once
#include "Environment.h"
#include "Timer.h"

#include <algorithm>
#include <vector>

namespace SHOT
{

class Timing
{
public:
    inline Timing(EnvironmentPtr envPtr) { env = envPtr; };

    inline ~Timing() { timers.clear(); }

    inline void createTimer(std::string name, std::string description) { timers.emplace_back(name, description); }

    inline void startTimer(std::string name)
    {
        auto timer = std::find_if(timers.begin(), timers.end(), [name](Timer const& T) { return (T.name == name); });

        if(timer == timers.end())
        {
            // env->output->outputError("Timer with name  \"" + name + "\" not found!");
            return;
        }

        timer->start();
    }

    inline void stopTimer(std::string name)
    {
        auto timer = std::find_if(timers.begin(), timers.end(), [name](Timer const& T) { return (T.name == name); });

        if(timer == timers.end())
        {
            // env->output->outputError("Timer with name  \"" + name + "\" not found!");
            return;
        }

        timer->stop();
    }

    inline void restartTimer(std::string name)
    {
        auto timer = std::find_if(timers.begin(), timers.end(), [name](Timer const& T) { return (T.name == name); });

        if(timer == timers.end())
        {
            // env->output->outputError("Timer with name  \"" + name + "\" not found!");
            return;
        }

        timer->restart();
    }

    inline double getElapsedTime(std::string name)
    {
        auto timer = std::find_if(timers.begin(), timers.end(), [name](Timer const& T) { return (T.name == name); });

        if(timer == timers.end())
        {
            // env->output->outputError("Timer with name  \"" + name + "\" not found!");
            return (0.0);
        }

        return (timer->elapsed());
    }

    std::vector<Timer> timers;

private:
    EnvironmentPtr env;
};

} // namespace SHOT