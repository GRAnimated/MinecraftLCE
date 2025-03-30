#pragma once
#include "Minecraft.Core/SimpleRegistry.h"
#include "Minecraft.Core/IdMap.h"

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>, typename HashValue = std::hash<Value>, typename ValueEqual = std::equal_to<Value>>
class MappedRegistry : public SimpleRegistry<Key, Value>, IdMap<Value>{

};