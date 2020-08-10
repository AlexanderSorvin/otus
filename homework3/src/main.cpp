#include "print_ip.hpp"
#include <vector>
#include <list>

int main()
{
    // -Печать адреса как  char(-1)
    print_ip(char(-1));
    // -Печать адреса как  short(0)
    print_ip(short(0));
    // -Печать адреса как  int(2130706433)
    print_ip(int(2130706433));
    // -Печать адреса как  long(8875824491850138409)
    print_ip(long(8875824491850138409));
    // -Печать адреса как  std::string
    print_ip(std::string("trololo"));
    // -Печать адреса как  std::vector
    print_ip(std::vector<int>{5, 4, 3, 2, 1});
    // -Печать адреса как  std::list
    print_ip(std::list<std::string>{"45", "44", "43", "42", "41"});
    // -Опционально. Печать адреса как  std::tuple
    print_ip(std::tuple<uint64_t, uint64_t, uint64_t>{202, 54, 22});
    // -Опционально. Печать адреса как  std::tuple
    // print_ip(std::tuple<uint64_t, std::string, uint64_t>{202, "54", 22});

    return 0;
}