#pragma once

#include <cstddef>
#include <stdexcept>

template <size_t size_object>
class PoolControlBlock
{
public:
    PoolControlBlock(size_t count_elements_in_pool);
    ~PoolControlBlock();

    PoolControlBlock(const PoolControlBlock&) = default;
    PoolControlBlock(PoolControlBlock&&) = default;
    PoolControlBlock& operator=(const PoolControlBlock&) = default;
    PoolControlBlock& operator=(PoolControlBlock&&) = default;

    void *allocate(std::size_t n);
    void deallocate(void *p, std::size_t n);

    void reseve(size_t count);

protected:
    void * data;

    void * getNextData(void * data);
};

template <size_t size_object>
PoolControlBlock<size_object>::PoolControlBlock(size_t count_elements_in_pool)
{
    static_assert(size_object > 0, "size_object is not less 1");

    reseve(count_elements_in_pool);
}

template <size_t size_object>
PoolControlBlock<size_object>::~PoolControlBlock()
{
    
}

template <size_t size_object>
void *PoolControlBlock<size_object>::allocate(std::size_t n)
{
    if (n == 0)
       throw std::logic_error("pool is not allocate 0 elements");

    if (n > 1)
        throw std::logic_error("pool is not allocate more 1 element");

    if (data == nullptr)
        throw std::logic_error("pool is over");
    
    auto result = data;
    data = getNextData(data);

    return result;
}

template <size_t size_object>
void PoolControlBlock<size_object>::deallocate(void *p, [[maybe_unused]]std::size_t n)
{
    *reinterpret_cast<void **>(p) = data;
    data = p;
}

template <size_t size_object>
void PoolControlBlock<size_object>::reseve(size_t count)
{
    for (size_t i = 0; i < count; i++)
        deallocate(new char[size_object], 1);
}

template <size_t size_object>
void * PoolControlBlock<size_object>::getNextData(void * data)
{
    return *reinterpret_cast<void **>(data);
}