#include "net/minecraft/core/System.h"
#include "net/minecraft/resources/ResourceLocation.h"
#include <cstdint>

std::int64_t ResourceLocation::hashCode() const {
    std::uint32_t namespaceHash = static_cast<std::uint32_t>(javaStringHashCode(getNamespace())) * 31u;
    int pathHash = static_cast<int>(javaStringHashCode(getPath()));
    return static_cast<std::int32_t>(namespaceHash + static_cast<std::uint32_t>(pathHash));
}
