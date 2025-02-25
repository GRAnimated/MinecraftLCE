#pragma once
#include "Minecraft.World/Registry.h"

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
class SimpleRegistry : public Registry<Key, Value, Hash, KeyEqual> {
public:
};