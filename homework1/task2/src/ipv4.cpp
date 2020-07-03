#include "ipv4.hpp"

ipv4::ipv4(const std::vector<std::string> &ip)
{
    if (ip.size() != ipv4::v4)
        throw std::invalid_argument("ip.size in vector<string> is not " + std::to_string(ipv4::v4));

    for (auto i = 0; i < ipv4::v4; i++)
    {
        auto byte = std::stol(ip[i]);
        if (byte > 255 || byte < 0)
            throw std::out_of_range("ip byte is less 0 or more 255");
        
        this->byte[i] = byte;
        this->ip += byte << (ipv4::v4 - i - 1) * 8;
    }
}

bool ipv4::filter(const std::initializer_list<uint8_t>& f) const
{
    if (f.size() > ipv4::v4)
        throw std::invalid_argument("filter.size is more " + std::to_string(v4));

    if (f.size() == 0)
        throw std::invalid_argument("filter.size is null");

    uint32_t findMask = 0;
    auto offset = f.size() - 1;
    for (auto i : f)
    {
        findMask += i << (8 * offset--);
    }

    // Можно было через строки сравнивать, собирая массив (по сути строку) byte[ipv4::v4 + 1],
    // где последний элемент массива был бы равен 0.
    // Логика немного изменится, хотя конструкции, наверное, будут более читабельны
    return (ip >> (8 * (ipv4::v4 - f.size()))) == findMask;
}

bool ipv4::filter_any(const std::initializer_list<uint8_t>& f) const
{
    if (f.size() > ipv4::v4)
        throw std::invalid_argument("filter.size is more " + std::to_string(v4));

    if (f.size() == 0)
        throw std::invalid_argument("filter.size is null");

    uint32_t findMask = 0;
    auto offset = f.size() - 1;
    for (auto i : f)
    {
        findMask += i << (8 * offset--);
    }

    bool result = false;

    for (auto i = 0; !result && i <= ipv4::v4 - f.size(); i++)
    {
        result = (ip << (8 * i) >> (8 * (ipv4::v4 - f.size()))) == findMask;
    }

    return result;
}

std::ostream& operator<< (std::ostream &out, const ipv4 &ip)
{
    out << static_cast<int>(ip.byte[0]) << "." 
        << static_cast<int>(ip.byte[1]) << "." 
        << static_cast<int>(ip.byte[2]) << "." 
        << static_cast<int>(ip.byte[3]);
    return out;
}

bool operator<(const ipv4& a, const ipv4& b)
{
    return a.ip < b.ip;
}

bool operator>(const ipv4& a, const ipv4& b)
{
    return a.ip > b.ip;
}

bool operator==(const ipv4& a, const ipv4& b)
{
    return a.ip == b.ip;
}