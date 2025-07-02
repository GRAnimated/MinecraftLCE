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
    // idk if this function below is in actual LCE, let's leave it as for now to make ResourceLocation to be
    // able to be in unordered_map
    bool operator==(const ResourceLocation& other) const;

    const std::wstring& getNamespace() const;
    const std::wstring& getPath() const;

    virtual std::wstring toString() const;

    char gap8[16];
    const std::wstring mPath;
    const std::wstring mNamespace;
    char byte48;
};

// this is actually ResourceLocation::hashCode
template <>
struct std::hash<ResourceLocation> {
    std::size_t operator()(const ResourceLocation& rl) const {
        return std::hash<std::wstring>()(rl.getPath()) ^ (std::hash<std::wstring>()(rl.getNamespace()) << 1);
    }
};
