#pragma once
#include <string>

class TextureAtlasSprite;

class IconRegister {
public:
    virtual ~IconRegister();
    virtual TextureAtlasSprite* registerIcon(std::wstring const&) = 0;
    virtual int getIconType() = 0;
};