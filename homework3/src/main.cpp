#include "print_ip.hpp"
#include <vector>
#include <list>

namespace hw3 = homework3;

int main()
{
    // -Печать адреса как  char(-1)
    hw3::print_ip(char(-1));
    std::cout << std::endl;

    // -Печать адреса как  short(0)
    hw3::print_ip(short(0));
    std::cout << std::endl;

    // -Печать адреса как  int(2130706433)
    hw3::print_ip(int(2130706433));
    std::cout << std::endl;

    // -Печать адреса как  long(8875824491850138409)
    hw3::print_ip(long(8875824491850138409));
    std::cout << std::endl;

    // -Печать адреса как  std::string
    hw3::print_ip(std::string("trololo"));
    std::cout << std::endl;

    // -Печать адреса как  std::vector
    hw3::print_ip(std::vector<int>{5, 4, 3, 2, 1});
    std::cout << std::endl;

    // -Печать адреса как  std::list
    hw3::print_ip(std::list<std::string>{"45", "44", "43", "42", "41"});
    std::cout << std::endl;

    // -Опционально. Печать адреса как  std::tuple
    hw3::print_ip(std::tuple<uint64_t, uint64_t, uint64_t>{202, 54, 22});
    std::cout << std::endl;
    
    // -Опционально. Печать адреса как  std::tuple
    // print_ip(std::tuple<uint64_t, std::string, uint64_t>{202, "54", 22});

    return 0;
}