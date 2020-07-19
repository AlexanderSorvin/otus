#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "PoolAllocator.hpp"

using test_type1 = int;
using test_type2 = double *;
using test_type3 = float *;
const size_t pool_count = 10;

template <size_t type_size>
class PoolControlBlock<type_size, pool_count>
{
public:
    PoolControlBlock() = default;

    PoolControlBlock(const PoolControlBlock &) = default;
    PoolControlBlock(PoolControlBlock &&) = default;
    PoolControlBlock &operator=(const PoolControlBlock &) = default;
    PoolControlBlock &operator=(PoolControlBlock &&) = default;

    //void *allocate(std::size_t n) noexcept;
    MOCK_METHOD(void *, allocate, (std::size_t), (noexcept));
    //void deallocate(void *p, std::size_t n);
    MOCK_METHOD(void, deallocate, (void *p, std::size_t n));

    //bool IsPointIn(const void *hint) noexcept;
    MOCK_METHOD(bool, IsPointIn, (const void *hint), (noexcept));
    //bool IsEmpty() noexcept;
    MOCK_METHOD(bool, IsEmpty, (), (noexcept));
};

template <typename T>
class TestPoolAllocator : public PoolAllocator<T, pool_count>
{
public:
    listPoolControlBlock<sizeof(T), pool_count> *getlist()
    {
        return this->list.get();
    }
};

TEST(test_pool_allocator, create)
{
    // Arrange

    // Act
    TestPoolAllocator<test_type1> a;
    PoolAllocator<test_type2, pool_count> b(a);
    PoolAllocator<test_type3, pool_count> c(b);

    // Assert
    ASSERT_EQ(a.getlist()->nextlist, nullptr);
    ASSERT_NE(a, b);
    ASSERT_EQ(b, c);
}

// TEST(test_pool_allocator, create_combo)
// {
//     // Arrange

//     // Act
//     PoolAllocator<test_type1, pool_count> a;

//     // Assert
//     ASSERT_EQ(a.getlist()->nextlist, nullptr);
// }
