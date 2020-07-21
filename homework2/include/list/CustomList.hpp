#pragma once

#include <memory>

template <typename T>
struct ListNode
{
    ListNode *next;
    ListNode *prev;
    T value;
};

template <typename T, class Allocator = std::allocator<ListNode<T>>>
class CustomList
{
protected:
    ListNode<T> * first;
    ListNode<T> * last;
};