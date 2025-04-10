#pragma once
#include "Minecraft.Client/resources/SimpleRegistry.h"
#include "Minecraft.Client/resources/IdMap.h"

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename HashValue = std::hash<Value>, typename ValueEqual = std::equal_to<Value>>
class MappedRegistry : public SimpleRegistry<Key, Value>, public IdMap<Value>{
public:
    // override everything from base, also this is wrong for whatever reason, idk how to fix it properly

    virtual void shit();
    virtual void registerMapping(int id, Key key, Value value);
};

template <typename KeyType, typename ValueType, typename KeyHash = std::hash<KeyType>, typename KeyEqual = std::equal_to<KeyType>, typename ValueHash = std::hash<ValueType>,
          typename ValueEqual = std::equal_to<ValueType>>
class DefaultedMappedRegistry : public MappedRegistry<KeyType, ValueType> {
public:
    DefaultedMappedRegistry();

    ValueType get(KeyType) override;
    void registerKey(KeyType, ValueType) override;
    void keySet() override;
    ValueType getRandom(Random*) override;
    bool containsKey(KeyType) override;
};