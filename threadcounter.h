#ifndef THREADCOUNTER_H
#define THREADCOUNTER_H

#include <atomic>
#include <cstdint>
using T = uint64_t;

class ThreadCounter
{
    std::atomic<T> & counter;
public:
    ThreadCounter(std::atomic<T> & counter) noexcept : counter{counter} 
        {counter.fetch_add(1, std::memory_order_relaxed);};
    ~ThreadCounter() noexcept   {counter.fetch_sub(1, std::memory_order_relaxed);};
};

#endif // THREADCOUNTER_H
