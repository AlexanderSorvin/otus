#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "PoolAllocator.hpp"

using test_type1 = int;
using test_type2 = double *;
using test_type3 = float *;
const size_t pool_count = 10;

template <typename T>
class TestPoolAllocator : public PoolAllocator<T, pool_count>
{
public:
    ListPoolControlBlock<sizeof(T), pool_count> *getlist()
    {
        return this->list.get();
    }
};

// TEST(test_pool_allocator, create)
// {
//     // Arrange

//     // Act
//     TestPoolAllocator<test_type1> a;
//     PoolAllocator<test_type2, pool_count> b(a);
//     PoolAllocator<test_type3, pool_count> c(b);

//     // Assert
//     ASSERT_EQ(a.getlist()->nextlist, nullptr);
//     ASSERT_NE(a, b);
//     ASSERT_EQ(b, c);
// }

// TEST(test_pool_allocator, create_combo)
// {
//     // Arrange

//     // Act
//     PoolAllocator<test_type1, pool_count> a;

//     // Assert
//     ASSERT_EQ(a.getlist()->nextlist, nullptr);
// }
