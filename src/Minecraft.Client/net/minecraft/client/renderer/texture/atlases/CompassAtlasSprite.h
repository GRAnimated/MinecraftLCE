#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"

class CompassAtlasSprite : public TextureAtlasSprite {
public:
    CompassAtlasSprite();
    CompassAtlasSprite(int, CompassAtlasSprite*);

    char filler[0x20];
};
