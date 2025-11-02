#include <iostream>
#include "karol.h"

using namespace std;

int main()
{
    vector<int> vec{0,5,1,8,11,4,0,0,0,5,22,1};
    cout << vec << endl;

    quickSortConcurrency(0,vec.size(), vec.data());
    cout << vec << endl;
}
