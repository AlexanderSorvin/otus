#pragma once

#include <memory>

template <typename T, typename Alloc = std::allocator<T>, size_t k = 3>
class CustomVector
{
public:
    using iterator = T *;
    struct reverse_iterator
    {
        reverse_iterator(T *object);
        ~reverse_iterator() = default;

        reverse_iterator &operator++();
        reverse_iterator &operator--();
        reverse_iterator &operator++(int);
        reverse_iterator &operator--(int);
        reverse_iterator &operator+=(int value);
        reverse_iterator &operator-=(int value);
        bool operator==(const reverse_iterator &it);
        bool operator!=(const reverse_iterator &it);

    protected:
        T *object;
    };

    CustomVector() = default;
    ~CustomVector();

    T &operator[](int index);

    void push_back(T &&element);
    void push(iterator it, const T &element);

    void pop_back();
    iterator pop(iterator it);

    iterator begin() noexcept;
    iterator end() noexcept;

    reverse_iterator rbegin() noexcept;
    reverse_iterator rend() noexcept;

    size_t size() const noexcept;
    bool empty() const noexcept;

    void resize(size_t size);
    void reserve(size_t size);

protected:
    T *_data = nullptr;
    size_t _size = 0;
    size_t _reserve = 0;
    Alloc allocator;

    void move_elements(size_t count_elements);
};

template <typename T, typename Alloc, size_t k>
CustomVector<T, Alloc, k>::reverse_iterator::reverse_iterator(T *object)
    : object(object)
{
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::reverse_iterator &CustomVector<T, Alloc, k>::reverse_iterator::operator++()
{
    object--;
    return this;
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::reverse_iterator &CustomVector<T, Alloc, k>::reverse_iterator::operator--()
{
    object++;
    return this;
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::reverse_iterator &CustomVector<T, Alloc, k>::reverse_iterator::operator++(int)
{
    --object;
    return this;
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::reverse_iterator &CustomVector<T, Alloc, k>::reverse_iterator::operator--(int)
{
    ++object;
    return this;
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::reverse_iterator &CustomVector<T, Alloc, k>::reverse_iterator::operator+=(int value)
{
    object -= value;
    return this;
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::reverse_iterator &CustomVector<T, Alloc, k>::reverse_iterator::operator-=(int value)
{
    object += value;
    return this;
}

template <typename T, typename Alloc, size_t k>
bool CustomVector<T, Alloc, k>::reverse_iterator::operator==(const reverse_iterator &it)
{
    return object == it.object;
}

template <typename T, typename Alloc, size_t k>
bool CustomVector<T, Alloc, k>::reverse_iterator::operator!=(const reverse_iterator &it)
{
    return object != it.object;
}

template <typename T, typename Alloc, size_t k>
CustomVector<T, Alloc, k>::~CustomVector()
{
    delete[] _data;
}

template <typename T, typename Alloc, size_t k>
T &CustomVector<T, Alloc, k>::operator[](int index)
{
    return _data[index];
}

template <typename T, typename Alloc, size_t k>
void CustomVector<T, Alloc, k>::push_back(T &&element)
{
    if (_reserve < _size + 1)
    {
        move_elements(_reserve > 0 ? _reserve * k : 1);
    }
    ::new (_data + _size++) T(std::forward<T>(element));
}

template <typename T, typename Alloc, size_t k>
void CustomVector<T, Alloc, k>::push(CustomVector<T, Alloc, k>::iterator it, const T &element)
{
    for (; it != end(); ++it)
    {
        std::swap(*it, element);
    }

    push_back(element);
}

template <typename T, typename Alloc, size_t k>
void CustomVector<T, Alloc, k>::pop_back()
{
    (_data + --_size)->~T();
}

template <typename T, typename Alloc, size_t k>
T *CustomVector<T, Alloc, k>::pop(CustomVector<T, Alloc, k>::iterator it)
{
    for (auto i = it; i != --end(); ++i)
    {
        std::swap(*i, *(i + 1));
    }

    pop_back();
    return it;
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::iterator CustomVector<T, Alloc, k>::begin() noexcept
{
    return _data;
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::iterator CustomVector<T, Alloc, k>::end() noexcept
{
    return _data + size;
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::reverse_iterator CustomVector<T, Alloc, k>::rbegin() noexcept
{
    return CustomVector<T, Alloc, k>::reverse_iterator(_data + size);
}

template <typename T, typename Alloc, size_t k>
typename CustomVector<T, Alloc, k>::reverse_iterator CustomVector<T, Alloc, k>::rend() noexcept
{
    return CustomVector<T, Alloc, k>::reverse_iterator(_data);
}

template <typename T, typename Alloc, size_t k>
size_t CustomVector<T, Alloc, k>::size() const noexcept
{
    return _size;
}

template <typename T, typename Alloc, size_t k>
bool CustomVector<T, Alloc, k>::empty() const noexcept
{
    return _size > 0;
}

template <typename T, typename Alloc, size_t k>
void CustomVector<T, Alloc, k>::resize(size_t size)
{
    while (_size > size)
    {
        pop_back();
    }

    while (_size < size)
    {
        push_back(T());
    }
}

template <typename T, typename Alloc, size_t k>
void CustomVector<T, Alloc, k>::reserve(size_t size)
{
    if (_reserve > size)
    {
        while (_size > size)
        {
            pop_back();
        }

        move_elements(size);
    }
    else if (_reserve < size)
    {
        move_elements(size);
    }
}

template <typename T, typename Alloc, size_t k>
void CustomVector<T, Alloc, k>::move_elements(size_t count_elements)
{
    auto newdata = allocator.allocate(count_elements);
    for (size_t i = 0; i < _size; ++i)
    {
        newdata[i] = std::move(_data[i]);
    }
    delete[] _data;
    _data = newdata;
}