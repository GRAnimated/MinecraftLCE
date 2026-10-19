#include "net/minecraft/resources/ResourceLocation.h"

#include "net/minecraft/core/System.h"
#include <cstdint>

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
    return this->m_namespace + L':' + this->m_path;
}

const std::wstring& ResourceLocation::getNamespace() const {
    return this->m_namespace;
}

const std::wstring& ResourceLocation::getPath() const {
    return this->m_path;
}

// name guessed
std::int64_t ResourceLocation::hashCode() const {
    std::uint32_t namespaceHash = static_cast<std::uint32_t>(javaStringHashCode(getNamespace())) * 31u;
    int pathHash = static_cast<int>(javaStringHashCode(getPath()));
    return static_cast<std::int32_t>(namespaceHash + static_cast<std::uint32_t>(pathHash));
}
