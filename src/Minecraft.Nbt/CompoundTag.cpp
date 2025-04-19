//
// Created by DexrnZacAttack on 4/18/2025.
//

#include "CompoundTag.h"

// NON_MATCHING
void CompoundTag::putBoolean(const std::wstring& name, bool value) {
    this->putByte(name, value);
}

// NON_MATCHING
void CompoundTag::putByte(const std::wstring& name, byte value) {
    Tag* t = this->get(name);
    // call some weird vfunc here
    // todo continue when not fried
}