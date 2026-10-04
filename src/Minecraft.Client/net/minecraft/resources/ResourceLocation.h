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
    ~ResourceLocation();

    bool operator==(const ResourceLocation* other) const;

    std::size_t hashCode() const;
    const std::wstring& getNamespace() const;
    const std::wstring& getPath() const;

    virtual std::wstring toString() const;

    char m_gap8[16];
    std::wstring m_path;
    std::wstring m_namespace;
    char m_byte48;
};

template <>
struct std::hash<ResourceLocation> {
    std::size_t operator()(const ResourceLocation& rl) const { return rl.hashCode(); }
};

template <>
struct std::equal_to<ResourceLocation> {
    bool operator()(const ResourceLocation& a, const ResourceLocation& b) const { return a == &b; }
};
