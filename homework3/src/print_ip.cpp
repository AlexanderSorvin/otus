#include "print_ip.hpp"
#include <iostream>

namespace detail {

std::string to_string(const std::string &node)
{
    return node;
}

std::string to_string(uint8_t node)
{
    return std::to_string(node);
}

}

void print_ip(const std::string &str)
{
    std::cout << str << std::endl;
}