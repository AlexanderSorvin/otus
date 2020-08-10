#pragma once

#include <type_traits>
#include <string>
#include <cassert>
#include <tuple>
#include <iostream>

namespace detail {

std::string to_string(const std::string &node);
std::string to_string(uint8_t node);

template <size_t number, typename T1, typename... T2>
struct tuple_node
{
    inline static void print_ip(const std::tuple<T1, T2...> &t)
    {
        using type = decltype(std::get<sizeof...(T2) - number>(t));
        static_assert(std::is_same<const T1&, type>::value, "В кортеже все типы должны совпадать");
        std::cout << "." << to_string(std::get<sizeof...(T2) - number>(t));
        tuple_node<number - 1, T1, T2...>::print_ip(t);
    }
};

template <typename T1, typename... T2>
struct tuple_node<0, T1, T2...>
{
    inline static void print_ip(const std::tuple<T1, T2...> &t)
    {
        using type = decltype(std::get<sizeof...(T2)>(t));
        static_assert(std::is_same<const T1&, type>::value, "В кортеже все типы должны совпадать");
        std::cout << "." << to_string(std::get<sizeof...(T2)>(t)) << std::endl;
    }
};

} // namespace detail

void print_ip(const std::string &str);

template <typename T,
          typename = typename std::enable_if<std::is_integral<T>::value>::type>
void print_ip(T value)
{
    for (size_t i = (sizeof(T) - 1) * 8; i > 0; i -= 8)
    {
        std::cout << static_cast<int>(uint8_t(value >> i)) << ".";
    }
    std::cout << static_cast<int>(uint8_t(value)) << std::endl;
}

template <typename T, typename... others, template<class, class...> class Container>
void print_ip(const Container<T, others...> &c)
{
    auto i = c.begin();
    std::cout << detail::to_string(*i);
    for (++i; i != c.end(); i++)
    {
        std::cout << "." << detail::to_string(*i);
    }
    std::cout << std::endl;
}

template <typename T1, typename... T2>
void print_ip(const std::tuple<T1, T2...> &t)
{
    std::cout << detail::to_string(std::get<0>(t));
    detail::tuple_node<sizeof...(T2) - 1, T1, T2...>::print_ip(t);
}