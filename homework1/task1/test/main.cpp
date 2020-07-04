#define BOOST_TEST_MODULE homework1

#include <boost/test/unit_test.hpp>
#include <boost/regex.hpp>
#include "version.hpp"

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_number_bild)
{
    // Arrange

    // Act

    // Assert
    BOOST_CHECK(GetNumberBuild() > 0);
}

// Вот мне непонятно, как можно будет данный тест лаконично написать без использования регулярных выражений 
BOOST_AUTO_TEST_CASE(test_valid_version)
{
    // Arrange
    boost::regex regEx("^\\d+\\.\\d+\\.(\\d+)$");
    boost::smatch result;

    // Act
    std::string version = GetVersion();
    bool IsFormat = boost::regex_match(version, result, regEx);

    // Assert
    BOOST_CHECK(IsFormat);
    BOOST_CHECK(atoi(static_cast<std::string>(result[1]).c_str()) == GetNumberBuild());
}

}