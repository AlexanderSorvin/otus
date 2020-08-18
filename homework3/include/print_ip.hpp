#pragma once

#include <type_traits>
#include <string>
#include <cassert>
#include <tuple>
#include <iostream>


namespace homework3 {

namespace detail {

/**
 * @brief Функция пребразования объекта в string
 * @param node объект ноды
 * @return полученная строка
 **/
std::string to_string(const std::string &node);

/**
 * @brief Функция пребразования объекта в string
 * @param node объект ноды
 * @return полученная строка
 **/
std::string to_string(uint8_t node);

template <size_t number, typename T1, typename... T2>
struct tuple_node
{
    /**
     * @brief Функция вывода на печать элемента кортежа ip-адреса
     * 
     * Функция выводит на печать объект кортежа ip-адреса с номером number 
     * (номерация объектов кортежа начинается с конца, 0 - последний). 
     * Не подходит для печати первого элемента кортежа.
     * 
     * @param t ссылка на кортеж ip адреса
     **/
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
    /**
     * @brief Функция вывода на печать элемента кортежа ip-адреса
     * 
     * Функция выводит на печать объект кортежа ip-адреса с номером number 
     * (номерация объектов кортежа начинается с конца, 0 - последний). 
     * Не подходит для печати первого элемента кортежа.
     * 
     * @param t ссылка на кортеж ip адреса
     **/
    inline static void print_ip(const std::tuple<T1, T2...> &t)
    {
        using type = decltype(std::get<sizeof...(T2)>(t));
        static_assert(std::is_same<const T1&, type>::value, "В кортеже все типы должны совпадать");
        std::cout << "." << to_string(std::get<sizeof...(T2)>(t));
    }
};

} // namespace detail

/**
 * @brief Функция вывода на экран ip адреса
 * @param str строка ip адреса
 **/
void print_ip(const std::string &str);

/**
 * @brief Функция вывода на экран ip адреса
 * @param value целочисленный объект в диапазоне от 0 до 255
 **/
template <typename T,
          typename = typename std::enable_if<std::is_integral<T>::value>::type>
void print_ip(T value)
{
    for (size_t i = (sizeof(T) - 1) * 8; i > 0; i -= 8)
    {
        std::cout << static_cast<int>(uint8_t(value >> i)) << ".";
    }
    std::cout << static_cast<int>(uint8_t(value));
}

/**
 * @brief Функция вывода на экран ip адреса
 * @param c объект-контейнер (не все типы: list, vector, set и др)
 **/
template <typename T, typename... others, template<class, class...> class Container>
void print_ip(const Container<T, others...> &c)
{
    auto i = c.begin();
    std::cout << detail::to_string(*i);
    for (++i; i != c.end(); i++)
    {
        std::cout << "." << detail::to_string(*i);
    }
}

/**
 * @brief Функция вывода на экран ip адреса
 * @param t кортежи с одиннаковыми типами (string или integral)
 **/
template <typename T1, typename... T2>
void print_ip(const std::tuple<T1, T2...> &t)
{
    std::cout << detail::to_string(std::get<0>(t));
    detail::tuple_node<sizeof...(T2) - 1, T1, T2...>::print_ip(t);
}

} // namespace homework3