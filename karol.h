#ifndef KAROL_H
#define KAROL_H
//=====================================================================================================================
//=====================================================================================================================
#include <iostream>
#include <thread>
#include <vector>
#include <future>

//---------------------------------------------------------------------------------------------------------------------
#include "threadcounter.h"
//=====================================================================================================================
using namespace std;
//=====================================================================================================================
constexpr unsigned int tresholdMinSizeNewThread = 25000;
constexpr unsigned int thresholdAlgorithm = 1;
constexpr unsigned int thresholdMaxThreadNumber = 16;
//=====================================================================================================================
/* to do section
 * - add thread counter
 * - add sort algorithm, that divides the vec for N equally portions, then executes separ
 * - licznik jako czesc samego merge do zarzadania ilosca watkow, opcja do wyciagniecia ilosci watkow w wersji debug
 * - dodac namespace, ukryc funkcje
 * - za duzo watkow / za maly problem -> nie tworz nowych watkow
 */
//=====================================================================================================================
ostream & operator << (ostream & os, const vector<int> & vec)
{
    for(auto elem : vec )
        os << elem << ", ";

    return os;
}
//---------------------------------------------------------------------------------------------------------------------
void wyswietl (int tab[], int b, int e)
{
    for(auto i=b; i<=e; ++i)
        cout << tab[i] << ", ";
}
//=====================================================================================================================
//=====================================================================================================================
void bubbleSort_asc_right(vector<int> & vec)
{
    if (vec.size() < 2)
        return;

    const auto iterCount = vec.size() - 1;
    for(int j=0; j < iterCount; ++j)
    {
        bool isChanged = false;
        for(int i=0; i < iterCount - j ;++i)
        {
            if(vec[i] > vec[i+1]){
                swap(vec[i], vec[i+1]);
                isChanged = true;
            }
        }
        if( ! isChanged)    //has not changed it means the vec is already sorted
            return;
    }
}
//=====================================================================================================================
void insertionSort_asc_left(vector<int> & vec)
{
    if (vec.size() < 2)
        return;

    const auto length = vec.size();
    for(int i=1; i < length; ++i)
    {
        const auto elem = vec[i];
        for(int j=i; j > 0; --j)    //small loop
        {
            if(elem >= vec[j-1])
                break;

            //swapping
            vec[j] = vec[j-1];
            vec[j-1] = elem;

        }
    }
}
//=====================================================================================================================
void merge(unsigned int b, unsigned int e, unsigned int m, int tab[])
{
    //1. coping the lef and right side of table, middle element stays wit left side
    unsigned int sizeL = m - b + 1;
    unsigned int sizeR = e - m;

    auto L = new int[sizeL];
    auto R = new int[sizeR];

    copy(tab+ b , tab + m + 1, L);
    copy(tab +m + 1, tab + e + 1, R);

    //2. inserting from both L and R to tab in sorted order
    unsigned int l = 0; //index of smallest elem remaining in left table
    unsigned int r = 0; //index of smallest elem remaining in right table
    unsigned int i = b; //index of place to insert a new elem

    while((l < sizeL) && (r < sizeR))
    {
        if(L[l] <= R[r])
        {
            tab[i] = L[l];
            ++l;
        }
        else
        {
            tab[i] = R[r];
            ++r;
        }
        ++i;
    }
    
    //3. coping the rest
    while(l < sizeL)
    {
        tab[i] = L[l];
        ++l;
        ++i;
    }
    while(r < sizeR)
    {
        tab[i] = R[r];
        ++r;
        ++i;
    }

    //4.clean
    delete[] L;
    delete[] R;
}
//---------------------------------------------------------------------------------------------------------------------
void mergeSort(unsigned int b, unsigned int e, int tab[])
{
    //check the condition of ending recursion
    if(b >= e)
        return;
    auto m = (e + b) >> 1;
    
    //divide
    mergeSort(b,m,tab);
    mergeSort(m+1,e,tab);
    
    //conquer
    merge(b,e,m,tab);
}
//---------------------------------------------------------------------------------------------------------------------
void mergeSortConcurrency(unsigned int b, unsigned int e, int tab[], std::atomic<T> & thread_counter)
{
    //check the condition of ending recursion
    if(b >= e)
        return;
    auto m = (e + b) >> 1;
    
    //divide
    if(e-b+1 < tresholdMinSizeNewThread || thread_counter.load(std::memory_order_relaxed) <= thresholdMaxThreadNumber)    //check if it is reasonable to start a new thread
    {
        mergeSortConcurrency(b, m, tab, thread_counter);
        mergeSortConcurrency(m+1,e,tab, thread_counter);
    }
    else
    {
        thread second([=, &thread_counter] () -> void {
            ThreadCounter counter{thread_counter};
            mergeSortConcurrency(b, m, tab, thread_counter);
        });
        mergeSortConcurrency(m+1,e,tab, thread_counter);
        second.join();
    }

    
    //conquer
    merge(b,e,m,tab);
}
//---------------------------------------------------------------------------------------------------------------------
void mergeSortMain(unsigned int b,
                   unsigned int e,
                   int tab[],
                   atomic<T> * counter_ptr = nullptr)
{

    std::atomic<uint64_t> local_counter{0};               // lokalny licznik na wypadek braku zewnętrznego
    std::atomic<uint64_t>& counter = counter_ptr ? *counter_ptr : local_counter;

    // Jeśli chcesz zliczać także „wątek-rodzic” rekurencji, odkomentuj:
    // ThreadCounterGuard root(*counter);

    mergeSortConcurrency(b, e, tab, counter);
}
//=====================================================================================================================


unsigned int partition(unsigned int b, unsigned int e, unsigned int pivIdx, int tab[])
{
    //check elems, if smaller than pivot, swap with pivot;
    //move the pivot to the the end of local table range
    swap(tab[e], tab[pivIdx]);

    auto pivot = tab[e];
    int next = b;
    for(unsigned int j=b; j < e; ++j)  //idx - idx of next elem after the highest idx of low side part of tab -> is also the idx of Pivot
    {
        if(tab[j] <= pivot)
        {
            swap(tab[next], tab[j]);
            ++next;
        }
    }
    //put pivot just after the left side so we have [left pivot right]
    swap(tab[next], tab[e]);

    return next;
}
//---------------------------------------------------------------------------------------------------------------------
void quickSort(int b, int e, int tab[])
{
    //validation of the args and table
    if (b >= e)
        return;
    //basic problem condition
    if(e-b+1 <= thresholdAlgorithm) //basic problem
    {
        mergeSort(b,e,tab);
        return;
    }

    //divide
    int pivIdx = e;    //here pivIdx should be calculated
    pivIdx = partition(b, e, pivIdx, tab);
    //conquer
    quickSort(b, pivIdx-1, tab);
    quickSort(pivIdx+1, e, tab);
}
//---------------------------------------------------------------------------------------------------------------------
void workerQuickSort()
{
    
}


void quickSortConcurrency(unsigned int b, unsigned int e, int tab[])
{
    //validation of the args and table
    if (b >= e)
        return;
    //basic problem condition
    if(e-b+1 <= thresholdAlgorithm) //basic problem
    {
        mergeSort(b,e,tab);
        return;
    }

    //divide
    int pivIdx = e;    //here pivIdx should be calculated
    pivIdx = partition(b, e, pivIdx, tab);
    
    //conquer
    thread second{quickSortConcurrency, b, pivIdx-1, tab};
    quickSortConcurrency(pivIdx+1, e, tab);
    second.join();
}
//=====================================================================================================================
//=====================================================================================================================





#endif // KAROL_H
