/**
 * @file
 * @brief Файл реализаций функций вывода ip адреса
 **/

#include "print_ip.hpp"
#include <iostream>

namespace homework3 {

namespace detail {

/**
 * @brief Функция пребразования объекта в string
 * @param node объект ноды
 * @return полученная строка
 **/
std::string to_string(const std::string &node)
{
    return node;
}

/**
 * @brief Функция пребразования объекта в string
 * @param node объект ноды
 * @return полученная строка
 **/
std::string to_string(uint8_t node)
{
    return std::to_string(node);
}

}

/**
 * @brief Функция вывода на экран ip адреса
 * @param str строка ip адреса
 **/
void print_ip(const std::string &str)
{
    std::cout << str;
}

} // namespace homework3