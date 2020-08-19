
#pragma once

#include "allocator/PoolControlBlock.hpp"
#include <memory>

namespace detail
{
    template <size_t size_object>
    struct _PoolAllocator
    {
        _PoolAllocator() = default;

        _PoolAllocator(std::shared_ptr<PoolControlBlock<size_object>> &&list)
            : list(list)
        {
        }

        _PoolAllocator(const _PoolAllocator &) = default;

    protected:
        std::shared_ptr<PoolControlBlock<size_object>> list;
    };

} // namespace detail

template <typename T, size_t size_pool, typename enable = typename std::enable_if<sizeof(void *) <= sizeof(T)>::type>
class PoolAllocator : public detail::_PoolAllocator<sizeof(T)>
{
public:
    using value_type = T;
    using size_type = size_t;
    using pointer = T *;
    using const_pointer = const T *;
    using reference = T &;
    using const_reference = const T &;

    template <typename U>
    struct rebind
    {
        typedef PoolAllocator<U, size_pool> other;
    };

    PoolAllocator() noexcept;

    template <typename U>
    PoolAllocator(const PoolAllocator<U, size_pool> &other) noexcept;

    T *allocate(std::size_t n, const void *hint = nullptr);
    void deallocate(T *p, std::size_t n);

    template <typename... Args>
    void construct(T *p, Args &&... args);

    void destroy(T *p);

    template <typename T1, typename T2, size_t size_of_pool>
    friend inline bool operator==(
        const PoolAllocator<T1, size_of_pool> &,
        const PoolAllocator<T2, size_of_pool> &) noexcept;
};

template <typename T1, typename T2, size_t size_of_pool>
inline bool operator!=(
    const PoolAllocator<T1, size_of_pool> &,
    const PoolAllocator<T2, size_of_pool> &) noexcept;

template <typename T, size_t size_pool, typename enable>
PoolAllocator<T, size_pool, enable>::PoolAllocator() noexcept
    : detail::_PoolAllocator<sizeof(T)>(
          std::make_shared<PoolControlBlock<sizeof(T)>>(size_pool))
{
}

template <typename T, size_t size_pool, typename enable>
template <typename U>
PoolAllocator<T, size_pool, enable>::PoolAllocator(
    const PoolAllocator<U, size_pool> &other) noexcept
    : detail::_PoolAllocator<sizeof(T)>((sizeof(T) == sizeof(U))
                                            ? reinterpret_cast<const detail::_PoolAllocator<sizeof(T)> &>(other)
                                            : std::make_shared<PoolControlBlock<sizeof(T)>>(size_pool))
{
}

template <typename T, size_t size_pool, typename enable>
T *PoolAllocator<T, size_pool, enable>::allocate(
    std::size_t n, [[maybe_unused]] const void *hint)
{
    if (n > size_pool)
    {
        throw std::bad_alloc();
    }
    return reinterpret_cast<T *>(this->list->allocate(n));
}

template <typename T, size_t size_pool, typename enable>
void PoolAllocator<T, size_pool, enable>::deallocate(
    T *p, std::size_t n)
{
    this->list->deallocate(p, n);
}

template <typename T, size_t size_pool, typename enable>
template <typename... Args>
void PoolAllocator<T, size_pool, enable>::construct(T *p, Args &&... args)
{
    ::new ((void *)p) T(std::forward<Args>(args)...);
}

template <typename T, size_t size_pool, typename enable>
void PoolAllocator<T, size_pool, enable>::destroy(T *p)
{
    p->~T();
}

template <typename T1, typename T2, size_t size_pool>
inline bool operator==(
    const PoolAllocator<T1, size_pool> &a,
    const PoolAllocator<T2, size_pool> &b) noexcept
{
    return static_cast<void *>(a.list.get()) ==
           static_cast<void *>(b.list.get());
}

template <typename T1, typename T2, size_t size_pool>
inline bool operator!=(
    const PoolAllocator<T1, size_pool> &a,
    const PoolAllocator<T2, size_pool> &b) noexcept
{
    return !(a == b);
}