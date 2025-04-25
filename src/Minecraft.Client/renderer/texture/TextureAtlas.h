#pragma once
#include "Minecraft.Client/renderer/texture/IconRegister.h"
#include <string>

class BufferedImage;

class TextureAtlas : public IconRegister {
public:
    TextureAtlas(int, const std::wstring& path, const std::wstring& filename, BufferedImage* image, bool);

    // it's probably TextureAtlasSprite but unsure
    virtual Texture* registerIcon(std::wstring const&) override;
    virtual int getIconType() override;

    void addIcon(bool, int, int, const std::wstring&);
    void addIconWithName(bool, int, int, const std::wstring&, const std::wstring&);

    void stitch();

    bool isItems;

    unsigned char padding[0xAF];
};
