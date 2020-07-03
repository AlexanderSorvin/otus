#pragma once

#include <vector>
#include <initializer_list>
#include <array>
#include <iostream>
#include <stdexcept>

class ipv4 
{
private:
    // Параметр просится быть шаблонным, но здесь в этом нет необходимости
    static const size_t v4 = 4;
public:
    ipv4(const std::vector<std::string> &ip);

    template <typename... T, typename = typename std::enable_if<sizeof...(T) < ipv4::v4>>
    inline bool filter(uint8_t value1, T... values) const;

    template <typename... T, typename = typename std::enable_if<sizeof...(T) < ipv4::v4>>
    inline bool filter_any(uint8_t value1, T... values) const;

    bool filter(const std::initializer_list<uint8_t>& f) const;
    bool filter_any(const std::initializer_list<uint8_t>& f) const;

    friend std::ostream& operator<< (std::ostream &out, const ipv4 &ip);
    friend bool operator< (const ipv4& a, const ipv4& b);
    friend bool operator> (const ipv4& a, const ipv4& b);
    friend bool operator==(const ipv4& a, const ipv4& b);
private:
    std::array<uint8_t, v4> byte;
    uint32_t ip = 0;

    ipv4() = delete;
};

inline bool operator!= (const ipv4& a, const ipv4& b);

// С помощью рекурсии можно было явно запретить использовать другие типы, кроме uint8_t,
// Это нужно было сделать или нет? Варнинга достаточно?
template <typename... T, typename>
inline bool ipv4::filter(uint8_t value1, T... values) const
{
    return filter({value1, values...});
}

template <typename... T, typename>
inline bool ipv4::filter_any(uint8_t value1, T... values) const
{
    return filter_any({value1, values...});
}

inline bool operator!= (const ipv4& a, const ipv4& b) 
{ 
    return !(a == b); 
}