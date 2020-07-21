#include <memory>
#include "PoolControlBlock.hpp"

template <size_t size_object, size_t size_pool>
struct ListPoolControlBlock
{
    ListPoolControlBlock() = default;
    ~ListPoolControlBlock() = default;

    void *allocate(std::size_t n);
    bool deallocate(void *p, std::size_t n);

    PoolControlBlock<size_object, size_pool> controlBlock;
    std::unique_ptr<ListPoolControlBlock> nextlist;
};

template <size_t size_object, size_t size_pool>
void *ListPoolControlBlock<size_object, size_pool>::allocate(std::size_t n)
{
    // Не стал проверять на n > size_pool. Здесь считается, что данное условие будет недостижимым

    void *result = controlBlock.allocate(n);
    if (result == nullptr)
    {
        if (nextlist == nullptr)
            nextlist.reset(new ListPoolControlBlock());
        nextlist->allocate(n);
    }

    return result;
}

template <size_t size_object, size_t size_pool>
bool ListPoolControlBlock<size_object, size_pool>::deallocate(
    void *p, std::size_t n)
{
    bool result = false;

    if (controlBlock.IsPointIn(p))
    {
        controlBlock.deallocate(p, n);
        result = true;
    }
    else if (nextlist != nullptr)
    {
        if (nextlist->deallocate(p, n) &&
            nextlist->controlBlock.IsEmpty())
        {
            nextlist.reset(nextlist->nextlist.release());
        }
    }
    else
    {
        throw std::logic_error("Block is not allocate");
    }

    return result;
}