#pragma once
#include <string>
#include "Minecraft.Client/renderer/texture/IconRegister.h"

class TextureAtlas : public IconRegister{
public:
    // it's probably TextureAtlasSprite but unsure
    virtual void* registerIcon(std::wstring const&) override;
    virtual int getIconType() override;

    void addIcon(bool, int, int, const std::wstring&);
    void addIconWithName(bool, int, int, const std::wstring&, const std::wstring&);
};
