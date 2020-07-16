#pragma once

template <size_t size_object, size_t size_pool>
class PoolControlBlock
{
public:
    PoolControlBlock();

    PoolControlBlock(const PoolControlBlock&) = default;
    PoolControlBlock(PoolControlBlock&&) = default;
    PoolControlBlock& operator=(const PoolControlBlock&) = default;
    PoolControlBlock& operator=(PoolControlBlock&&) = default;

    void *allocate(std::size_t n) noexcept;
    void deallocate(void *p, std::size_t n);

    bool IsPointIn(const void *hint) noexcept;
    bool IsEmpty() noexcept;

protected:
    uint8_t mask[size_pool / 8 + (size_pool % 8 ? 1 : 0)] = {};
    uint8_t data[size_object * size_pool];
};

template <size_t size_object, size_t size_pool>
PoolControlBlock<size_object, size_pool>::PoolControlBlock()
{
    static_assert(size_object > 0, "size_object is not less 1");
    static_assert(size_pool > 0, "size_pool is not less 1");
}

template <size_t size_object, size_t size_pool>
void *PoolControlBlock<size_object, size_pool>::allocate(std::size_t n) noexcept
{
    for (auto i = 0; i < size_pool - n + 1; i++)
    {
        auto j = 0;
        for (; j < n; j++)
        {
            if (mask[(i + j) / 8] >> (7 - (i + j) % 8) & 0x1)
                break;
        }

        // Если свободное место нужного размера найдено
        if (j == n)
        {
            for (j = 0; j < n; j++)
            {
                mask[(i + j) / 8] |= (1 << (7 - (i + j) % 8));
            }
            return data + size_object * i;
        }
    }

    // Свободное место данного размера не найдено
    return nullptr;
}

template <size_t size_object, size_t size_pool>
void PoolControlBlock<size_object, size_pool>::deallocate(void *p, std::size_t n)
{
    if (!IsPointIn(p))
    {
        throw std::invalid_argument("p is not in controlBlock");
    }

    auto i = (static_cast<uint8_t *>(p) - data) / size_object;

    if (i + n > size_pool)
    {
        throw std::invalid_argument("n is long");
    }

    for (auto j = 0; j < n; j++)
    {
        mask[(i + j) / 8] &= ~(1 << (7 - (i + j) % 8));
    }
}

template <size_t size_object, size_t size_pool>
bool PoolControlBlock<size_object, size_pool>::IsPointIn(const void *hint) noexcept
{
    return hint >= &data && hint < data + size_object * size_pool;
}

template <size_t size_object, size_t size_pool>
bool PoolControlBlock<size_object, size_pool>::IsEmpty() noexcept
{
    for (auto i = 0; i < sizeof(mask); i++)
    {
        if (mask[i])
            return false;
    }

    return true;
}