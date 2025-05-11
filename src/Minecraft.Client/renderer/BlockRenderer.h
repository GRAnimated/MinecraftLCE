#pragma once

#include "Minecraft.World/level/storage/LevelSource.h"

class TextureAtlasSprite;
class AABB;

class BlockRenderer {
public:
    BlockRenderer(LevelSource*, int, int, int, unsigned char*);
    ~BlockRenderer();

    void setLightOverride(int);
    bool tesselateInWorld(const BlockState*, const BlockPos&, const BlockState*,
                          std::shared_ptr<BlockEntity>);
    void tesselateInWorldFixedTexture(const BlockState*, const BlockPos&, TextureAtlasSprite*);
    void clearLightOverride();
    void setShape(const AABB*);
    void renderFaceUp(BlockState const*, double, double, double, TextureAtlasSprite*, float, float, float,
                      float);
    void renderFaceDown(BlockState const*, double, double, double, TextureAtlasSprite*, float, float, float,
                        float);
    void renderNorth(BlockState const*, double, double, double, TextureAtlasSprite*, float, float, float,
                     float);
    void renderSouth(BlockState const*, double, double, double, TextureAtlasSprite*, float, float, float,
                     float);
    void renderEast(BlockState const*, double, double, double, TextureAtlasSprite*, float, float, float,
                    float);
    void renderWest(BlockState const*, double, double, double, TextureAtlasSprite*, float, float, float,
                    float);

    TextureAtlasSprite* getTexture(const BlockState*, const Direction*);
    bool hasFixedTexture();

    void tesselateEndRodCenter(BlockState const*, float, float, float);
    void tesselateCrossTexture(BlockState const*, float, float, float, float);

    char gap0[8];
    LevelSource* mSource;
    TextureAtlasSprite* mFixedTexture;
    char gap18[4];
    bool mIsFlippedTexture;
    bool mIsCullFaceDown;
    bool mIsFancyLighting;
    bool _1f;
    float _20;
    float _24;
    float _28;
    float _2C;
    float _30;
    float _34;
    char gap38[94];
    int dword98;
    int dword9C;
    int dwordA0;
    int dwordA4;
    int dwordA8;
    int dwordAC;
    int dwordB0;
    int dwordB4;
    int dwordB8;
    int dwordBC;
    int dwordC0;
    int dwordC4;
    int dwordC8;
    bool _CC;
    void* qwordD0;
    char gapD8[216];
};
