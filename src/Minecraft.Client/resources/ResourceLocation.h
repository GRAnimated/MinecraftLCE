#pragma once
#include <string>

class ResourceLocation{
public:
    ResourceLocation(const std::wstring&);
    ~ResourceLocation();

    char size[0x50];
};