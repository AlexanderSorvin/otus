#include <gtest/gtest.h>
#include "ipv4.hpp"

TEST(test_ipv4, create_arg_number)
{
	// Arrange
    std::vector<std::string> v0 = {};
    std::vector<std::string> v1 = {"1"};
    std::vector<std::string> v2 = {"1", "2"};
    std::vector<std::string> v3 = {"1", "2", "3"};
    std::vector<std::string> v4 = {"1", "2", "3", "4"};
    std::vector<std::string> v5 = {"1", "2", "3", "4", "5"};
    std::vector<std::string> v6 = {"1", "2", "3", "4", "5", "6"};

    // Act

    // Assert
    ASSERT_THROW((ipv4(v0)), std::invalid_argument);
    ASSERT_THROW((ipv4(v1)), std::invalid_argument);
    ASSERT_THROW((ipv4(v2)), std::invalid_argument);
    ASSERT_THROW((ipv4(v3)), std::invalid_argument);
    ASSERT_NO_THROW((ipv4(v4)));
    ASSERT_THROW((ipv4(v5)), std::invalid_argument);
    ASSERT_THROW((ipv4(v6)), std::invalid_argument);
}

TEST(test_ipv4, create_arg_value)
{
	// Arrange
    std::vector<std::string> v1 = {"-1", "2", "3", "4"};
    std::vector<std::string> v2 = {"1", "256", "3", "4"};
    std::vector<std::string> v3 = {"1", "2", "a", "4"};
    std::vector<std::string> v4 = {"128", "1", "222", "255"};
    std::vector<std::string> v5 = {"43", "12", "", "255"};

    // Act

    // Assert
    ASSERT_THROW((ipv4(v1)), std::out_of_range);
    ASSERT_THROW((ipv4(v2)), std::out_of_range);
    ASSERT_THROW((ipv4(v3)), std::invalid_argument);
    ASSERT_NO_THROW((ipv4(v4)));
    ASSERT_THROW((ipv4(v5)), std::invalid_argument);
}

TEST(test_ipv4, equal)
{
	// Arrange
    std::vector<std::string> v1 = {"1", "2", "3", "4"};
    std::vector<std::string> v2 = {"1", "2", "4", "4"};

    // Act

    // Assert
    ASSERT_EQ((ipv4(v1)), (ipv4(v1)));
    ASSERT_NE((ipv4(v1)), (ipv4(v2)));
}

TEST(test_ipv4, more_less)
{
	// Arrange
    std::vector<std::string> v1 = {"1", "2", "3", "4"};
    std::vector<std::string> v2 = {"1", "2", "4", "4"};
    std::vector<std::string> v3 = {"1", "5", "4", "4"};
    std::vector<std::string> v4 = {"255", "1", "1", "1"};

    // Act

    // Assert
    ASSERT_LT((ipv4(v1)), (ipv4(v2)));
    ASSERT_GT((ipv4(v4)), (ipv4(v2)));
    ASSERT_GT((ipv4(v3)), (ipv4(v2)));
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
    auto i = ipv4(v1);

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
    auto i = ipv4(v1);

    // Assert
    ASSERT_TRUE(i.filter_any(n1));
    ASSERT_TRUE(i.filter_any(n2));
    ASSERT_TRUE(i.filter_any(n1, n2));
    ASSERT_FALSE(i.filter_any(n1, n3));
    ASSERT_TRUE(i.filter_any(n1, n2, n3));
    ASSERT_TRUE(i.filter_any(n1, n2, n3, n4));
    ASSERT_TRUE(i.filter_any(n2, n3, n4));
    ASSERT_TRUE(i.filter_any(n3, n4));
    ASSERT_FALSE(i.filter_any(n3, n4, n5));
    // i.filter_any(n1, n2, n3, n4, n5); // not compile
    // i.filter_any(); // not compile

    ASSERT_TRUE(i.filter_any({n1}));
    ASSERT_TRUE(i.filter_any({n2}));
    ASSERT_TRUE(i.filter_any({n1, n2}));
    ASSERT_FALSE(i.filter_any({n1, n3}));
    ASSERT_TRUE(i.filter_any({n1, n2, n3}));
    ASSERT_TRUE(i.filter_any({n1, n2, n3, n4}));
    ASSERT_TRUE(i.filter_any({n2, n3, n4}));
    ASSERT_TRUE(i.filter_any({n3, n4}));
    ASSERT_FALSE(i.filter_any({n3, n4, n5}));

    ASSERT_THROW(i.filter_any({n1, n2, n3, n4, n5}), std::invalid_argument);
    ASSERT_THROW(i.filter_any({}), std::invalid_argument);
}