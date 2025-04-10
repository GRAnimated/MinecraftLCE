#pragma once
#include <unordered_map>
#include "Minecraft.Client/resources/Registry.h"

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class SimpleRegistry : public Registry<Key, Value> {
public:
    Value get(const Key&) override;
    void registerKey(const Key& key, const Value& value) override;
    std::unordered_map<Key, Value> keySet() override;
    Value getRandom(Random*) override;
    bool containsKey(const Key&);

    char fill[0x50 - 0x8];
    //void* qword8;
    //std::unordered_map<Key, Value> mMap;
};