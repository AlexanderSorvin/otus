
#pragma once

#include <memory>
#include <list>
#include "PoolControlBlock.hpp"

template <typename T, size_t size_pool>
class PoolAllocator
{
public:
    using value_type = T;
    using size_type = size_t;

    template <typename U>
    struct rebind
    {
        typedef PoolAllocator<U, size_pool> other;
    };

    PoolAllocator<T, size_pool>() noexcept;

    template <typename U>
    PoolAllocator<T, size_pool>(const PoolAllocator<U, size_pool> &other) noexcept;

    T *allocate(std::size_t n, const void *hint = nullptr);
    void deallocate(T *p, std::size_t n);

    template <typename T1, typename T2, size_t size_of_pool>
    friend inline bool operator==(
        const PoolAllocator<T1, size_of_pool> &,
        const PoolAllocator<T2, size_of_pool> &) noexcept;

protected:
    struct listPoolControlBlock
    {
        void *allocate(std::size_t n);
        void deallocate(T *p, std::size_t n);

        PoolControlBlock<sizeof(T), size_pool> controlBlock;
        std::unique_ptr<listPoolControlBlock> nextlist;
    };

    std::shared_ptr<listPoolControlBlock> list;
};

template <typename T, size_t size_pool>
PoolAllocator<T, size_pool>::PoolAllocator() noexcept
    : list(std::make_shared<listPoolControlBlock>())
{
}

template <typename T, size_t size_pool>
template <typename U>
PoolAllocator<T, size_pool>::PoolAllocator(
    const PoolAllocator<U, size_pool> &other) noexcept
    : list(sizeof(T) == sizeof(U) ? list
                                  : std::make_shared<PoolAllocator<U, size_pool>::PoolControlBlock>())
{
}

template <typename T, size_t size_pool>
T *PoolAllocator<T, size_pool>::allocate(
    std::size_t n, const void *hint)
{
    if (n > size_pool)
    {
        throw std::bad_alloc();
    }
    return reinterpret_cast<T*>(list->controlBlock.allocate(n));
}

template <typename T, size_t size_pool>
void PoolAllocator<T, size_pool>::deallocate(
    T *p, std::size_t n)
{
    list->deallocate(p, n);
}

template <typename T, size_t size_pool>
void *PoolAllocator<T, size_pool>::listPoolControlBlock::allocate(std::size_t n)
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

template <typename T, size_t size_pool>
void PoolAllocator<T, size_pool>::listPoolControlBlock::deallocate(
    T *p, std::size_t n)
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

template <typename T1, typename T2, size_t size_pool>
inline bool operator==(
    const PoolAllocator<T1, size_pool> &a,
    const PoolAllocator<T2, size_pool> &b) noexcept
{
    return a.controlBlock.get() == b.controlBlock.get();
}