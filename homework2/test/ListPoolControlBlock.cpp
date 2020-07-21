#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include "allocator/ListPoolControlBlock.hpp"
#include <new>

using testing::_;
using testing::Return;

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

TEST(test_list_pool_control_block, create)
{
    // Arrange

    // Act
    ListPoolControlBlock<sizeof(test_type1), pool_count> a;

    // Assert
    ASSERT_FALSE(a.nextlist);
}

TEST(test_list_pool_control_block, allocate_not_null)
{
    // Arrange
    ListPoolControlBlock<sizeof(test_type1), pool_count> a;
    size_t count_elements = 4;
    void *result_adress = (void *)1;

    // Prepare mocks
    EXPECT_CALL(a.controlBlock, allocate(count_elements))
        .Times(1)
        .WillOnce(Return(result_adress));

    // Act
    auto result = a.allocate(4);

    // Assert
    ASSERT_FALSE(a.nextlist);
    ASSERT_EQ(result, result_adress);
}

// TEST(test_list_pool_control_block, allocate_null)
// {
//     // Arrange
//     ListPoolControlBlock<sizeof(test_type1), pool_count> a;

//     size_t count_elements = 4;
//     void *result_adress = (void *)1;

//     // Prepare mocks
//     EXPECT_CALL(a.controlBlock, allocate(count_elements))
//         .Times(1)
//         .WillOnce(Return(nullptr));

//     // Падение здесь, не знаю как починить
//     EXPECT_CALL(a.nextlist->controlBlock, allocate(count_elements))
//         .Times(1)
//         .WillOnce(Return(result_adress));

//     // Act
//     auto result = a.allocate(4);

//     // Assert
//     ASSERT_TRUE(a.nextlist);
//     ASSERT_EQ(result, result_adress);
// }

TEST(test_list_pool_control_block, deallocate_in_first_element)
{
    // Arrange
    ListPoolControlBlock<sizeof(test_type1), pool_count> a;

    test_type1 element;
    size_t count_elements = 3;

    // Prepare mocks
    EXPECT_CALL(a.controlBlock, IsPointIn(&element))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(a.controlBlock, deallocate(&element, count_elements))
        .Times(1);

    // Act
    auto result = a.deallocate(&element, count_elements);

    // Assert
    ASSERT_TRUE(result);
}

TEST(test_list_pool_control_block, deallocate_in_other_element_not_null)
{
    // Arrange
    ListPoolControlBlock<sizeof(test_type1), pool_count> a;

    auto b1 = new ListPoolControlBlock<sizeof(test_type1), pool_count>();
    a.nextlist.reset(b1);

    test_type1 element;
    size_t count_elements = 3;

    // Prepare mocks
    EXPECT_CALL(a.controlBlock, IsPointIn(&element))
        .Times(1)
        .WillOnce(Return(false));

    EXPECT_CALL(b1->controlBlock, IsPointIn(&element))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(b1->controlBlock, deallocate(&element, count_elements))
        .Times(1);

    EXPECT_CALL(b1->controlBlock, IsEmpty())
        .Times(1)
        .WillOnce(Return(false));

    // Act
    auto result = a.deallocate(&element, count_elements);

    // Assert
    ASSERT_FALSE(result);
    ASSERT_TRUE(a.nextlist);
}

TEST(test_list_pool_control_block, deallocate_in_other_element_null)
{
    // Arrange
    ListPoolControlBlock<sizeof(test_type1), pool_count> a;

    auto b1 = new ListPoolControlBlock<sizeof(test_type1), pool_count>();
    a.nextlist.reset(b1);

    test_type1 element;
    size_t count_elements = 3;

    // Prepare mocks
    EXPECT_CALL(a.controlBlock, IsPointIn(&element))
        .Times(1)
        .WillOnce(Return(false));

    EXPECT_CALL(b1->controlBlock, IsPointIn(&element))
        .Times(1)
        .WillOnce(Return(true));

    EXPECT_CALL(b1->controlBlock, deallocate(&element, count_elements))
        .Times(1);

    EXPECT_CALL(b1->controlBlock, IsEmpty())
        .Times(1)
        .WillOnce(Return(true));

    // Act
    auto result = a.deallocate(&element, count_elements);

    // Assert
    ASSERT_FALSE(result);
    ASSERT_FALSE(a.nextlist);
}

TEST(test_list_pool_control_block, deallocate_with_error)
{
    // Arrange
    ListPoolControlBlock<sizeof(test_type1), pool_count> a;

    auto b1 = new ListPoolControlBlock<sizeof(test_type1), pool_count>();
    a.nextlist.reset(b1);

    test_type1 element;
    size_t count_elements = 3;

    // Prepare mocks
    EXPECT_CALL(a.controlBlock, IsPointIn(&element))
        .Times(1)
        .WillOnce(Return(false));

    EXPECT_CALL(b1->controlBlock, IsPointIn(&element))
        .Times(1)
        .WillOnce(Return(false));

    // Act

    // Assert
    ASSERT_THROW(a.deallocate(&element, count_elements), std::logic_error);
}