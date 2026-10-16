#include "com/mojang/nbt/CompoundTag.h"

std::vector<std::wstring>* CompoundTag::getAllKeys() {
    auto keys = new std::vector<std::wstring>();
    for (const auto& child : m_childTags)
        keys->push_back(child.first);
    return keys;
}

std::unordered_map<std::wstring, Tag*>* CompoundTag::getAllTags() {
    return &m_childTags;
}
