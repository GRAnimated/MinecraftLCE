#pragma once

#include "net/minecraft/client/resources/MappedRegistry.h"
#include "net/minecraft/world/entity/Entity.h"
#include <string>

class ResourceLocation {
public:
    static MappedRegistry<ResourceLocation, eINSTANCEOF, std::hash<ResourceLocation>,
                          std::equal_to<ResourceLocation>, std::hash<eINSTANCEOF>, std::equal_to<eINSTANCEOF>>
        Registry;

    ResourceLocation();
    ResourceLocation(const std::wstring&);
    ResourceLocation(const ResourceLocation&);
    ResourceLocation& operator=(const ResourceLocation&);
    ~ResourceLocation();

    bool operator==(const ResourceLocation* other) const;
    // idk if this function below is in actual LCE, let's leave it as for now to make ResourceLocation to be
    // able to be in unordered_map
    bool operator==(const ResourceLocation& other) const;

    const std::wstring& getNamespace() const;
    const std::wstring& getPath() const;
    std::int64_t hashCode() const;

    virtual std::wstring toString() const;

    char m_gap8[16];
    std::wstring m_path;
    std::wstring m_namespace;
    char m_byte48;
};

template <>
struct std::equal_to<ResourceLocation> {
    // name guessed
    // NON_MATCHING | score: 5 (lower is better)
    bool operator()(const ResourceLocation& lhs, const ResourceLocation& rhs) const {
        return lhs.operator==(&rhs);
    }
};

/** Uses the original LCE resource-key hash.
 */
template <>
struct std::hash<ResourceLocation> {
    // NON_MATCHING | score: 5 (lower is better)
    std::size_t operator()(const ResourceLocation& rl) const { return rl.hashCode(); }
};
