#pragma once
#include <functional>
#include <unordered_map>

class Random;

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class Registry {
public:
    virtual Value get(const Key&) = 0;
    virtual void registerKey(const Key& key, const Value& value) = 0;
    virtual std::unordered_map<Key, Value> keySet() = 0;
    virtual Value getRandom(Random*) = 0;
    //virtual bool containsKey(const Key&) = 0;
};