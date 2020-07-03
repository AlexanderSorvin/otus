#include "ipv4.hpp"

ipv4::ipv4(const std::vector<std::string> &ip)
{
    if (ip.size() != ipv4::v4)
        throw std::invalid_argument("ip.size in vector<string> is not " + std::to_string(ipv4::v4));

    for (auto i = 0; i < ipv4::v4; i++)
    {
        auto byte = std::stol(ip[i]);
        if (byte > 256 && byte < 0)
            throw std::out_of_range("ip byte is less 0 or more 255");
        
        this->byte[i] = byte;
        this->ip = byte << (ipv4::v4 - i - 1) * 8;
    }
}

bool ipv4::operator==(const ipv4& ip)
{
    return this->ip == ip.ip;
}

bool ipv4::filter(const std::initializer_list<uint8_t>& f)
{
    if (f.size() > ipv4::v4)
        throw std::invalid_argument("filter.size is more " + std::to_string(v4));

    if (f.size() == 0)
        throw std::invalid_argument("filter.size is null");

    uint32_t findMask = 0;
    auto offset = ipv4::v4 - 1;
    for (auto i : f)
    {
        findMask = i << offset--;
    }

    // Можно было через строки сравнивать, собирая массив byte[ipv4::v4 + 1]
    return (findMask & ip) == findMask;
}

bool ipv4::filter_any(const std::initializer_list<uint8_t>& f)
{
    if (f.size() > ipv4::v4)
        throw std::invalid_argument("filter.size is more " + std::to_string(v4));

    if (f.size() == 0)
        throw std::invalid_argument("filter.size is null");

    uint32_t findMask = 0;
    auto offset = f.size() - 1;
    for (auto i : f)
    {
        findMask = i << offset--;
    }

    bool result = false;

    for (auto i = 0; !result && i < ipv4::v4 - f.size(); i++)
    {
        result = ((findMask << i) & ip) == findMask;
    }

    return result;
}

std::ostream& operator<< (std::ostream &out, const ipv4 &ip)
{
    out << ip.byte[0] << "." << ip.byte[1] << "." << ip.byte[2] << "." << ip.byte[3];
    return out;
}

bool operator<(const ipv4& ip1, const ipv4& ip2)
{
    return ip1.ip < ip2.ip;
}