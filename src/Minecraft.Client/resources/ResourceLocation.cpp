#include "Minecraft.Client/resources/ResourceLocation.h"
#include <string>

bool ResourceLocation::operator==(const ResourceLocation* other) const {
    if (this == other)
        return true;

    return !this->getNamespace().compare(other->getNamespace()) && !this->getPath().compare(other->getPath());
}

bool ResourceLocation::operator==(const ResourceLocation& other) const {
    return !this->getNamespace().compare(other.getNamespace()) && !this->getPath().compare(other.getPath());
}

std::wstring ResourceLocation::toString() const {
    return this->mNamespace + L':' + this->mPath;
}

const std::wstring& ResourceLocation::getNamespace() const {
    return this->mNamespace;
}

const std::wstring& ResourceLocation::getPath() const {
    return this->mPath;
}