#pragma once
#include <unordered_map>
#include "Minecraft.Client/resources/Registry.h"

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class SimpleRegistry : public Registry<Key, Value> {
public:
    virtual Value get(Key) override;
    virtual void registerKey(Key key, Value value) override;
    virtual std::unordered_map<Key, Value> keySet() override;
    virtual Value getRandom(Random*) override;
    virtual bool containsKey(Key);

    char fill[0x50 - 0x8];
    //void* qword8;
    //std::unordered_map<Key, Value> mMap;
};