#pragma once
#include <string>

class TextureAtlasSprite;

class IconRegister {
public:
    virtual ~IconRegister();
    virtual TextureAtlasSprite* registerIcon(const std::wstring&) = 0;
    virtual int getIconType() = 0;
};