#include <allocator/PoolAllocator.hpp>

#include <map>
#include <vector>
#include <list>
#include <set>
#include <deque>

int main()
{
    std::map<int, int, std::less<int>, PoolAllocator<std::pair<const int, int>, 5>> map;
    map[3] = 10;
    std::vector<int, PoolAllocator<int, 5>> vector;
    std::list<int, PoolAllocator<int, 5>> list;
    std::set<int, std::less<int>, PoolAllocator<int, 5>> set;
    std::deque<int, PoolAllocator<int, 200>> deque;
    return 0;
}