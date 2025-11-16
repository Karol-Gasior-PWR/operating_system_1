#ifndef TIMER_H
#define TIMER_H

#include <chrono>

class Timer
{
public:
    using Clock      = std::chrono::steady_clock;
    using TimePoint  = std::chrono::time_point<Clock>;
public:
    Timer();
    void start();
    void stop();
    long long get_miliseconds();
    void reset();
private:
    bool running_;
    TimePoint start_point_;
    std::chrono::duration<double> elapsed_;

};

#endif // TIMER_H
