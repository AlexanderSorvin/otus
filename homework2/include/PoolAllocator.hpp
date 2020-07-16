
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

    template <typename U, typename = typename std::enable_if<sizeof(T) == sizeof(U)>::type>
    PoolAllocator<T, size_pool>(const PoolAllocator<U, size_pool> &other) noexcept;

    T *allocate(std::size_t n, const void *hint = 0);
    void deallocate(T *p, std::size_t n);

    template <typename T1, typename T2, size_t size_of_pool>
    friend inline bool operator==(
        const PoolAllocator<T1, size_of_pool> &,
        const PoolAllocator<T2, size_of_pool> &) noexcept;

protected:
    std::shared_ptr<PoolControlBlock<sizeof(T), size_pool>> controlBlock;
};

template <typename T, size_t size_pool>
PoolAllocator<T, size_pool>::PoolAllocator() noexcept
    : controlBlock(std::make_shared<PoolControlBlock<sizeof(T), size_pool>>())
{
}

template <typename T, size_t size_pool>
template <typename U, typename>
PoolAllocator<T, size_pool>::PoolAllocator(
    const PoolAllocator<U, size_pool> &other) noexcept
    : controlBlock(controlBlock)
{
}

template <typename T, size_t size_pool>
T *PoolAllocator<T, size_pool>::allocate(
    std::size_t n, const void *hint)
{
    return reinterpret_cast<T *>(controlBlock->allocate(n));
}

template <typename T, size_t size_pool>
void PoolAllocator<T, size_pool>::deallocate(
    T *p, std::size_t n)
{
    controlBlock->deallocate(p, n);
}

template <typename T1, typename T2, size_t size_pool>
inline bool operator==(
    const PoolAllocator<T1, size_pool> &a,
    const PoolAllocator<T2, size_pool> &b) noexcept
{
    return a.controlBlock.get() == b.controlBlock.get();
}