#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "allocator/PoolAllocator.hpp"

using testing::Return;

using test_type1 = char;
using test_type2 = double *;
using test_type3 = float *;
const size_t pool_count = 10;

template <>
class ListPoolControlBlock<sizeof(test_type1), pool_count>
{
public:
    //void *allocate(std::size_t n);
    MOCK_METHOD(void *, allocate, (std::size_t n));

    //bool deallocate(void *p, std::size_t n);
    MOCK_METHOD(bool, deallocate, (void *p, std::size_t n));
};

class TestPoolAllocator : public PoolAllocator<test_type1, pool_count>
{
public:
    ListPoolControlBlock<sizeof(test_type1), pool_count> *getlist()
    {
        return this->list.get();
    }
};

TEST(test_pool_allocator, create)
{
    // Arrange

    // Act
    PoolAllocator<test_type1, pool_count> a;
    PoolAllocator<test_type2, pool_count> b(a);
    PoolAllocator<test_type3, pool_count> c(b);
    PoolAllocator<test_type2, pool_count>::rebind<test_type3>::other d(b);
    PoolAllocator<test_type3, pool_count> e;

    // Assert
    ASSERT_NE(a, b);
    ASSERT_EQ(b, c);
    ASSERT_EQ(b, d);
    ASSERT_NE(c, e);
}

TEST(test_pool_allocator, allocate)
{
    // Arrange
    TestPoolAllocator a;
    test_type1 type;
    size_t correct_size_alloc = 4;
    size_t notcorrect_size_alloc = 15;

    // Prepare mocks
    EXPECT_CALL(*a.getlist(), allocate(correct_size_alloc))
        .Times(1)
        .WillOnce(Return(&type));

    // Act
    auto result = a.allocate(4, (void *)5);

    // Assert
    ASSERT_EQ(result, &type);
    ASSERT_THROW(a.allocate(notcorrect_size_alloc, (void *)5), std::bad_alloc);
}

TEST(test_pool_allocator, deallocate)
{
    // Arrange
    TestPoolAllocator a;
    test_type1 type;
    size_t size_dealloc = 5;

    // Prepare mocks
    EXPECT_CALL(*a.getlist(), deallocate(&type, size_dealloc))
        .Times(1);

    // Act

    // Assert
    a.deallocate(&type, size_dealloc);
}