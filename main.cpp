#include <iostream>
#include <random>
#include "karol.h"
#include "timer.h"

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
    auto v = make_int_vector(-100,100, 1'000'000);
    Timer t{};
    /*
    //depth i size jest po to, aby nie blokować slotów na wątki dla małych podtablic
    auto depth = 12;
    auto size = 1000;
    auto liczba_watkow = 16;



    cout << "End of generation" << endl;

    counting_semaphore<semaphore_max>sem{liczba_watkow};


    cout << liczba_watkow << endl;

    for(int i=0; i<25; ++i)
    {
        auto copy_v = v;
        t.start();
        //quickSort_simple_main(0,v.size()-1,v.data());
        //quickSort(0,v.size()-1,v.data());
        quickSort_depth(0,copy_v.size()-1,copy_v.data(),depth, sem);
        //quickSort_size(0,v.size()-1,v.data(),size, sem);



        t.stop();
        cout << t.get_miliseconds() << ", " << endl; ;
        t.reset();
    }
    cout << endl;

    */

    //kod dla badania wykorzystnia wątków
    // constexpr unsigned int thresholdMaxThreadNumber = 16; z pliku karol.h zmienic na std::thread::hardware_concurrency() ewnetualnie cos odjac

    unsigned long period_ms = 100;

    atomic<T> counter{};
    atomic<bool> running = true;

    for(int i=0; i<25; ++i)
    {
        auto vc = v;
        cout << "time ns \t threads" << endl;
        t.start();
        thread worker{ [& counter, &vc, &running] ()->void
                      {
                          quickSort_simple(0,vc.size()-1,vc.data(),counter);
                          running.store(false);
                      }};

        while (running.load())
        {
            cout << t.get_miliseconds() << '\t' << counter.load() << endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(period_ms));
        }

        worker.join();
        t.reset();
    }














}
