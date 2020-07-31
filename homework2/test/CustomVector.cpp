#include <gtest/gtest.h>
#include "vector/CustomVector.hpp"

using basic_type = int;

class type : public CustomVector<basic_type>
{
public:
    type() = default;
    type(std::initializer_list<basic_type> a) : CustomVector<basic_type>(a) {}

    ~type() = default;

    size_t get_reverse() { return _reserve; }
};

TEST(customVector, create)
{
    // Arrange

    // Act
    type a;
    type b = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    // Assert
    ASSERT_EQ(a.size(), 0);
    ASSERT_TRUE(a.empty());
    ASSERT_EQ(a.get_reverse(), 0);

    ASSERT_EQ(b.size(), 10);
    ASSERT_FALSE(b.empty());
    ASSERT_EQ(b.get_reverse(), 10);
}

TEST(customVector, push_back)
{
    // Arrange
    type a;

    // Act
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    a.push_back(4);
    a.push_back(5);

    // Assert
    ASSERT_EQ(a.size(), 5);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(a.get_reverse(), 9);

    ASSERT_EQ(a[0], 1);
    ASSERT_EQ(a[1], 2);
    ASSERT_EQ(a[2], 3);
    ASSERT_EQ(a[3], 4);
    ASSERT_EQ(a[4], 5);
}

TEST(customVector, push)
{
    // Arrange
    type a;

    // Act
    a.push_back(1);
    a.push_back(2);
    a.push(a.begin(), 3);
    a.push(a.end(), 4);

    // Assert
    ASSERT_EQ(a.size(), 4);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(a.get_reverse(), 9);

    ASSERT_EQ(a[0], 3);
    ASSERT_EQ(a[1], 1);
    ASSERT_EQ(a[2], 2);
    ASSERT_EQ(a[3], 4);
}

TEST(customVector, pop)
{
    // Arrange
    type a = {1, 2, 3, 4, 5};

    // Act
    a.pop_back();
    a.pop(a.rbegin().toIterator());
    a.pop(a.rend().toIterator());

    // Assert
    ASSERT_EQ(a.size(), 2);
    ASSERT_FALSE(a.empty());
    ASSERT_EQ(a.get_reverse(), 5);

    ASSERT_EQ(a[0], 2);
    ASSERT_EQ(a[1], 3);
}

TEST(customVector, iterator)
{
    // Arrange
    type a = {1, 2, 3};
    basic_type b[3], c[3];

    // Act
    int j = 0;
    for (auto i : a)
    {
        b[j++] = i;
    }

    j = 0;
    for (auto i = a.rbegin(); i != a.rend(); i++)
    {
        c[j++] = *i;
    }

    // Assert
    ASSERT_EQ(b[0], 1);
    ASSERT_EQ(b[1], 2);
    ASSERT_EQ(b[2], 3);

    ASSERT_EQ(c[0], 3);
    ASSERT_EQ(c[1], 2);
    ASSERT_EQ(c[2], 1);
}

TEST(customVector, re)
{
    // Arrange
    type a;
    type b;
    type c = {1, 2, 3, 4, 5, 6};
    type d = {1, 2, 3, 4};
    type e = {1, 2, 3, 4, 5, 6};

    // Act
    a.reserve(5);
    b.resize(5);
    c.resize(5);
    d.resize(5);
    e.reserve(5);

    // Assert
    ASSERT_EQ(a.size(), 0);
    ASSERT_EQ(a.get_reverse(), 5);

    ASSERT_EQ(b.size(), 5);
    ASSERT_EQ(b.get_reverse(), 5);

    ASSERT_EQ(c.size(), 5);
    ASSERT_EQ(c.get_reverse(), 6);

    ASSERT_EQ(d.size(), 5);
    ASSERT_EQ(d.get_reverse(), 5);

    ASSERT_EQ(e.size(), 5);
    ASSERT_EQ(e.get_reverse(), 5);
}