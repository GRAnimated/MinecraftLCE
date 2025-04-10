#pragma once
#include "Minecraft.Client/renderer/texture/IconRegister.h"
#include <string>

class TextureAtlas : public IconRegister {
public:
    // it's probably TextureAtlasSprite but unsure
    virtual void* registerIcon(std::wstring const&) override;
    virtual int getIconType() override;

    void addIcon(bool, int, int, const std::wstring&);
    void addIconWithName(bool, int, int, const std::wstring&, const std::wstring&);

    bool isItems;
};
