#include "Minecraft.World/net/minecraft/world/level/block/boxed/Boxed.h"

Boxed::Boxed(const std::type_info* typeInfo) {
    this->mTypeInfo = typeInfo;
}

Boxed::~Boxed() = default;

bool Boxed::isA(const std::type_info* type) const {
    return mTypeInfo->hash_code() == type->hash_code();
}

bool Boxed::isA(const std::type_info& type) const {
    return mTypeInfo->hash_code() == type.hash_code();
}

bool Boxed::operator==(Boxed* other) const {
    return !operator==(static_cast<const Boxed*>(other));
}

bool Boxed::operator!=(const Boxed* other) const {
    return operator==(other);
}

bool Boxed::operator!=(Boxed* other) const {
    return !operator==(static_cast<const Boxed*>(other));
}
