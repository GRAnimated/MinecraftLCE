#pragma once

#include "Minecraft.World/level/storage/LevelSource.h"

class TextureAtlasSprite;

class BlockRenderer {
public:
    BlockRenderer(LevelSource*, int, int, int, unsigned char*);
    ~BlockRenderer();

    void setLightOverride(int);
    bool tesselateInWorld(const BlockState*, const BlockPos&, const BlockState*,
                          std::shared_ptr<BlockEntity>);
    void tesselateInWorldFixedTexture(const BlockState*, const BlockPos&, TextureAtlasSprite*);
    void clearLightOverride();

    void* filler[0x1B0 / 8];
};
