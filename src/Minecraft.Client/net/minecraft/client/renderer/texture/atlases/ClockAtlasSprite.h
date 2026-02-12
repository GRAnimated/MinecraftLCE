#pragma once

#include "net/minecraft/client/renderer/texture/TextureAtlasSprite.h"

class ClockAtlasSprite : public TextureAtlasSprite {
public:
    ClockAtlasSprite();
    ClockAtlasSprite(int, ClockAtlasSprite*);

    char m_filler[0x20];
};
