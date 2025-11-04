#include <iostream>
#include "karol.h"

using namespace std;

int main()
{


    cout << std::thread::hardware_concurrency() << endl;


    atomic<T> counter{};
    atomic<bool> running = true;

    vector<int> v{1,2,3,8,1,2,3,5,6,9,8,7,6,0,0,0,-1,10,-5,-4,-3,-1,-2,-3,1,6,6};

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
