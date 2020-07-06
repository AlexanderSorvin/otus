#include <gtest/gtest.h>
#include "ip.hpp"

TEST(test_ipv4, create_arg_number)
{
	// Arrange
    std::vector<std::string> _v0 = {};
    std::vector<std::string> _v1 = {"1"};
    std::vector<std::string> _v2 = {"1", "2"};
    std::vector<std::string> _v3 = {"1", "2", "3"};
    std::vector<std::string> _v4 = {"1", "2", "3", "4"};
    std::vector<std::string> _v5 = {"1", "2", "3", "4", "5"};
    std::vector<std::string> _v6 = {"1", "2", "3", "4", "5", "6"};

    // Act

    // Assert
    ASSERT_THROW((ip<v4>(_v0)), std::invalid_argument);
    ASSERT_THROW((ip<v4>(_v1)), std::invalid_argument);
    ASSERT_THROW((ip<v4>(_v2)), std::invalid_argument);
    ASSERT_THROW((ip<v4>(_v3)), std::invalid_argument);
    ASSERT_NO_THROW((ip<v4>(_v4)));
    ASSERT_THROW((ip<v4>(_v5)), std::invalid_argument);
    ASSERT_THROW((ip<v4>(_v6)), std::invalid_argument);
}

TEST(test_ipv4, create_arg_value)
{
	// Arrange
    std::vector<std::string> _v1 = {"-1", "2", "3", "4"};
    std::vector<std::string> _v2 = {"1", "256", "3", "4"};
    std::vector<std::string> _v3 = {"1", "2", "a", "4"};
    std::vector<std::string> _v4 = {"128", "1", "222", "255"};
    std::vector<std::string> _v5 = {"43", "12", "", "255"};

    // Act

    // Assert
    ASSERT_THROW((ip<v4>(_v1)), std::out_of_range);
    ASSERT_THROW((ip<v4>(_v2)), std::out_of_range);
    ASSERT_THROW((ip<v4>(_v3)), std::invalid_argument);
    ASSERT_NO_THROW((ip<v4>(_v4)));
    ASSERT_THROW((ip<v4>(_v5)), std::invalid_argument);
}

TEST(test_ipv4, equal)
{
	// Arrange
    std::vector<std::string> _v1 = {"1", "2", "3", "4"};
    std::vector<std::string> _v2 = {"1", "2", "4", "4"};

    // Act

    // Assert
    ASSERT_EQ((ip<v4>(_v1)), (ip<v4>(_v1)));
    ASSERT_NE((ip<v4>(_v1)), (ip<v4>(_v2)));
}

TEST(test_ipv4, more_less)
{
	// Arrange
    std::vector<std::string> _v1 = {"1", "2", "3", "4"};
    std::vector<std::string> _v2 = {"1", "2", "4", "4"};
    std::vector<std::string> _v3 = {"1", "5", "4", "4"};
    std::vector<std::string> _v4 = {"255", "1", "1", "1"};

    // Act

    // Assert
    ASSERT_LT((ip<v4>(_v1)), (ip<v4>(_v2)));
    ASSERT_GT((ip<v4>(_v4)), (ip<v4>(_v2)));
    ASSERT_GT((ip<v4>(_v3)), (ip<v4>(_v2)));
}

TEST(test_ipv4, filter)
{
	// Arrange
    std::vector<std::string> v1 = {"1", "2", "3", "4"};
    uint8_t n1 = 1;
    uint8_t n2 = 2;
    uint8_t n3 = 3;
    uint8_t n4 = 4;
    uint8_t n5 = 5;

    // Act
    auto i = ip<v4>(v1);

    // Assert
    ASSERT_TRUE(i.filter(n1));
    ASSERT_FALSE(i.filter(n2));
    ASSERT_TRUE(i.filter(n1, n2));
    ASSERT_FALSE(i.filter(n1, n3));
    ASSERT_TRUE(i.filter(n1, n2, n3));
    ASSERT_TRUE(i.filter(n1, n2, n3, n4));
    // i.filter(n1, n2, n3, n4, n5); // not compile
    // i.filter(); // not compile

    ASSERT_TRUE(i.filter({n1}));
    ASSERT_FALSE(i.filter({n2}));
    ASSERT_TRUE(i.filter({n1, n2}));
    ASSERT_FALSE(i.filter({n1, n3}));
    ASSERT_TRUE(i.filter({n1, n2, n3}));
    ASSERT_TRUE(i.filter({n1, n2, n3, n4}));

    ASSERT_THROW(i.filter({n1, n2, n3, n4, n5}), std::invalid_argument);
    ASSERT_THROW(i.filter({}), std::invalid_argument);
}

TEST(test_ipv4, filter_any)
{
	// Arrange
    std::vector<std::string> v1 = {"1", "2", "3", "4"};
    uint8_t n1 = 1;
    uint8_t n2 = 2;
    uint8_t n3 = 3;
    uint8_t n4 = 4;
    uint8_t n5 = 5;

    // Act
    auto i = ip<v4>(v1);

    // Assert
    ASSERT_TRUE(i.filter_mask(n1));
    ASSERT_TRUE(i.filter_mask(n2));
    ASSERT_TRUE(i.filter_mask(n1, n2));
    ASSERT_FALSE(i.filter_mask(n1, n3));
    ASSERT_TRUE(i.filter_mask(n1, n2, n3));
    ASSERT_TRUE(i.filter_mask(n1, n2, n3, n4));
    ASSERT_TRUE(i.filter_mask(n2, n3, n4));
    ASSERT_TRUE(i.filter_mask(n3, n4));
    ASSERT_FALSE(i.filter_mask(n3, n4, n5));
    // i.filter_mask(n1, n2, n3, n4, n5); // not compile
    // i.filter_mask(); // not compile

    ASSERT_TRUE(i.filter_mask({n1}));
    ASSERT_TRUE(i.filter_mask({n2}));
    ASSERT_TRUE(i.filter_mask({n1, n2}));
    ASSERT_FALSE(i.filter_mask({n1, n3}));
    ASSERT_TRUE(i.filter_mask({n1, n2, n3}));
    ASSERT_TRUE(i.filter_mask({n1, n2, n3, n4}));
    ASSERT_TRUE(i.filter_mask({n2, n3, n4}));
    ASSERT_TRUE(i.filter_mask({n3, n4}));
    ASSERT_FALSE(i.filter_mask({n3, n4, n5}));

    ASSERT_THROW(i.filter_mask({n1, n2, n3, n4, n5}), std::invalid_argument);
    ASSERT_THROW(i.filter_mask({}), std::invalid_argument);
}