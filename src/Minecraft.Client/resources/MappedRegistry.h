#pragma once

#include <functional>

class Random;

template <typename KeyType, typename ValueType, typename KeyHash = std::hash<KeyType>, typename KeyEqual = std::equal_to<KeyType>, typename ValueHash = std::hash<ValueType>,
          typename ValueEqual = std::equal_to<ValueType>>
class MappedRegistry {
public:
    MappedRegistry();

    virtual ValueType get(KeyType);
    virtual void registerKey(KeyType, ValueType);
    virtual void keySet();
    virtual ValueType getRandom(Random*);
    virtual bool containsKey(KeyType);

    KeyType getKey(ValueType) const;
    int getId(ValueType);
    ValueType byId(int);
    void registerMapping(int, KeyType, ValueType);
    bool containsId(int);
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
