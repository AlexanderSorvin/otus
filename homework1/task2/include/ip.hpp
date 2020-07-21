#pragma once

#include <vector>
#include <initializer_list>
#include <array>
#include <iostream>
#include <stdexcept>

enum ip_protocol
{
    v4 = 4,
    v6 = 12
};

template <ip_protocol protocol>
class ip
{
public:
    ip(const std::vector<std::string> &ip);
    ~ip();

    template <typename... T, typename = typename std::enable_if<sizeof...(T) < protocol>>
    inline bool filter(uint8_t value1, T... values) const;

    template <typename... T, typename = typename std::enable_if<sizeof...(T) < protocol>>
    inline bool filter_mask(uint8_t value1, T... values) const;

    bool filter(const std::initializer_list<uint8_t> &f) const;
    bool filter_mask(const std::initializer_list<uint8_t> &f) const;

    template <ip_protocol _protocol>
    friend std::ostream &operator<<(std::ostream &out, const ip<_protocol> &ip);
    template <ip_protocol _protocol>
    friend bool operator<(const ip<_protocol> &a, const ip<_protocol> &b);
    template <ip_protocol _protocol>
    friend bool operator>(const ip<_protocol> &a, const ip<_protocol> &b);
    template <ip_protocol _protocol>
    friend bool operator==(const ip<_protocol> &a, const ip<_protocol> &b);

protected:
    std::array<uint8_t, protocol> byte;

    ip() = delete;
};

template <ip_protocol protocol>
inline bool operator!=(const ip<protocol> &a, const ip<protocol> &b);

template <ip_protocol protocol>
template <typename... T, typename>
inline bool ip<protocol>::filter(uint8_t value1, T... values) const
{
    return filter({value1, values...});
}

template <ip_protocol protocol>
template <typename... T, typename>
inline bool ip<protocol>::filter_mask(uint8_t value1, T... values) const
{
    return filter_mask({value1, values...});
}

template <ip_protocol protocol>
inline bool operator!=(const ip<protocol> &a, const ip<protocol> &b)
{
    return !(a == b);
}

template <ip_protocol protocol>
ip<protocol>::ip(const std::vector<std::string> &ip)
{
    if (ip.size() != protocol)
        throw std::invalid_argument("ip.size in vector<string> is not " + std::to_string(protocol));

    for (auto i = 0; i < protocol; i++)
    {
        auto byte = std::stol(ip[i]);
        if (byte > 255 || byte < 0)
            throw std::out_of_range("ip byte is less 0 or more 255");

        this->byte[i] = byte;
    }
}

template <ip_protocol protocol>
ip<protocol>::~ip()
{
}

template <ip_protocol protocol>
bool ip<protocol>::filter(const std::initializer_list<uint8_t> &f) const
{
    if (f.size() > protocol)
        throw std::invalid_argument("filter.size is more " + std::to_string(protocol));

    if (f.size() == 0)
        throw std::invalid_argument("filter.size is null");

    auto source = byte.begin();
    auto mask = f.begin();

    while (source != byte.end() && mask != f.end() &&
           *source == *mask)
    {
        source++;
        mask++;
    }

    return mask == f.end();
}

template <ip_protocol protocol>
bool ip<protocol>::filter_mask(const std::initializer_list<uint8_t> &f) const
{
    if (f.size() > protocol)
        throw std::invalid_argument("filter.size is more " + std::to_string(protocol));

    if (f.size() == 0)
        throw std::invalid_argument("filter.size is null");

    bool result = false;

    for (unsigned int i = 0; result == false && i < protocol + 1 - f.size(); i++)
    {
        auto mask = f.begin();
        for (auto j = i; mask != f.end() && *mask == byte[j]; mask++, j++)
        {
        }

        result = (mask == f.end());
    }

    return result;
}

template <ip_protocol protocol>
std::ostream &operator<<(std::ostream &out, const ip<protocol> &ip)
{
    int i = 0;
    for (; i < protocol - 1; i++)
    {
        out << static_cast<int>(ip.byte[i]) << ".";
    }
    out << static_cast<int>(ip.byte[i]);
    return out;
}

template <ip_protocol protocol>
bool operator<(const ip<protocol> &a, const ip<protocol> &b)
{
    int i = 0;
    while (a.byte[i] == b.byte[i] && i < protocol - 1)
    {
        i++;
    }

    return a.byte[i] < b.byte[i];
}

template <ip_protocol protocol>
bool operator>(const ip<protocol> &a, const ip<protocol> &b)
{
    int i = 0;
    while (a.byte[i] == b.byte[i] && i < protocol - 1)
    {
        i++;
    }

    return a.byte[i] > b.byte[i];
}

template <ip_protocol protocol>
bool operator==(const ip<protocol> &a, const ip<protocol> &b)
{
    int i = 0;
    while (a.byte[i] == b.byte[i] && i < protocol - 1)
    {
        i++;
    }

    return a.byte[i] == b.byte[i];
}