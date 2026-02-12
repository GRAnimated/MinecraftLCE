#pragma once

#include "net/minecraft/client/resources/Registry.h"
#include "net/minecraft/world/Random.h"
#include <set>
#include <unordered_map>

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
class SimpleRegistry : public Registry<Key, Value> {
public:
    Value get(Key key) override { return this->m_map.at(key); }
    void registerKey(Key key, Value value) override {
        this->m_map[key] = value;
        this->m_set.insert(value);
    }
    std::unordered_map<Key, Value>* keySet() override { return &this->m_map; }
    Value* getRandom(Random* random) override;
    virtual bool containsKey(Key key) { return this->m_map.find(key) != this->m_map.end(); }

    // char filler[0x50 - 0x8];
    void* m_qword8;
    std::unordered_map<Key, Value> m_map;
    std::set<Value> m_set;
};
