#pragma once
#include "net/minecraft/client/resources/IdMap.h"
#include "net/minecraft/client/resources/SimpleRegistry.h"

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>, typename HashValue = std::hash<Value>,
          typename ValueEqual = std::equal_to<Value>>
class MappedRegistry : public SimpleRegistry<Key, Value>, public IdMap<Value> {
public:
    // override everything from base, also this is wrong for whatever reason, idk how to fix it
    // properly
    virtual void registerMapping(int id, Key key, Value value);
    virtual Key getKey(Value) const;
    virtual int getId(Value) override;
    virtual Value byId(int) override;
    virtual bool containsId(int);
};

template <typename Key, typename Value, typename KeyHash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>, typename ValueHash = std::hash<Value>,
          typename ValueEqual = std::equal_to<Value>>
class DefaultedMappedRegistry : public MappedRegistry<Key, Value> {
public:
    DefaultedMappedRegistry();

    // marked as virtual as if DefaultedMappedRegistry is going to be overriden one more time it
    // won't allow you to overwrite
    virtual Value get(Key) override;
    virtual void registerKey(Key key, Value value) override;
    virtual std::unordered_map<Key, Value>* keySet() override;
    virtual Value* getRandom(Random*) override;
    virtual bool containsKey(Key) override;
};