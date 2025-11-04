#include <iostream>
#include <random>
#include "karol.h"

using namespace std;

std::vector<int> make_int_vector(int min_val, int max_val, std::size_t count) {
    if (min_val > max_val) {
        throw std::invalid_argument("min_val must be <= max_val");
    }
    std::random_device rd;                  // źródło ziarna (może delegować do systemowego RNG)
    std::mt19937 gen(rd());                 // silnik Mersenne Twister z ziarnem z rd
    std::uniform_int_distribution<int> dist(min_val, max_val); // rozkład całkowity na [min,max]
    std::vector<int> v;
    v.reserve(count);
    for (std::size_t i = 0; i < count; ++i) {
        v.push_back(dist(gen));
    }
    return v;
}


int main()
{


    cout << std::thread::hardware_concurrency() << endl;


    atomic<T> counter{};
    atomic<bool> running = true;

    vector<int> v1{1,2,3,8,1,2,3,5,6,9,8,7,6,0,0,0,-1,10,-5,-4,-3,-1,-2,-3,1,6,6};

    auto v = make_int_vector(-100,100, 100'000'000);
    cout << "End of generation" << endl;

    thread worker{ [& counter, &v, &running] ()->void
        {
            mergeSortMain(0,v.size()-1,v.data(),&counter);
            running.store(false);
    }};

    while (running.load())
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        cout << counter.load() << endl;
    }

    worker.join();
}
