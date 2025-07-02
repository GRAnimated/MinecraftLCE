#include "Minecraft.Client/renderer/texture/TextureAtlasSprite.h"
class ClockAtlasSprite : public TextureAtlasSprite {
public:
    ClockAtlasSprite();
    ClockAtlasSprite(int, ClockAtlasSprite*);

    char filler[0x20];
};