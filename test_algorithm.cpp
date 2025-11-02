#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
//=====================================================================================================================
//includes
//=====================================================================================================================
//std libraries
#include <algorithm>
//---------------------------------------------------------------------------------------------------------------------
//test functions
#include "test_utils.h"
//---------------------------------------------------------------------------------------------------------------------
//modules to test
#include "karol.h"
//---------------------------------------------------------------------------------------------------------------------
//=====================================================================================================================
using namespace std;
//---------------------------------------------------------------------------------------------------------------------
using namespace test_utils;
//=====================================================================================================================
TEST_CASE("Sorting algorithms - single thread version", "[single_thread][quick][merge]")
{
    vector<int> ascending_vec{1,2,3,4,5,6,9,9};
    vector<int> descending_vec{9,8,7,6,5,4,4,3,2,1,1};
    vector<int> mid_vec{1,2,3,8,1,2,3,5,6,9,8,7,6,0,0,0,-1,10,-5,-4,-3,-1,-2,-3,1,6,6};


    auto r_ascending_vec = ascending_vec,
        r_descending_vec = descending_vec,
        r_mid_vec = mid_vec;

    std::sort(r_ascending_vec.begin(), r_ascending_vec.end());
    std::sort(r_descending_vec.begin(), r_descending_vec.end());
    std::sort(r_mid_vec.begin(), r_mid_vec.end());


    SECTION("Quick sort")
    {
        quickSort(0, ascending_vec.size(), ascending_vec.data());
        quickSort(0, descending_vec.size(), descending_vec.data());
        quickSort(0, mid_vec.size(), mid_vec.data());

        INFO("Check - ascending");
        REQUIRE(isAscending(ascending_vec));
        REQUIRE(isAscending(r_descending_vec));
        REQUIRE(isAscending(r_mid_vec));

        INFO("Compare with std::sort");
        REQUIRE(ascending_vec == r_ascending_vec);
        REQUIRE(r_descending_vec == descending_vec);
        REQUIRE(r_mid_vec == mid_vec);
    }
    //-----------------------------------------------------------------------------------------------------------------
    SECTION("Merge sort")
    {
        mergeSort(0, ascending_vec.size(), ascending_vec.data());
        mergeSort(0, descending_vec.size(), descending_vec.data());
        mergeSort(0, mid_vec.size(), mid_vec.data());

        INFO("Check - ascending");
        REQUIRE(isAscending(ascending_vec));
        REQUIRE(isAscending(r_descending_vec));
        REQUIRE(isAscending(r_mid_vec));

        INFO("Compare with std::sort");
        REQUIRE(ascending_vec == r_ascending_vec);
        REQUIRE(r_descending_vec == descending_vec);
        REQUIRE(r_mid_vec == mid_vec);
    }
}
