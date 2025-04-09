#pragma once
#include <functional>

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class Registry {
public:
    virtual void virtual_0();
    virtual void virtual_1();
    virtual void virtual_2();
    virtual void virtual_3();
    virtual void virtual_4();

    char fill[0x50 - 0x8];
};