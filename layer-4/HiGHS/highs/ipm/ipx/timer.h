/**
 * @file timer.h
 * @brief High-resolution wall-clock timer
 *
 * Simple timer class using std::chrono::high_resolution_clock
 * for measuring elapsed time in seconds. Used throughout IPX
 * to profile solver phases and report timing statistics.
 *
 * @see control.h for timer usage in solver logging
 * @see info.h for timing statistics storage
 */
#ifndef IPX_TIMER_H_
#define IPX_TIMER_H_

#include <chrono>

namespace ipx {

class Timer {
public:
    Timer();
    double Elapsed() const;
    void Reset();

private:
    typedef std::chrono::time_point<std::chrono::high_resolution_clock>
        TimePoint;
    static TimePoint tic();
    static double toc(TimePoint start);
    TimePoint t0_;
};

}  // namespace ipx

#endif  // IPX_TIMER_H_
