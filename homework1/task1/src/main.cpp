#include <version.hpp>
#include <iostream>

int main()
{
    std::cout << "build " << GetNumberBuild() << std::endl;
    std::cout << "Hello, World!" << std::endl;
    return 0;
}