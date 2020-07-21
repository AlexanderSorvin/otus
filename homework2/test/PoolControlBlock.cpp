#include <gtest/gtest.h>
#include <PoolControlBlock.hpp>

TEST(test_pool_control_block, create)
{
	// Arrange
    PoolControlBlock<13, 15> a;

    // Act

    // Assert
    ASSERT_NO_THROW((PoolControlBlock<10, 54>()));
    ASSERT_NO_THROW((PoolControlBlock<1, 545>()));
    ASSERT_NO_THROW((PoolControlBlock<45, 1>()));
    ASSERT_TRUE(a.IsEmpty());
}

TEST(test_pool_control_block, allocate)
{
	// Arrange
    using type = double;
    PoolControlBlock<sizeof(type), 16> a;

    // Act
    type * b1 = static_cast<type *>(a.allocate(1));
    type * b2 = static_cast<type *>(a.allocate(3));
    type * b3 = static_cast<type *>(a.allocate(5));
    type * b4 = static_cast<type *>(a.allocate(7));
    type * b5 = static_cast<type *>(a.allocate(1));

    // Assert
    ASSERT_TRUE(a.IsPointIn(b1));
    ASSERT_TRUE(a.IsPointIn(b2));
    ASSERT_TRUE(a.IsPointIn(b3));
    ASSERT_TRUE(a.IsPointIn(b4));
    ASSERT_FALSE(a.IsPointIn(b5));

    ASSERT_EQ(b1 + 1, b2);
    ASSERT_EQ(b2 + 3, b3);
    ASSERT_EQ(b3 + 5, b4);
    ASSERT_EQ(b5, nullptr);
}

TEST(test_pool_control_block, deallocate)
{
	// Arrange
    using type = int;
    PoolControlBlock<sizeof(type), 15> a;

    // Act
    auto b1 = a.allocate(4);
    auto b2 = a.allocate(5);
    auto b3 = a.allocate(1);
    auto b4 = a.allocate(3);
    auto b5 = a.allocate(2);

    auto b6 = static_cast<type *>(b1) - 1;
    auto b7 = static_cast<type *>(b5) + 4;

    // Assert
    ASSERT_FALSE(a.IsEmpty());
    ASSERT_NO_THROW(a.deallocate(b4, 3));
    ASSERT_FALSE(a.IsEmpty());
    ASSERT_NO_THROW(a.deallocate(b3, 1));
    ASSERT_NO_THROW(a.deallocate(b5, 2));
    ASSERT_NO_THROW(a.deallocate(b1, 4));
    ASSERT_FALSE(a.IsEmpty());
    ASSERT_NO_THROW(a.deallocate(b2, 5));
    ASSERT_TRUE(a.IsEmpty());
    ASSERT_THROW(a.deallocate(b6, 1), std::invalid_argument);
    ASSERT_THROW(a.deallocate(b7, 1), std::invalid_argument);
    ASSERT_THROW(a.deallocate(b5, 4), std::invalid_argument);
}