#pragma once
#include "Minecraft.Client/resources/MappedRegistry.h"
#include "Minecraft.World/entity/Entity.h"
#include <string>

class ResourceLocation {
public:
    static MappedRegistry<ResourceLocation, eINSTANCEOF, std::hash<ResourceLocation>,
                          std::equal_to<ResourceLocation>, std::hash<eINSTANCEOF>, std::equal_to<eINSTANCEOF>>
        Registry;

    ResourceLocation(const std::wstring&);
    ResourceLocation(const ResourceLocation&);
    ~ResourceLocation();

    std::wstring toString() const;

    char size[0x50];
};
