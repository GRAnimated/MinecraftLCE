#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"

class CompassAtlasSprite : public TextureAtlasSprite {
public:
    CompassAtlasSprite();
    CompassAtlasSprite(int, CompassAtlasSprite*);

    char m_filler[0x20];
};
