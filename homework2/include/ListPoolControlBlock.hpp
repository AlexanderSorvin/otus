#include <memory>
#include "PoolControlBlock.hpp"

template <size_t size_object, size_t size_pool>
struct listPoolControlBlock
{
    listPoolControlBlock() = default;
    ~listPoolControlBlock() = default;

    void *allocate(std::size_t n);
    void deallocate(void *p, std::size_t n);

    PoolControlBlock<size_object, size_pool> controlBlock;
    std::unique_ptr<listPoolControlBlock> nextlist;
};

template <size_t size_object, size_t size_pool>
void *listPoolControlBlock<size_object, size_pool>::allocate(std::size_t n)
{
    void *result = controlBlock.allocate();
    if (result == nullptr)
    {
        if (nextlist == nullptr)
            nextlist.reset(new listPoolControlBlock());
        nextlist->allocate(n);
    }

    return result;
}

template <size_t size_object, size_t size_pool>
void listPoolControlBlock<size_object, size_pool>::deallocate(
    void *p, std::size_t n)
{
    if (controlBlock.IsPointIn(p))
    {
        controlBlock.deallocate(p, n);
    }
    else if (nextlist != nullptr)
    {
        nextlist->deallocate(p, n);
    }
    else
    {
        throw std::logic_error("Block is not allocate");
    }
}