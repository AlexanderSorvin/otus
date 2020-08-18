#include "print_ip.hpp"
#include <gtest/gtest.h>

#include <list>
#include <array>
#include <map>
#include <unordered_map>
#include <set>
#include <string>
#include <vector>
#include <tuple>

using namespace homework3;
using testing::internal::CaptureStdout;
using testing::internal::GetCapturedStdout;

TEST(test_print_ip, list)
{
	// Arrange
    CaptureStdout();
    std::list<int> a = {1, 2, 3, 5};

    // Act
    print_ip(a);
    std::string output = GetCapturedStdout();

    // Assert
    ASSERT_EQ(std::string{"1.2.3.5"}, output);
}

// TEST(test_print_ip, array)
// {
// 	// Arrange
//     CaptureStdout();
//     std::array<int, 4> a = {1, 2, 3, 5};

//     // Act
//     print_ip(a);
//     std::string output = GetCapturedStdout();

//     // Assert
//     ASSERT_EQ(std::string{"1.2.3.5"}, output);
// }

// TEST(test_print_ip, map)
// {
// 	// Arrange
//     CaptureStdout();
//     std::map<int, std::string> a = {{0, "1"}, {1, "2"}, {2, "3"}, {4, "5"}};

//     // Act
//     print_ip(a);
//     std::string output = GetCapturedStdout();

//     // Assert
//     ASSERT_EQ(std::string{"1.2.3.5"}, output);
// }

// TEST(test_print_ip, unordered_map)
// {
// 	// Arrange
//     CaptureStdout();
//     std::unordered_map<int, std::string> a = {{0, "1"}, {1, "2"}, {2, "3"}, {4, "5"}};

//     // Act
//     print_ip(a);
//     std::string output = GetCapturedStdout();

//     // Assert
//     ASSERT_EQ(std::string{"1.2.3.5"}, output);
// }

TEST(test_print_ip, set)
{
	// Arrange
    CaptureStdout();
    std::set<long int> a = {1, 2, 3, 5};

    // Act
    print_ip(a);
    std::string output = GetCapturedStdout();

    // Assert
    ASSERT_EQ(std::string{"1.2.3.5"}, output);
}

TEST(test_print_ip, string)
{
	// Arrange
    CaptureStdout();
    std::string a = "1.2.3.5";

    // Act
    print_ip(a);
    std::string output = GetCapturedStdout();

    // Assert
    ASSERT_EQ(std::string{"1.2.3.5"}, output);
}

TEST(test_print_ip, vector)
{
	// Arrange
    CaptureStdout();
    std::vector<unsigned char> a = {1, 2, 3, 5};

    // Act
    print_ip(a);
    std::string output = GetCapturedStdout();

    // Assert
    ASSERT_EQ(std::string{"1.2.3.5"}, output);
}

TEST(test_print_ip, tuple)
{
	// Arrange
    CaptureStdout();
    std::tuple<long long int, long long int, long long int, long long int> a = {1, 2, 3, 5};

    // Act
    print_ip(a);
    std::string output = GetCapturedStdout();

    // Assert
    ASSERT_EQ(std::string{"1.2.3.5"}, output);
}