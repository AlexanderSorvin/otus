
#pragma once
#include "ListPoolControlBlock.hpp"

namespace detail
{
    template <size_t size_object, size_t size_pool>
    struct _PoolAllocator
    {
        _PoolAllocator() = default;

        _PoolAllocator(std::shared_ptr<listPoolControlBlock<size_object, size_pool>> &&list)
            : list(list)
        {
        }

        _PoolAllocator(const _PoolAllocator &) = default;

    protected:
        std::shared_ptr<listPoolControlBlock<size_object, size_pool>> list;
    };

} // namespace detail

template <typename T, size_t size_pool>
class PoolAllocator : public detail::_PoolAllocator<sizeof(T), size_pool>
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

    PoolAllocator<T, size_pool>() noexcept;

    template <typename U>
    PoolAllocator<T, size_pool>(const PoolAllocator<U, size_pool> &other) noexcept;

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

template <typename T, size_t size_pool>
PoolAllocator<T, size_pool>::PoolAllocator() noexcept
    : detail::_PoolAllocator<sizeof(T), size_pool>(
          std::make_shared<listPoolControlBlock<sizeof(T), size_pool>>())
{
}

template <typename T, size_t size_pool>
template <typename U>
PoolAllocator<T, size_pool>::PoolAllocator(
    const PoolAllocator<U, size_pool> &other) noexcept
    : detail::_PoolAllocator<sizeof(T), size_pool>((sizeof(T) == sizeof(U))
                                                       ? reinterpret_cast<const detail::_PoolAllocator<sizeof(T), size_pool> &>(other)
                                                       : std::make_shared<listPoolControlBlock<sizeof(T), size_pool>>())
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
    return reinterpret_cast<T *>(this->list->controlBlock.allocate(n));
}

template <typename T, size_t size_pool>
void PoolAllocator<T, size_pool>::deallocate(
    T *p, std::size_t n)
{
    this->list->deallocate(p, n);
}

template <typename T, size_t size_pool>
template <typename... Args>
void PoolAllocator<T, size_pool>::construct(T *p, Args &&... args)
{
    ::new ((void *)p) T(std::forward<Args>(args)...);
}

template <typename T, size_t size_pool>
void PoolAllocator<T, size_pool>::destroy(T *p)
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