#include <allocator/PoolAllocator.hpp>
#include <vector/CustomVector.hpp>

#include <map>
#include <vector>
#include <list>
#include <set>
#include <deque>

#include <iostream>

template <size_t count>
struct factorial
{
    static uint64_t value;
};

template <size_t count>
uint64_t factorial<count>::value = count *factorial<count - 1>::value;

template <>
uint64_t factorial<0>::value = 1;

namespace detail
{
    template <size_t max_number, typename T>
    void ConstructFactorial(T &element)
    {
        if constexpr (max_number > 0)
            ConstructFactorial<max_number - 1>(element);
        element[max_number] = factorial<max_number>::value;
    }
} // namespace detail

int main()
{
    std::map<int, size_t> map1;
    std::map<int, size_t, std::less<int>, PoolAllocator<std::pair<const int, size_t>, 10>> map2;

    // CustomVector<int> vector1;
    // vector1.resize(10);

    // CustomVector<size_t, PoolAllocator<size_t, 10>> vector2;
    // vector2.resize(10);

    detail::ConstructFactorial<9>(map1);
    detail::ConstructFactorial<9>(map2);
    // detail::ConstructFactorial<9>(vector1);
    // detail::ConstructFactorial<9>(vector2);

    std::cout << "   map1: ";
    for (auto &i : map1)
    {
        std::cout << "[" << i.first << " " << i.second << "] ";
    }
    std::cout << std::endl;

    std::cout << "   map2: ";
    for (auto &i : map2)
    {
        std::cout << "[" << i.first << " " << i.second << "] ";
    }
    std::cout << std::endl;

    // std::cout << "vector1: ";
    // for (size_t i = 0; i < vector1.size(); ++i)
    // {
    //     std::cout << "[" << i << " " << vector1[i] << "] ";
    // }
    // std::cout << std::endl;

    // std::cout << "vector2: ";
    // for (size_t i = 0; i < vector2.size(); ++i)
    // {
    //     std::cout << "[" << i << " " << vector2[i] << "] ";
    // }
    // std::cout << std::endl;

    return 0;
}