#pragma once
#include "net/minecraft/client/resources/Registry.h"
#include "net/minecraft/world/Random.h"
#include <set>
#include <unordered_map>

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
class SimpleRegistry : public Registry<Key, Value> {
public:
    virtual Value get(Key key) override { return this->mMap.at(key); }
    virtual void registerKey(Key key, Value value) override {
        this->mMap[key] = value;
        this->set.insert(value);
    }
    virtual std::unordered_map<Key, Value>* keySet() override { return &this->mMap; }
    virtual Value* getRandom(Random* random) override;
    virtual bool containsKey(Key key) { return this->mMap.find(key) != this->mMap.end(); }

    // char filler[0x50 - 0x8];
    void* qword8;
    std::unordered_map<Key, Value> mMap;
    std::set<Value> set;
};