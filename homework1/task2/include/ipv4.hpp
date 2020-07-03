#pragma once

#include <vector>
#include <initializer_list>
#include <array>
#include <iostream>
#include <stdexcept>

class ipv4 
{
private:
    static const size_t v4 = 4;
public:
    ipv4(const std::vector<std::string> &ip);

    bool operator== (const ipv4& ip);
    inline bool operator!= (const ipv4& ip) { !(*this == ip); }

    template <typename... T, typename = typename std::enable_if<sizeof...(T) < ipv4::v4 - 1>>
    inline bool filter(uint8_t value1, T... values);

    template <typename... T, typename = typename std::enable_if<sizeof...(T) < ipv4::v4 - 1>>
    inline bool filter_any(uint8_t value1, T... values);

    bool filter(const std::initializer_list<uint8_t>& f);
    bool filter_any(const std::initializer_list<uint8_t>& f);

    friend std::ostream& operator<< (std::ostream &out, const ipv4 &ip);
    friend bool operator< (const ipv4& ip1, const ipv4& ip2);
private:
    std::array<uint8_t, v4> byte;
    uint32_t ip;

    ipv4() = delete;
};

template <typename... T, typename>
inline bool filter(uint8_t value1, T... values)
{
    return filter({value1, values...});
}

template <typename... T, typename>
inline bool filter_any(uint8_t value1, T... values)
{
    return filter_any({value1, values...});
}