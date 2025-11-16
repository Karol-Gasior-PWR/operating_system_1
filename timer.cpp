#include "timer.h"

using namespace std::chrono;

Timer::Timer()
    : running_(false),
    elapsed_(std::chrono::duration<double>::zero())
{
}
void Timer::start()
{
    if (!running_) {
        running_ = true;
        start_point_ = Clock::now();
    }
}

void Timer::stop()
{
    if (running_) {
        auto now = Clock::now();
        elapsed_ += now - start_point_;
        running_ = false;
    }
}

long long Timer::get_miliseconds()
{

    auto total = elapsed_;              // duration<double> w sekundach
    if (running_)
        total += Clock::now() - start_point_;

    return duration_cast<milliseconds>(total).count();
}
long long Timer::get_nanoseconds()
{

    auto total = elapsed_;              // duration<double> w sekundach
    if (running_)
        total += Clock::now() - start_point_;

    return duration_cast<nanoseconds>(total).count();
}
void Timer::reset()
{
    running_ = false;
    elapsed_ = std::chrono::duration<double>::zero();
}
