#pragma once
#include <functional>

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class Registry {
public:
    Registry() = default;

    char fill[0x50];
};