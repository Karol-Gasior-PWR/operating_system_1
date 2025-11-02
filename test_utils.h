#ifndef TEST_UTILS_H
#define TEST_UTILS_H
//=====================================================================================================================
//includes
#include <vector>
//=====================================================================================================================
//=====================================================================================================================
namespace test_utils
{
//templates
/**
 * @brief isAscending checks is elements of the vector are in ascending order
 * @param vec
 * @return true - elements of
 */
template <typename T>
bool isAscending(std::vector<T> & vec)
{
    auto size = vec.size();
    for(std::size_t i=0; i < size-1; ++i)
    {
        if(vec[i] > vec[i+1])
            return false;
    }
    return true;
}
//---------------------------------------------------------------------------------------------------------------------
/**
 * @brief isDescending
 * @param vec
 * @return
 */
template <typename T>
bool isDescending(std::vector<T> & vec)
{
    auto end = vec.cend();
    for(auto iter = vec.cbegin()+1; iter != end; ++iter)
    {
        if(*(iter-1) > *(iter))
            return false;
    }
    return true;
}
} //end of namespace test_utils

#endif // TEST_UTILS_H
