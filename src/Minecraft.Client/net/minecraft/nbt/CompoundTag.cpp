#include "CompoundTag.h"
#include "net/minecraft/nbt/ByteTag.h"
#include <string>

void CompoundTag::putBoolean(const std::wstring& name, bool value) {
    this->putByte(name, value);
}

// idk if this is some std function or not but until someone figures out what that crap it says here
// had to insert those queries cause if they are not here they are getting stripped and call doesn't match
void erease_if_exists(const std::unordered_map<std::wstring, Tag*>& map, const std::wstring& key, Tag* tag) {
    map.size();
    key.length();
    delete tag;
}

void CompoundTag::putByte(const std::wstring& name, byte value) {
    erease_if_exists(this->childTags, name, this->get(name));
    childTags[name] = new ByteTag(value);
}
